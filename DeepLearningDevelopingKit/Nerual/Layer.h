/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include "..\MathLib\MathLib.h"
#include "..\Nerual\Node.h"
#include "..\Util\Port.h"

// Name space
using namespace std;

/***************************************************************************************************/
// Namespace : Nerual
namespace Nerual
{
	/***************************************************************************************************/
	// Class : LayerPointer 
	class LayerPointer;
	/***************************************************************************************************/
	// Class : Layer 
	/// Base class of the layer class
	template<size_t M, size_t N> 
	class Layer : public LayerPointer
	{
	protected:
		virtual void SetInput(const Vector<double, M> & _data) = 0;
		virtual Vector<double, N> Output(void) = 0;
		virtual void Forward(void) = 0;
	};

	/***************************************************************************************************/
	// Class : InputLayer 
	template<size_t M, size_t N>
	class InputLayer : public Layer<M, N>
	{
	public:
		InputLayer(void);

	public:
		// Set the input of the layer
		void SetInput(const Vector<double, M> & _vec) { this->inputBuffer = _vec; }
		// Get the output of the layer
		Vector<double, N> Output(void);
		// Forward propegation
		void Forward(void);

	private:
		Vector<double, M> inputBuffer;
		vector<InputNode> nodes;
	};

	template<size_t M, size_t N>
	inline InputLayer<M, N>::InputLayer(void)
	{
		for (size_t i = 0; i < N; i++)
		{
			InputNode tempNode = *new InputNode();
			nodes.push_back(tempNode);
		}
	}

	template<size_t M, size_t N>
	inline Vector<double, N> InputLayer<M, N>::Output(void)
	{
		Vector<double, N> temp;
		for (size_t i = 0; i < N; i++)
		{
			temp(i) = this->nodes.at(i).value;
		}
		return temp;
	}

	template<size_t M, size_t N>
	inline void InputLayer<M, N>::Forward(void)
	{
		for (size_t i = 0; i < N; i++)
		{
			this->nodes.at(i).value = inputBuffer(i);
		}
	}

	/***************************************************************************************************/
	// Class : HiddenLayer
	template<size_t M, size_t N>
	class HiddenLayer : public Layer<M, N>
	{
	public:
		HiddenLayer(void);
	public:
		// Set the input of the layer
		void SetInput(const Vector<double, M> & _vec) 
		{
			// _vec.PrintToConsole();
			for (size_t i = 0; i < M; i++)
			{
				this->inputBuffer(i) = _vec(i);
			}
		}
		// Get the output of the layer
		Vector<double, N> Output(void);
		// Forward propegation
		void Forward(void)
		{
			for (size_t i = 0; i < N; i++)
			{
				HiddenNode<M> * temp = &this->nodes.at(i);
				temp->value = (inputBuffer * temp->weight).Sum() - temp->bias;
			}
		}
	private:
		Vector<double, M> inputBuffer;
		vector<HiddenNode<M>> nodes;
	};

	template<size_t M, size_t N>
	inline HiddenLayer<M, N>::HiddenLayer(void)
	{
		for (size_t i = 0; i < N; i++)
		{
			HiddenNode<M> tempNode = *new HiddenNode<M>();
			nodes.push_back(tempNode);
		}
	}

	template<size_t M, size_t N>
	inline Vector<double, N> HiddenLayer<M, N>::Output(void)
	{
		Vector<double, N> temp;
		for (size_t i = 0; i < N; i++)
		{
			temp(i) = this->nodes.at(i).value;
		}
		return temp;
	}

	/***************************************************************************************************/
	// Class : OutputLayer
	template<size_t M, size_t N>
	class OutputLayer : public Layer<M, N>
	{
	public:
		OutputLayer()
		{
			for (size_t i = 0; i < N; i++)
			{
				OutputNode<M> tempNode = *new OutputNode<M>();
				nodes.push_back(tempNode);
			}
		}
	public:
		void SetInput(const Vector<double, M> & _data) { this->inputBuffer = _data; }
		Vector<double, N> Output(void)
		{
			Vector<double, N> temp;
			for (size_t i = 0; i < N; i++)
			{
				temp(i) = this->nodes.at(i).value;
			}
			return temp;
		}
		void Forward(void)
		{
			for (size_t i = 0; i < N; i++)
			{
				OutputNode<M> * temp = &this->nodes.at(i);
				temp->value = (inputBuffer * temp->weight).Sum() - temp->bias;
			}
		}
	private:
		Vector<double, M> inputBuffer;
		vector<OutputNode<M>> nodes;
	};
}
