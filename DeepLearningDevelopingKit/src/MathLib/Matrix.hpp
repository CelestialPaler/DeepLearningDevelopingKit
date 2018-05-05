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

	public: // Initializing

		// Initializing function
		/// Initializing the Vector after defined by default constructor.
		void Init(const size_t _n, const VectorType _type = VectorType::Zero);

	public: // Quantification

		// Size function
		/// Return the size of the Matrix.
		const size_t Size(void) const;
		// Sum function
		/// Add up all the element in the Matrix.
		T Sum(void) const;
		// Average function
		/// Calculate the average value of all the element in the Matrix.
		T Average(void) const;
		// Max function
		/// Get the value of the max element in the Matrix.
		T Max(void) const;
		// Min function
		/// Get the value of the min element in the Matrix.
		T Min(void) const;

		// Rank function
		/// Get the value of the rank in the Matrix.
		int Rank(void);

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
		friend std::ostream& operator<<(std::ostream& _outstream, Matrix<T>& _mat)
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
		std::vector<std::vector<T>> _data;
		size_t m, n;
	};

	template<class T>
	inline Matrix<T>::Matrix(const size_t _m, const size_t _n, const MatrixType _type)
	{
		for (size_t i = 0; i < _m; i++)
		{
			std::vector<T> tempVec = *new std::vector<T>;
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
	

	template<class T>
	inline T Matrix<T>::Sum(void) const
	{
		const Vector<T> & self = *this;
		T Sum = 0;
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				Sum += self(i, j);
			}
		}
		return Sum;
	}

	template<class T>
	inline T Matrix<T>::Average(void) const
	{
		return Sum()/ (m*n);
	}

	template<class T>
	inline T Matrix<T>::Max(void) const
	{
		const Vector<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				if (self(i, j) > temp)
					temp = self(i, j);
		return temp;
	}

	template<class T>
	inline T Matrix<T>::Min(void) const
	{
		const Vector<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				if (self(i, j) > temp)
					temp = self(i, j);
		return temp;
	}

	template<class T>
	inline int Matrix<T>::Rank(void)
	{
		return 0;
	}
}

