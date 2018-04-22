/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Node 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include "..\MathLib\MathLib.h"

// Name space
#ifdef USING_STATIC_MATHLIB
using namespace MathLibStatic;
#endif // USING_STATIC_MATHLIB
#ifdef USING_STANDARD_MATHLIB
using namespace MathLib;
#endif // USING_STANDARD_MATHLIB

/***************************************************************************************************/
// Namespace : Nerual
/// Provide Node for nerual network algorithms.
namespace Nerual
{
	typedef double ElemType;

	/**********************************************************************************************************/
	// Class : Node
	/// Base class of Nodes.
	class Node {};

	/**********************************************************************************************************/
	// Class : InputNode
	class InputNode : public Node
	{
		friend class InputLayer;
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		InputNode(void);

	public: // Operator Overloading

		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, InputNode & _node);

	private:

		// Basic
		ElemType value;

		ElemType tempInput;

	};

	/**********************************************************************************************************/
	// Class : HiddenNode
	class HiddenNode : public Node
	{
		friend class HiddenLayer;
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		HiddenNode(const size_t _n);

	public: // Operator Overloading

		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, HiddenNode & _node);

	private:

		// Basic
		ElemType value;
		ElemType bias;
		Vector<ElemType> weight;

		ElemType loss;
		ElemType expectation;
		Vector<ElemType> tempInput;

		// Used for BP Algorithm
		ElemType valueDelta;
		ElemType valueDeltaSum;
		ElemType biasDelta;
		ElemType biasDeltaSum;
		Vector<ElemType> weightDelta;
		Vector<ElemType> weightDeltaSum;

	};
	
	/**********************************************************************************************************/
	// Class : OutputNode
	class OutputNode : public Node
	{
		friend class OutputLayer;
	public: // Constructors

		// Default constructor
		/// Take no parameters.
		OutputNode(const size_t _n);

	public: // Operator Overloading

		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, OutputNode & _node);

	private:

		// Basic
		ElemType value;
		ElemType bias;
		Vector<ElemType> weight;

		ElemType loss;
		ElemType expectation;
		Vector<ElemType> tempInput;
		
		// Used for BP Algorithm
		ElemType valueDelta;
		ElemType valueDeltaSum;
		ElemType biasDelta;
		ElemType biasDeltaSum;
		Vector<ElemType> weightDelta;
		Vector<ElemType> weightDeltaSum;

	};
}
