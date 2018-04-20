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

	class Node
	{

	public:

		virtual void Calculate(void) = 0;

	private:
	};

	/**********************************************************************************************************/
	// Class : InputNode
	class InputNode : public Node
	{
		friend class InputLayer;
	public:
		/// Constructor
		InputNode(void);

	public:
		void Calculate(void) override;

	public:
		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, InputNode & _node);

	private:
		/// Used for BP Algorithm
		ElemType value;
		ElemType tempInput;
	};

	/**********************************************************************************************************/
	// Class : HiddenNode
	class HiddenNode : public Node
	{
		friend class HiddenLayer;
	public:
		/// Constructor
		HiddenNode(const size_t _n);
	public:
		void Calculate(void) override;

	public:
		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, HiddenNode & _node);

	private:
		/// Used for BP Algorithm
		ElemType value;
		ElemType delta;
		ElemType bias;
		ElemType biasDelta;
		Vector<ElemType> tempInput;
		Vector<ElemType> weight;
		Vector<ElemType> weightDelta;
	};
	
	/**********************************************************************************************************/
	// Class : OutputNode
	class OutputNode : public Node
	{
		friend class OutputLayer;
	public:
		/// Constructor
		OutputNode(const size_t _n);
	public:
		void Calculate(void) override;

	public:
		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, OutputNode & _node);

	private:
		/// Used for BP Algorithm
		ElemType value;
		ElemType delta;
		ElemType error;
		ElemType loss;
		ElemType bias;
		ElemType biasDelta;
		ElemType expectation;
		Vector<ElemType> tempInput;
		Vector<ElemType> weight;
		Vector<ElemType> weightDelta;
	};
}
