#include "Edf.h"
#include <cmath>
#include <algorithm>
#include "Random.h"

#define MAX 10000

Edf::Edf() = default;
Edf::~Edf() = default;

int Edf::run(std::vector<Zlecenie>& v, int prev, long& result, long& cancelled, long& oczekiwanie, int& add_size)
{
    int curr = 0;
    int curr_deadline = 0;
    int droga = 0;
	
    bool right_result = false;
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

		int smallest = MAX;

		for (Zlecenie element : v)
		{
			if (element.getRealTime())
			{
				int odleglosc = element.getCylinder() - local_prev;
				if (abs(odleglosc) < smallest)
				{
					curr = element.getCylinder();
					curr_deadline = element.getDeadline();
					smallest = abs(odleglosc);
				}
			}
		}

		bool real_time_event = false;
		droga = abs(curr-local_prev);

		if (droga < curr_deadline)
			right_result = true;
		if (droga > curr_deadline)
		{
			droga  = curr_deadline;
		    local_prev = local_prev < curr ? local_prev + droga : local_prev - droga;
		}
		
		for (int i=1; i <= droga; ++i)
        {
            for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
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
                    local_prev = local_prev < curr ? local_prev + droga : local_prev - droga;
                    real_time_event = true;
                    break;
                }
            }
        }
        if (real_time_event) continue;
        result += droga;
        if (right_result)
        {
            for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie)
                {
                    if (zlecenie.getCylinder()==curr)
                        oczekiwanie += zlecenie.getOczekiwanie();
                });
        	auto remove = remove_if(v.begin(), v.end(),[&](Zlecenie& zlecenie) ->
        		bool {return zlecenie.getCylinder()==curr;});
            v.erase(remove, v.end());
            local_prev = curr;
        }
    }
    return local_prev;
}

bool Edf::hasRT(std::vector<Zlecenie>& v)
{
	for (Zlecenie element : v)
	{
		if (element.getRealTime()) return true;
	}
	return false;
}
