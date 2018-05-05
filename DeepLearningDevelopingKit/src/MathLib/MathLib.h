/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              MathLib 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#define USING_STANDARD_MATHLIB

#ifdef USING_STATIC_MATHLIB
#include "MatrixStatic.h"
#include "VectorStatic.h"
#endif // USING_STATIC_MATHLIB

#ifdef USING_STANDARD_MATHLIB
#include "Matrix.hpp"
#include "Vector.hpp"
#include "RandomEngine.h"
#endif // USING_DYNAMIC_MATHLIB
