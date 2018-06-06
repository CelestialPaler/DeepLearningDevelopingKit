/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	CNN Image Recognization   													   */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define CNNImageRecognization

#ifdef CNNImageRecognization
#include "..\\Algorithm\NeuralNetwork\NeuralLib.h"

Vector<double> Matrix2Vector(const Matrix<double> & _mat);
Matrix<double> Vector2Matrix(const Vector<double> & _vec);

#include <thread>
#include <vector>
#include <mutex>

std::mutex workQueueMutex;
std::mutex plotMutex;
bool threadLifeFlag;

static void trainThreadFunc(
	Neural::ConvolutionalLayer convLayer1,
	Neural::PoolingLayer poolLayer1,
	Neural::ProcessLayer process1,
	Neural::ConvolutionalLayer convLayer2,
	Neural::PoolingLayer poolLayer2,
	Neural::ProcessLayer process2,
	Neural::SerializeLayer serial,
	Neural::InputLayer inputLayer,
	Neural::HiddenLayer hiddenLayer1,
	Neural::HiddenLayer hiddenLayer2,
	Neural::OutputLayer outputLayer,
	Data::ImageSet & trainSet,
	std::queue<size_t> & workQueue
)
{
	int ID;
	bool workFlag = false;

	while (threadLifeFlag)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		workQueueMutex.lock();
		if (!workQueue.empty())
		{
			ID = workQueue.front();
			workQueue.pop();
			workFlag = true;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		workQueueMutex.unlock();

		if (workFlag)
		{
			auto sample = trainSet.GetSample(ID);

			// Initialzing input
			std::vector<MathLib::Matrix<double>> input{ sample.first + Random() };

			/***************************************************************************************************/
			// Forward Propagation
			// convLayer 1
			convLayer1.SetInput(input);
			convLayer1.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv1kernals = convLayer1.GetKernelAll();
			std::vector<Neural::ConvFeature> conv1features = convLayer1.GetFeatureAll();
			// poolLayer 1
			poolLayer1.SetInput(conv1features);
			poolLayer1.ForwardPropagation();
			std::vector<Neural::Feature> pool1features = poolLayer1.GetFeatureAll();
			// processLayer 1
			process1.SetInput(pool1features);
			process1.Process();
			std::vector<Neural::Feature> process1output = process1.GetOutputAll();
			// convLayer 2
			convLayer2.SetInput(process1output);
			convLayer2.ForwardPropagation();
			std::vector<Neural::ConvKernel> conv2kernals = convLayer2.GetKernelAll();
			std::vector<Neural::ConvFeature> conv2features = convLayer2.GetFeatureAll();
			// poolLayer 2
			poolLayer2.SetInput(conv2features);
			poolLayer2.ForwardPropagation();
			std::vector<Neural::Feature> pool2features = poolLayer2.GetFeatureAll();
			// processLayer 2
			process2.SetInput(pool2features);
			process2.Process();
			std::vector<Neural::Feature> process2output = process2.GetOutputAll();
			// serialLayer
			serial.SetDeserializedMat(process2output);
			MathLib::Vector<double> serializedVec = Matrix2Vector(serial.Serialize());
			// inputLayer
			inputLayer.SetInput(serializedVec);
			inputLayer.ForwardPropagation();
			MathLib::Vector<double> inputout = inputLayer.GetOutput();
			// hiddenLayer 1
			hiddenLayer1.SetInput(inputout);
			hiddenLayer1.ForwardPropagation();
			MathLib::Vector<double> hidden1output = hiddenLayer1.GetOutput();
			// hiddenLayer 2
			hiddenLayer2.SetInput(hidden1output);
			hiddenLayer2.ForwardPropagation();
			MathLib::Vector<double> hidden2output = hiddenLayer2.GetOutput();
			// outputLayer
			outputLayer.SetInput(hidden2output);
			outputLayer.ForwardPropagation();
			MathLib::Vector<double> output = outputLayer.GetOutput();
			/***************************************************************************************************/

			// Initialzing lable
			MathLib::Vector<double> lable = sample.second;

			// Calculating Error
			MathLib::Vector<double> error = output - lable;

			/***************************************************************************************************/
			// Backward Propagation
			MathLib::Vector<double> outputLayerDelta = outputLayer.BackwardPropagation(lable);
			// hiddenLayer 1
			MathLib::Vector<double> hiddenLayer2Delta = hiddenLayer2.BackwardPropagation(outputLayerDelta);
			// hiddenLayer 2
			MathLib::Vector<double> hiddenLayer1Delta = hiddenLayer1.BackwardPropagation(hiddenLayer2Delta);
			// outputLayer
			MathLib::Vector<double> inputLayerDelta = inputLayer.BackwardPropagation(hiddenLayer1Delta);
			// serialLayer
			serial.SetSerializedMat(Vector2Matrix(inputLayerDelta));
			std::vector<MathLib::Matrix<double>> deserialized = serial.Deserialize();
			// process 2
			process2.SetInput(deserialized);
			process2.Deprocess();
			std::vector<MathLib::Matrix<double>> deprocess2output = process2.GetOutputAll();
			// poolLayer 2
			poolLayer2.SetDelta(deprocess2output);
			poolLayer2.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> pool2Delta = poolLayer2.GetDelta();
			// convLayer 2
			convLayer2.SetDelta(pool2Delta);
			convLayer2.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> conv2Delta = convLayer2.GetDelta();
			// process 1
			process1.SetInput(conv2Delta);
			process1.Deprocess();
			std::vector<MathLib::Matrix<double>> deprocess1output = process1.GetOutputAll();
			// poolLayer 1
			poolLayer1.SetDelta(deprocess1output);
			poolLayer1.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> pool1Delta = poolLayer1.GetDelta();
			// convLayer 1
			convLayer1.SetDelta(pool1Delta);
			convLayer1.BackwardPropagation();
			std::vector<MathLib::Matrix<double>> conv1Delta = convLayer1.GetDelta();
			/***************************************************************************************************/


			/***************************************************************************************************/
			// Updating

			//plotMutex.lock();
			//std::cout << "ID : " << ID << std::endl;
			////Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 0, 0, false);
			////Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 350, 0, false);
			////Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 400, 0, false);
			////Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 750, 0, true);
			////Visual::Plot2D::Plot2DMatrixVec(conv2kernals, "conv2kernals", Visual::Plot2DMode::RB, 900, 0, false);
			////Visual::Plot2D::Plot2DMatrixVec(conv2features, "conv2features", Visual::Plot2DMode::RB, 1100, 0, false);
			////Visual::Plot2D::Plot2DMatrixVec(pool2features, "pool2features", Visual::Plot2DMode::RB, 1300, 0, true);
			//plotMutex.unlock();
			workFlag = false;
		}
	}
}



