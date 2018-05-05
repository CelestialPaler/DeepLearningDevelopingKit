﻿/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	                Vector  	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

#include "Matrix.hpp"

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	// Type of Vector.
	enum class VectorType {
		Zero,
		Ones,
		Random,
		Identity
	};

	/***************************************************************************************************/
	// Class : Vector
	/// Implemented in std::vector.
	/// Specialized for deep learning purpose. (Maybe...) 
	template<class T>
	class Vector
	{
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		/// After default constructor and before use the Vector object, Init() should be involked.
		Vector(void);
		// Constructor (Using Size and Type)
		/// Specified the size of Vector.
		Vector(const size_t _n, const VectorType _type = VectorType::Zero);
		// Constructor (Using given Data)
		/// Using data from a given pointer, which is pointed to an array, to initialize the Vector.
		Vector(const std::initializer_list<int> & _list);

	public: // Initializing

		// Initializing function
		/// Initializing the Vector after defined by default constructor.
		void Init(const size_t _n, const VectorType _type = VectorType::Zero);

	public: // Arithmatic

		// Inner product function
		/// 
		static T InnerProduct(const Vector<T> & _first, const Vector<T> & _second);
		// Dot product function
		/// 
		static T DotProduct(const Vector<T> & _first, const Vector<T> & _second);
		// Outer product function
		/// 
		static T OuterProduct(const Vector<T> & _first, const Vector<T> & _second);

	public: // Quantification

		// Size function
		/// Return the size of the Vector.
		const size_t Size(void) const;
		// Sum function
		/// Add up all the element in the Vector.
		T Sum(void) const;
		// Average function
		/// Calculate the average value of all the element in the Vector.
		T Average(void) const;
		// Max function
		/// Get the value of the max element in the Vector.
		T Max(void) const;
		// Min function
		/// Get the value of the min element in the Vector.
		T Min(void) const;

	public: // Transformation

		Matrix<T> Matrixize(void);

	public: // Pointer

		// Pointer
		T * data() { return this->_data[0]; }
		// Const pointer
		const T * data() const { return this->_data[0]; }

	public: // Operator Overloading

		// "( )" operator
		/// Used for accessing the element in the Vector.
		inline T operator()(size_t _j) const
		{
			return this->_data[_j];
		}

		/// Used for referencing the element in the Vector.
		inline T & operator()(size_t _j)
		{
			return this->_data[_j];
		}

		// "<<" operator
		/// Used for streaming in format.
		friend std::ostream & operator<<(std::ostream& _outstream, Vector<T>& _vec)
		{
			_outstream << typeid(_vec).name() << " ";
			_outstream << "|";
			for (size_t j = 0; j < _vec.n; j++)
			{
				_outstream << _vec(j);
				if (j != _vec.n - 1)	_outstream << " ";
			}
			_outstream << "|" << std::endl;
			return _outstream;
		}

		// "=" operator
		Vector<T> & operator = (const Vector<T> & _other)
		{
			if (this != &_other)
				_data = _other._data;
			return (*this);
		}

		// "+" operator
		/// Addition of two Vectors.
		Vector<T> operator + (const Vector<T> & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(n);
			if (self.n != _other.n)
			{
				cerr << "ERROR : Invalid Vector Addtion!" << endl;
				return temp;
			}
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) + _other(j);
			return temp;
		}

		/// Addition of a Vector and a scalar.
		/// Add scalar to each element in the Vector.
		Vector<T> operator + (const T & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(n);
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) + _other;
			return temp;
		}

		// "+=" operator
		/// Add another Vector to this Vector.
		void operator += (const Vector<T> & _other)
		{
			Vector<T> & self = *this;
			if (self.n != _other.n)
			{
				std::cerr << "ERROR : Invalid Vector Self-Addtion!" << std::endl;
			}
			for (size_t j = 0; j < self.n; j++)
				self(j) = self(j) + _other(j);
		}

		/// Add another scalar to this Vector.
		void operator += (const T & _other)
		{
			Vector<T> & self = *this;
			for (size_t j = 0; j < self.n; j++)
				self(j) = self(j) + _other;
		}

		// "-" operator
		/// Substraction of two Vectors.
		Vector<T> operator - (const Vector<T> & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(n);
			if (self.n != _other.n)
			{
				cerr << "ERROR : Invalid Vector Substraction!" << endl;
				return temp;
			}
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) - _other(j);
			return temp;
		}

		/// Substraction of a Vector and a scalar.
		/// Substract a scalar to each element in the Vector.
		Vector<T> operator - (const T & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(n);
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) - _other;
			return temp;
		}

		// "-=" operator
		/// Substract another matrix to this Vector.
		void operator -= (const Vector<T> & _other)
		{
			Vector<T> & self = *this;
			if (self.n != _other.n)
			{
				cerr << "ERROR : Invalid Vector Self-Substraction!" << endl;
			}
			for (size_t j = 0; j < self.n; j++)
				self(j) = self(j) - _other(j);
		}

		/// Substract another scalar to this Vector.
		void operator -= (const T & _other)
		{
			Vector<T> & self = *this;
			for (size_t j = 0; j < self.n; j++)
				self(j) = self(j) - _other;
		}

		// "*" operator
		/// Multiplication of a Vector and a scalar.
		Vector<T> operator * (const T & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(n);
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) * _other;
			return temp;
		}

	private:
		std::vector<T> _data;
		size_t n;
	};
}

