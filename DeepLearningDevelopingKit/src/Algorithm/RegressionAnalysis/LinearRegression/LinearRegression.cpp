/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      Linear Regression     	                                                       */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "LinearRegression.h"

Regression::LinearRegression::LinearRegression(void)
{
	this->_weight = 0.f;
	this->_bias = 0.f;
}

void Regression::LinearRegression::Train(void)
{
	OrdinaryLeastSquares();
}

void Regression::LinearRegression::Test(void) const
{
	size_t testSetSize = _testset->GetSize();
	for (int i = 0; i < testSetSize; i++)
	{
		Data::NumericSet::Sample sample = _testset->GetSample(i);
		double x = sample.first(0);
		double predict = _weight * x + _bias;
		double y = sample.second(0);
	}
}

const double Regression::LinearRegression::Predict(const double _x) const 
{
	double predict = _weight * _x + _bias;
	return predict;
}

void Regression::LinearRegression::SetTrainSet(Data::NumericSet * _trainset)
{
	this->_trainset = _trainset;
}

void Regression::LinearRegression::SetTestSet(Data::NumericSet * _testset)
{
	this->_testset = _testset;
}

void Regression::LinearRegression::SetValidationSet(Data::NumericSet * _validationset)
{
	this->_validationset = _validationset;
}

void Regression::LinearRegression::OrdinaryLeastSquares(void)
{
	double sumX{ 0.f };
	double sumY{ 0.f };
	double 	sumXSquared{ 0.f };
	double 	sumXY{ 0.f };

	size_t tarinsetSize = _trainset->GetSize();
	for (int i = 0; i < tarinsetSize; i++)
	{
		Data::NumericSet::Sample sample = _trainset->GetSample(i);
		double x = sample.first(0);
		double y = sample.second(0);
		sumX += x;
		sumY += y;
		sumXSquared += x * x;
		sumXY += x * y;
	}

	if (fabs(tarinsetSize * sumXSquared - sumX * sumX) > DBL_EPSILON) 
	{
		this->_weight = (tarinsetSize * sumXY - sumY * sumX) / (tarinsetSize * sumXSquared - sumX * sumX);
		this->_bias = (sumXSquared * sumY - sumX * sumXY) / (tarinsetSize * sumXSquared - sumX * sumX);
	}
	else 
	{
		this->_weight = 0;
		this->_bias = 0;
	}
}

Regression::MultivariateLinearRegression::MultivariateLinearRegression(const size_t _inputNum)
{
	this->_theta.Init(_inputNum + 1, 1, MathLib::MatrixType::Random);
}

void Regression::MultivariateLinearRegression::Train(void)
{
	static const double learn_rate{ 0.001 };
	MathLib::Matrix<double> X(_trainset->GetSize(), _theta.ColumeSize());
	MathLib::Matrix<double> y_lable(_trainset->GetSize(), 1);
	for (size_t i = 0; i < _trainset->GetSize(); i++)
	{
		Data::NumericSet::Sample sample = _trainset->GetSample(i);
		for (size_t j = 0; j < sample.first.Size(); j++)
			X(i, j) = sample.first(j);
		X(i, sample.first.Size()) = 1;
		y_lable(i, 0) = sample.second(0);
	}
	MathLib::Matrix<double> temp(X.ColumeSize(), _theta.RowSize());

	MathLib::Matrix<double> sum(_theta.ColumeSize(), 1);
	do
	{
		for (size_t i = 0; i < _theta.ColumeSize(); i++)
		{
			sum(i, 0) = 0;
			for (size_t j = 0; j < X.ColumeSize(); j++)
				sum(i, 0) += (temp(j, 0) - y_lable(j, 0)) * X(j, i) / X.ColumeSize();
		}

		_theta -= sum * learn_rate;
		temp = X * _theta;
	} while (LossFunction(temp, y_lable) > 0.1);
}

void Regression::MultivariateLinearRegression::Test(void)
{
	std::cout << "y = " << _theta(0, 0) << " x1 + " << _theta(1, 0) << " x2 + " << _theta(2, 0) << std::endl;
	std::cout << "Predict : " << _theta(0, 0) * 2.3659 + _theta(1, 0) * 6.3265 + _theta(2, 0) << "    Label : " << 2.3659 + 6.3265 << std::endl;
}

void Regression::MultivariateLinearRegression::SetTrainSet(Data::NumericSet * _trainset)
{
	this->_trainset = _trainset;
}

const double Regression::MultivariateLinearRegression::LossFunction(const MathLib::Matrix<double>& _predict, const MathLib::Matrix<double>& _lable) const
{
	double sum{ 0.f };
	for (size_t i = 0; i < _predict.ColumeSize(); i++)
	{
		sum += (_predict(i, 0) - _lable(i, 0)) * (_predict(i, 0) - _lable(i, 0)) / _predict.ColumeSize();
	}
	return sum;
}
