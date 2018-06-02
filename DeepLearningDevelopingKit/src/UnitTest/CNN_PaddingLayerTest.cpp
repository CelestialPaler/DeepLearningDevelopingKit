
#include "..\Algorithm\NeuralNetwork\NeuralLib.h"

/*
int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	std::cout << "Unit Test : CNN-PaddingLayer" << std::endl;
	std::cout << "Project : DeepLearningDevelopingKit\n";
	std::cout << "Branch  : Master\n";
	std::cout << "Version : Windows-x64-1.0.0-CPU\n";
	std::cout << "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";


	MathLib::Matrix<double> testMat(5, 5, MathLib::MatrixType::Ones);
	std::cout << "Original input: " << testMat << std::endl;
	MathLib::Matrix<double> result;

	std::cout << "--PaddingMethod--" << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::LeftDown, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingMethod::LeftDown: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::LeftUp, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingMethod::LeftUp: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::RightDown, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingMethod::RightDown: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::RightUp, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingMethod::RightUp: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingMethod::Surround: \n" << result << std::endl;

	std::cout << "--PaddingNum--" << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "PaddingNum::ZeroPadding: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::OnePadding, 1, 1);
	std::cout << "PaddingNum::OnePadding: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::RandomPadding, 1, 1);
	std::cout << "PaddingNum::RandomPadding: \n" << result << std::endl;

	std::cout << "--PaddingSize--" << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 1, 1);
	std::cout << "1, 1: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 2, 2);
	std::cout << "2, 2: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 1, 2);
	std::cout << "1, 2: \n" << result << std::endl;
	result = Neural::Pad::Padding(testMat, Neural::PaddingMethod::Surround, Neural::PaddingNum::ZeroPadding, 0, 0);
	std::cout << "0, 0: \n" << result << std::endl;

	std::cout << "\n\nTest OK" << std::endl;

	system("pause");
	return 0;
}*/