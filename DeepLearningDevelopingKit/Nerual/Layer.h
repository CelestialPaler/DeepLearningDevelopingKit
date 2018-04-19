/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	                Layer     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <vector>
#include "Node.h"
#include "..\MathLib\MathLib.h"

// Name space
using namespace std;

/***************************************************************************************************/
// Namespace : Nerual
/// Provide Node for nerual network algorithms.
namespace Nerual
{
	/***************************************************************************************************/
	// Class : Layer 
	/// Base class of the layer class.
	class Layer
	{
	public:

		// Set the input of a layer.
		virtual void SetInput(const Vector<ElemType> & _vec) = 0;
		// Get the value of a layer.
		virtual Vector<ElemType> GetOutput(void) = 0;
		// Forward Propagation.
		virtual void ForwardPropagation(void) = 0;
		// Backward Propagation.
		virtual void BackwardPropagation(const Vector<ElemType> & _weightDelta, const ElemType & _biasDelta) = 0;

	private:


	};

	/***************************************************************************************************/
	// Class : InputLayer
	/// Used for input data.
	class InputLayer : public Layer
	{
	public: // Constructors

		// Default constructor
		/// Take no parameters and before use Init() should be involked.
		InputLayer(void);
		// Constructor (Using Size)
		/// Specified the node num of InputLayer.
		InputLayer(const size_t _n);

	public: // Operator Overloading

		// "<<" operator
		/// Used for streaming in format.
		friend ostream & operator<<(ostream & _outstream, InputLayer &  _layer);

	public: // 

		void SetInput(const Vector<ElemType> & _vec) override;
		Vector<ElemType> GetOutput(void) override;

	public:

		void ForwardPropagation(void) override;

	private:
		vector<InputNode> _nodes;
		size_t n;
	};

	/***************************************************************************************************/
	// Class : FilterLayer
	/// Used for filter out specified range of data.
	class FilterLayer : public Layer
	{
	public:

		FilterLayer(void);
		FilterLayer(const size_t _n);

	public:

		friend ostream & operator<<(ostream & _outstream, FilterLayer &  _layer);

		void SetInput(const Vector<ElemType> & _vec) override;
		Vector<ElemType> GetOutput(void) override;
		void ForwardPropagation(void) override;

	private:

		vector<InputNode> _nodes;
		size_t n;
	};

	/***************************************************************************************************/
	// Class : NoiseLayer
	/// Used for appending various noise to the data;
	class NoiseLayer : public Layer
	{
	public:

		NoiseLayer(void);
		NoiseLayer(const size_t _n);

	public:

		friend ostream & operator<<(ostream & _outstream, NoiseLayer &  _layer);

		void SetInput(const Vector<ElemType> & _vec) override;
		Vector<ElemType> GetOutput(void) override;
		void ForwardPropagation(void) override;

	private:

		vector<InputNode> _nodes;
		size_t n;
	};

	/***************************************************************************************************/
	// Class : HiddenLayer
	/// Used for input data.
	class HiddenLayer : public Layer
	{
	public:
		HiddenLayer(void);
		HiddenLayer(const size_t _n, const size_t _m);

	public:
		void SetInput(const Vector<ElemType> & _vec) override;
		Vector<ElemType> GetOutput(void) override;
		void ForwardPropagation(void) override;

	private:
		vector<HiddenNode> _nodes;
		size_t n;
		size_t m;
	};

}
