/***************************************************************************************************/
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

#include "MathDef.h"

// Namespaces
using namespace std;

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	/***************************************************************************************************/
	// Class : Vector
	/// Implemented in std::vector.
	/// Specialized for deep learning purpose. (Maybe...) 
	template<class T>
	class Vector
	{
	public: // Constructors

		// Default constructor
		/// Take no parameters and before use Init() should be involked.
		Vector(void);
		// Constructor (Using Size and Type)
		/// Specified the size of vector.
		Vector(const size_t _n, const VectorType _type = VectorType::Zero);
		// Constructor (Using given Data)
		/// Using data from a given pointer, which is pointed to an array, to initialize the vector
		// Matrix(const T * _data, size_t n);

	public: // Initializing
		void Init(const size_t _n, const VectorType _type = VectorType::Zero);

	public: // Initializing

	public: // Pointer

		// Pointer
		T * data() { return this->_data[0]; }
		// Const pointer
		const T * data() const { return this->_data[0]; }

	public: // Operator Overloading

		// "( )" operator
		/// Used for accessing the element in the vector.
		inline T operator()(size_t _j) const
		{
			return this->_data[_j];
		}

		/// Used for referencing the element in the vector.
		inline T & operator()(size_t _j)
		{
			return this->_data[_j];
		}

		// "<<" operator
		/// Used for streaming in format.
		friend ostream& operator<<(ostream& _outstream, Vector<T>& _vec)
		{
			_outstream << typeid(_vec).name() << endl;
			_outstream << "|";
			for (size_t j = 0; j < _vec.n; j++)
			{
				_outstream << _vec(j);
				if (j != _vec.n - 1)	_outstream << " ";
			}
			_outstream << "|" << endl;
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
		/// Addition of two matrixs.
		Vector<T> operator + (const Vector<T> & _other) const
		{
			const Vector<T> & self = *this;
			Vector<T> temp(m);
			if (self.n != _other.n)
			{
				cerr << "ERROR : Invalid Vector Addtion!" << endl;
				return temp;
			}
			for (size_t j = 0; j < self.n; j++)
				temp(j) = self(j) + _other(j);
			return temp;
		}

		/***************************************************************************************************/
		// Used for debugging
	public:
		void PrintToConsole(void);

	private:
		vector<T> _data;
		size_t n;
	};

	template<class T>
	inline MathLib::Vector<T>::Vector(const size_t _n, const VectorType _type)
	{
		for (size_t j = 0; j < _n; j++)
		{
			T tempElem = *new T;
			tempElem = 0;
			_data.push_back(tempElem);
		}
		n = _n;
	}

	template<class T>
	inline void Vector<T>::Init(const size_t _n, const VectorType _type)
	{
		this->n = _n;
		for (size_t j = 0; j < _n; j++)
		{
			T tempElem = *new T;
			tempElem = 0;
			_data.push_back(tempElem);
		}
	}

}

