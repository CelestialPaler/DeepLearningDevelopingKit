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
					input1(i, j) = 0.f;
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
				delta1(i, j) = 1;
			else
				delta1(i, j) = 0;

	std::vector<MathLib::Matrix<double>> delta;
	delta.push_back(delta1);


	convLayer.SetDelta(delta);

	convLayer.ForwardPropagation();

	std::vector<Neural::ConvFeature> a = convLayer.GetFeatureAll();
	std::cout << "Output Features : " << std::endl << std::endl;
	for (auto mat : a)
		std::cout << mat << std::endl;

	convLayer.BackwardPropagation();

	std::cout << "Delta LastLayer : " << std::endl << std::endl;
	for (auto mat : convLayer._derivativeLastLayer)
		std::cout << mat << std::endl;
	std::cout << "Delta : " << std::endl << std::endl;
	for (auto mat : convLayer._derivative)
		std::cout << mat << std::endl;

	convLayer.Update();

	std::cout << "Updated Kernels : " << std::endl << std::endl;
	std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
	for (auto mat : conv1kernalsUpdated)
		std::cout << mat << std::endl;
	convLayer.ForwardPropagation();
	std::vector<Neural::ConvFeature> conv1featuresUpdated = convLayer.GetFeatureAll();
	std::cout << "Updated Output Features : " << std::endl << std::endl;
	for (auto mat : conv1featuresUpdated)
		std::cout << mat << std::endl;


	

	system("pause");
	return 0;
}

#endif