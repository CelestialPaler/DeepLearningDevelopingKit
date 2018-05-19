/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	          Process Layer     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "..\..\..\MathLib\MathLib.h"

/***************************************************************************************************/
// Namespace : Neural
/// Provide Neural Network algorithm library.
namespace Neural
{
	// Define the Element datatype.
	/// Mainly using float and double.
	typedef double ElemType;

	// Process Layer Initor
	/// Used for initialization of a ConvLayer.
	struct ProcessLayerInitor
	{
		// Size of input matrix. 
		MathLib::Size InputSize;
		ElemType(*ProcessFunction)(ElemType x);
		ElemType(*ProcessFunctionDerivative)(ElemType x);
	};

	/***************************************************************************************************/
	// Class : Process Layer
	/// Used for XXXXXXX.
	class ProcessLayer
	{
	public:

		ProcessLayer(const ProcessLayerInitor _initor);

		// Set the input of the ConvLayer.
		void SetInput(const std::vector<MathLib::Matrix<ElemType>> &  _data);

		void Process(void);
		void Deprocess(void);

		inline const MathLib::Matrix<ElemType> GetOutput(const size_t _index) const { return _data.at(_index); }
		inline const std::vector<MathLib::Matrix<ElemType>> GetOutputAll(void) const { return _data; }


	private:

		// Input of the layer.
		std::vector<MathLib::Matrix<ElemType>> _data;

		// Input size.
		MathLib::Size _inputSize;
		MathLib::Size _outputSize;

		// Process Function
		ElemType(*processFunction)(ElemType x);
		ElemType(*processFunctionDerivative)(ElemType x);
	};
}
