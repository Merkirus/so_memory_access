#ifndef IAlgo_H
#define IAlgo_H

#include <vector>
#include "Zlecenie.h"


class IAlgo
{
public:
	virtual int run(std::vector<Zlecenie>& v, int curr, int& result) = 0;
	virtual bool tooFar(std::vector<Zlecenie>& v, int curr) = 0;
	virtual bool hasRT(std::vector<Zlecenie>& v) = 0;
};

#endif