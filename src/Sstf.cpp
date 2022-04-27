#include "Sstf.h"
#include "Random.h"

#define MAX 200

Sstf::Sstf(std::vector<Zlecenie> v) : v{v} {}

void Sstf::run()
{
	int size, add_size;
	int curr, prev;
	long result, cancelled;

	long oczekiwanie;

	size = v.size();
	add_size = 0;
	result = 0;
	cancelled = 0;
	oczekiwanie = 0;

	if (size != 0)
	{
		curr = v.front().getCylinder();
		v.erase(v.begin());
	}

	while (!v.empty() && size + add_size < MAX)
	{
		prev = curr;
		curr = v.front().getCylinder();
		int droga = abs(curr - prev);
		for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
			int temp  = zlecenie.getCylinder();
			if (abs(temp-prev) < droga)
			{
				curr = zlecenie.getCylinder();
				droga = abs(curr-prev);
			}
		});
		for (int i=1; i <= droga; ++i)
		{
			for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
				zlecenie.setOczekiwanie(1);});
			if (randnum(0,20) == 1)
			{
				Zlecenie nowe = Zlecenie::makeZlecenie();
				v.push_back(nowe);
				++add_size;
				if (curr > prev)
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
		auto remove = remove_if(v.begin(), v.end(),
                [&](Zlecenie& zlecenie) -> bool {
                	return (zlecenie.getCylinder()==curr);
                });
		oczekiwanie += remove->getOczekiwanie();
        v.erase(remove, v.end());
	}
	std::cout << "Łączna liczba przewiniętych cylindrów " << result << std::endl;
	std::cout << "Średnie oczekiwanie " << oczekiwanie/(size+add_size) << std::endl;
}