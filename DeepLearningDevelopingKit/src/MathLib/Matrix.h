/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	                Matrix   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Headerfiles
#include <iostream>
#include <vector>

// Namespaces
using namespace std;

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	// Type of Matrix.
	enum class MatrixType {
		Zero,
		Ones,
		Random,
		Identity,
		Diagonal,
		Triangle
	};

	/***************************************************************************************************/
	// Class : Matrix
	/// Implemented in std::vector.
	/// Specialized for deep learning purpose. (Maybe...) 
	template<class T>
	class Matrix
	{
	public: // Constructors

			// Default constructor
			/// Take no parameters and before use Init() should be involked.
		Matrix(void);
		// Constructor (Using Size and Type)
		/// Specified the size of vector.
		Matrix(const size_t _m, const size_t _n, const MatrixType _type = MatrixType::Zero);
		// Constructor (Using given Data)
		/// Using data from a given pointer, which is pointed to a 2D array, to initialize the matrix
		// Matrix(const T ** _data, size_t m, size_t n);

	public: // Pointers

			// Pointer
		T * data() { return this->_data[0]; }
		// Const pointer
		const T * data() const { return this->_data[0]; }

	public: // Operator Overloading 

			// "( )" operator
			/// Used for accessing the element in the Matrix.
		inline T operator()(size_t _i, size_t _j) const
		{
			return this->_data[_i][_j];
		}

		/// Used for referencing the element in the Matrix.
		inline T & operator()(size_t _i, size_t _j)
		{
			return this->_data[_i][_j];
		}

		// "<<" operator
		/// Used for streaming in format.
		friend ostream& operator<<(ostream& _outstream, Matrix<T>& _mat)
		{
			_outstream << typeid(_mat).name() << endl;
			for (size_t i = 0; i < _mat.m; i++)
			{
				_outstream << "|";
				for (size_t j = 0; j < _mat.n; j++)
				{
					_outstream << _mat(i, j);
					if (j != _mat.n - 1)	_outstream << " ";
				}
				_outstream << "|" << endl;
			}
			return _outstream;
		}

		// "=" operator
		Matrix<T> & operator = (const Matrix<T> & _other)
		{
			if (this != &_other)
				_data = _other._data;
			return (*this);
		}

		// "+" operator
		/// Addition of two Matrixs.
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
		/// Add scalar to each element in the Matrix.
		Matrix<T> operator + (const T & _other) const
		{
			const Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) = self(i, j) + _other;
			return temp;
		}

		// "+=" operator
		/// Add another Matrix to this Matrix.
		void operator += (const Matrix<T> & _other)
		{
			Matrix<T> & self = *this;
			if (self.m != _other.m || self.n != _other.n)
			{
				cerr << "ERROR : Invalid Matrix Addtion!" << endl;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					self(i, j) = self(i, j) + _other(i, j);
		}

		/// Add another scalar to this Matrix.
		void operator += (const T & _other)
		{
			Matrix<T> & self = *this;
			if (self.m != _other.m || self.n != _other.n)
			{
				cerr << "ERROR : Invalid Matrix Addtion!" << endl;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					self(i, j) = self(i, j) + _other;
		}

		// "-" operator
		/// Substraction of two Matrixs.
		Matrix<T> operator - (const Matrix<T> & _other) const
		{
			const Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			if (self.m != _other.m || self.n != _other.n)
			{
				cerr << "ERROR : Invalid Matrix Substraction!" << endl;
				return temp;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) = self(i, j) - _other(i, j);
			return temp;
		}

		/// Substraction of a matrix and a scalar.
		/// Substract a scalar to each element in the matrix.
		Matrix operator - (const T & _other) const
		{
			const Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) = self(i, j) - _other;
			return temp;
		}

		// "-=" operator
		/// Substract another matrix to this matrix.
		void operator -= (const Matrix<T> & _other)
		{
			Matrix<T> & self = *this;
			if (self.m != _other.m || self.n != _other.n)
			{
				cerr << "ERROR : Invalid Matrix Addtion!" << endl;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					self(i, j) = self(i, j) - _other(i, j);
		}

		/// Substract scalar to each element in this matrix.
		void operator -= (const T & _other)
		{
			Matrix<T> & self = *this;
			Matrix<T> temp(m, n);
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					self(i, j) = self(i, j) - _other;
		}

		// "*" operator
		/// Multiplication of two matrixs.
		Matrix<T> operator * (const Matrix<T> & _other) const
		{
			const Matrix<T> &self = *this;
			Matrix<T> temp(self.m, _other.n);
			if (self.n != _other.m)
			{
				cerr << "ERROR : Invalid Matrix Addtion!" << endl;
				return temp;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t k = 0; k < _other.m; k++)
					for (size_t j = 0; j < self.n; j++)
						temp(i, k) += self(i, j) * _other(j, k);
			return temp;
		}

		// "*" operator
		/// Multiply a scalar to each element in the matrix.
		Matrix<T> operator * (const T & _other) const
		{
			const Matrix<T> &self = *this;
			Matrix<T> temp(self.m, self.n);
			for (size_t i = 0; i < self.m; i++)
				for (size_t j = 0; j < self.n; j++)
					temp(i, j) += self(i, j) * _other;
			return temp;
		}

	private:
		vector<vector<T>> _data;
		size_t m, n;
	};

	template<class T>
	inline Matrix<T>::Matrix(const size_t _m, const size_t _n, const MatrixType _type)
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
}

