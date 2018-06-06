/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      ConvolutionalLayer Test   													     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#define ConvolutionalLayerImgDebug

#ifdef ConvolutionalLayerImgDebug

#include "..\Algorithm\NeuralNetwork\NeuralLib.h"
//#include "..\Visualizer\Visualize.h"

int main(int argc, char ** argv)
{
	cv::Mat imgRGB = cv::imread("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\example\\OpenCV\\niconi.png");
	cv::Mat img = cv::imread("F:\\Software\\Top Peoject\\DeepLearningProject\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\DeepLearningDevelopingKit\\data\\example\\OpenCV\\niconi.png", cv::IMREAD_GRAYSCALE);
	cv::imshow("Rem", imgRGB);
	cv::waitKey(500);

	cv::normalize(img, img, 0, 1, cv::NORM_MINMAX);
	MathLib::Matrix<double> data = Visual::OpenCV::Mat2Matrix<unsigned char>(img);
	std::vector<MathLib::Matrix<double>> input;
	input.push_back(data);

	// Convolutional Layer Init
	Neural::ConvLayerInitor convInitor;
	convInitor.InputSize = MathLib::Size(data.ColumeSize(), data.RowSize());
	convInitor.KernelSize = MathLib::Size(3, 3);
	convInitor.Stride = 1;
	convInitor.KernelNum = 2;
	convInitor.ActivationFunction = ActivationFunction::Linear;
	convInitor.PaddingMethod = Neural::PaddingMethod::Surround;
	convInitor.PaddingNum = Neural::PaddingNum::ZeroPadding;
	Neural::ConvolutionalLayer convLayer(convInitor);

	Neural::ProcessLayerInitor processInitor;
	processInitor.InputSize = MathLib::Size(data.ColumeSize(), data.RowSize());
	processInitor.ProcessFunction = ReLU;
	processInitor.ProcessFunctionDerivative = ReLUDerivative;
	Neural::ProcessLayer process(processInitor);

	// Kernel
	{
		convLayer._convNodes.at(0).kernel.Clear();
		for (size_t i = 0; i < convLayer._convNodes.at(0).kernel.ColumeSize(); i++)
			for (size_t j = 0; j < convLayer._convNodes.at(0).kernel.RowSize(); j++)
				if (i == 2)
					convLayer._convNodes.at(0).kernel(i, j) = 1.f;
				else
					convLayer._convNodes.at(0).kernel(i, j) = -1.f;

		convLayer._convNodes.at(1).kernel.Clear();
		for (size_t i = 0; i < convLayer._convNodes.at(0).kernel.ColumeSize(); i++)
			for (size_t j = 0; j < convLayer._convNodes.at(0).kernel.RowSize(); j++)
				if (j == 2)
					convLayer._convNodes.at(1).kernel(i, j) = 1.f;
				else
					convLayer._convNodes.at(1).kernel(i, j) = -1.f;
	}

	convLayer.SetInput(input);
	convLayer.ForwardPropagation();
	std::vector<Neural::ConvFeature> conv1featuresUpdated = convLayer.GetFeatureAll();

	for (size_t i = 0; i < 2; i++)
		conv1featuresUpdated.at(i) -= 0;
	process.SetInput(conv1featuresUpdated);
	process.Process();
	std::vector<Neural::Feature> processOutput = process.GetOutputAll();
	data = processOutput.at(0) + processOutput.at(1);
	MathLib::Matrix<float> data2(data.ColumeSize(), data.RowSize());
	for (size_t i = 0; i < data.ColumeSize(); i++)
		for (size_t j = 0; j < data.RowSize(); j++)
			data2(i, j) = data(i, j);
	cv::Mat newImg = Visual::OpenCV::Matrix2Mat<float>(data2);
	cv::normalize(newImg, newImg, 0, 1, cv::NORM_MINMAX);
	cv::imshow("Rem", newImg);
	cv::waitKey();

	return 0;
}

#endif