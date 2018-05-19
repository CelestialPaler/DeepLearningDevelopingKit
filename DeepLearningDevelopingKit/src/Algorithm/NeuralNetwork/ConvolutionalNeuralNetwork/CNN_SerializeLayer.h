/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	         Serialize Layer     	                                                          */
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
	struct SerializeLayerInitor
	{
		MathLib::Size SerializeSize;
		MathLib::Size DeserializeSize;
	};

	/***************************************************************************************************/
	// Class : Serialize Layer
	/// Used for XXXXXXX.
	class SerializeLayer
	{
	public:

		SerializeLayer(const SerializeLayerInitor _initor);

		// Set the input of the ConvLayer.
		void SetSerializedMat(const MathLib::Matrix<ElemType> &  _input);
		void SetDeserializedMat(const std::vector<MathLib::Matrix<ElemType>> &  _input);

		void Serialize(void);
		void Deserialize(void);

		inline const MathLib::Matrix<ElemType> GetSerializedMat(void) const { return _serializedMat; }
		inline const std::vector<MathLib::Matrix<ElemType>> GetDeserializedMat(void) const { return _deserializedMat; }

	private:

		MathLib::Matrix<ElemType> _serializedMat;
		std::vector<MathLib::Matrix<ElemType>> _deserializedMat;

		// Input size.
		MathLib::Size _serializedSize;
		MathLib::Size _deserializedSize;
	};
}
