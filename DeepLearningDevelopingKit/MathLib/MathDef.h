/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              Mathdef 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

namespace MathLib
{
	// Type of vector and matrix
	enum class MatrixType {
		Zero,
		Ones,
		Random,
		Identity,
		Diagonal,
		Triangle
	};

	// Type of vector and matrix
	enum class VectorType {
		Zero,
		Ones,
		Random,
		Identity
	};
}

namespace MathLibStatic
{
	// Type of vector and matrix
	enum Type {
		Zero,
		Ones,
		Random,
		Identity,
		Diagonal,
		Triangle
	};
}