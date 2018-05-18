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
	/***************************************************************************************************/
	// Input
	MathLib::Matrix<double> input(10, 10, MathLib::MatrixType::Random);

	/***************************************************************************************************/
	// Initializing Convolutional Layer
	Neural::ConvLayerInitor convInitor;
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.InputSize = MathLib::Size(10, 10);
	convInitor.StrideM = 1;
	convInitor.StrideN = 1;
	convInitor.KernelNum = 5;
	convInitor.LossFunction = LossFunction::MES;
	convInitor.ActivationFunction = ActivationFunction::ReLU;
	Neural::ConvolutionalLayer testLayer(convInitor);

	/***************************************************************************************************/
	// Initializing Pooling Layer
	Neural::PoolLayerInitor poolInitor;
	poolInitor.InputSize = MathLib::Size(10, 10);
	poolInitor.Stride = 2;
	poolInitor.PoolSize = MathLib::Size(2, 2);
	poolInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor.PaddingMethod = Neural::PaddingMethod::RightDown;
	Neural::PoolingLayer testPooling(poolInitor);

	system("pause");
	return 0;
}

#endif // CNNDebug
