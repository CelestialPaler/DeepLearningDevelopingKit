/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      ConvolutionalLayer Test   													     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define ConvolutionalLayerImgDebug

#ifdef ConvolutionalLayerImgDebug

#include "..\ConvolutionalNeuralNetwork\CNN_ConvolutionalLayer.h"
#include "..\..\..\MathLib\MathLib.h"

int main(int argc, char ** argv)
{
	// Convolutional Layer Init
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(5, 5);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 1;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	MathLib::Matrix<double> input1(5, 5, MathLib::MatrixType::Zero);
	std::vector<MathLib::Matrix<double>> input;
	{
		for (size_t i = 0; i < input1.ColumeSize(); i++)
		{
			for (size_t j = 0; j < input1.RowSize(); j++)
				if (i == j)
					input1(i, j) = 1.f;
				else
					input1(i, j) = 1.f;
		}
		input.push_back(input1);
	}

	// Kernel
	{
		convLayer._convNodes.at(0).kernel.Clear();
		for (size_t i = 0; i < convLayer._convNodes.at(0).kernel.ColumeSize(); i++)
			for (size_t j = 0; j < convLayer._convNodes.at(0).kernel.RowSize(); j++)
				if (i == j)
					convLayer._convNodes.at(0).kernel(i, j) = 1.f;
	}

	convLayer.SetInput(input);
	std::cout << "Orignal Input : " << std::endl;
	std::cout << convLayer._input.at(0) << std::endl;

	std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();

	std::cout << "Orignal Kernels : " << std::endl << std::endl;
	for (auto mat : conv1kernals)
		std::cout << mat << std::endl;

	MathLib::Matrix<double> delta1(5, 5, MathLib::MatrixType::Zero);
	for (size_t i = 0; i < delta1.ColumeSize(); i++)
		for (size_t j = 0; j < delta1.RowSize(); j++)
			if (i == j)
				delta1(i, j) = 1.f;
			else
				delta1(i, j) = 0.f;

	std::vector<MathLib::Matrix<double>> delta;
	delta.push_back(delta1);

	convLayer.SetInput(input);
	convLayer.SetDelta(delta);

	convLayer.ForwardPropagation();

	std::cout << "Padded Input : " << std::endl;
	std::cout << convLayer._paddedInput.at(0) << std::endl;

	std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1featuresUpdated = convLayer.GetFeatureAll();
	std::cout << "Output Features : " << std::endl << std::endl;
	for (auto mat : conv1featuresUpdated)
		std::cout << mat << std::endl;

	// convLayer.BackwardPropagation();


	convLayer.Update();



	

	system("pause");
	return 0;
}

#endif