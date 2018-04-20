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
#include "..\MathLib\LossFunction.h"

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
		virtual Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) = 0;

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
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;

	public:

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
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;
		void Update(void);

	private:
		vector<HiddenNode> _nodes;
		size_t n;
		size_t m;
	};

	/***************************************************************************************************/
	// Class : OutputLayer
	/// Used for output data, quantify the loss of the output.
	class OutputLayer : public Layer
	{
	public: // Constructors

		// Constructor (Using Size and Type)
		/// n is the input num of the layer.
		/// m is the output num of the layer, which of course is the node num in thisn layer.
		OutputLayer(const size_t _n, const size_t _m);

	public: // Setters
		
		// Set the input of the layer.
		/// Which means set the nodes` tempInput.
		void SetInput(const Vector<ElemType> & _vec) override;
		// Set the expectation of the OutputLayer.
		void SetExpectation(const Vector<ElemType> & _vec);

	public: // Getters

		// Get the output of the layer.
		/// Which means get the value pf all nodes in Vector.
		Vector<ElemType> GetOutput(void) override;
		// Get the estimated loss between output and expectation.
		ElemType GetLoss(void);
		// Get the exact error(Delta) between output and expectation.
		Vector<ElemType> GetDelta(void);

	public: // BackPropagation Algorithm

		// ForwardPropagation Function
		void ForwardPropagation(void) override;
		// BackwardPropagation Function
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;
		// Update Function
		void Update(void);

	private:
		vector<OutputNode> _nodes;
		size_t n, m;
	};
}
