#include "Scan.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include "Random.h"

#define MAX 200

Scan::Scan(std::vector<Zlecenie> v) : v{v} {}

void Scan::run()
{
	int size, add_size;
	int curr, prev;
	long result, cancelled;

	long oczekiwanie = 0;

	size = v.size();
	add_size = 0;
	result = 0;
	cancelled = 0;

	if (size != 0)
	{
		curr = v.front().getCylinder();
	}

	/* 1 ->, 0 <- */
	bool to_right = true;

	while (v.size() != 1 && size + add_size <  MAX)
	{
		prev = curr;
		if (to_right)
			sort(v.begin(), v.end(), [&](Zlecenie& first, Zlecenie& second)
				{return first.getCylinder() < second.getCylinder();});
		else sort(v.begin(), v.end(), [&](Zlecenie& first, Zlecenie& second)
				{return first.getCylinder() > second.getCylinder();});

		auto pPrev = find_if(v.begin(), v.end(), [&](Zlecenie& zlecenie)
				{return zlecenie.getCylinder() == prev;});

		if (++pPrev != v.end())
		{
			curr = pPrev->getCylinder();
			int droga = abs(curr-prev);
			for (int i=1; i <= droga; ++i)
			{
				for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
					zlecenie.setOczekiwanie(1);});
				if (randnum(0,20) == 1)
				{
					Zlecenie nowe = Zlecenie::makeZlecenie();
					v.push_back(nowe);
					++add_size;
					if (to_right)
					{
						if (nowe.getCylinder() > prev+i && nowe.getCylinder() < curr)
						{
							curr = nowe.getCylinder();
							droga = abs(curr-prev);
						}
					}
					else
					{
						if (nowe.getCylinder() < prev-i && nowe.getCylinder() > curr)
						{
							curr = nowe.getCylinder();
							droga = abs(curr-prev);
						}
					}
				}
			}
			result += droga;
			v.erase(pPrev-1);
			auto current_curr = find_if(v.begin(), v.end(), [&](Zlecenie& zlecenie)
				{return zlecenie.getCylinder() == curr;});
			oczekiwanie += current_curr->getOczekiwanie();
		}
		else to_right = (to_right==true) ? false : true;
	}

	std::cout << "Łączna liczba przewiniętych cylindrów " << result << std::endl;
	std::cout << "Średnie oczekiwanie " << oczekiwanie/(size+add_size) << std::endl;
}