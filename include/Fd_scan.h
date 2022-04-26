#ifndef FD_SCAN_H
#define FD_SCAN_H

#include "IAlgo.h"
#include "Zlecenie.h"
#include <vector>
#include <cmath>

class Fd_scan : public IAlgo
{
public:
	Fd_scan();
	virtual ~Fd_scan();
	int run(std::vector<Zlecenie>& v, int prev, long& cancelled) override;
	bool hasRT(std::vector<Zlecenie>& v) override;
};

#endif