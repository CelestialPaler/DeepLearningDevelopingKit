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
#include <iomanip>
#include <cmath>

#include "MathLibError.h"
#include "MathTool.hpp"
#include "Vector.hpp"

/***************************************************************************************************/
// Namespace : MathLib
/// Provide basic mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	// Type of Matrix.
	enum class MatrixType {
		Zero,
		Ones,
		Random,
		Identity
	};

	// Size of Matrix.
	struct Size
	{
		Size() = default;
		Size(size_t _m, size_t _n) : m(_m), n(_n) {}
		size_t m;
		size_t n;
	};

	/***************************************************************************************************/
	// Class : Matrix
	/// Implemented in std::vector.
	/// Specialized for mechine learning purpose.
	template<class T>
	class Matrix
	{
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		/// After default constructor and before use the Matrix object, Init() should be involked.
		Matrix(void);
		// Constructor (Using Size and Type)
		/// Specified the size of Matrix.
		Matrix(const size_t _m, const size_t _n, const MatrixType _type = MatrixType::Zero);
		// Constructor (Using given Data)
		/// Using data from a given pointer, which is pointed to a 2D array, to initialize the Matrix.
		Matrix(const std::initializer_list<int> & _list);
		// Copy constructor
		Matrix(const Matrix& _mat);

		~Matrix() {
			for (size_t i = 0; i < _data.size(); i++)
			{
				_data.at(i).clear();
			}
			_data.clear();
		}

	public: // Initializing

		// Initializing function
		/// Initializing the Matrix after defined by default constructor.
		void Init(const size_t _m, const size_t _n, const MatrixType _type = MatrixType::Zero);

	public: // Quantification

		// Size function
		/// Return the size of the Matrix.
		inline const size_t ColumeSize(void) const { return m; }
		inline const size_t RowSize(void) const { return n; }
		inline const Size GetSize(void) const { return size; }
		// Sum function
		/// Add up all the element in the Matrix.
		const T Sum(void) const;
		// Average function
		/// Calculate the average value of all the element in the Matrix.
		const T Average(void) const;
		// Max function
		/// Get the value of the max element in the Matrix.
		const T Max(void) const;
		// Min function
		/// Get the value of the min element in the Matrix.
		const T Min(void) const;

	public: // Advanced Quantification

		//	Determinant function
		/// Calcutate the determinant of the Matrix.
		const T Determinant(void) const;
		// Trace
		/// Calcutate the trace of the Matrix.
		const T Trace(void) const;
		// Cofactor function
		/// Calcutate the cofactor of the Matrix.
		const T Cofactor(const size_t _i, const size_t _j) const;
		// Algebraic Cofactor function
		/// Calcutate the algebraic cofactor of the Matrix.
		const T AlgebraicCofactor(const size_t _i, const size_t _j) const;
		// Rank function
		/// Calcutate the rank of the Matrix.
		const unsigned int Rank(void) const;
		// 1-Norm
		/// Calcutate the 1-norm of the Matrix.
		const T OneNorm(void) const;
		// Forbenivs Norm
		/// Calcutate the Forbenivs norm of the Matrix.
		const T ForbenivsNorm(void) const;
		// P-Norm
		/// Calcutate the P-Norm of the Matrix.
		const T PNorm(const unsigned int _p) const;
		
	public: // Transformation

		// Clear
		void Clear(void);
		// Gaussian Elimination
		const Matrix<T> GaussianElimination(void) const;
		// Transposition matrix
		const Matrix<T> Transpostion(void) const;
		// Adjoint matrix
		const Matrix<T> Adjoint(void) const;
		// Inverse matrix
		const Matrix<T> Inverse(void) const;

	private: // Inner woking functions

		// Swap two columns
		void SwapColumn(const size_t _i, const size_t _j);
		// Resize the matrix
		void Resize(const size_t _m, const size_t _n);

	public: // Pointers

		// Pointer
		T * Data() { return this->_data[0]; }
		// Const pointer
		const T * Data() const { return this->_data[0]; }

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
			_outstream << typeid(_mat).name() << std::endl;
			_outstream << std::fixed << std::setprecision(3);
			for (size_t i = 0; i < _mat.m; i++)
			{
				_outstream << "|";
				for (size_t j = 0; j < _mat.n; j++)
				{
					_outstream << _mat(i, j);
					if (j != _mat.n - 1)	_outstream << " ";
				}
				_outstream << "|" << std::endl;
			}
			return _outstream;
		}

		// "=" operator
		Matrix<T> & operator = (const Matrix<T> & _other)
		{
			if (this != &_other)
			{
				_data = _other._data;
				size = _other.size;
				m = _other.m;
				n = _other.n;
			}
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
				std::cerr << "ERROR : Invalid Matrix Addtion!" << std::endl;
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
				std::cerr << "ERROR : Invalid Matrix Addtion!" << std::endl;
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
				std::cerr << "ERROR : Invalid Matrix Addtion!" << std::endl;
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
				std::cerr << "ERROR : Invalid Matrix Addtion!" << std::endl;
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
				std::cerr << "ERROR : Invalid Matrix Addtion!" << std::endl;
				return temp;
			}
			for (size_t i = 0; i < self.m; i++)
				for (size_t k = 0; k < _other.n; k++)
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
		Size size;
	};
}

