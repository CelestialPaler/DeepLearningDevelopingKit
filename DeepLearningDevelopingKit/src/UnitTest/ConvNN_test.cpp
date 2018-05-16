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
	testInitor.InputSize = MathLib::Size(3, 3);
	testInitor.KernalNum = 2;
	testInitor.KernalSize = MathLib::Size(2, 2);
	testInitor.PaddingMethod = Neural::PaddingMethod::LeftUp;
	testInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	testInitor.Stride = 1;
	testInitor.ActivationFunction = ActivationFunction::ReLU;
	testInitor.LossFunction = LossFunction::MES;

	Neural::ConvolutionalLayer testLayer(testInitor);

	MathLib::Matrix<double> input(3, 3, MathLib::MatrixType::Random);
	
	testLayer.SetInput(input);
	testLayer.Padding();

	std::cout << input << std::endl;
	MathLib::Matrix<double> temp(testLayer._paddedInput.GetSize().m, testLayer._paddedInput.GetSize().n);
	temp = testLayer._paddedInput;
	std::cout << temp << std::endl;

	testLayer.ForwardPropagation();


	system("pause");
	return 0;
}

#endif // CNNDebug
