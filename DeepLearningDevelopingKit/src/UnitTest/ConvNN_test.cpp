/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           CNN Test   															      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define CNNDebug

#ifdef CNNDebug

#include <fstream>

#include "..\Algorithm\NeuralNetwork\NeuralLib.h"

int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	std::string temp;
	temp += "Project : Deep Learning Developing Kit\n";
	temp += "Branch  : Master\n";
	temp += "Version : Windows-x64-0.2.1-CPU\n";
	temp += "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";
	std::cout << temp.c_str() << std::endl;

	/***************************************************************************************************/
	// Input
	MathLib::Matrix<double> input1(16, 16, MathLib::MatrixType::Random);
	std::vector<MathLib::Matrix<double>> input;
	input.push_back(input1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer 1
	Neural::ConvLayerInitor convInitor1;
	convInitor1.InputSize = MathLib::Size(16, 16);
	convInitor1.KernelSize = MathLib::Size(3, 3);
	convInitor1.Stride = 1;
	convInitor1.KernelNum = 5;
	convInitor1.ActivationFunction = ActivationFunction::Sigmoid;
	convInitor1.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer conv1(convInitor1);

	/***************************************************************************************************/
	// Initializing Pooling Layer 1
	Neural::PoolLayerInitor poolInitor1;
	poolInitor1.InputSize = MathLib::Size(16, 16);
	poolInitor1.Stride = 4;
	poolInitor1.PoolSize = MathLib::Size(4, 4);
	poolInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor1.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor1.PaddingMethod = Neural::PaddingMethod::RightDown;
	Neural::PoolingLayer pool1(poolInitor1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer 2
	Neural::ConvLayerInitor convInitor2;
	convInitor2.InputSize = MathLib::Size(4, 4);
	convInitor2.KernelSize = MathLib::Size(2, 2);
	convInitor2.Stride = 1;
	convInitor2.KernelNum = 10;
	convInitor2.ActivationFunction = ActivationFunction::Sigmoid;
	convInitor2.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer conv2(convInitor2);

	/***************************************************************************************************/
	// Initializing Pooling Layer 2
	Neural::PoolLayerInitor poolInitor2;
	poolInitor2.InputSize = MathLib::Size(4, 4);
	poolInitor2.Stride = 2;
	poolInitor2.PoolSize = MathLib::Size(2, 2);
	poolInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor2.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor2.PaddingMethod = Neural::PaddingMethod::RightDown;
	Neural::PoolingLayer pool2(poolInitor2);

	/***************************************************************************************************/
	// Initializing Process Layer
	Neural::ProcessLayerInitor processInitor;
	processInitor.InputSize = MathLib::Size(2, 2);
	processInitor.ProcessFunction = ReLU;
	processInitor.ProcessFunctionDerivative = ReLUDerivative;
	Neural::ProcessLayer process(processInitor);

	/***************************************************************************************************/
	// Initializing Serialize Layer
	Neural::SerializeLayerInitor serialInitor;
	serialInitor.SerializeSize = MathLib::Size(2 * 2 * 10, 1);
	serialInitor.DeserializeSize = MathLib::Size(2, 2);
	Neural::SerializeLayer serial(serialInitor);

	/***************************************************************************************************/
	// Initializing FullConnect Layer
	Neural::InputLayer inputLayer(2 * 2 * 10, 2 * 2 * 10);
	inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	inputLayer.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer(2 * 2 * 10, 20);
	hiddenLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	hiddenLayer.SetLossFunction(LossFunction::MES);

	Neural::OutputLayer outputLayer(20, 1);
	outputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	outputLayer.SetLossFunction(LossFunction::MES);

	for (size_t iteration = 0; iteration < 10; iteration++)
	{
		/***************************************************************************************************/
		// Forward Propagation
		conv1.SetInput(input);
		conv1.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv1kernals = conv1.GetKernelAll();
		std::vector<Neural::ConvFeature> conv1features = conv1.GetFeatureAll();

		pool1.SetInput(conv1features);
		pool1.ForwardPropagation();
		std::vector<Neural::Feature> pool1features = pool1.GetFeatureAll();

		conv2.SetInput(pool1features);
		conv2.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv2kernals = conv2.GetKernelAll();
		std::vector<Neural::ConvFeature> conv2features = conv2.GetFeatureAll();

		pool2.SetInput(conv2features);
		pool2.ForwardPropagation();
		std::vector<Neural::Feature> pool2features = pool2.GetFeatureAll();

		process.SetInput(pool2features);
		process.Process();
		std::vector<Neural::Feature> processOutput = process.GetOutputAll();

		serial.SetDeserializedMat(processOutput);

		MathLib::Matrix<double> serializedMat = serial.Serialize();

		MathLib::Vector<double> serializedVec(serializedMat.ColumeSize());
		for (size_t i = 0; i < serializedMat.ColumeSize(); i++)
		{
			serializedVec(i) = serializedMat(i, 0);
		}

		inputLayer.SetInput(serializedVec);
		inputLayer.ForwardPropagation();

		hiddenLayer.SetInput(inputLayer.GetOutput());
		hiddenLayer.ForwardPropagation();

		outputLayer.SetInput(hiddenLayer.GetOutput());
		outputLayer.ForwardPropagation();

		/***************************************************************************************************/
		// Lable
		MathLib::Vector<double> lable(2);

		// \(ΘwΘ)/  \(ΘwΘ)/  \(ΘwΘ)/  \(ΘwΘ)/
		/*
		*					Classifier Thingy
		*			Linear Regression			(MLR).
		*			Logistic Regression			(LR)
		*			Supported Vector Machine		(SVM)
		*			K Nearest Neighbors			(KNN)
		*			Decision Tree		 (DT)
		*			Naive Bayes		 (NB)
		*			Random Trees		(RT)
		*			Neural Network		 (NN)
		\	*    /
		\	*  /
		\*/

		/***************************************************************************************************/
		// Backward Propagation

		MathLib::Vector<double> outputLayerDelta = outputLayer.BackwardPropagation(lable);

		MathLib::Vector<double> hiddenLayerDelta = hiddenLayer.BackwardPropagation(outputLayerDelta);

		MathLib::Vector<double> inputLayerDelta = inputLayer.BackwardPropagation(hiddenLayerDelta);

		MathLib::Matrix<double> inputLayerDeltaMat(inputLayerDelta.Size(), 1);
		for (size_t i = 0; i < serializedMat.ColumeSize(); i++)
		{
			inputLayerDeltaMat(i, 0) = inputLayerDelta(i);
		}

		serial.SetSerializedMat(inputLayerDeltaMat);
		serial.Deserialize();
		std::vector<MathLib::Matrix<double>> deserialized = serial.Deserialize();

		process.SetInput(deserialized);
		process.Deprocess();
		std::vector<MathLib::Matrix<double>> deprocessOutput = process.GetOutputAll();

		pool2.SetDelta(deprocessOutput);
		pool2.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> pool2Delta = pool2.GetDelta();

		conv2.SetDelta(pool2Delta);
		conv2.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> conv2Delta = conv2._deltaDeconved;

		pool1.SetDelta(conv2Delta);
		pool1.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> pool1Delta = pool1.GetDelta();

		conv1.SetDelta(pool1Delta);
		conv1.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> conv1Delta = conv1._deltaDeconved;

		MathLib::Matrix<double> result(16, 16);
		for (auto mat : conv1Delta) result += mat;

		/***************************************************************************************************/
		// Updating weight
		conv1.Update();
		pool1.Update();
		conv2.Update();
		pool2.Update();
		inputLayer.Update();
		hiddenLayer.Update();
		outputLayer.Update();

		std::cout << "Iteration : " << iteration << std::endl;
	}

	///*{
	//	std::ofstream log;
	//	std::string path = "log\\CNN_debug_output.txt";
	//	log.open(path);
	//	if (!log.is_open()) 
	//		exit(0);
	//	std::string temp;
	//	temp += "Project : Deep Learning Developing Kit\n";
	//	temp += "Branch  : Master\n";
	//	temp += "Version : Windows-x64-0.2.1-CPU\n";
	//	temp += "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";
	//	log << temp.c_str() << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Input Data" << std::endl;
	//	for (auto mat : input)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Convolutional Layer 1" << std::endl;
	//	for (auto mat : conv1kernals)
	//		log << mat << std::endl;
	//	for (auto mat : conv1features)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Pooling Layer 1" << std::endl;
	//	for (auto mat : pool1features)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Convolutional Layer 2" << std::endl;
	//	for (auto mat : conv2kernals)
	//		log << mat << std::endl;
	//	for (auto mat : conv2features)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Pooling Layer 2" << std::endl;
	//	for (auto mat : pool2features)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Process Layer" << std::endl;
	//	for (auto mat : processOutput)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Serialize Layer" << std::endl;
	//	log << serializedMat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Start Backpropagation" << std::endl << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Serialize Layer" << std::endl;
	//	for (auto mat : deserialized)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Process Layer" << std::endl;
	//	for (auto mat : deprocessOutput)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Pooling Layer 2" << std::endl;
	//	for (auto mat : pool2Delta)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Convolutional Layer 2" << std::endl;
	//	for (auto mat : conv2Delta)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Pooling Layer 1" << std::endl;
	//	for (auto mat : pool1Delta)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Convolutional Layer 1" << std::endl;
	//	for (auto mat : conv1Delta)
	//		log << mat << std::endl;

	//	log << "/***************************************************************************************************/"
	//		<< std::endl << "Out from CNN-FNN" << std::endl;
	//	log << result << std::endl;

	//	log.close();
	//}*/
	return 0;
}


#endif // CNNDebug
