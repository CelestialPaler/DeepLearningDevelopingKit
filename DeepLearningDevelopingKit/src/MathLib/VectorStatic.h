/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	                Vector 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include "Mathdef.h"
#include "MatrixStatic.h"

using namespace std;

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
/// Specialized for deep learning purpose. Emm might be true ... or not ... XD whatever!
namespace MathLibStatic
{
	/***************************************************************************************************/
	// Class : Vector
	/// 
	template<class T, size_t M>
	class Vector : public Matrix<T, M, 1>
	{
		/***************************************************************************************************/
		// Constructors
	public:
		// Default constructor
		/// Take no parameters, set elements to 0.
		Vector(void);
		// Constructor (Type)
		/// Specified a type of vector.
		Vector(Type _type);
		// Constructor (Data)
		/// Using data from a given pointer, which is pointed to an array, to initialize the vector.
		Vector(const T _data[M]);

	public:
		T Sum(void) {
			const Vector<T, M> &self = *this;
			T temp = 0;
			for (size_t i = 0; i < M; i++)
				temp += self(i);
			return temp;
		}

	public:
		// Pointers
		T * data()
		{
			return data[0];
		}

		const T * data() const
		{
			return data[0];
		}

		// ???? Wired bug here
		/// temp code 
		Vector<T, M> & operator = (const Vector<T, M> & _other)
		{
			if (this != &_other) {
				for (size_t i = 0; i < M; i++)
				{
					this->_data[i][0] = _other._data[i][0];
				}
			}
			return (*this);
		}

		inline T operator () (size_t _i) const
		{
			return this->_data[_i][0];
		}

		inline T & operator()(size_t _i)
		{
			return this->_data[_i][0];
		}

		// 
		Vector<T, M> operator * (const Vector<T, M> & _other) const
		{
			const Vector<T, M> &self = *this;
			Vector<T, M> temp;
			for (size_t i = 0; i < M; i++)
				temp(i) = self(i) * _other(i);
			return temp;
		}

		/***************************************************************************************************/
		// Used for debugging
	public:
		void PrintToConsole(void);

	private:
	};
}

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
namespace MathLibStatic
{
	template<class T, size_t M>
	inline Vector<T, M>::Vector(void)
	{
		for (size_t i = 0; i < M; i++)
			this->_data[i][0] = 0;
	}

	template<class T, size_t M>
	inline Vector<T, M>::Vector(Type _type)
	{
		for (size_t i = 0; i < M; i++)
			this->_data[i][0] = 0;
	}

	template<class T, size_t M>
	inline Vector<T, M>::Vector(const T _data[M])
	{
		for (size_t i = 0; i < M; i++)
			this->_data[i][0] = _data[i];
	}

	template<class T, size_t M>
	inline void Vector<T, M>::PrintToConsole(void)
	{
		const Matrix<T, M, 1> &v = *this;
		for (size_t i = 0; i < M; i++)
		{
			cout << "|";
			cout << v(i, 0) << " ";
			cout << "|" << endl;
		}
		cout << endl;
	}
}
