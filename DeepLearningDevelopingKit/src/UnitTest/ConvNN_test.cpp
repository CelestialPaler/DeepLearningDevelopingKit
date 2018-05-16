/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	   Linear Regression Test   	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNDebug

#ifdef CNNDebug

#include "..\Algorithm\NeuralNetwork\ConvolutionalNeuralNetwork\CNN_Layer.h"


int main(int argc, char ** argv)
{
	Neural::ConvLayerInitor testInitor;
	testInitor.InputSize = MathLib::Size(10, 10);
	testInitor.KernalNum = 5;
	testInitor.KernalSize = MathLib::Size(3, 3);
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

	std::vector<MathLib::Matrix<double>> kernals = testLayer.GetKernalAll();
	for (auto & vec : kernals)
		std::cout << vec << std::endl;



	system("pause");
	return 0;
}

#endif // CNNDebug
