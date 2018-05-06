/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		   Matrix Decomposotion Test                                                     */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#define MatrixDecompostionDebug

#ifdef MatrixDecompostionDebug

// Header files
#include <iostream>
#include <ctime>
#include "..\MathLib\MathLib.h"
#include "..\Algorithm\MatrixAnalysis\LUD.hpp"

using namespace std;
using namespace MathLib;

int main()
{
	srand((unsigned)time(NULL));
	Matrix<double> L(3, 3, MatrixType::Random);
	Matrix<double> U(3, 3, MatrixType::Random);
	Matrix<double> A(3, 3, MatrixType::Random);
	auto temp1 = MatrixDecomposition::LUD(A, MatrixDecomposition::LUDMethod::Doolittle);
	L = temp1.first;
	U = temp1.second;

	cout << "Matrix A : " << A << endl;
	cout << "/**************************/" << endl;
	cout << "After LU Decomposotion : " << endl << endl;
	cout << "Matrix L : " << endl << L << endl;
	cout << "Matrix U : " << endl << U << endl;
	A = L * U;
	cout << "/**************************/" << endl;
	cout << "Matrix LU :" << A << endl;

	cout << "/**************************/" << endl;
	cout << "det(A) : " << A.Determinant() <<"   tr(U) : " 
		<< MatrixDecomposition::LU_Determinant(A) << endl;

	system("pause");
	return 0;
}
#endif // Decomposotion
