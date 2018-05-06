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
	this->_weight.Init(_inputNum, 1, MathLib::MatrixType::Random);
	this->_bias = Random();
}

void Regression::MultivariateLinearRegression::Train(void)
{
	MathLib::Matrix<double> w_hat(_weight.ColumeSize() + 1, 1);
	for (size_t i = 0; i < _weight.ColumeSize(); i++)
	{
		w_hat(i, 0) = _weight(i, 0);
	}
	w_hat(_weight.ColumeSize(), 0) = _bias;

	std::cout << _weight << _bias << w_hat << std::endl;
}