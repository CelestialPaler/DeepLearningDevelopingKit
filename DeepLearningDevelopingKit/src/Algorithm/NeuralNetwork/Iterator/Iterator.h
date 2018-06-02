/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		                   Iterator     	                                                          */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/
#pragma once

/***************************************************************************************************/
// Namespace : Neural
/// Provide Neural Network algorithm library.
namespace Neural
{
	class Iterator
	{
	public:

		Iterator();

	private:

	};

    class GDIterator
	{
	public:

		GDIterator();

    public:

        void Train();
        void Test();

	private:

        void(*forwardPropagationFunction)();

	};
}