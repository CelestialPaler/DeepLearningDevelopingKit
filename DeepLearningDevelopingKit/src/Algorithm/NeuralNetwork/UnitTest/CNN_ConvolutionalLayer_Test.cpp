/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      ConvolutionalLayer Test   													     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define ConvolutionalLayerDebug

#ifdef ConvolutionalLayerDebug

#include "..\ConvolutionalNeuralNetwork\CNN_ConvolutionalLayer.h"
#include "..\..\..\MathLib\MathLib.h"

int main(int argc, char ** argv)
{
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(3, 3);
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 5;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	MathLib::Matrix<double> input1(3, 3, MathLib::MatrixType::Random);
	std::vector<MathLib::Matrix<double>> input;
	input.push_back(input1);

	convLayer.SetInput(input);
	convLayer.ForwardPropagation();

	std::vector<Neural::ConvKernel> conv1kernals = convLayer.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1features = convLayer.GetFeatureAll();

	std::cout << input.at(0) << std::endl;
	for (auto mat : conv1kernals)
		std::cout << mat << std::endl;
	for (auto mat : conv1features)
		std::cout << mat << std::endl;

	system("pause");
	return 0;
}

#endif