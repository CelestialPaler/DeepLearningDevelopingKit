/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           CNN Test   															      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNDebug

#ifdef CNNDebug

#include "..\Algorithm\NeuralNetwork\ConvolutionalNeuralNetwork\CNN_ConvolutionalLayer.h"
#include "..\Algorithm\NeuralNetwork\ConvolutionalNeuralNetwork\CNN_PoolingLayer.h"


int main(int argc, char ** argv)
{
	Neural::ConvLayerInitor testInitor;
	testInitor.InputSize = MathLib::Size(10, 10);
	testInitor.KernelNum = 5;
	testInitor.KernelSize = MathLib::Size(3, 3);
	testInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	testInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	testInitor.Stride = 1;
	testInitor.ActivationFunction = ActivationFunction::ReLU;
	testInitor.LossFunction = LossFunction::MES;

	Neural::ConvolutionalLayer testLayer(testInitor);

	MathLib::Matrix<double> input(10, 10, MathLib::MatrixType::Random);
	
	testLayer.SetInput(input);
	testLayer.Padding();

	std::cout << input << std::endl;
	MathLib::Matrix<double> temp1(testLayer._paddedInput.GetSize().m, testLayer._paddedInput.GetSize().n);
	temp1 = testLayer._paddedInput;
	std::cout << temp1 << std::endl;

	testLayer.ForwardPropagation();

	std::vector<MathLib::Matrix<double>> features= testLayer.GetFeatureAll();
	for (auto & vec : features)
		std::cout << vec << std::endl;

	std::vector<MathLib::Matrix<double>> kernels = testLayer.GetKernelAll();
	for (auto & vec : kernels)
		std::cout << vec << std::endl;

	Neural::PoolLayerInitor poolinitor;
	poolinitor.InputSize = MathLib::Size(10, 10);
	poolinitor.Stride = 2;
	poolinitor.PoolSize = MathLib::Size(2, 2);
	poolinitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	poolinitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolinitor.PoolingMethod = Neural::PoolingMethod::MaxPooling;

	Neural::PoolingLayer testPooling(poolinitor);

	testPooling.SetInput(features);
	testPooling.DownSampling();

	std::vector<MathLib::Matrix<double>> smallerFeature = testPooling.GetFeatureAll();
	for (auto & vec : smallerFeature)
		std::cout << vec << std::endl;

	system("pause");
	return 0;
}

#endif // CNNDebug
