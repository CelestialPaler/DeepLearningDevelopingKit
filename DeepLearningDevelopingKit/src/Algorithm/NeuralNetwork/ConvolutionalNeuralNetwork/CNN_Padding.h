/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 		           Padding     	                                                           */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#include "..\..\..\MathLib\MathLib.h"

/***************************************************************************************************/
// Namespace : Neural
/// Provide Neural Network algorithm library.
namespace Neural
{
	// Method of appending paddings to original data
	/// For most situation, Right Down is the most common practice.
	enum class PaddingMethod {
		LeftUp,
		LeftDown,
		RightUp,
		RightDown,
		Surround
	};

	// What data is going to be appended original data as a padding.
	enum class PaddingNum {
		ZeroPadding,
		OnePadding,
		RandomPadding
	};

	class Pad
	{
		// Define the Element datatype.
		/// Mainly using float and double.
		typedef double ElemType;

	public:
		
		static MathLib::Matrix<ElemType> Padding(const MathLib::Matrix<ElemType> & _input, const PaddingMethod _method, const PaddingNum _num)
		{
			size_t paddingSizeM = 2;
			size_t paddingSizeN = 2;
			size_t inputSizeM = _input.GetSize().m, inputSizeN = _input.GetSize().n;
			size_t outputSizeM = 0, outputSizeN = 0;
			MathLib::Matrix<ElemType> output;
			switch (_method)
			{
			case Neural::PaddingMethod::LeftUp:
				outputSizeM = inputSizeM + paddingSizeM;
				outputSizeN = inputSizeN + paddingSizeN;
				output.Init(outputSizeM, outputSizeN);

				for (size_t i = 0; i < outputSizeM; i++)
					for (size_t j = 0; j < outputSizeN; j++)
						if (i < paddingSizeM || j < paddingSizeN)
							output(i, j) = Pad::PaddingNum(_num);

				for (size_t i = 0; i < inputSizeN; i++)
					for (size_t j = 0; j < inputSizeN; j++)
						output(i + paddingSizeM, j + paddingSizeN) = _input(i, j);

				break;
			case Neural::PaddingMethod::LeftDown:
				outputSizeM = inputSizeM + paddingSizeM;
				outputSizeN = inputSizeN + paddingSizeN;
				output.Init(outputSizeM, outputSizeN);

				for (size_t i = 0; i < outputSizeM; i++)
					for (size_t j = 0; j < outputSizeN; j++)
						if (i > outputSizeM - paddingSizeM || j < paddingSizeN)
							output(i, j) = Pad::PaddingNum(_num);

				for (size_t i = 0; i < inputSizeN; i++)
					for (size_t j = 0; j < inputSizeN; j++)
						output(i, j + paddingSizeN) = _input(i, j);

				break;
			case Neural::PaddingMethod::RightUp:
				outputSizeM = inputSizeM + paddingSizeM;
				outputSizeN = inputSizeN + paddingSizeN;
				output.Init(outputSizeM, outputSizeN);

				for (size_t i = 0; i < outputSizeM; i++)
					for (size_t j = 0; j < outputSizeN; j++)
						if (i < paddingSizeM || j >  outputSizeN - paddingSizeN)
							output(i, j) = Pad::PaddingNum(_num);

				for (size_t i = 0; i < inputSizeN; i++)
					for (size_t j = 0; j < inputSizeN; j++)
						output(i + paddingSizeM, j) = _input(i, j);

				break;
			case Neural::PaddingMethod::RightDown:
				outputSizeM = inputSizeM + paddingSizeM;
				outputSizeN = inputSizeN + paddingSizeN;
				output.Init(outputSizeM, outputSizeN);

				for (size_t i = 0; i < outputSizeM; i++)
					for (size_t j = 0; j < outputSizeN; j++)
						if (i > outputSizeM - paddingSizeM || j >  outputSizeN - paddingSizeN)
							output(i, j) = Pad::PaddingNum(_num);

				for (size_t i = 0; i < inputSizeN; i++)
					for (size_t j = 0; j < inputSizeN; j++)
						output(i, j) = _input(i, j);

				break;
			case Neural::PaddingMethod::Surround:
				outputSizeM = inputSizeM + 2 * paddingSizeM;
				outputSizeN = inputSizeN + 2 * paddingSizeN;
				output.Init(outputSizeM, outputSizeN);

				for (size_t i = 0; i < outputSizeM; i++)
					for (size_t j = 0; j < outputSizeN; j++)
						if (i < paddingSizeM || j < paddingSizeN)
							output(i, j) = Pad::PaddingNum(_num);

				for (size_t i = 0; i < inputSizeN; i++)
					for (size_t j = 0; j < inputSizeN; j++)
						output(i + paddingSizeM, j + paddingSizeN) = _input(i, j);

				break;
			default:
				break;
			}

			return output;
		}

	private:

		static ElemType PaddingNum(const PaddingNum _num)
		{
			switch (_num)
			{
			case Neural::PaddingNum::ZeroPadding:
				return 0;
				break;
			case Neural::PaddingNum::OnePadding:
				return 1;
				break;
			case Neural::PaddingNum::RandomPadding:
				return Random();
				break;
			default:
				return 0;
				break;
			}
		}
	};
}