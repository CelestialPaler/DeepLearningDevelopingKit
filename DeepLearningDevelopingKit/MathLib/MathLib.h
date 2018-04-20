/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              MathLib 	                                                                  */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

#define USING_STANDARD_MATHLIB

#ifdef USING_STATIC_MATHLIB
#include "..\MathLib\MatrixStatic.h"
#include "..\MathLib\VectorStatic.h"
#endif // USING_STATIC_MATHLIB

#ifdef USING_STANDARD_MATHLIB
#include "..\MathLib\Matrix.h"
#include "..\MathLib\Vector.h"
#endif // USING_DYNAMIC_MATHLIB

#include "..\MathLib\ToolFunction.h"
#include "..\MathLib\ActivationFunction.h"
// #include "..\Util\Log.h"