namespace MathLib
{
	template<class T>
	inline Vector<T>::Vector(void)
	{

	}

	template<class T>
	inline Vector<T>::Vector(const size_t _n, const VectorType _type)
	{
		Init(_n, _type);
	}

	template<class T>
	inline Vector<T>::Vector(const std::initializer_list<int> & _list)
	{
		for (auto iter1 = _list.cbegin(); iter1 != _list.cend(); ++iter1)
		{
			for (auto iter2 = (*iter1).cbegin(); iter2 != (*iter1).cend(); ++iter2)
			{
				this._data->push_pack(*iter2);
			}
		}
	}

	template<class T>
	inline void Vector<T>::Init(const size_t _n, const VectorType _type)
	{
		switch (_type)
		{
		case VectorType::Zero:
			for (size_t j = 0; j < _n; j++)
			{
				T tempElem = *new T;
				tempElem = 0.f;
				_data.push_back(tempElem);
			}
			break;
		case VectorType::Ones:
			for (size_t j = 0; j < _n; j++)
			{
				T tempElem = *new T;
				tempElem = 1.f;
				_data.push_back(tempElem);
			}
			break;
		case VectorType::Random:
			for (size_t j = 0; j < _n; j++)
			{
				T tempElem = *new T;
				tempElem = Random();
				_data.push_back(tempElem);
			}
			break;
		default:
			break;
		}
		n = _n;
	}

	template<class T>
	inline T Vector<T>::InnerProduct(const Vector<T>& _first, const Vector<T>& _second)
	{
		T temp = 0;
		if (_first.Size() != _second.Size())
			return 0;
		for (size_t i = 0; i < _first.Size(); i++)
		{
			temp += _first(i) * _second(i);
		}
		return temp;
	}

	template<class T>
	inline T Vector<T>::DotProduct(const Vector<T>& _first, const Vector<T>& _second)
	{
		return InnerProduct(_first, _second);
	}

	template<class T>
	inline const size_t Vector<T>::Size(void) const
	{
		return n;
	}

	template<class T>
	T Vector<T>::Sum(void) const
	{
		const Vector<T> & self = *this;
		T Sum = 0;
		for (size_t i = 0; i < n; i++)
		{
			Sum += self(i);
		}
		return Sum;
	}

	template<class T>
	inline T Vector<T>::Average(void) const
	{
		return Sum() / n;
	}

	template<class T>
	inline T Vector<T>::Max(void) const
	{
		const Vector<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < n; i++)
			if (self(i) > temp)
				temp = self(i);
		return temp;
	}
	
	template<class T>
	inline T Vector<T>::Min(void) const
	{
		const Vector<T> & self = *this;
		T temp = 0;
		for (size_t i = 0; i < n; i++)
			if (self(i) < temp)
				temp = self(i);
		return temp;
	}
	
	template<class T>
	inline Matrix<T> Vector<T>::Matrixize(void)
	{
		const Vector<T> & self = *this;
		Matrix<T> temp(1, n);
		for (size_t i = 0; i < n; i++)
		{
			temp(0, i) = self(i);
		}
		return temp;
	}
}
