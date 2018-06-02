/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	CNN Image Recognization   													   */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define CNNImageRecognization

#ifdef CNNImageRecognization
#include "..\NeuralLib.h"

int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	Data::ImageSet XOImageTrainSet;
	XOImageTrainSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\TrainSet");

	Data::ImageSet XOImageTestSet;
	XOImageTestSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\TestSet");

	/***************************************************************************************************/
	// Initializing Convolutional Layer 1
	Neural::ConvLayerInitor convInitor1;
	convInitor1.InputSize = MathLib::Size(16, 16);
	convInitor1.KernelSize = MathLib::Size(3, 3);
	convInitor1.Stride = 1;
	convInitor1.KernelNum = 5;
	convInitor1.ActivationFunction = ActivationFunction::ReLU;
	convInitor1.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer1(convInitor1);

	/***************************************************************************************************/
	// Initializing Pooling Layer 1
	Neural::PoolLayerInitor poolInitor1;
	poolInitor1.InputSize = MathLib::Size(16, 16);
	poolInitor1.Stride = 4;
	poolInitor1.PoolSize = MathLib::Size(4, 4);
	poolInitor1.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor1.PaddingMethod = Neural::PaddingMethod::Surround;
	poolInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::PoolingLayer poolLayer1(poolInitor1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer 2
	Neural::ConvLayerInitor convInitor2;
	convInitor2.InputSize = MathLib::Size(4, 4);
	convInitor2.KernelSize = MathLib::Size(3, 3);
	convInitor2.Stride = 1;
	convInitor2.KernelNum = 5;
	convInitor2.ActivationFunction = ActivationFunction::ReLU;
	convInitor2.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer2(convInitor2);

	/***************************************************************************************************/
	// Initializing Pooling Layer 2
	Neural::PoolLayerInitor poolInitor2;
	poolInitor2.InputSize = MathLib::Size(4, 4);
	poolInitor2.Stride = 2;
	poolInitor2.PoolSize = MathLib::Size(2, 2);
	poolInitor2.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor2.PaddingMethod = Neural::PaddingMethod::Surround;
	poolInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::PoolingLayer poolLayer2(poolInitor2);

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

	Neural::HiddenLayer hiddenLayer(2 * 2 * 10, 2 * 2 * 10);
	hiddenLayer.SetActivationFunction(ActivationFunction::ReLU);
	hiddenLayer.SetLossFunction(LossFunction::MES);

	Neural::OutputLayer outputLayer(2 * 2 * 10, 2);
	outputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	outputLayer.SetLossFunction(LossFunction::MES);

	int totalIteration = 100;

	for (size_t iteration = 0; iteration < totalIteration; iteration++)
	{
		for (size_t ID = 0; ID < XOImageTrainSet.GetSampleSize(); ID++)
		{
			auto sample = XOImageTrainSet.GetRandomSample();

			std::vector<MathLib::Matrix<double>> input;
			input.clear();
			input.push_back(sample.first + Random());

			/***************************************************************************************************/
			// Forward Propagation
			convLayer1.SetInput(input);
			convLayer1.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv1kernals = convLayer1.GetKernelAll();
			std::vector<Neural::ConvFeature> conv1features = convLayer1.GetFeatureAll();

			poolLayer1.SetInput(conv1features);
			poolLayer1.ForwardPropagation();
			std::vector<Neural::Feature> pool1features = poolLayer1.GetFeatureAll();

			convLayer2.SetInput(pool1features);
			convLayer2.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv2kernals = convLayer2.GetKernelAll();
			std::vector<Neural::ConvFeature> conv2features = convLayer2.GetFeatureAll();

			poolLayer2.SetInput(conv2features);
			poolLayer2.ForwardPropagation();
			std::vector<Neural::Feature> pool2features = poolLayer2.GetFeatureAll();

			process.SetInput(pool2features);
			process.Process();
			std::vector<Neural::Feature> processOutput = process.GetOutputAll();

			serial.SetDeserializedMat(processOutput);
			MathLib::Matrix<double> serializedMat = serial.Serialize();

			MathLib::Vector<double> serializedVec(serializedMat.ColumeSize());
			MathLib::Matrix<float> CNNout(serializedMat.ColumeSize(), 1);
			for (size_t i = 0; i < serializedMat.ColumeSize(); i++)
			{
				serializedVec(i) = serializedMat(i, 0);
				CNNout(i, 0) = serializedMat(i, 0);
			}

			inputLayer.SetInput(serializedVec);
			inputLayer.ForwardPropagation();

			hiddenLayer.SetInput(inputLayer.GetOutput());
			hiddenLayer.ForwardPropagation();

			outputLayer.SetInput(hiddenLayer.GetOutput());
			outputLayer.ForwardPropagation();

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

			/***************************************************************************************************/
			// Updating
			int batchsize = 1;
			inputLayer.BatchDeltaSumUpdate(batchsize);
			outputLayer.BatchDeltaSumUpdate(batchsize);
			hiddenLayer.BatchDeltaSumUpdate(batchsize);

			outputLayer.LossSumUpdate();

			convLayer1.Update();
			poolLayer1.Update();
			convLayer2.Update();
			poolLayer2.Update();
			inputLayer.Update();
			hiddenLayer.Update();
			outputLayer.Update();

			inputLayer.BatchDeltaSumClear();
			outputLayer.BatchDeltaSumClear();
			hiddenLayer.BatchDeltaSumClear();

			auto loss = outputLayer.GetLoss();
			outputLayer.LossSumClear();
			std::cout << "Iteration : " << std::setw(3) << std::setfill('0') << iteration << " | "
				<< "ID : " << std::setw(3) << std::setfill('0') << ID << " | "
				<< "Predict : " << std::fixed << std::setprecision(3) << outputLayer.GetOutput()(0) << " , " << outputLayer.GetOutput()(1) << " | "
				<< "Lable : " << lable(0) << " , " << lable(1) << " | "
				<< "Error : " << error(0) << " , " << error(1)
				<< std::endl;

			Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 100, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 300, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 500, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 700, 200, true);
			Visual::Plot2D::Plot2DMatrixVec(conv2kernals, "conv2kernals", Visual::Plot2DMode::RB, 900, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(conv2features, "conv2features", Visual::Plot2DMode::RB, 1100, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(pool2features, "pool2features", Visual::Plot2DMode::RB, 1300, 200, true);
		}
	}

	std::cout << "Testing : " << std::endl;
	std::cout << "Total Iteration : " << totalIteration << std::endl;
	for (size_t ID = 0; ID < XOImageTestSet.GetSampleSize(); ID++)
	{
		auto sample = XOImageTestSet.GetBatch();

		std::vector<MathLib::Matrix<double>> input;
		input.clear();
		input.push_back(sample.first);

		/***************************************************************************************************/
		// Forward Propagation
		convLayer1.SetInput(input);
		convLayer1.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv1kernals = convLayer1.GetKernelAll();
		std::vector<Neural::ConvFeature> conv1features = convLayer1.GetFeatureAll();

		poolLayer1.SetInput(conv1features);
		poolLayer1.ForwardPropagation();
		std::vector<Neural::Feature> pool1features = poolLayer1.GetFeatureAll();

		convLayer2.SetInput(pool1features);
		convLayer2.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv2kernals = convLayer2.GetKernelAll();
		std::vector<Neural::ConvFeature> conv2features = convLayer2.GetFeatureAll();

		poolLayer2.SetInput(conv2features);
		poolLayer2.ForwardPropagation();
		std::vector<Neural::Feature> pool2features = poolLayer2.GetFeatureAll();

		process.SetInput(pool2features);
		process.Process();
		std::vector<Neural::Feature> processOutput = process.GetOutputAll();

		serial.SetDeserializedMat(processOutput);
		MathLib::Matrix<double> serializedMat = serial.Serialize();

		MathLib::Vector<double> serializedVec(serializedMat.ColumeSize());
		MathLib::Matrix<float> CNNout(serializedMat.ColumeSize(), 1);
		for (size_t i = 0; i < serializedMat.ColumeSize(); i++)
		{
			serializedVec(i) = serializedMat(i, 0);
			CNNout(i, 0) = serializedMat(i, 0);
		}

		inputLayer.SetInput(serializedVec);
		inputLayer.ForwardPropagation();

		hiddenLayer.SetInput(inputLayer.GetOutput());
		hiddenLayer.ForwardPropagation();

		outputLayer.SetInput(hiddenLayer.GetOutput());
		outputLayer.ForwardPropagation();

		std::cout << "ID : " << std::setw(3) << std::setfill('0') << ID << " | "
			<< "Predict : " << std::fixed << std::setprecision(3) << outputLayer.GetOutput()(0) << " , " << outputLayer.GetOutput()(1) << " | "
			<< "Lable : " << sample.second.at(0) << " , " << sample.second.at(1) << " | "
			<< std::endl;
	}

	system("pause");
	return 0;
}
#endif // CNNImageRecognization

