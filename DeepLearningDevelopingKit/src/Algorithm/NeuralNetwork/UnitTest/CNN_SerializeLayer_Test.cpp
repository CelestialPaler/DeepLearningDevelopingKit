/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	      SerializeLayer Test   													     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// #define SerializeLayerDebug

#ifdef SerializeLayerDebug
#include "..\ConvolutionalNeuralNetwork\CNN_SerializeLayer.h"

int main(int argc, char ** argv)
{
	const size_t deserializedSizeM = 1;
	const size_t deserializedSizeN = 1;
	const size_t deserializedNum = 5;
	Neural::SerializeLayerInitor serialInitor;
	serialInitor.SerializeSize = MathLib::Size(deserializedSizeM*deserializedSizeN*deserializedNum, 1);
	serialInitor.DeserializeSize = MathLib::Size(deserializedSizeM, deserializedSizeN);
	Neural::SerializeLayer serial(serialInitor);

	MathLib::Matrix<double> serializedMat(deserializedSizeM*deserializedSizeN*deserializedNum, 1, MathLib::MatrixType::Random);

	serial.SetSerializedMat(serializedMat);
	std::vector<MathLib::Matrix<double>> deserializedMat = serial.Deserialize();
	serializedMat = serial.Serialize();

	for(auto mat: deserializedMat)
		std::cout<< mat<<std::endl;

	std::cout << serializedMat<<std::endl;

	system("pause");
	return 0;
}

#endif