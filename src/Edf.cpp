#include "Edf.h"
#include <cmath>
#include <algorithm>

#define MAX 10000

Edf::Edf() = default;
Edf::~Edf() = default;

int Edf::run(std::vector<Zlecenie>& v, int prev, long& cancelled)
{
	int curr = 0;
	int curr_deadline = 0;
	int smallest = MAX;
	int size_before = v.size();
	auto remove = remove_if(v.begin(), v.end(),
            [&](Zlecenie& zlecenie) -> bool {
                return (zlecenie.getDeadline() < 0 && zlecenie.getRealTime());
            });
    v.erase(remove, v.end());
    int size_after = v.size();
    cancelled += size_before - size_after;
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
	if (smallest == MAX) return prev;
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
