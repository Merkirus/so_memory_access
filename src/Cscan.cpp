#include "Cscan.h"
#include "Random.h"
#include <algorithm>
#include <cmath>
#include <iostream>

#define MAX 200

Cscan::Cscan(std::vector<Zlecenie> v) : v{v} {}

void Cscan::run()
{
	int size, add_size;
	int curr, prev;
	long result, reset;

	long oczekiwanie = 0;

	size = v.size();
	add_size = 0;
	result = 0;
	reset = 0;

	if (size != 0)
	{
		curr = v.front().getCylinder();
	}

	while (v.size() != 1 && size + add_size < MAX)
	{
		prev = curr;
		sort(v.begin(), v.end(), [&](Zlecenie& first, Zlecenie& second)
			{return first.getCylinder() < second.getCylinder();});

		auto pPrev = find_if(v.begin(), v.end(), [&](Zlecenie& zlecenie)
				{return zlecenie.getCylinder() == prev;});


		if (++pPrev != v.end())
		{
			curr = pPrev->getCylinder();
			int droga = abs(curr-prev);
			for (int i=1; i <= droga; ++i)
			{
				if (randnum(0,20) == 1)
				{
					Zlecenie nowe = Zlecenie::makeZlecenie();
					v.push_back(nowe);
					++add_size;
					if (nowe.getCylinder() > prev+i && nowe.getCylinder() < curr)
					{
						curr = nowe.getCylinder();
						droga = abs(curr-prev);
					}
				}
				for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
					zlecenie.setOczekiwanie(1);});
			}
			result += droga;
			oczekiwanie += (pPrev-1)->getOczekiwanie();
			v.erase(pPrev-1);
		}
		else
		{
			curr = v.front().getCylinder();
			++reset;
			oczekiwanie += (pPrev-1)->getOczekiwanie();
			v.erase(pPrev-1);
		}
	}

	std::cout << result << std::endl;
	std::cout << "Przesunięcia głowicy " << reset << std::endl;
	std::cout << "Średnie oczekiwanie " << oczekiwanie/(size+add_size) << std::endl;
}