namespace MathLib
{
	// Default constructor
	/// Take no parameters.
	/// After default constructor and before use the Matrix object, Init() should be involked.
	template<class T>
	inline Matrix<T>::Matrix(void)
	{

	}

	// Constructor (Using Size and Type)
	/// Specified the size of Matrix.
	template<class T>
	inline Matrix<T>::Matrix(const size_t _m, const size_t _n, const MatrixType _type)
	{
		Init(_m, _n, _type);
	}

	// Constructor (Using given Data)
	/// Using data from a given pointer, which is pointed to a 2D array, to initialize the Matrix.
	template<class T>
	inline Matrix<T>::Matrix(const std::initializer_list<int>& _list)
	{
	}

	// Copy constructor
	template<class T>
	inline Matrix<T>::Matrix(const Matrix & _mat)
	{
		this->_data = _mat._data;
		this->size = _mat.size;
		this->m = _mat.m;
		this->n = _mat.n;
	}

	// Initializing function
	/// Initializing the Matrix after defined by default constructor.
	template<class T>
	inline void Matrix<T>::Init(const size_t _m, const size_t _n, const MatrixType _type)
	{
		switch (_type)
		{
		case MatrixType::Zero:
			for (size_t i = 0; i < _m; i++)
			{
				std::vector<T> tempVec;
				for (size_t j = 0; j < _n; j++)
				{
					T tempElem = 0.f;
					tempVec.push_back(tempElem);
				}
				_data.push_back(tempVec);
			}
			break;
		case MatrixType::Ones:
			for (size_t i = 0; i < _m; i++)
			{
				std::vector<T> tempVec;
				for (size_t j = 0; j < _n; j++)
				{
					T tempElem = 1.f;
					tempVec.push_back(tempElem);
				}
				_data.push_back(tempVec);
			}
			break;
		case MatrixType::Random:
			for (size_t i = 0; i < _m; i++)
			{
				std::vector<T> tempVec;
				for (size_t j = 0; j < _n; j++)
				{
					T tempElem = Random();
					tempVec.push_back(tempElem);
				}
				_data.push_back(tempVec);
			}
			break;
		case MatrixType::Identity:
			for (size_t i = 0; i < _m; i++)
			{
				std::vector<T> tempVec;
				for (size_t j = 0; j < _n; j++)
				{
					T tempElem;
					if (i == j)
						tempElem = 1.f;
					else
						tempElem = 0.f;
					tempVec.push_back(tempElem);
				}
				_data.push_back(tempVec);
			}
			break;
		default:
			break;
		}
		m = _m;
		n = _n;
		size.m = _m;
		size.n = _n;
	}

	template<class T>
	inline const T Matrix<T>::Sum(void) const
	{
		const Matrix<T> & self = *this;
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
	inline const T Matrix<T>::Average(void) const
	{
		return Sum() / (m*n);
	}

	template<class T>
	inline const T Matrix<T>::Max(void) const
	{
		const Matrix<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				if (self(i, j) > temp)
					temp = self(i, j);
		return temp;
	}

	template<class T>
	inline const T Matrix<T>::Min(void) const
	{
		const Matrix<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < m; i++)
			for (size_t j = 0; j < n; j++)
				if (self(i, j) > temp)
					temp = self(i, j);
		return temp;
	}

	template<class T>
	inline const T Matrix<T>::Determinant(void) const
	{
		Matrix<T> tempMat = *this;
		int iter = 0;
		T det = 1, multiple;

		for (size_t i = 0; i < n; i++)
		{
			if (tempMat(i, i) == 0)
			{
				for (size_t j = i; j < n; j++)
				{ 
					if (tempMat(j, i) != 0)
					{
						tempMat.SwapColumn(i, j);
						iter++;
					}
				}
			}
			else
			{
				for (size_t k = i + 1; k < n; k++)
				{
					multiple = -1 * tempMat(k, i) / tempMat(i, i);
					for (size_t u = 0; u < n; u++)
						tempMat(k, u) += tempMat(i, u) * multiple;
				}
			}
		}

		det = tempMat.Trace();
		if (iter % 2)
			det = -det;
		return det;
	}

