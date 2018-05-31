/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         OpenCV Test   															  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define OpenCVDebug

#ifdef OpenCVDebug

#include "..\Visualizer\Visualize.h"

int main(int argc, char ** argv)
{
	srand((unsigned)time(NULL));
	/*
	cv::Mat imageTest = cv::imread("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\Data\\O_0.png");
	if (!imageTest.data)
		return -1;
	cv::resize(imageTest, imageTest, cv::Size(500, 500), cv::INTER_LINEAR);
	cv::namedWindow("data", cv::WINDOW_AUTOSIZE);
	cv::imshow("data", imageTest);
	cv::waitKey();
	*/

	//cv::Mat testMat1(cv::Size(500, 500), CV_32FC1);
	//MathLib::Matrix<float> testMatrix1(500, 500, MathLib::MatrixType::Random);

	//testMat1 = Visual::OpenCV::Matrix2Mat<float>(testMatrix1);
	//testMatrix1 = Visual::OpenCV::Mat2Matrix<float>(testMat1);
	//std::cout << testMatrix1 << std::endl;
	//std::cout << testMat1 << std::endl;

	// Visual::Plot2D::Plot2DMatrix(testMatrix1);
	// Visual::Plot2D::PerlinNoiseDemo(800, 800);

	//system("pause");
	return 0;
}

#endif // OpenCVDebug

