#include "DataSet.h"

ostream & Data::operator<<(ostream & _outstream, NumaricSet::Sample & _sample)
{
	_outstream << typeid(_sample).name() << endl;
	_outstream << "Input: " << _sample.first;
	_outstream << "Output: " << _sample.second;
	return _outstream;
}
