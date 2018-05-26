/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              OpenCV    															       */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include <iostream>

#include "..\..\MathLib\MathLib.h"

// OpenCV
#include "..\..\..\external\opencv\include\opencv2\core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

/***************************************************************************************************/
// Namespace : Visual
/// Provide tools for data visualization.
namespace Visual
{
	class OpenCV
	{
	public:

		// Convert a cv::Mat into a MathLib::Matrix.
		template<class T>
		static MathLib::Matrix<double> Mat2Matrix(const cv::Mat & _mat);
		// Convert a MathLib::Matrix into a cv::Mat.
		template<class T>
		static cv::Mat Matrix2Mat(const MathLib::Matrix<T> & _matrix);

	private:

	};
}

namespace Visual
{
	template<class T>
	MathLib::Matrix<double> OpenCV::Mat2Matrix(const cv::Mat & _mat)
	{
		MathLib::Matrix<double> tempMat(_mat.cols, _mat.rows, MathLib::MatrixType::Zero);
		for (size_t i = 0; i < _mat.cols; i++)
		{
			for (size_t j = 0; j < _mat.rows; j++)
			{
				tempMat(i, j) = _mat.at<T>(i, j);
			}
		}
		return tempMat;
	}

	template<class T>
	inline cv::Mat OpenCV::Matrix2Mat(const MathLib::Matrix<T>& _matrix)
	{
		cv::Mat tempMat(_matrix.ColumeSize(), _matrix.RowSize(), CV_32FC1, cv::Scalar::all(0));
		for (size_t i = 0; i < tempMat.cols; i++)
		{
			for (size_t j = 0; j < tempMat.rows; j++)
			{
				tempMat.at<T>(i, j) = _matrix(i, j);
			}
		}
		return tempMat;
	}

}



