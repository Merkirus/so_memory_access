#include "Fd_scan.h"
#include <algorithm>
#include <cmath>

Fd_scan::Fd_scan() = default;
Fd_scan::~Fd_scan() = default;

int Fd_scan::run(std::vector<Zlecenie>& v, int prev, long& cancelled)
{
	int curr = 0;
	int curr_deadline = 0;
	int furthest = 0;
	int size_before = v.size();
	auto remove = remove_if(v.begin(), v.end(),
            [&](Zlecenie& zlecenie) -> bool {
            	if (zlecenie.getRealTime())
            	{
            		int odleglosc = zlecenie.getCylinder() - prev;
            		return (zlecenie.getDeadline() < abs(odleglosc));
            	}
                return false;
            });
    v.erase(remove, v.end());
    int size_after = v.size();
    cancelled += size_before - size_after;
	for (Zlecenie element : v)
	{
		if (element.getRealTime())
		{
			int odleglosc = element.getCylinder() - prev;
			if (abs(odleglosc) > furthest)
			{
				furthest = abs(odleglosc);
				curr = element.getCylinder();
			}
		}
	}

	if (furthest == 0) return prev;

	auto remove2 = remove_if(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
		return (zlecenie.getCylinder() >= prev && zlecenie.getCylinder() < curr);
	});
	v.erase(remove2, v.end());
	return curr;
}

bool Fd_scan::hasRT(std::vector<Zlecenie>& v)
{
	for (Zlecenie element : v)
	{
		if (element.getRealTime())
			return true;
	}
	return false;
}