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
	int run(std::vector<Zlecenie>& v, int curr, int& result) override;
	bool hasRT(std::vector<Zlecenie>& v) override;
	bool tooFar(std::vector<Zlecenie>& v, int curr) override;
};

#endif