#ifndef SSTF_H
#define SSTF_H

#include "Zlecenie.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

class Sstf
{
public:
	Sstf(std::vector<Zlecenie> v);
	void run();
private:
	std::vector<Zlecenie> v;
};

#endif