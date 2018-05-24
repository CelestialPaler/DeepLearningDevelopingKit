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
		static void Plot2DMatrix(const MathLib::Matrix<T> & _mat, const std::string & _name = "Figure1", const Plot2DMode _mode= Plot2DMode::RB);

		static void PerlinNoiseDemo(const size_t _m, const size_t _n);

	private:

	};

	template<class T>
	inline void Plot2D::Plot2DMatrix(const MathLib::Matrix<T>& _mat, const std::string & _name, const Plot2DMode _mode)
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

		cv::namedWindow(_name, cv::WINDOW_AUTOSIZE);
		cv::imshow(_name, img);
		cv::waitKey();
	}
}