/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	         Vector Dynamic 	                                                           */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include "MathLib.h"

#ifdef USING_STATIC_MATHLIB
#include "..\MathLib\MathDef.h"
#include "..\MathLib\MatrixStatic.h"
#include "..\MathLib\VectorStatic.h"
#include "..\MathLib\ToolFunction.h"
#endif // USING_STATIC_MATHLIB

#ifdef USING_DYNAMIC_MATHLIB
#include "..\MathLib\MathDef.h"
#include "..\MathLib\MatrixDynamic.h"
#include "..\MathLib\ToolFunction.h"
#endif // USING_DYNAMIC_MATHLIB

using namespace std;


/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
/// Specialized for deep learning purpose. Emm might be true ... or not ... XD whatever!
namespace MathLibDynamic
{
	/***************************************************************************************************/
	// Class : Vector
	/// 
	template<class T>
	class Vector
	{
		/***************************************************************************************************/
		// Constructors
	public:
		Vector(const size_t _n);

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
		inline T operator()(size_t _j) const
		{
			return this->_data[_j];
		}

		/// Used for referencing the element in the matrix.
		inline T & operator()(size_t _j)
		{
			return this->_data[_j];
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
			Vector<T> temp(n);
			if (self.n != _other.n)
			{
				cerr << "ERROR : Invalid Vector Addtion!" << endl;
				return temp;
			}
			for (size_t j = 0; j < self.n; j++)
				temp( j) = self(j) + _other(j);
			return temp;
		}

		friend ostream& operator<<(ostream& _os, Vector<T>& _mat)
		{
			_os << typeid(_mat).name() << endl;
			_os << "|";
			for (size_t j = 0; j < _mat.n; j++)
			{
				_os << _mat(j);
				if (j != _mat.n - 1)	_os << " ";
			}
			_os << "|" << endl;
			return _os;
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
	inline MathLibDynamic::Vector<T>::Vector(const size_t _n)
	{
		for (size_t j = 0; j < _n; j++)
		{
			T tempElem = *new T;
			tempElem = 0;
			_data.push_back(tempElem);
		}
		n = _n;
	}
}
