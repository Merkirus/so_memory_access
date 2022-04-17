#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "Zlecenie.h"
#include "IAlgo.h"

class Fcfs
{
public:
	Fcfs(std::vector<Zlecenie> v, IAlgo& rt_algo);
	~Fcfs();
	void run();
private:
	std::vector<Zlecenie> v;
	IAlgo* rt_algo;
};

#endif