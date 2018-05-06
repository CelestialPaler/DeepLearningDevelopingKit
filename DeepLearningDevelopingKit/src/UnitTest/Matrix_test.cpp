/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	            Matrix Test   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
// #define MatrixDecompostionDebug

#ifdef MatrixDecompostionDebug

// Header files
#include <iostream>
#include "..\MathLib\MathLib.h"
#include "..\Algorithm\MatrixAnalysis\Decomposition.hpp"

using namespace std;
using namespace MathLib;

int main()
{
	Matrix<int> A(3, 3, MatrixType::Identity);
	Matrix<int> B(3, 3, MatrixType::Identity);
	cout << A << endl;
	cout << A.Determinant() << endl;

	cout << B << endl;
	cout << "Trace of B :" << B.Trace() << endl;
	cout << "Rank of B :" << B.Rank() << endl;

	B = B.Transpostion();
	cout << "Transpos of B :" << B << endl;

	cout << "Cofactor of B :" << B.Cofactor(1, 1) << endl;
	cout << "AlgebraicCofactor of B :" << B.AlgebraicCofactor(1, 1) << endl;

	B = B.Adjoint();
	cout << "Adjoint of B :" << B << endl;

	B = B.Inverse();
	cout << "Inverse of B :" << B << endl;

	Matrix<double> L(3, 3, MatrixType::Random);
	Matrix<double> U(3, 3, MatrixType::Random);
	Matrix<double> C(3, 3, MatrixType::Random);
	L = MatrixDecomposotion<double>::LU(C).first;
	U = MatrixDecomposotion<double>::LU(C).second;

	cout << L << U << endl;
	system("pause");
	return 0;
}
#endif // MatrixDebug
