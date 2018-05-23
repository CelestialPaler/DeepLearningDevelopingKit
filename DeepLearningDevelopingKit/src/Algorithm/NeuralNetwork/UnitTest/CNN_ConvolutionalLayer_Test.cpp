/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      ConvolutionalLayer Test   													     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define ConvolutionalLayerDebug

#ifdef ConvolutionalLayerDebug

#include "..\ConvolutionalNeuralNetwork\CNN_ConvolutionalLayer.h"
#include "..\..\..\MathLib\MathLib.h"

int main(int argc, char ** argv)
{
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(5, 5);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 2;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	MathLib::Matrix<double> input1(5, 5, MathLib::MatrixType::Zero);
	for (size_t i = 0; i < input1.ColumeSize(); i++)
		for (size_t j = 0; j < input1.RowSize(); j++)
			if (i == j)
				input1(i, j) = 1.f;
			else
				input1(i, j) = 0.5;

	std::vector<MathLib::Matrix<double>> input;
	input.push_back(input1);

	convLayer._convNodes.at(0).kernel.Clear();
	for (size_t i = 0; i < convLayer._convNodes.at(0).kernel.ColumeSize(); i++)
		for (size_t j = 0; j < convLayer._convNodes.at(0).kernel.RowSize(); j++)
			if (i == j)
				convLayer._convNodes.at(0).kernel(i, j) = 1.f;

	convLayer._convNodes.at(1).kernel.Clear();
	for (size_t i = 0; i < convLayer._convNodes.at(1).kernel.ColumeSize(); i++)
		for (size_t j = 0; j < convLayer._convNodes.at(1).kernel.RowSize(); j++)
			if (i + j + 1== convLayer._convNodes.at(1).kernel.RowSize())
				convLayer._convNodes.at(1).kernel(i, j) = 1.f;

	convLayer.SetInput(input);
	std::cout << "Orignal Input : " << std::endl;
	std::cout << convLayer._input.at(0) << std::endl;

	std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();

	std::cout << "Orignal Kernel : " << std::endl;
	std::cout << "Kernels : " << std::endl << std::endl;
	for (auto mat : conv1kernals)
		std::cout << mat << std::endl;

	std::cout << "Features : " << std::endl << std::endl;
	for (auto mat : conv1features)
		std::cout << mat << std::endl;

	MathLib::Matrix<double> delta1(5, 5, MathLib::MatrixType::Zero);
	for (size_t i = 0; i < delta1.ColumeSize(); i++)
		for (size_t j = 0; j < delta1.RowSize(); j++)
			if (i == j)
				delta1(i, j) = 1.f;
			else
				delta1(i, j) = 0.f;

	MathLib::Matrix<double> delta2(5, 5, MathLib::MatrixType::Zero);
	for (size_t i = 0; i < delta2.ColumeSize(); i++)
		for (size_t j = 0; j < delta2.RowSize(); j++)
			if (i == j)
				delta2(i, j) = -0.5;
			else
				delta2(i, j) = 0.5;

	std::vector<MathLib::Matrix<double>> delta;
	delta.push_back(delta1);
	delta.push_back(delta2);
	convLayer.SetDelta(delta);

	std::cout << "Delta : " << std::endl;
	std::cout << "Kernels : " << std::endl << std::endl;
	for (auto mat : delta)
		std::cout << mat << std::endl;

	for (size_t iteration = 0; iteration < 1000; iteration++)
	{
		convLayer.ForwardPropagation();
		convLayer.BackwardPropagation();
		convLayer.Update();
	}

	std::vector<Neural::ConvKernel> conv1kernalsUpdated = convLayer.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1featuresUpdated = convLayer.GetFeatureAll();
	std::cout << "Kernels : " << std::endl << std::endl;
	for (auto mat : conv1kernalsUpdated)
		std::cout << mat << std::endl;
	std::cout << "Features : " << std::endl << std::endl;
	for (auto mat : conv1featuresUpdated)
		std::cout << mat << std::endl;

	system("pause");
	return 0;
}

#endif