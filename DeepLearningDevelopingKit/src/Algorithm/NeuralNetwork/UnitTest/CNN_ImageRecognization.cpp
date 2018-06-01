/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	CNN Image Recognization   													   */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNImageRecognization

#ifdef CNNImageRecognization
#include "..\NeuralLib.h"

int main(int argc, char ** argv)
{
	Data::ImageSet XOImageTrainSet;
	XOImageTrainSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\TrainSet");

	Data::ImageSet XOImageTestSet;
	XOImageTestSet.LoadFromJson("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\TestSet");

	unsigned kernalNum = 5;

	/***************************************************************************************************/
	// Initializing Convolutional Layer
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(16, 16);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = kernalNum;
	convInitor.ActivationFunction = ActivationFunction::ReLU;
	convInitor.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	/***************************************************************************************************/
	// Initializing Pooling Layer
	Neural::PoolLayerInitor poolInitor;
	poolInitor.InputSize = MathLib::Size(16, 16);
	poolInitor.Stride = 4;
	poolInitor.PoolSize = MathLib::Size(4, 4);
	poolInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor.PaddingMethod = Neural::PaddingMethod::Surround;
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
	serialInitor.SerializeSize = MathLib::Size(4 * 4 * kernalNum, 1);
	serialInitor.DeserializeSize = MathLib::Size(4, 4);
	Neural::SerializeLayer serial(serialInitor);

	/***************************************************************************************************/
	// Initializing FullConnect Layer
	Neural::InputLayer inputLayer(4 * 4 * kernalNum, 4 * 4 * kernalNum);
	inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	inputLayer.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer(4 * 4 * kernalNum, 4 * 4 * kernalNum);
	hiddenLayer.SetActivationFunction(ActivationFunction::ReLU);
	hiddenLayer.SetLossFunction(LossFunction::MES);

	Neural::OutputLayer outputLayer(4 * 4 * kernalNum, 1);
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
			convLayer.SetInput(input);
			convLayer.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
			std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();

			poolLayer.SetInput(conv1features);
			poolLayer.ForwardPropagation();
			std::vector<Neural::Feature> pool1features = poolLayer.GetFeatureAll();

			process.SetInput(pool1features);
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
			MathLib::Vector<double> lable(1);
			lable(0) = sample.second.at(0);
			MathLib::Vector<double> error(1);
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

			poolLayer.SetDelta(deprocessOutput);
			poolLayer.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> pool1Delta = poolLayer.GetDelta();

			convLayer.SetDelta(pool1Delta);
			convLayer.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> conv1Delta = convLayer._derivative;

			/***************************************************************************************************/
			// Updating
			int batchsize = 1;
			inputLayer.BatchDeltaSumUpdate(batchsize);
			outputLayer.BatchDeltaSumUpdate(batchsize);
			hiddenLayer.BatchDeltaSumUpdate(batchsize);

			outputLayer.LossSumUpdate();

			convLayer.Update();
			poolLayer.Update();
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
				<< "Predict : " << std::fixed << std::setprecision(3) << outputLayer.GetOutput()(0) << " | "
				<< "Lable : " << lable(0) << " | "
				<< "Error : " << error(0)
				<< std::endl;

			Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 200, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 400, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 600, 200, false);
			Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 800, 200, true);
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
		convLayer.SetInput(input);
		convLayer.ForwardPropagation();
		std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
		std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();

		poolLayer.SetInput(conv1features);
		poolLayer.ForwardPropagation();
		std::vector<Neural::Feature> pool1features = poolLayer.GetFeatureAll();

		process.SetInput(pool1features);
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
			<< "Predict : " << std::fixed << std::setprecision(3) << outputLayer.GetOutput()(0) << " | "
			<< "Lable : " << sample.second.at(0)
			<< std::endl;
	}

	system("pause");
	return 0;
}
#endif // CNNImageRecognization

