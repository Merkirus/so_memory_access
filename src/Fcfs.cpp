#include <iostream>
#include <cmath>
#include "Fcfs.h"
#include "Random.h"

#define MAX 200

Fcfs::Fcfs(std::vector<Zlecenie> v, IAlgo& rt_algo)
: v{v}, rt_algo{&rt_algo} {}

Fcfs::Fcfs(std::vector<Zlecenie> v)
: v{v}, rt_algo{nullptr} {}

Fcfs::~Fcfs()
{
    delete rt_algo;
}

void Fcfs::run()
{
    int size, add_size;
    int curr, prev;
    long result, canceled;

    long oczekiwanie = 0;

    size = v.size();
    add_size = 0;
    result = 0;
    canceled = 0;

    if (size != 0)
    {
        curr = v.front().getCylinder();
        v.erase(v.begin());
    }

    if (rt_algo)
    {
        while (!v.empty() && size + add_size < MAX)
        {
            bool real_time_event = false;
            prev = curr;
            int droga = 0;
            if (rt_algo->hasRT(v))
            {
                prev = rt_algo->run(v, prev, result, canceled, oczekiwanie, add_size);
            }
            else
            {
                curr = v.front().getCylinder();
                droga = abs(curr-prev);
                for (int i=1; i <= droga; ++i)
                {
                    for_each(v.begin(), v.end(), [&](Zlecenie& zlecenie) {
                        zlecenie.setOczekiwanie(1);});
                    for_each(v.begin(), v.end()-1, [&](Zlecenie& zlecenie) {
                        zlecenie.setDeadline(1);});
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
                            real_time_event = true;
                            break;
                        }
                    }
                }
                if (real_time_event) continue;
                result += droga;
                oczekiwanie += v.begin()->getOczekiwanie();
                v.erase(v.begin());
            }
        }
        std::cout << "Łączna liczba przewiniętych cylindrów " << result << std::endl;
        std::cout << "Średnie oczekiwanie " << oczekiwanie << std::endl;
        std::cout << "Anulowane procesy " << canceled << std::endl;
    }
    else
    {
        while (!v.empty() && size + add_size < MAX)
        {
            prev = curr;
            curr = v.front().getCylinder();
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
                    
                }
            }
            result += droga;
            oczekiwanie += v.begin()->getOczekiwanie();
            v.erase(v.begin());
        }
        std::cout << "Łączna liczba przewiniętych cylindrów " << result << std::endl;
        std::cout << "Średnie oczekiwanie " << oczekiwanie << std::endl;
    }
}