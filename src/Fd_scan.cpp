#include "Fd_scan.h"
#include <algorithm>
#include <cmath>
#include "Random.h"

Fd_scan::Fd_scan() = default;
Fd_scan::~Fd_scan() = default;

int Fd_scan::run(std::vector<Zlecenie>& v, int prev, long& result, long& cancelled, long& oczekiwanie, int& add_size)
{
	int curr = 0;
	int local_prev = prev;

	while (hasRT(v))
	{
		/* Usuwanie przedawnionych realtime */
		int size_before = v.size();
		auto remove = remove_if(v.begin(), v.end(),
	            [&](Zlecenie& zlecenie) -> bool {
	                return (zlecenie.getDeadline() <= 0 && zlecenie.getRealTime());
	            });
	    v.erase(remove, v.end());
	    int size_after = v.size();
	    cancelled += size_before - size_after;
	    /* --- */

		if (!hasRT(v)) continue;

		int furthest = 0;

		/* Usuwanie wszystkich nie możliwych do realizacji zleceń */
		auto remove5 = remove_if(v.begin(), v.end(),
	            [&](Zlecenie& zlecenie) -> bool {
	            	int odleglosc = zlecenie.getCylinder() - local_prev;
	            	if (zlecenie.getRealTime())
	            	{
		            	if (zlecenie.getDeadline() <= abs(odleglosc))
		            	{
		            		++cancelled;
		            		return true;
		            	}
		                return false;
	            	}
	            	return false;
	            });
	    v.erase(remove5, v.end());
		/* --- */

		/* Znalezienie kolejnego najdalszego realtime,
		który jest możliwy do zrealizowania */
		for (Zlecenie element : v)
		{
			if (element.getRealTime())
			{
				int odleglosc = element.getCylinder() - local_prev;
				if (abs(odleglosc) > furthest)
				{
					furthest = abs(odleglosc);
					curr = element.getCylinder();
				}
			}
		}
		/* --- */
		
		bool real_time_event = false;
		int droga = abs(curr - local_prev);

		for (int i=1; i <= droga; ++i)
	    {
	        for_each(v.begin(), v.end()-1, [&](Zlecenie& zlecenie) {
	            zlecenie.setDeadline(1);});
	        for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
	            zlecenie.setOczekiwanie(1);});
	        if (randnum(0,20) == 1)
	        {
	            Zlecenie nowe = Zlecenie::makeZlecenie();
	            v.push_back(nowe);
	            ++add_size;
	            if (nowe.getRealTime())
	            {
	                droga = i;
	                result += droga;
	                curr = prev < curr ? prev + droga : prev - droga;
	                /* Usuwanie miniętych po drodze procesów */
	                if (curr > local_prev)
	                {
		                auto remove2 = remove_if(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
							return (zlecenie.getCylinder() >= local_prev && zlecenie.getCylinder() <= curr);});
		                v.erase(remove2, v.end());
	                }
	                else
	                {
	                	auto remove2 = remove_if(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
							return (zlecenie.getCylinder() <= local_prev && zlecenie.getCylinder() >= curr);});
	                	v.erase(remove2, v.end());
	                }
	                /* --- */
                	local_prev = curr;
	                real_time_event = true;
	                break;
	            }
	        }
	    }
	    if (real_time_event) continue;
		result += droga;
		/* Usuwanie miniętych po drodze procesów */
		if (curr > local_prev)
        {
            auto remove3 = remove_if(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
				return (zlecenie.getCylinder() >= local_prev && zlecenie.getCylinder() <= curr);});
            v.erase(remove3, v.end());
        }
        else
        {
        	auto remove3 = remove_if(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
				return (zlecenie.getCylinder() <= local_prev && zlecenie.getCylinder() >= curr);});
        	v.erase(remove3, v.end());
        }
        /* --- */
    	local_prev = curr;
	}
	return local_prev;
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