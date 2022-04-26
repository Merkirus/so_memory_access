#ifndef IAlgo_H
#define IAlgo_H

#include <vector>
#include "Zlecenie.h"


class IAlgo
{
public:
	virtual ~IAlgo()=default;
	virtual int run(std::vector<Zlecenie>& v, int prev, long& result, long& cancelled, long& oczekiwanie, int& add_size) = 0;
	virtual bool hasRT(std::vector<Zlecenie>& v) = 0;
};

#endif