/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                 Plot   															          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "..\..\MathLib\MathLib.h"
#include <string>
#include "..\OpenCV\OpenCV.hpp"

/***************************************************************************************************/
// Namespace : Visual
/// Provide tools for data visualization.
namespace Visual
{
	enum class Plot2DMode {
		R,
		G,
		B,
		RG,
		GB,
		RB,
		RGB
	};

	class Plot2D
	{
	public:
		template<class T>
		static void Plot2DMatrix(const MathLib::Matrix<T> & _mat, const std::string & _name = "Figure1", const Plot2DMode _mode = Plot2DMode::RB, unsigned _x = 100, unsigned _y = 100);

		template<class T>
		static void Plot2DMatrixVec(const std::vector<MathLib::Matrix<T>> & _mat, const std::string & _name = "Figure1", const Plot2DMode _mode = Plot2DMode::RB, unsigned _x = 100, unsigned _y = 100, bool _normalize = false );

		static void PerlinNoiseDemo(const size_t _m, const size_t _n);

		static cv::Mat Scale(const cv::Mat _mat, unsigned n);

		template<class T>
		static void PlotCNNTrainProcess(const std::vector<std::vector<MathLib::Matrix<T>>> _data, const std::string & _name = "Layer1");
	};

	template<class T>
	inline void Plot2D::Plot2DMatrix(const MathLib::Matrix<T>& _mat, const std::string & _name, const Plot2DMode _mode, unsigned _x, unsigned _y)
	{
		cv::Mat tempMat(cv::Size(_mat.ColumeSize(), _mat.RowSize()), CV_32FC1);
		tempMat = Visual::OpenCV::Matrix2Mat<float>(_mat);
		tempMat += 1;
		cv::normalize(tempMat, tempMat, 0, 1, cv::NORM_MINMAX);

		cv::Mat img(tempMat.cols, tempMat.rows, CV_8UC3);
		for (size_t i = 0; i < tempMat.cols; i++)
		{
			for (size_t j = 0; j < tempMat.rows; j++)
			{
				cv::Vec3b pixel;
				switch (_mode)
				{
				case Plot2DMode::R:
					pixel.val[0] = 0; // B
					pixel.val[1] = 0; // G
					pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
					break;
				case Plot2DMode::G:
					pixel.val[0] = 0; // B
					pixel.val[1] = tempMat.at<float>(i, j) * 255; // G
					pixel.val[2] = 0; // R
					break;
				case Plot2DMode::B:
					pixel.val[0] = tempMat.at<float>(i, j) * 255; // B
					pixel.val[1] = 0; // G
					pixel.val[2] = 0; // R
					break;
				case Plot2DMode::RG:
					pixel.val[0] = 0; // B
					pixel.val[1] = (1 - tempMat.at<float>(i, j)) * 255; // G
					pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
					break;
				case Plot2DMode::GB:
					pixel.val[0] = 0; // B
					pixel.val[1] = (1 - tempMat.at<float>(i, j)) * 255; // G
					pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
					break;
				case Plot2DMode::RB:
					pixel.val[0] = (1 - tempMat.at<float>(i, j)) * 255; // B
					pixel.val[1] = 0; // G
					pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
					break;
				default:
					pixel.val[0] = (1 - tempMat.at<float>(i, j)) * 255; // B
					pixel.val[1] = 0; // G
					pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
					break;
				}
				img.at<cv::Vec3b>(i, j) = pixel;
			}
		}
		resize(img, img, cv::Size(img.cols * 10, img.rows * 10), 0, 0, cv::INTER_NEAREST);

		cv::namedWindow(_name, cv::WINDOW_AUTOSIZE);
		cv::imshow(_name, img);
		cv::waitKey(10);
	}

	template<class T>
	inline static void Plot2D::Plot2DMatrixVec(const std::vector<MathLib::Matrix<T>>& _mat, const std::string & _name, const Plot2DMode _mode, unsigned _x, unsigned _y, bool _normalize)
	{
		cv::Mat img;
		for (const MathLib::Matrix<double> & mat : _mat)
		{
			MathLib::Matrix<float> data2(mat.ColumeSize(), mat.RowSize());
			for (size_t i = 0; i < mat.ColumeSize(); i++)
				for (size_t j = 0; j < mat.RowSize(); j++)
					data2(i, j) = mat(i, j);
			cv::Mat newImg = Visual::OpenCV::Matrix2Mat<float>(data2);
			cv::normalize(newImg, newImg, 0, 1, cv::NORM_MINMAX);

			cv::Mat img_temp(newImg.size(), CV_8UC3);
			for (size_t i = 0; i < newImg.rows; i++)
			{
				for (size_t j = 0; j < newImg.cols; j++)
				{
					cv::Vec3b pixel;
					pixel.val[0] = (1 - newImg.at<float>(i, j)) * 255; // B
					pixel.val[1] = 0; // G
					pixel.val[2] = newImg.at<float>(i, j) * 255; // R
					img_temp.at<cv::Vec3b>(i, j) = pixel;
				}
			}
			img.push_back(img_temp);

			cv::Mat img_div(1, mat.RowSize(), CV_8UC3, cv::Scalar::all(0));
			img.push_back(img_div);
		}

		resize(img, img, cv::Size(img.cols * 10, img.rows * 10), 0, 0, cv::INTER_NEAREST);

		cv::namedWindow(_name, cv::WINDOW_AUTOSIZE);
		cv::moveWindow(_name, _x, _y);
		cv::imshow(_name, img);
		cv::waitKey(1);
	}

	template<class T>
	inline void Plot2D::PlotCNNTrainProcess(const std::vector<std::vector<MathLib::Matrix<T>>> _data, const std::string & _name)
	{

	}
}