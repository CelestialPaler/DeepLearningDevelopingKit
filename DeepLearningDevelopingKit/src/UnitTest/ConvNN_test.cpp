/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	   Linear Regression Test   	                                                      */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define CNNDebug

#ifdef CNNDebug
#include "..\Algorithm\NeuralNetwork\CNN\CNN.h"


int main(int argc, char ** argv)
{
	Neural::ConvLayerInitor testInitor;
	testInitor.InputSize = MathLib::Size(3, 3);
	testInitor.KernalNum = 2;
	testInitor.KernalSize = MathLib::Size(2, 2);
	testInitor.SamplingMethod = Neural::SamplingMethod::NoPadding;
	testInitor.Stride = 1;

	Neural::ConvolutionalLayer tstLayer(testInitor);


	system("pause");
	return 0;
}

#endif // CNNDebug
