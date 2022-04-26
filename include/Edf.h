#ifndef EDF_H
#define EDF_H

#include <vector>
#include "IAlgo.h"
#include "Zlecenie.h"
#include <cmath>

class Edf : public IAlgo
{
public:
	Edf();
	virtual ~Edf();
	int run(std::vector<Zlecenie>& v, int prev, long& result, long& cancelled, long& oczekiwanie, int& add_size) override;
	bool hasRT(std::vector<Zlecenie>& v) override;
};

#endif