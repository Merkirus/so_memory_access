#include <vector>
#include <iostream>
#include <time.h>
#include "Zlecenie.h"
#include "Fcfs.h"
#include "Edf.h"
#include "IAlgo.h"

#define MAX_ZLECENIA 10

using namespace std;

auto main() -> int {

	srand(time(NULL));

	vector<Zlecenie> v;
	v.reserve(MAX_ZLECENIA);

	for (int i=0; i < MAX_ZLECENIA; ++i)
	{
		v.push_back(Zlecenie::makeZlecenie());
	}

	vector<IAlgo*> algorytmy;
	algorytmy.push_back(new Edf());
	
	Fcfs fcfs{v,*algorytmy.front()};

	fcfs.run();

	return 0;
}