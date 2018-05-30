/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	             CNN Test   													              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNDebug

#ifdef CNNDebug
#include "..\NeuralLib.h"
#include "..\..\..\MathLib\MathLib.h"
#include "..\..\..\Visualizer\Visualize.h"

int main(int argc, char ** argv)
{
	while (true)
	{
		srand((unsigned)time(NULL));

		MathLib::Matrix<double> input1(16, 16, MathLib::MatrixType::Zero);
		for (size_t i = 0; i < input1.ColumeSize(); i++)
		{
			for (size_t j = 0; j < input1.RowSize(); j++)
			{
				if (i == j || i + j == input1.ColumeSize() - 1)
					input1(i, j) = 1;
				else
					input1(i, j) = Random();
			}
		}
		std::vector<MathLib::Matrix<double>> input;
		input.push_back(input1);

		unsigned kernalNum = 5;

		/***************************************************************************************************/
		// Initializing Convolutional Layer
		Neural::ConvLayerInitor convInitor;
		convInitor.InputSize = MathLib::Size(16, 16);
		convInitor.KernelSize = MathLib::Size(5, 5);
		convInitor.Stride = 1;
		convInitor.KernelNum = kernalNum;
		convInitor.ActivationFunction = ActivationFunction::Sigmoid;
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
		Neural::InputLayer inputLayer(4 * 4 * kernalNum, 8 * 88 * 8 * kernalNum);
		inputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
		inputLayer.SetLossFunction(LossFunction::MES);

		Neural::HiddenLayer hiddenLayer(4 * 4 * kernalNum, 10);
		hiddenLayer.SetActivationFunction(ActivationFunction::ReLU);
		hiddenLayer.SetLossFunction(LossFunction::MES);

		Neural::OutputLayer outputLayer(10, 1);
		outputLayer.SetActivationFunction(ActivationFunction::Sigmoid);
		outputLayer.SetLossFunction(LossFunction::MES);

		for (size_t iteration = 0; iteration < 10000; iteration++)
		{
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
			lable(0) = 1;
			MathLib::Vector<double> error(1);
			error = lable - outputLayer.GetOutput();
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
			convLayer.Update();
			poolLayer.Update();
			inputLayer.Update();
			hiddenLayer.Update();
			outputLayer.Update();

			Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 200, 200);
			Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 400, 200);
			Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 600, 200);
			Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 800, 200);
			//Visual::Plot2D::Plot2DMatrix<float>(CNNout, "CNNout", Visual::Plot2DMode::RB, 1000, 200);

			std::cout << error << std::endl;
			if (error(0) < 0.001)
			{
				while (true)
				{
					Visual::Plot2D::Plot2DMatrixVec(input, "input", Visual::Plot2DMode::RB, 200, 200);
					Visual::Plot2D::Plot2DMatrixVec(conv1kernals, "conv1kernals", Visual::Plot2DMode::RB, 400, 200);
					Visual::Plot2D::Plot2DMatrixVec(conv1features, "conv1features", Visual::Plot2DMode::RB, 600, 200);
					Visual::Plot2D::Plot2DMatrixVec(pool1features, "pool1features", Visual::Plot2DMode::RB, 800, 200);
				}
			}

			//std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
			//std::cout << "Kernels : " << std::endl << std::endl;
			//for (auto mat : conv1kernalsUpdated)
			//	std::cout << mat << std::endl;
		}
	}

	//std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
	//std::cout << "Kernels : " << std::endl << std::endl;
	//for (auto mat : conv1kernalsUpdated)
	//	std::cout << mat << std::endl;

	system("pause");
	return 0;
}
#endif // CNNDebug

