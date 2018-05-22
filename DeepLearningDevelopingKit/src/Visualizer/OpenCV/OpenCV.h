/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         OpenCV Test   															  */
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

		OpenCV();

	public:

		// Convert a cv::Mat into a MathLib::Matrix.
		static MathLib::Matrix<double> Mat2Matrix(const cv::Mat & _mat);

	private:

	};

	class Image
	{
	public:

		Image();

	private:

	};


}


