#include "Edf.h"
#include <cmath>
#include <algorithm>

#define MAX 10000

Edf::Edf() = default;
Edf::~Edf() = default;

int Edf::run(std::vector<Zlecenie>& v, int prev, int& cancelled)
{
	int curr = 0;
	int curr_deadline = 0;
	int smallest = MAX;
	for (Zlecenie element : v)
	{
		if (element.getRealTime())
		{
			int odleglosc = element.getCylinder() - prev;
			if (abs(odleglosc) < smallest)
			{
				curr = element.getCylinder();
				curr_deadline = element.getDeadline();
				smallest = abs(odleglosc);
			}
		}
	}
	int droga = abs(curr-prev);
	if (droga > curr_deadline)
	{
		droga  = curr_deadline;
		++cancelled;
		auto remove = remove_if(v.begin(), v.end(),
	                    [&](Zlecenie& zlecenie) -> bool {return zlecenie.getCylinder()==curr;});
	    v.erase(remove, v.end());
	}
	return prev < curr ? prev + droga : prev - droga;
}

bool Edf::hasRT(std::vector<Zlecenie>& v)
{
	for (Zlecenie element : v)
	{
		if (element.getRealTime()) return true;
	}
	return false;
}
