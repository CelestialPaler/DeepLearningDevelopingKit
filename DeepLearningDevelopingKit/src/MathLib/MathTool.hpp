/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	           Math Library 	                                                              */
/*								        		 	                Matrix   	                                                              */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

/***************************************************************************************************/
// Namespace : MathLib
/// Provide basic mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	struct Size
	{
		Size(size_t _m, size_t _n) : m(_m), n(_n) {}
		size_t m;
		size_t n;
	};
}