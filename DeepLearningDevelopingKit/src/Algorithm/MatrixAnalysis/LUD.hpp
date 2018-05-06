/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	       LU Decomposotion 	                                                    */
/*								        		 	                Matrix   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

#include "..\..\MathLib\MathLib.h"


namespace MathLib
{
	namespace MatrixDecomposition
	{
		// LU decomposition
		/// Factors a matrix as the product of a lower triangular matrix and an upper triangular matrix.
		enum class LUDMethod {
			Doolittle,
			Crout,
			Cholesky
		};

		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> LUD(
			const MathLib::Matrix<T> & _mat, const LUDMethod & _method);

		// Doolittle Method
		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> Doolittle(const MathLib::Matrix<T> & _mat);

		// Crout Method
		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> Crout(const MathLib::Matrix<T> & _mat);

		template<class T>
		T LU_Determinant(const MathLib::Matrix<T> & _mat);
	}
}


namespace MathLib
{
	namespace MatrixDecomposition
	{
		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> LUD(const MathLib::Matrix<T>& _mat, const LUDMethod & _method)
		{
			switch (_method)
			{
			case MathLib::MatrixDecomposition::LUDMethod::Doolittle:
				return Doolittle(_mat);
				break;
			case MathLib::MatrixDecomposition::LUDMethod::Crout:
				return Crout(_mat);
				break;
			case MathLib::MatrixDecomposition::LUDMethod::Cholesky:
				break;
			default:
				return Doolittle(_mat);
				break;
			}
			return std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>>();
		}

		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> Doolittle(const MathLib::Matrix<T>& _mat)
		{
			size_t matSize = _mat.Size();
			MathLib::Matrix<T> L(matSize, matSize);
			MathLib::Matrix<T> U(matSize, matSize);
			for (int a = 0; a < matSize; a++)
			{
				for (int b = 0; b < matSize; b++)
				{
					double sum = 0.0;
					if (a <= b)
					{
						for (int i = 0; i < a; i++)
							sum += L(a, i) * U(i, b);
						U(a, b) = _mat(a, b) - sum;
					}
					else
					{
						for (int i = 0; i < b; i++)
							sum += L(a, i) * U(i, b);
						L(a, b) = (_mat(a, b) - sum) / U(b, b);
					}
				}
			}
			for (size_t i = 0; i < matSize; i++)
				L(i, i) = 1.f;
			return std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>>(L, U);
		}

		template<class T>
		std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>> Crout(const MathLib::Matrix<T>& _mat)
		{
			size_t matSize = _mat.Size();
			MathLib::Matrix<T> L(matSize, matSize);
			MathLib::Matrix<T> U(matSize, matSize);
			MathLib::Matrix<T> tempMat(matSize, matSize);
			tempMat = _mat.Transpostion();
			for (int a = 0; a < matSize; a++)
			{
				for (int b = 0; b < matSize; b++)
				{
					double sum = 0.0;
					if (a <= b)
					{
						for (int i = 0; i < a; i++)
							sum += L(a, i) * U(i, b);
						U(a, b) = tempMat(a, b) - sum;
					}
					else
					{
						for (int i = 0; i < b; i++)
							sum += L(a, i) * U(i, b);
						L(a, b) = (tempMat(a, b) - sum) / U(b, b);
					}
				}
			}
			for (size_t i = 0; i < matSize; i++)
				U(i, i) = 1.f;
			return std::pair<MathLib::Matrix<T>, MathLib::Matrix<T>>(L, U);
		}

		template<class T>
		T LU_Determinant(const MathLib::Matrix<T>& _mat)
		{
			Matrix<double> L(3, 3, MatrixType::Random);
			Matrix<double> U(3, 3, MatrixType::Random);
			auto temp = MatrixDecomposition::Doolittle(_mat);
			L = temp.first;
			U = temp.second;
			T det = U.Trace();
			return det;
		}
	}
}