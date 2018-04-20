/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	            NodeVector     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

// Header files
#include <iostream>
#include <vector>

// Namespaces
using namespace std;

/***************************************************************************************************/
// Namespace : MathLib
/// Provide mathematic support and calculation tools for different algorithms.
namespace MathLib
{
	template<class T>
	class NodeVector
	{
	public:
		NodeVector(void);

	private:
		vector<T> _nodes;
	};
}
