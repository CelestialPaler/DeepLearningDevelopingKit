/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        				              Port     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\MathLib\MathLib.h"

// Name space
// Name space
#ifdef USING_STATIC_MATHLIB
using namespace MathLibStatic;
#endif // USING_STATIC_MATHLIB
#ifdef USING_DYNAMIC_MATHLIB
using namespace MathLib;
#endif // USING_STATIC_MATHLIB

class PortPointer {};

template<size_t M, size_t N>
class Port : public PortPointer
{
public:
	virtual void Set() {};
};

template<size_t M, size_t N>
class InputPort : public Port<M, N>
{
public:
	void Set(const Matrix<double,M,N> & _data)
	{
		this->_data = _data;
	}
private:
	Matrix<double, M, N> _data;
};

template<size_t M, size_t N>
class OutputPort : public Port<M, N>
{
public:
	void Set(const Matrix<double, M, N> & _data)
	{
		this->_data = _data;
	}
private:
	Matrix<double, M, N> _data;
};

