#include <vector>
#include <iostream>
#include <time.h>
#include "Zlecenie.h"
#include "Fcfs.h"
#include "Edf.h"
#include "IAlgo.h"
#include "Fd_scan.h"
#include "Sstf.h"
#include "Scan.h"
#include "Cscan.h"

#define MAX_ZLECENIA 100

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
	algorytmy.push_back(new Fd_scan());
	
	Fcfs fcfs{v, *algorytmy.at(0)};
	Fcfs fcfs2{v, *algorytmy.at(1)};
	Fcfs fcfs3{v};
	Sstf sstf{v};
	Scan scan{v};
	Cscan cscan{v};

	cout << "FCFS z EDF" << '\n';
	fcfs.run();
	cout << "====" << '\n';
	cout << "FCFS Z FD-SCAN" << '\n';
	fcfs2.run();
	cout << "====" << '\n';
	cout << "FCFS" << '\n';
	fcfs3.run();
	cout << "====" << '\n';
	cout << "SSTF" << '\n';
	sstf.run();
	cout << "====" << '\n';
	cout << "SCAN" << '\n';
	scan.run();
	cout << "====" << '\n';
	cout << "C-SCAN" << '\n';
	cscan.run();
	return 0;
}