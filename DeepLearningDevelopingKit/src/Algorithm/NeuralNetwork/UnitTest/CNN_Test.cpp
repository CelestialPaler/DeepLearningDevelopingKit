/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             CNN Test   													              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define CNNDebug

#ifdef CNNDebug
#include "..\NeuralLib.h"
#include "..\..\..\MathLib\MathLib.h"

int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));

	MathLib::Matrix<double> input1(8, 8, MathLib::MatrixType::Zero);
	std::vector<MathLib::Matrix<double>> input;
	for (size_t i = 0; i < input1.ColumeSize(); i++)
		for (size_t j = 0; j < input1.RowSize(); j++)
			if (i == j)
				input1(i, j) = 1.f;
			else
				input1(i, j) = 0.f;
	input.push_back(input1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(8, 8);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 1;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	/***************************************************************************************************/
	// Initializing Pooling Layer
	Neural::PoolLayerInitor poolInitor;
	poolInitor.InputSize = MathLib::Size(8, 8);
	poolInitor.Stride = 2;
	poolInitor.PoolSize = MathLib::Size(2, 2);
	poolInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	Neural::PoolingLayer poolLayer(poolInitor);

	/***************************************************************************************************/
	// Initializing Process Layer
	Neural::ProcessLayerInitor processInitor;
	processInitor.InputSize = MathLib::Size(4, 4);
	processInitor.ProcessFunction = ReLU;
	processInitor.ProcessFunctionDerivative = ReLUDerivative;
	Neural::ProcessLayer process(processInitor);

	/***************************************************************************************************/
	// Initializing Serialize Layer
	Neural::SerializeLayerInitor serialInitor;
	serialInitor.SerializeSize = MathLib::Size(4 * 4 * 1, 1);
	serialInitor.DeserializeSize = MathLib::Size(4, 4);
	Neural::SerializeLayer serial(serialInitor);

	/***************************************************************************************************/
	// Initializing FullConnect Layer
	Neural::InputLayer inputLayer(4 * 4 * 1, 4 * 4 * 1);
	inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	inputLayer.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer(4 * 4 * 1, 10);
	hiddenLayer.SetActivationFunction(ActivationFunction::ReLU);
	hiddenLayer.SetLossFunction(LossFunction::MES);

	Neural::OutputLayer outputLayer(10, 1);
	outputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	outputLayer.SetLossFunction(LossFunction::MES);

	for (size_t iteration = 0; iteration < 100; iteration++)
	{
		/***************************************************************************************************/
		// Forward Propagation
		convLayer.SetInput(input);
		convLayer.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
		std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();
		//std::cout << "ConvWeight : " << conv1kernals.at(0) << std::endl;
		//std::cout << "ConvFeature : " << conv1features.at(0) << std::endl;

		poolLayer.SetInput(conv1features);
		poolLayer.ForwardPropagation();
		std::vector<Neural::Feature> pool1features = poolLayer.GetFeatureAll();
		//std::cout << "PoolFeature : " << pool1features.at(0) << std::endl;

		process.SetInput(pool1features);
		process.Process();
		std::vector<Neural::Feature> processOutput = process.GetOutputAll();
		//std::cout << "ReLU : " << processOutput.at(0) << std::endl;

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
		// Backward Propagation
		MathLib::Vector<double> lable(1);
		lable(0) = 1;

		MathLib::Vector<double> outputLayerDelta = outputLayer.BackwardPropagation(lable);

		MathLib::Vector<double> hiddenLayerDelta = hiddenLayer.BackwardPropagation(outputLayerDelta);

		MathLib::Vector<double> inputLayerDelta = inputLayer.BackwardPropagation(hiddenLayerDelta);

		MathLib::Matrix<double> inputLayerDeltaMat(inputLayerDelta.Size(), 1);
		for (size_t i = 0; i < serializedMat.ColumeSize(); i++)
		{
			inputLayerDeltaMat(i, 0) = inputLayerDelta(i);
		}

		serial.SetSerializedMat(inputLayerDeltaMat);
		std::vector<MathLib::Matrix<double>> deserialized = serial.Deserialize();

		process.SetInput(deserialized);
		process.Deprocess();
		std::vector<MathLib::Matrix<double>> deprocessOutput = process.GetOutputAll();

		poolLayer.SetDelta(deprocessOutput);
		poolLayer.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> pool1Delta = poolLayer.GetDelta();

		convLayer.SetDelta(pool1Delta);
		convLayer.BackwardPropagation();
		std::vector<MathLib::Matrix<double>> conv1Delta = convLayer._deltaDeconved;

		/***************************************************************************************************/
		// Updating
		convLayer.Update();
		poolLayer.Update();
		inputLayer.Update();
		hiddenLayer.Update();
		outputLayer.Update();

		MathLib::Vector<double> result = outputLayer.GetOutput();
		std::cout << result << std::endl;

	}

	std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
	std::cout << "Kernels : " << std::endl << std::endl;
	for (auto mat : conv1kernalsUpdated)
		std::cout << mat << std::endl;

	system("pause");
	return 0;
}
#endif // CNNDebug

