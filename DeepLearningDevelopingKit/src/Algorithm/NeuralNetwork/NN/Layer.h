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
#include "..\ActivationFunction.h"
#include "..\LossFunction.h"
#include "..\..\..\MathLib\MathLib.h"

/***************************************************************************************************/
// Namespace : Neural
/// Provide Node for nerual network algorithms.
namespace Neural
{
	/***************************************************************************************************/
	// Class : Layer 
	/// Base class of the layer class.
	class Layer
	{
	public: // Setters

		// Set the input of the layer.
		/// Which means set the nodes` tempInput.
		virtual void SetInput(const Vector<ElemType> & _vec) = 0;
		// Set the activation function of the layer.
		virtual void SetActivationFunction(const ActivationFunction _function) = 0;
		// Set the loss function of the layer.
		virtual void SetLossFunction(const LossFunction _function) = 0;

	public: // Getters

		// Get the output of the layer.
		/// Which means get the value of all nodes in Vector.
		virtual Vector<ElemType> GetOutput(void) = 0;
		// Get the node number of the layers.
		size_t GetNodeNum(void);

	public: // BackPropagation Algorithm

		// ForwardPropagation Function
		/// Calculate the value of each node.
		virtual void ForwardPropagation(void) = 0;
		// BackwardPropagation Function
		/// Calculate the gradient(delta) of each node.
		virtual Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) = 0;
		// Update Function
		/// Update the weight and bias of each node.
		virtual void Update(void) = 0;
		// Sum up the delta of a batch.
		virtual void BatchDeltaSumUpdate(const size_t _batchSize) = 0;
		// Clear the deltaSum of a batch.
		virtual void BatchDeltaSumClear(void) = 0;

	protected:

		ElemType(*activationFunction)(ElemType x);
		ElemType(*activationFunctionDerivative)(ElemType x);
		ElemType(*lossFunction)(ElemType x, ElemType y);
		ElemType(*lossFunctionDerivative)(ElemType x, ElemType y);
		size_t n, m;
	};

	/***************************************************************************************************/
	// Class : InputLayer
	/// Used for input data.
	class InputLayer : public Layer
	{
	public: // Constructors

		// Constructor
		/// n is the input num of the layer.
		/// m is the output num of the layer, which of course is the node num in this layer.
		InputLayer(const size_t _n, const size_t _m);

	public: // Operator Overloading

		// "<<" operator
		/// Used for streaming in format.
		friend std::ostream & operator<<(std::ostream & _outstream, InputLayer &  _layer);

	public: // Setters

		// Set the input of the layer.
		/// Which means set the nodes` tempInput.
		void SetInput(const Vector<ElemType> & _vec) override;
		// Set the activation function of the layer.
		virtual void SetActivationFunction(const ActivationFunction _function) override;
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function) override;

	public: // Getters

		// Get the output of the layer.
		/// Which means get the value of all nodes in Vector.
		Vector<ElemType> GetOutput(void) override;

	public: // BackPropagation Algorithm

		// ForwardPropagation Function
		/// Calculate the value of each node.
		void ForwardPropagation(void) override;
		// BackwardPropagation Function
		/// Calculate the gradient(delta) of each node.
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;
		// Update Function
		/// Update the weight and bias of each node.
		void Update(void) override;
		// Sum up the delta of a batch.
		void BatchDeltaSumUpdate(const size_t _batchSize) override;
		// Clear the sumdelta of a batch.
		void BatchDeltaSumClear(void) override;

	private:

		std::vector<InputNode> _nodes;
	};

	/***************************************************************************************************/
	// Class : HiddenLayer
	/// Used for adjust weights and bias to fit and minimize the loss.
	class HiddenLayer : public Layer
	{
	public: // Constructors

		// Constructor
		/// n is the input num of the layer.
		/// m is the output num of the layer, which of course is the node num in this layer.
		HiddenLayer(const size_t _n, const size_t _m);

	public: // Setters

		// Set the input of the layer.
		/// Which means set the nodes` tempInput.
		void SetInput(const Vector<ElemType> & _vec) override;
		// Set the expectation of the OutputLayer.
		void SetExpectation(const Vector<ElemType> & _vec);
		// Set the activation function of the layer.
		virtual void SetActivationFunction(const ActivationFunction _function) override;
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function) override;

	public: // Getters

		// Get the output of the layer.
		/// Which means get the value of all nodes in Vector.
		Vector<ElemType> GetOutput(void) override;

	public: // BackPropagation Algorithm

		// ForwardPropagation Function
		/// Calculate the value of each node.
		void ForwardPropagation(void) override;
		// BackwardPropagation Function
		/// Calculate the gradient(delta) of each node.
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;
		// Update Function
		/// Update the weight and bias of each node.
		void Update(void);
		// Sum up the delta of a batch.
		void BatchDeltaSumUpdate(const size_t _batchSize) override;
		// Clear the sum of sum of delta.
		void BatchDeltaSumClear(void) override;

	private:
		std::vector<HiddenNode> _nodes;
	};

	/***************************************************************************************************/
	// Class : OutputLayer
	/// Used for output data, quantify the loss of the output.
	class OutputLayer : public Layer
	{
	public: // Constructors

		// Constructor
		/// n is the input num of the layer.
		/// m is the output num of the layer, which of course is the node num in this layer.
		OutputLayer(const size_t _n, const size_t _m);

	public: // Setters
		
		// Set the input of the layer.
		/// Which means set the nodes` tempInput.
		void SetInput(const Vector<ElemType> & _vec) override;
		// Set the expectation of the OutputLayer.
		void SetExpectation(const Vector<ElemType> & _vec);
		// Set the activation function of the layer.
		void SetActivationFunction(const ActivationFunction _function) override;
		// Set the loss function of the layer.
		void SetLossFunction(const LossFunction _function) override;

	public: // Getters

		// Get the output of the layer.
		/// Which means get the value of all nodes in Vector.
		Vector<ElemType> GetOutput(void) override;
		// Get the estimated loss between output and expectation.
		ElemType GetLoss(void);
		// Get the exact error(Delta) between output and expectation.
		Vector<ElemType> GetDelta(void);

	public: // BackPropagation Algorithm

		// ForwardPropagation Function
		/// Calculate the value of each node.
		void ForwardPropagation(void) override;
		// BackwardPropagation Function
		/// Calculate the gradient(delta) of each node.
		Vector<ElemType> BackwardPropagation(const Vector<ElemType> & _vec) override;
		// Update Function
		/// Update the weight and bias of each node.
		void Update(void);
		// Sum up the delta of a batch.
		void BatchDeltaSumUpdate(const size_t _batchSize) override;
		// Clear the sum of sum of delta.
		void BatchDeltaSumClear(void) override;
		// Sum up the loss of a batch.
		void LossSumUpdate(void);
		// Clear the sum of loss od a batch.
		void LossSumClear(void);

	private:

		std::vector<OutputNode> _nodes;
	};

	/***************************************************************************************************/
	// Class : ConvolutionalLayer
	/// Convelutional Layer
	class ConvelutionalLayer
	{
	public:

		ConvelutionalLayer(void);

	private:

		std::vector<InputNode> _nodes;
	};
}
