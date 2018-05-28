#include "Plot.hpp"

class PerlinNoise {
public:
	double operator()(float x, float y) {
		double total = 0;
		double p = persistence;
		int n = Number_Of_Octaves;
		for (int i = 0; i<n; i++)
		{
			double frequency = pow(2, i);
			double amplitude = pow(p, i);
			total = total + InterpolatedNoise(x * frequency, y * frequency) * amplitude;
		}
		return total;
	}
private:
	float persistence = 0.50;
	int Number_Of_Octaves = 4;

	double Noise(int x, int y)
	{
		int n = x + y * 57;
		n = (n << 13) ^ n;
		return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
	}

	double SmoothedNoise(int x, int y)
	{
		double corners = (Noise(x - 1, y - 1) + Noise(x + 1, y - 1) + Noise(x - 1, y + 1) + Noise(x + 1, y + 1)) / 16;
		double sides = (Noise(x - 1, y) + Noise(x + 1, y) + Noise(x, y - 1) + Noise(x, y + 1)) / 8;
		double center = Noise(x, y) / 4;
		return corners + sides + center;
	}

	double Cosine_Interpolate(double a, double b, double x)
	{
		double ft = x * 3.1415927;
		double f = (1 - cos(ft)) * 0.5;
		return a * (1 - f) + b * f;
	}

	double InterpolatedNoise(float x, float y)
	{
		int integer_X = int(x);
		float  fractional_X = x - integer_X;
		int integer_Y = int(y);
		float fractional_Y = y - integer_Y;
		double v1 = SmoothedNoise(integer_X, integer_Y);
		double v2 = SmoothedNoise(integer_X + 1, integer_Y);
		double v3 = SmoothedNoise(integer_X, integer_Y + 1);
		double v4 = SmoothedNoise(integer_X + 1, integer_Y + 1);
		double i1 = Cosine_Interpolate(v1, v2, fractional_X);
		double i2 = Cosine_Interpolate(v3, v4, fractional_X);
		return Cosine_Interpolate(i1, i2, fractional_Y);
	}
};

void Visual::Plot2D::PerlinNoiseDemo(const size_t _m, const size_t _n)
{
	std::cout << "Perlin Noise Demo" << std::endl;
	std::cout << "Project : Perlin Noise OpenCV Demo\n";
	std::cout << "Branch  : Master\n";
	std::cout << "Version : Windows-x64-1.0.0-CPU\n";
	std::cout << "Copyright 2015-2018 Celestial Tech Inc.\nFor more check www.tianshicangxie.com\n";
	MathLib::Matrix<float> Mat(_m, _n, MathLib::MatrixType::Random);
	float step = 0.02;
	float bias = rand();
	cv::namedWindow("Perlin Noise Anim", cv::WINDOW_AUTOSIZE);
	PerlinNoise pNoise;
	while (cv::waitKey(1))
	{
		bias += 0.1;
		for (size_t i = 0; i < Mat.ColumeSize(); i++)
			for (size_t j = 0; j < Mat.RowSize(); j++)
				Mat(i, j) = 2 * pNoise(i * step + bias, j * step + bias);
		cv::Mat tempMat(cv::Size(Mat.ColumeSize(), Mat.RowSize()), CV_32FC1);
		tempMat = Visual::OpenCV::Matrix2Mat<float>(Mat);
		tempMat += 1;
		cv::normalize(tempMat, tempMat, 0, 1, cv::NORM_MINMAX);

		cv::Mat img(tempMat.cols, tempMat.rows, CV_8UC3);

		for (size_t i = 0; i < tempMat.cols; i++)
		{
			for (size_t j = 0; j < tempMat.rows; j++)
			{
				tempMat.at<float>(i, j);
				cv::Vec3b pixel;
				pixel.val[0] = (1 - tempMat.at<float>(i, j)) * 255; // B
				pixel.val[1] = 0; // G
				pixel.val[2] = tempMat.at<float>(i, j) * 255; // R
				img.at<cv::Vec3b>(i, j) = pixel;
			}
		}
		cv::imshow("Perlin Noise Anim", img);
	}
}

cv::Mat Visual::Plot2D::Scale(const cv::Mat _mat, unsigned n)
{
	MathLib::Matrix<double> data1(_mat.cols, _mat.rows);
	MathLib::Matrix<double> data2(_mat.cols*n, _mat.rows*n);
	data1 = OpenCV::Mat2Matrix<float>(_mat);
	for (size_t i = 0; i < data2.ColumeSize(); i++)
	{
		for (size_t j = 0; j < data2.RowSize(); j++)
		{
			data2(i, j) = data1(i / n, j / n);
		}
	}
	return OpenCV::Matrix2Mat(data2);
}
