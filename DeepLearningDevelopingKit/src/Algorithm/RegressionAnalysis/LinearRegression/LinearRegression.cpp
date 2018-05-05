/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      Linear Regression     	                                                       */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "LinearRegression.h"

Regression::LinearRegression::LinearRegression()
{
}

Regression::LinearRegression::~LinearRegression()
{
}

void Regression::LinearRegression::Train(void)
{
	switch (this->_method)
	{
	case LinearRegressionMethod::OrdinaryLeastSquares:
		OrdinaryLeastSquares();
		break;
	default:
		OrdinaryLeastSquares();
		break;
	}
}

void Regression::LinearRegression::Test(void)
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

double Regression::LinearRegression::Predict(void)
{
	return 0;
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

void Regression::LinearRegression::SetMethod(const LinearRegressionMethod _method)
{
	this->_method = _method;
}

void Regression::LinearRegression::OrdinaryLeastSquares(void)
{
	double sumX = 0; 
	double sumY = 0;
	double 	sumXSquared = 0;
	double 	sumXY = 0;

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
