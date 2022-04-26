#ifndef SCAN_H
#define SCAN_H

#include <vector>
#include "Zlecenie.h"

class Scan
{
public:
	Scan(std::vector<Zlecenie> v);
	void run();
private:
	std::vector<Zlecenie> v;
};

#endif