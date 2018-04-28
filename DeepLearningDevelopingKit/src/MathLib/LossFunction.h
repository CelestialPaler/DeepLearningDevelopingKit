/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Loss Function   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <cmath>

/************************************************************************************************************/
/* Loss functions */
enum class LossFunction {
	MES,
	ZeroOne,
	CEC
};

enum class LossFunctionDerivative {
	MESDerivative,
	ZeroOneDerivative,
	CECDerivative
};

// Variance loss function 
inline double MES(double _predict, double _expectation) {
	return (_expectation - _predict) * (_expectation - _predict);
}

// Variance loss function 
inline double MESDerivative(double _predict, double _expectation) {
	return 2 * (_expectation - _predict);
}

// Zero-One loss function
inline double ZeroOne(double x) {
	return x > 0 ? 1.f : 0.f;
}

// Cross-Entropy Cost Function
inline double CEC(double _predict, double _expectation) {
	return -1 * (_expectation * log(_predict) + (1 - _expectation)*log(1 - _predict));
}