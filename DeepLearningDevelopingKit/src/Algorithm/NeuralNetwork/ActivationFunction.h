﻿/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	       Activation Function   	                                                       */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include <iostream>
#include <vector>
#include <cmath>

/************************************************************************************************************/
// Activation functions 
/// Activation Function Enums
enum class ActivationFunction {
	Linear,
	Sigmoid,
	ReLU,
	LeakyReLU,
	ELU,
	Sinh,
	Cosh,
	Tanh,
	Softplus,
	Custom
}; 

enum class ActivationFunctionDerivative {
	LinearDerivative,
	SigmoidDerivative,
	ReLUDerivative,
	LeakyReLUDerivative,
	ELUDerivative,
	SinhDerivative,
	CoshDerivative,
	TanhDerivative,
	SoftplusDerivative,
	CustomDerivative
};

//Linear Function
const double K = 1;
inline double Linear(double x) {
	return x * K;
}

//Linear Derivative Function
inline double LinearDerivative(double x) {
	return K;
}

// Sigmoid Function
/// Logistic activation function
const double A = 1;
const double B = 1;
inline double Sigmoid(double x) {
	return A / (1 + exp(-x / B));
}

// Sigmoid Derivative Function
/// Logistic activation derivative function
inline double SigmoidDerivative(double x) {
	return x * (1 - x);
}

// Rectified Linear Units (ReLU)
/// non-negative rectification
inline double ReLU(double x) {
	return x > 0 ? x : 0;
}

// Rectified Linear Units (ReLU)
/// non-negative rectification
inline double ReLUDerivative(double x) {
	return x > 0 ? 1 : 0;
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
//inline double sinh(double x) {
//	return (exp(x) - exp(-x)) / 2;
//}

// Hyperbolic cosh Function
//inline double cosh(double x) {
//	return (exp(x) + exp(-x)) / 2;
//}

// Hyperbolic tanh Function
//inline double tanh(double x) {
//	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
//}

// Softplus Function
/// A smoother version of ReLU
inline double Softplus(double x) {
	return logf(1 + exp(x));
}


