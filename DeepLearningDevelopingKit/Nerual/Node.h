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
using namespace MathLib;

/***************************************************************************************************/
// Namespace : Nerual
namespace Nerual
{
	class Node
	{
	public:
		virtual void Init() {};
	private:

	};

	/**********************************************************************************************************/
	// Class : InputNode
	class InputNode : public Node
	{
	public:
		/// Constructor
		InputNode() { Init(); }
	public:
		void Init(void);

	public:
		/// Used for BP Algorithm
		double value;
	};

	inline void InputNode::Init(void)
	{
		this->value = 0.f;
	}

	/**********************************************************************************************************/
	// Class : HiddenNode
	template<size_t N>
	class HiddenNode : public Node
	{
	public:
		/// Constructor
		HiddenNode() { Init(); }
	public:
		void Init(void);

	public:
		/// Used for BP Algorithm
		double value;
		double delta;
		double bias;
		double biasDelta;
		Vector<double, N> weight;
		Vector<double, N> weightDelta;
	};

	template<size_t N>
	inline void HiddenNode<N>::Init(void)
	{
		this->value = 0.f;
		this->delta = 0.f;
		this->bias = 0.f;
		this->biasDelta = 0.f;
		for (size_t i = 0; i < N; i++)
			this->weight(i) = RandomSqrt(N);
		for (size_t i = 0; i < N; i++)
			this->weightDelta(i) = RandomSqrt(N);
	}

	/**********************************************************************************************************/
	// Class : OutputNode
	template<size_t N>
	class OutputNode : public Node
	{
	public:
		/// Constructor
		OutputNode() { Init(); }
	public:
		void Init(void);

	public:
		/// Used for BP Algorithm
		double value;
		double delta;
		double error;
		double loss;
		double expectation;
		double bias;
		double biasDelta;
		Vector<double, N> weight;
		Vector<double, N> weightDelta;
	};

	template<size_t N>
	inline void OutputNode<N>::Init(void)
	{
		this->value = 0.f;
		this->delta = 0.f;
		this->error = 0.f;
		this->loss = 0.f;
		this->expectation = 0.f;
		this->bias = 0.f;
		this->biasDelta = 0.f;
		for (size_t i = 0; i < N; i++)
			this->weight(i) = RandomSqrt(N);
		for (size_t i = 0; i < N; i++)
			this->weightDelta(i) = RandomSqrt(N);
	}
}
