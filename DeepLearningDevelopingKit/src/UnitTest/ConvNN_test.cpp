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
	MathLib::Matrix<double> input1(10, 10, MathLib::MatrixType::Random);
	std::vector<MathLib::Matrix<double>> input;
	input.push_back(input1);

	for (auto mat : input)
		std::cout << mat << std::endl;

	/***************************************************************************************************/
	// Initializing Convolutional Layer 1
	std::cout << "/***************************************************************************************************/"
		<< std::endl << "Convolutional Layer 1" << std::endl;
	Neural::ConvLayerInitor convInitor1;
	convInitor1.InputSize = MathLib::Size(10, 10);
	convInitor1.KernelSize = MathLib::Size(3, 3);
	convInitor1.Stride = 1;
	convInitor1.KernelNum = 5;
	convInitor1.ActivationFunction = ActivationFunction::Sigmoid;
	convInitor1.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer conv1(convInitor1);

	conv1.SetInput(input);
	conv1.Padding();
	conv1.ForwardPropagation();

	std::vector<Neural::ConvKernel> conv1kernals = conv1.GetKernelAll();
	std::vector<Neural::ConvFeature> conv1features = conv1.GetFeatureAll();

	for (auto mat : conv1kernals)
		std::cout << mat << std::endl;
	for (auto mat : conv1features)
		std::cout << mat << std::endl;

	/***************************************************************************************************/
	// Initializing Pooling Layer 1
	std::cout << "/***************************************************************************************************/" 
		<< std::endl <<"Pooling Layer 1"<< std::endl;
	Neural::PoolLayerInitor poolInitor1;
	poolInitor1.InputSize = MathLib::Size(10, 10);
	poolInitor1.Stride = 2;
	poolInitor1.PoolSize = MathLib::Size(2, 2);
	poolInitor1.PaddingNum = Neural::PaddingNum::ZeroPadding;
	poolInitor1.PoolingMethod = Neural::PoolingMethod::MaxPooling;
	poolInitor1.PaddingMethod = Neural::PaddingMethod::RightDown;
	Neural::PoolingLayer pool1(poolInitor1);

	pool1.SetInput(conv1features);
	pool1.Padding();
	pool1.DownSampling();

	std::vector<Neural::Feature> pool1features = pool1.GetFeatureAll();

	for (auto mat : pool1features)
		std::cout << mat << std::endl;

	/***************************************************************************************************/
	// Initializing Convolutional Layer 2
	std::cout << "/***************************************************************************************************/"
		<< std::endl << "Convolutional Layer 2" << std::endl;
	Neural::ConvLayerInitor convInitor2;
	convInitor2.InputSize = MathLib::Size(5, 5);
	convInitor2.KernelSize = MathLib::Size(3, 3);
	convInitor2.Stride = 1;
	convInitor2.KernelNum = 2;
	convInitor2.ActivationFunction = ActivationFunction::Sigmoid;
	convInitor2.PaddingMethod = Neural::PaddingMethod::RightDown;
	convInitor2.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer conv2(convInitor2);

	conv2.SetInput(pool1features);
	conv2.Padding();
	conv2.ForwardPropagation();

	std::vector<Neural::ConvKernel> conv2kernals = conv2.GetKernelAll();
	std::vector<Neural::ConvFeature> conv2features = conv2.GetFeatureAll();

	for (auto mat : conv2kernals)
		std::cout << mat << std::endl;
	for (auto mat : conv2features)
		std::cout << mat << std::endl;

	system("pause");
	return 0;
}

#endif // CNNDebug
