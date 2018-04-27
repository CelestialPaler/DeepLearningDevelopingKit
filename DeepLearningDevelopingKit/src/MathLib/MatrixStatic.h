/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	           Matrix Static   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include "MathDef.h"

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
/// Specialized for deep learning purpose. Emm might be true ... or not ... XD whatever!
namespace MathLibStatic
{
	/***************************************************************************************************/
	// Class : Matrix
	/// A matrix class, which is implemented in template.
	/// T is the type of element stored in the matrix , M and N is the size(shape) of the matrix.
	/// While constructing a matrix, a MatrixType is needed though which is not a must.
	template<class T, size_t M, size_t N>
	class Matrix
	{
		/***************************************************************************************************/
		// Constructors
	public:
		// Default constructor
		/// Take no parameters, set elements to 0.
		Matrix(void);
		// Constructor (Type)
		/// Specified a type of matrix.
		Matrix(Type _type);
		// Constructor (Data)
		/// Using data from a given pointer, which is pointed to a 2D array, to initialize the matrix
		Matrix(const T _data[M][N]);

		/***************************************************************************************************/
		// Operator overload
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

		// "=" operator
		Matrix<T, M, N> & operator = (const Matrix<T, M, N> & _other)
		{
			if (this != &_other)
				memcpy(this->_data, _other._data, sizeof(_data));
			return (*this);
		}

		// "+" operator
		/// Addition of two matrixs.
		Matrix operator + (const Matrix & _other)
		{
			Matrix<T, M, N> temp;
			const Matrix<T, M, N> & self = *this;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					temp(i, j) = self(i, j) + _other(i, j);
			return temp;
		}

		/// Addition of a matrix and a scalar.
		/// Add scalar to each element in the matrix.
		Matrix operator + (const T & _other)
		{
			Matrix<T, M, N> temp;
			const Matrix<T, M, N> & self = *this;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					temp(i, j) = self(i, j) + _other;
			return temp;
		}

		// "-" operator
		Matrix operator - (const Matrix & _other)
		{
			Matrix<T, M, N> temp;
			const Matrix<T, M, N> & self = *this;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					temp(i, j) = self(i, j) - _other(i, j);
			return temp;
		}

		Matrix operator - (const T & _other)
		{
			Matrix<T, M, N> temp;
			const Matrix<T, M, N> & self = *this;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					temp(i, j) = self(i, j) - _other;
			return temp;
		}

		// "*" operator
		template<size_t P>
		Matrix<T, M, P> operator * (const Matrix<T, M, P> &_other) const
		{
			const Matrix<T, M, N> &self = *this;
			Matrix<T, M, P> temp;
			for (size_t i = 0; i < M; i++)
				for (size_t k = 0; k < P; k++)
					for (size_t j = 0; j < N; j++)
						temp(i, k) += self(i, j) * _other(j, k);
			return temp;
		}

		// "*" operator
		Matrix<T, M, N> operator * (const T & _other) const
		{
			const Matrix<T, M, N> &self = *this;
			Matrix<T, M, N> temp;
			for (size_t i = 0; i < M; i++)
				for (size_t j = 0; j < N; j++)
					temp(i, j) += self(i, j) * _other;
			return temp;
		}

		/***************************************************************************************************/
		// Used for debugging
	public:
		void PrintToConsole(void);

		/***************************************************************************************************/
		// private members
	public:
		T _data[M][N];
	};

	/***************************************************************************************************/
	// Class : NodeMatrix
	template<class T, size_t M, size_t N>
	class NodeMatrix
	{
	public:
		/***************************************************************************************************/
		// Constructors
	public:

	private:
		T _nodes[M][N];
	};
}

/***************************************************************************************************/
// Implement
namespace MathLibStatic
{
	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(void)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				this->_data[i][j] = 0;
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(Type _type)
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				this->_data[i][j] = 0;
	}

	template<class T, size_t M, size_t N>
	inline Matrix<T, M, N>::Matrix(const T _data[M][N])
	{
		for (size_t i = 0; i < M; i++)
			for (size_t j = 0; j < N; j++)
				this->_data[i][j] = _data[i][j];
	}

	// Used for debugging
	template<class T, size_t M, size_t N>
	inline void MathLibStatic::Matrix<T, M, N>::PrintToConsole(void)
	{
		for (size_t i = 0; i < M; i++)
		{
			cout << "|";
			for (size_t j = 0; j < N; j++)
				cout << _data[i][j] << " ";
			cout << "|" << endl;
		}
		cout << endl;
	}
}