/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include "..\Nerual\Node.h"
#include "..\Util\Port.h"

// Name space
using namespace std;

/***************************************************************************************************/
// Namespace : Nerual
namespace Nerual
{
	/***************************************************************************************************/
	// Class : Layer 
	/// 
	template<size_t N>
	class Layer
	{
	public:
		virtual void SetInput(const Vector<double, N> & _data) {}
	protected:

	};

	template<size_t N>
	class InputLayer : public Layer
	{
	public:
		InputLayer(size_t _num)
		{
			for (size_t i = 0; i < _num; i++)
			{
				InputNode tempNode = *new InputNode();
				_nodes.push_back(tempNode);
			}
		}
	public:
		void SetInput(const Vector<double, N> & _data);
	private:
		vector<InputNode> _nodes;
	};

	template<size_t N>
	class HiddenLayer : public Layer
	{
	public:
		HiddenLayer(size_t _num)
		{
			for (size_t i = 0; i < _num; i++)
			{
				HiddenNode<N> tempNode = *new HiddenNode<N>();
				_nodes.push_back(tempNode);
			}
		}
	public:
		void SetInput()
	private:
		vector<HiddenNode<N>> _nodes;
	};

	template<size_t N>
	class OutputLayer : public Layer
	{
	public:
		OutputLayer(size_t _num)
		{
			for (size_t i = 0; i < _num; i++)
			{
				OutputNode<N> tempNode = *new OutputNode<N>();
				_nodes.push_back(tempNode);
			}
		}
	private:
		vector<OutputNode<N>> _nodes;
	};

	template<size_t N>
	inline void InputLayer<N>::SetInput(const Vector<double, N>& _data)
	{
		for (size_t i = 0; i < N; i++)
		{
			this->_nodes.at(i).value = _data(i);
		}
	}

}