int main(int argc, char ** argv)
{
	// Visualization
	const bool visualWhileTraining = true;
	// Logging
	const bool detailLoggingWhileTraining = true;

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
	convInitor1.KernelNum = 5;
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
	Neural::ProcessLayer processLayer1(processInitor1);

	/***************************************************************************************************/
	// Initializing Convolutional Layer 2
	Neural::ConvLayerInitor convInitor2;
	convInitor2.InputSize = MathLib::Size(8, 8);
	convInitor2.KernelSize = MathLib::Size(3, 3);
	convInitor2.Stride = 1;
	convInitor2.KernelNum = 10;
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
	Neural::ProcessLayer processLayer2(processInitor2);

	/***************************************************************************************************/
	// Initializing Serialize Layer
	Neural::SerializeLayerInitor serialInitor;
	serialInitor.SerializeSize = MathLib::Size(2 * 2 * 10, 1);
	serialInitor.DeserializeSize = MathLib::Size(2, 2);
	Neural::SerializeLayer serialLayer(serialInitor);

	/***************************************************************************************************/
	// Initializing FullConnect Layer
	Neural::InputLayer inputLayer(2 * 2 * 10, 2 * 2 * 10);
	inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
	inputLayer.SetLossFunction(LossFunction::MES);

	Neural::HiddenLayer hiddenLayer1(2 * 2 * 10, 2 * 2 * 10);
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
	const double globalRate = 0.001 * 0.001 * 0.01;
	convLayer1.SetLearnRate(globalRate);
	convLayer2.SetLearnRate(globalRate);
	hiddenLayer1.SetLearnRate(globalRate);
	hiddenLayer2.SetLearnRate(globalRate);

	std::vector<Neural::ConvKernel> kernel1DeltaSum;
	std::vector<Neural::ConvKernel> kernel2DeltaSum;
	std::vector<double> biasDeltaSum;

	/***************************************************************************************************/
	// Start Training
	int totalTrainIteration = 100;
	for (size_t iteration = 0; iteration < totalTrainIteration; iteration++)
	{
		std::queue<size_t> workQueue;

		std::vector<std::thread *> threadpool;
		threadLifeFlag = true;
		for (size_t i = 0; i < 8; i++)
		{
			std::thread * tempthread = new std::thread(
				trainThreadFunc,
				convLayer1,
				poolLayer1,
				processLayer1,
				convLayer2,
				poolLayer2,
				processLayer2,
				serialLayer,
				inputLayer,
				hiddenLayer1,
				hiddenLayer2,
				outputLayer,
				std::ref(TrainSet),
				std::ref(workQueue)
			);
			threadpool.push_back(tempthread);
		}

		for (size_t i = 0; i < TrainSet.GetSampleSize(); i++)
			workQueue.push(i);

		while (!workQueue.empty())
			std::this_thread::sleep_for(std::chrono::milliseconds(10));

		threadLifeFlag = false;
		for (std::thread * thr : threadpool)
			thr->join();

		/***************************************************************************************************/
		// Updating
		convLayer1.Update();
		MathLib::Matrix<double> temp = convLayer1.GetKernel(0);
		std::cout << temp << std::endl;
		poolLayer1.Update();
		convLayer2.Update();
		poolLayer2.Update();
		inputLayer.Update();
		hiddenLayer1.Update();
		hiddenLayer2.Update();
		outputLayer.Update();

		convLayer1.BatchDeltaSumClear();
		convLayer2.BatchDeltaSumClear();
		hiddenLayer1.BatchDeltaSumClear();
		hiddenLayer2.BatchDeltaSumClear();
		outputLayer.BatchDeltaSumClear();
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

Matrix<double> Vector2Matrix(const Vector<double> & _vec) {
	Matrix<double> mat(_vec.Size(), 1, MatrixType::Zero);
	for (size_t i = 0; i < _vec.Size(); i++)
		mat(i, 0) = _vec(i);
	return mat;
}

#endif // CNNImageRecognization

