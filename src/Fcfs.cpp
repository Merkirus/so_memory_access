#include <iostream>
#include <cmath>
#include "Fcfs.h"
#include "Random.h"

#define MAX 20

Fcfs::Fcfs(std::vector<Zlecenie> v, IAlgo& rt_algo)
: v{v}, rt_algo{&rt_algo} {}

Fcfs::~Fcfs()
{
    delete rt_algo;
}

void Fcfs::run()
{
    int size, add_size;
    int curr, prev;
    int result, canceled;

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
                curr = rt_algo->run(v, prev, canceled);
                droga = abs(curr-prev);
                for (int i=1; i <= droga; ++i)
                {
                    if (randnum(0,50) == 1)
                    {
                        Zlecenie nowe = Zlecenie::makeZlecenie();
                        v.push_back(nowe);
                        ++add_size;
                        if (nowe.getRealTime())
                        {
                            droga = i;
                            result += droga;
                            curr = prev < curr ? curr - droga : curr + droga;
                            real_time_event = true;
                            break;
                        }
                    }
                }
                if (real_time_event) continue;
                result += droga;
                auto remove = remove_if(v.begin(), v.end(),
                        [&](Zlecenie& zlecenie) -> bool {
                            return (zlecenie.getCylinder()==curr && zlecenie.getDeadline());
                        });
                v.erase(remove, v.end());
            }
            else
            {
                curr = v.front().getCylinder();
                droga = abs(curr-prev);
                for (int i=1; i <= droga; ++i)
                {
                    if (randnum(0,50) == 1)
                    {
                        Zlecenie nowe = Zlecenie::makeZlecenie();
                        v.push_back(nowe);
                        ++add_size;
                        if (nowe.getRealTime())
                        {
                            droga = i;
                            result += droga;
                            curr = prev < curr ? curr - droga : curr + droga;
                            real_time_event = true;
                            break;
                        }
                    }
                }
                if (real_time_event) continue;
                result += droga;
                v.erase(v.begin());
            }
        }  
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
                if (randnum(0,20) == 1)
                {
                    Zlecenie nowe = Zlecenie::makeZlecenie();
                    v.push_back(nowe);
                    ++add_size;
                }
            }
            result += droga;
            v.erase(v.begin());
        }
    }
    std::cout << result << std::endl;
    std::cout << canceled << std::endl;
}