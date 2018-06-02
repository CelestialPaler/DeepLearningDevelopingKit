/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	CNN Image Recognization   													   */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNImageRecognization

#ifdef CNNImageRecognization
#include "..\\Algorithm\NeuralNetwork\NeuralLib.h"

Vector<double> Matrix2Vector(const Matrix<double> & _mat);

int main(int argc, char ** argv)
{
	// Visualization
	const visualWhileTraining = false;

	// Randomize the seed
	srand((unsigned)time(NULL));

	/***************************************************************************************************/
	// Initializing Train Set
	Data::ImageSet TrainSet;
	TrainSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\Example\\ImageRecognization\\TrainSet");

	/***************************************************************************************************/
	// Initializing Test Set
	Data::ImageSet TestSet;
	TestSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\Example\\ImageRecognization\\TestSet");

	/***************************************************************************************************/
	// Initializing Convolutional Layer 1
	Neural::ConvLayerInitor convInitor1;
	convInitor1.InputSize = MathLib::Size(32, 32);
	convInitor1.KernelSize = MathLib::Size(5, 5);
	convInitor1.Stride = 1;
	convInitor1.KernelNum = 10;
	convInitor1.ActivationFunction = ActivationFunction::Linear;
	convInitor1.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer1(convInitor1);

	/***************************************************************************************************/
	// Initializing Pooling Layer 1
	Neural::PoolLayerInitor poolInitor1;
	poolInitor1.InputSize = MathLib::Size(32, 32);
	poolInitor1.Stride = 4;
	poolInitor1.PoolSize = MathLib::Size(4, 4);
	poolInitor1.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor1.PaddingMethod = Neural::PaddingMethod::Surround;
	poolInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::PoolingLayer poolLayer1(poolInitor1);

	/***************************************************************************************************/
	// Initializing Process Layer 1
	Neural::ProcessLayerInitor processInitor1;
	processInitor1.InputSize = MathLib::Size(8, 8);
	processInitor1.ProcessFunction = ReLU;
	processInitor1.ProcessFunctionDerivative = ReLUDerivative;
	Neural::ProcessLayer process1(processInitor1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer 2
	Neural::ConvLayerInitor convInitor2;
	convInitor2.InputSize = MathLib::Size(8, 8);
	convInitor2.KernelSize = MathLib::Size(3, 3);
	convInitor2.Stride = 1;
	convInitor2.KernelNum = 20;
	convInitor2.ActivationFunction = ActivationFunction::Linear;
	convInitor2.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer2(convInitor2);

	/***************************************************************************************************/
	// Initializing Pooling Layer 2
	Neural::PoolLayerInitor poolInitor2;
	poolInitor2.InputSize = MathLib::Size(8, 8);
	poolInitor2.Stride = 4;
	poolInitor2.PoolSize = MathLib::Size(4, 4);
	poolInitor2.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor2.PaddingMethod = Neural::PaddingMethod::Surround;
	poolInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::PoolingLayer poolLayer2(poolInitor2);

	/***************************************************************************************************/
	// Initializing Process Layer 2
	Neural::ProcessLayerInitor processInitor2;
	processInitor2.InputSize = MathLib::Size(2, 2);
	processInitor2.ProcessFunction = ReLU;
	processInitor2.ProcessFunctionDerivative = ReLUDerivative;
	Neural::ProcessLayer process2(processInitor2);

	/***************************************************************************************************/
	// Initializing Serialize Layer
	Neural::SerializeLayerInitor serialInitor;
	serialInitor.SerializeSize = MathLib::Size(2 * 2 * 20, 1);
	serialInitor.DeserializeSize = MathLib::Size(2, 2);
	Neural::SerializeLayer serial(serialInitor);

	/***************************************************************************************************/
	// Initializing FullConnect Layer
	Neural::InputLayer inputLayer(2 * 2 * 20, 2 * 2 * 20);
	inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	inputLayer.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer1(2 * 2 * 20, 2 * 2 * 20);
	hiddenLayer1.SetActivationFunction(ActivationFunction::ReLU);
	hiddenLayer1.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer2(2 * 2 * 20, 2 * 2 * 5);
	hiddenLayer2.SetActivationFunction(ActivationFunction::ReLU);
	hiddenLayer2.SetLossFunction(LossFunction::MES);

	Neural::OutputLayer outputLayer(2 * 2 * 5, 4);
	outputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	outputLayer.SetLossFunction(LossFunction::MES);

	/***************************************************************************************************/
	// Setting Learning Rate
	const double globalRate = 0.001 * 0.001;
	convLayer1.SetLearnRate(globalRate);
	convLayer2.SetLearnRate(globalRate);
	hiddenLayer1.SetLearnRate(globalRate);
	hiddenLayer2.SetLearnRate(globalRate);

	/***************************************************************************************************/
	// Start Training
	int totalTrainIteration = 100;

	for (size_t iteration = 0; iteration < totalTrainIteration; iteration++)
	{
		for (size_t ID = 0; ID < TrainSet.GetSampleSize(); ID++)
		{
			// Initialzing input
			auto sample = TrainSet.GetSample(ID);
			std::vector<MathLib::Matrix<double>> input{ sample.first + Random() };

			/***************************************************************************************************/
			// Forward Propagation

			// convLayer 1
			convLayer1.SetInput(input);
			convLayer1.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv1kernals = convLayer1.GetKernelAll();
			std::vector<Neural::ConvFeature> conv1features = convLayer1.GetFeatureAll();
			//		  |
			//      \|/
			// poolLayer 1
			poolLayer1.SetInput(conv1features);
			poolLayer1.ForwardPropagation();
			std::vector<Neural::Feature> pool1features = poolLayer1.GetFeatureAll();
			//		  |
			//      \|/
			// processLayer 1
			process1.SetInput(pool1features);
			process1.Process();
			std::vector<Neural::Feature> process1output = process1.GetOutputAll();
			//		  |
			//      \|/
			// convLayer 2
			convLayer2.SetInput(process1output);
			convLayer2.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv2kernals = convLayer2.GetKernelAll();
			std::vector<Neural::ConvFeature> conv2features = convLayer2.GetFeatureAll();
			//		  |
			//      \|/
			// poolLayer 2
			poolLayer2.SetInput(conv2features);
			poolLayer2.ForwardPropagation();
			std::vector<Neural::Feature> pool2features = poolLayer2.GetFeatureAll();
			//		  |
			//      \|/
			// processLayer 2
			process2.SetInput(pool2features);
			process2.Process();
			std::vector<Neural::Feature> process2output = process2.GetOutputAll();
			//		  |
			//      \|/
			// serialLayer
			serial.SetDeserializedMat(process2output);
			MathLib::Vector<double> serializedVec = Matrix2Vector(serial.Serialize());
			//		  |
			//      \|/
			// inputLayer
			inputLayer.SetInput(serializedVec);
			inputLayer.ForwardPropagation();
			MathLib::Vector<double> inputout = inputLayer.GetOutput();
			//		  |
			//      \|/
			// hiddenLayer 1
			hiddenLayer1.SetInput(inputout);
			hiddenLayer1.ForwardPropagation();
			MathLib::Vector<double> hidden1output = hiddenLayer1.GetOutput();
			//		  |
			//      \|/
			// hiddenLayer 2
			hiddenLayer2.SetInput(hidden1output);
			hiddenLayer2.ForwardPropagation();
			MathLib::Vector<double> hidden2output = hiddenLayer2.GetOutput();
			//		  |
			//      \|/
			// outputLayer
			outputLayer.SetInput(hidden2output);
			outputLayer.ForwardPropagation();
			MathLib::Vector<double> output = outputLayer.GetOutput();

			/***************************************************************************************************/
			// Backward Propagation
			MathLib::Vector<double> lable(2);
			for (size_t i = 0; i < 2; i++)
				lable(i) = sample.second.at(i);
			MathLib::Vector<double> error(2);
			error = outputLayer.GetOutput() - lable;
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

			poolLayer2.SetDelta(deprocessOutput);
			poolLayer2.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> pool2Delta = poolLayer2.GetDelta();

			convLayer2.SetDelta(pool2Delta);
			convLayer2.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> conv2Delta = convLayer2._derivative;

			poolLayer1.SetDelta(conv2Delta);
			poolLayer1.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> pool1Delta = poolLayer1.GetDelta();

			convLayer1.SetDelta(pool1Delta);
			convLayer1.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> conv1Delta = convLayer1._derivative;

			if (visualWhileTraining)
			{
				Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 100, 200, false);
				Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 300, 200, false);
				Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 500, 200, false);
				Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 700, 200, true);
				Visual::Plot2D::Plot2DMatrixVec(conv2kernals, "conv2kernals", Visual::Plot2DMode::RB, 900, 200, false);
				Visual::Plot2D::Plot2DMatrixVec(conv2features, "conv2features", Visual::Plot2DMode::RB, 1100, 200, false);
				Visual::Plot2D::Plot2DMatrixVec(pool2features, "pool2features", Visual::Plot2DMode::RB, 1300, 200, true);
			}
		}
	}



	system("pause");
	return 0;
}





Vector<double> Matrix2Vector(const Matrix<double> & _mat) {
	Vector<double> vec(_mat.ColumeSize(), VectorType::Zero);
	for (size_t i = 0; i < _mat.ColumeSize(); i++)
		vec(i) = _mat(i, 0);
	return vec;
}

#endif // CNNImageRecognization

