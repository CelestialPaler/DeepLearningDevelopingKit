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

// Name space
using namespace std;

/***************************************************************************************************/
// Namespace : Nerual
namespace Nerual
{
	/***************************************************************************************************/
	// Class : Layer 
	/// Base class of the layer class
	class Layer
	{
	public:
		virtual void SetInput(const Vector<ElemType> & _vec) = 0;
	private:

	};

	class InputLayer : public Layer
	{
	public:
		InputLayer(void);
		InputLayer(const size_t _n);

	public:
		friend ostream & operator<<(ostream & _outstream, InputLayer &  _layer);

		void SetInput(const Vector<ElemType> & _vec) override;

	private:
		vector<InputNode> _nodes;
		size_t n;
	};

	class HIddenLayer : public Layer
	{
	public:
		HIddenLayer(void);
		HIddenLayer(const size_t _n, const size_t _m);

	public:
		void SetInput(const Vector<ElemType> & _vec) override;

	private:
		vector<HiddenNode> _nodes;
		size_t n;
		size_t m;
	};

}