	template<class T>
	inline const T Matrix<T>::Trace(void) const
	{
		const Matrix<T> & self = *this;
		T trace = 1;
		for (size_t i = 0; i < n; i++)
		{
			trace = trace * self(i, i);
		}
		return trace;
	}

	template<class T>
	inline void Matrix<T>::Clear(void)
	{
		Matrix<T> & self = *this;
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				self(i, j) = 0.f;
			}
		}
	}

	template<class T>
	inline const Matrix<T> Matrix<T>::GaussianElimination(void) const
	{
		Matrix<T> tempMat = *this;
		T multiple;

		for (size_t i = 0; i < n; i++)
		{
			if (tempMat(i, i) == 0)
			{
				for (size_t j = i; j < n; j++)
				{
					if (tempMat(j, i) != 0)
					{
						tempMat.SwapColumn(i, j);
					}
				}
			}
			else
			{
				for (size_t k = i + 1; k < n; k++)
				{
					multiple = -1 * tempMat(k, i) / tempMat(i, i);
					for (size_t u = 0; u < n; u++)
						tempMat(k, u) += tempMat(i, u) * multiple;
				}
			}
		}
		return tempMat;
	}

	template<class T>
	inline const Matrix<T> Matrix<T>::Transpostion(void) const
	{
		const Matrix<T> & self = *this;
		Matrix<T> tempMat(n, n);
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				tempMat(i, j) = self(j, i);
		return tempMat;
	}

	template<class T>
	inline const Matrix<T> Matrix<T>::Adjoint(void) const
	{
		Matrix<T> self = *this;
		Matrix<T> tempMat(n, n);
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				tempMat(i, j) = self.AlgebraicCofactor(j, i);
		return tempMat;
	}

	template<class T>
	inline const Matrix<T> Matrix<T>::Inverse(void) const
	{
		Matrix<T> self = *this;
		Matrix<T> tempMat(n, n);
		tempMat = self.Adjoint() * (1 / self.Determinant());
		return tempMat;
	}

	template<class T>
	inline const T MathLib::Matrix<T>::Cofactor(const size_t _i, const size_t _j) const
	{
		Matrix<T> tempMat = *this;
		auto iter1 = tempMat._data.begin() + _i;
		tempMat._data.erase(iter1);
		for (size_t i = 0; i < m - 1; i++)
		{
			auto iter2 = tempMat._data.at(i).begin() + _j;
			tempMat._data.at(i).erase(iter2);
		}
		tempMat.Resize(m - 1, n - 1);
		return tempMat.Determinant();
	}

	template<class T>
	inline const T MathLib::Matrix<T>::AlgebraicCofactor(const size_t _i, const size_t _j) const
	{
		T temp = Cofactor(_i, _j);
		if (temp<DBL_EPSILON && temp >(-1)*DBL_EPSILON)
			return 0.f;
		else if ((_i + _j) % 2 == 0)
			return temp;
		else
			return (-1) * temp;
	}

	template<class T>
	inline const unsigned int Matrix<T>::Rank(void) const
	{
		Matrix<T> tempMat = *this;
		tempMat = tempMat.GaussianElimination();
		int rank = 0;
		for (size_t i = 0; i < n; i++)
			if (tempMat(i, i)!=0)
				rank++;

		return rank;
	}

	template<class T>
	inline const T Matrix<T>::OneNorm(void) const
	{
		const Matrix<T> & self = *this;
		T tempMax{0.f}, sum{0.f};
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
				sum += self(i, j);
			if (sum>tempMax)
				tempMax = sum;
			sum = 0;
		}
		return tempMax;
	}

	template<class T>
	inline const T Matrix<T>::ForbenivsNorm(void) const
	{
		const Matrix<T> & self = *this;
		T sum{ 0.f };
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				sum += self(i, j) * self(i, j);
		return std::sqrtf(sum);
	}

	template<class T>
	inline const T Matrix<T>::PNorm(const unsigned int _p) const
	{
		const Matrix<T> & self = *this;
		T sum{ 0.f };
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				sum += std::powf(self(i, j), _p);
		return std::powf(sum, 1 / _p);
	}

	template<class T>
	inline void Matrix<T>::SwapColumn(const size_t _i, const size_t _j)
	{
		swap(_data.at(_i), _data.at(_j));
	}

	template<class T>
	inline void Matrix<T>::Resize(const size_t _m, const size_t _n)
	{
		m = _m;
		n = _n;
	}
}
