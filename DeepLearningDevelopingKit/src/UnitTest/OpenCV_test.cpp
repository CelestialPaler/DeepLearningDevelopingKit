/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         OpenCV Test   															  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define OpenCVDebug

#ifdef OpenCVDebug

#include "..\Visualizer\OpenCV\OpenCV.h"

int main(int argc, char ** argv)
{
	cv::Mat imageTest = cv::imread("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\XO\\Data\\O_0.png");
	if (!imageTest.data)
		return -1;
	cv::resize(imageTest, imageTest, cv::Size(500, 500), cv::INTER_LINEAR);
	cv::namedWindow("data", cv::WINDOW_AUTOSIZE);
	cv::imshow("data", imageTest);
	cv::waitKey();
	system("pause");
	return 0;
}

#endif // OpenCVDebug

