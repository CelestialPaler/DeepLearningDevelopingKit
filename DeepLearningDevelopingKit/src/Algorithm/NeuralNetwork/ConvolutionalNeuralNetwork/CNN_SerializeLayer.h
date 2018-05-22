/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         Serialize Layer     	                                                       */
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

	// Serialize Layer Initor
	/// Used for initialization of a SerializeLayer.
	struct SerializeLayerInitor
	{
		MathLib::Size SerializeSize;
		MathLib::Size DeserializeSize;
	};

	/***************************************************************************************************/
	// Class : Serialize Layer
	/// Used for serialize the data from a serial of Matrix into a single Vector, and
	/// deserialize it back in the oppsite diraction.
	class SerializeLayer
	{
	public:

		SerializeLayer(const SerializeLayerInitor _initor);

		// Set the input of the ConvLayer.
		void SetSerializedMat(const MathLib::Matrix<ElemType> &  _input);
		void SetDeserializedMat(const std::vector<MathLib::Matrix<ElemType>> &  _input);

		MathLib::Matrix<ElemType> Serialize(void);
		std::vector<MathLib::Matrix<ElemType>> Deserialize(void);

	private:

		MathLib::Matrix<ElemType> _serializedMat;
		std::vector<MathLib::Matrix<ElemType>> _deserializedMat;

		// Input size.
		MathLib::Size _serializedSize;
		MathLib::Size _deserializedSize;
	};
}
