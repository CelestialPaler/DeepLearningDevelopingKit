/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	       Activation Function   	                                                       */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/************************************************************************************************************/
// Activation functions 
/// Activation Function Enums
enum class ActivationFunction {
	SigmoidFunc,
	ReLUFunc,
	LeakyReLUFunc,
	ELUFunc,
	SinhFunc,
	CoshFunc,
	TanhFunc,
	SoftplusFunc
}; 

// Sigmoid Function
/// Logistic activation function
const double A = 1;
const double B = 1;
inline double Sigmoid(double x) {
	return A / (1 + exp(-x / B));
}

// Rectified Linear Units (ReLU)
/// non-negative rectification
inline double ReLU(double x) {
	return x > 0 ? x : 0;
}

// Leaky-ReLU
/// Advanced ReLU
const double C = 0.1;
inline double LeakyReLU(double x) {
	return x > 0 ? x : C * x;
}

// ELU
/// A combination of Sigmoid and ReLU
const double D = 0.25;
inline double ELU(double x) {
	return x > 0 ? x : D * (exp(x) - 1);
}

// Hyperbolic sinh Function
inline double sinh(double x) {
	return (exp(x) - exp(-x)) / 2;
}

// Hyperbolic cosh Function
inline double cosh(double x) {
	return (exp(x) + exp(-x)) / 2;
}

// Hyperbolic tanh Function
inline double tanh(double x) {
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

// Softplus Function
/// A smoother version of ReLU
inline double Softplus(double x) {
	return logf(1 + exp(x));
}

/************************************************************************************************************/
/* Loss functions */
enum LossFunction {
	MESFunc,
	ZeroOneFunc,
	CECFunc
};

/// Variance loss function 
inline double MES(double _predict, double _expectation) {
	return pow(_predict - _expectation, 2) / 2;
}

/// Zero-One loss function
inline double ZeroOne(double x) {
	return x > 0 ? 1.f : 0.f;
}

/// Cross-Entropy Cost Function
inline double CEC(double _predict, double _expectation) {
	return -1 * (_expectation * log(_predict) + (1 - _expectation)*log(1 - _predict));
}

