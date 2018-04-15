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
using namespace MathLib;

class PortPointer {};

template<size_t M,size_t N>
class Port : public PortPointer
{
public:
	virtual void Set() {} = 0;
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

