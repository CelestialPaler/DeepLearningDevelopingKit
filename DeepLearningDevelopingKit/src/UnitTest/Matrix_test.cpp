/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	            Matrix Test   	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#define MatrixDebug

#ifdef MatrixDebug

// Header files
#include <iostream>
#include "..\MathLib\MathLib.h"

using namespace std;
using namespace MathLib;

int main()
{
	Matrix<double> A(3, 3, MatrixType::Identity);
	Matrix<double> B(3, 3, MatrixType::Zero);
	cout << A << endl;
	cout << A.Determinant() << endl;

	B = A.GaussianElimination();
	cout << B << endl;
	cout << "Trace of B :" << B.Trace() << endl;
	cout << "Rank of B :" << B.Rank() << endl;

	B = B.Transpostion();
	cout << "Transpos of B :" << B << endl;

	cout << "Cofactor of B :" << B.Cofactor(1, 1) << endl;
	system("pause");
	return 0;
}
#endif // MatrixDebug
