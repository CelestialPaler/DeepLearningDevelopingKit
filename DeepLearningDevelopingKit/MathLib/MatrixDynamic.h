/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	         Matrix Dynamic   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

/***************************************************************************************************
 * Dynamic Matrix Lib, which means the size(shape) of Matrix is changeable. Implemented in 
 * std::vector<T> gives the matrix with flexbility.
 */

// Headr Files
#include <iostream>
#include <vector>

#include "MathDef.h"

// Namespaces
using namespace std;

/***************************************************************************************************
* Namespace : MathLibDynamic
* Provide mathematic support and calculation tools for different algorithms.
* Specialized for deep learning purpose.
*/
namespace MathLibDynamic
{
	/***************************************************************************************************
	* Class : Matrix
	* 
	*/
	template<class T>
	class Matrix
	{
	public:
		Matrix(const size_t _m, const size_t _n);
		Matrix(Type );

	public:
		// Pointer
		T * data()
		{
			return this->_data[0];
		}

		// Const pointer
		const T * data() const
		{
			return this->_data[0];
		}

		// "( )" operator
		/// used for accessing the elemnet in the matrix.
		inline T operator()(size_t _i, size_t _j) const
		{
			return this->_data[_i][_j];
		}

		/// Used for referencing the element in the matrix.
		inline T & operator()(size_t _i, size_t _j)
		{
			return this->_data[_i][_j];
		}

		friend ostream& operator<<(ostream& _os, Matrix<T>& _mat)
		{
			_os << typeid(_mat).name() << endl;
			for (size_t i = 0; i < _mat.m; i++)
			{
				_os << "|";
				for (size_t j = 0; j < _mat.n; j++)
				{
					_os << _mat(i, j);
					if (j != _mat.n - 1)	_os << " ";
				}
				_os << "|" << endl;
			}
			return _os;
		}

		// "=" operator
		Matrix<T> & operator = (const Matrix<T> & _other)
		{
			if (this != &_other)
				_data = _other._data;
			return (*this);
		}

		// "+" operator
		/// Addition of two matrixs.
		Matrix<T> operator + (const Matrix<T> & _other) const
		{
			const Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			if (self.m != _other.m || self.n != _other.n)
			{
				cerr << "ERROR : Invalid Matrix Addtion!" << endl;
				return temp;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) = self(i, j) + _other(i, j);
			return temp;
		}

		/// Addition of a matrix and a scalar.
		/// Add scalar to each element in the matrix.
		Matrix operator + (const T & _other) const
		{
			const Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) = self(i, j) + _other;
			return temp;
		}

		/***************************************************************************************************/
		// Used for debugging
	public:
		void PrintToConsole(void);

	private:
		vector<vector<T>> _data;
		size_t m, n;
	};

	template<class T>
	inline Matrix<T>::Matrix(const size_t _m, const size_t _n)
	{
		for (size_t i = 0; i < _m; i++)
		{
			vector<T> tempVec = *new vector<T>;
			for (size_t j = 0; j < _n; j++)
			{
				T tempElem = *new T;
				tempElem = 0;
				tempVec.push_back(tempElem);
			}
			this->_data.push_back(tempVec);
		}
		m = _m;
		n = _n;
	}

	// Used for debugging
	template<class T>
	inline void MathLibDynamic::Matrix<T>::PrintToConsole(void)
	{
		for (size_t i = 0; i < m; i++)
		{
			cout << "|";
			for (size_t j = 0; j < n; j++)
				cout << _data[i][j] << " ";
			cout << "|" << endl;
		}
		cout << endl;
	}
}

