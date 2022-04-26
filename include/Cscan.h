#ifndef CSCAN_H
#define CSCAN_H

#include <vector>
#include "Zlecenie.h"

class Cscan
{
public:
	Cscan(std::vector<Zlecenie> v);
	void run();
private:
	std::vector<Zlecenie> v;
};

#endif