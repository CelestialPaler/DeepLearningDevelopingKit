/***************************************************************************************************/
/*                                               Deep Learning Developing Kit                                                   */
/*								        		 	              DataSet     	                                                               */
/*                                                   www.tianshicangxie.com                                                        */
/*                                      Copyright © 2015-2018 Celestial Tech Inc.                                          */
/***************************************************************************************************/

// Header files
#include "DataSet.h"

Data::NumaricSet::NumaricSet()
{

}

void Data::NumaricSet::AddToSet(const Sample & _sample)
{
	_data.push_back(_sample);
}

Data::NumaricSet::Sample Data::NumaricSet::GetBatch(void)
{
	static int count = 0;
	count++;
	if (count == _data.size())
	{
		count = 0;
	}
	return _data.at(count);
}

