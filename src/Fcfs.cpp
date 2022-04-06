#include <iostream>
#include "Fcfs.h"
#include <cmath>

#define MAX 200

Fcfs::Fcfs(std::vector<Zlecenie> v, IAlgo* rt_algo)
: v{v}, rt_algo{*rt_algo} {}

void Fcfs::run()
{
    int size, add, curr, result, canceled;

    size = v.size();
    result = 0;
    add = 0;
    canceled = 0;

    for (Zlecenie element : v) std::cout << element.getCylinder() << std::endl;

    if (size != 0)
    {
        curr = v.front().getCylinder();
        v.erase(v.begin());
    } 

    while (!v.empty() && size + add < MAX)
    {
        if (rt_algo.hasRT(v))
        {
            if (rt_algo.tooFar(v, curr))
            {
                curr = rt_algo.run(v, curr, result);
                auto it = std::remove_if(v.begin(), v.end(),
                [&](Zlecenie& z) {return z.getCylinder() == curr;});
                v.erase(it, v.end());
                ++canceled;
            }
            else
            {
                curr = rt_algo.run(v, curr, result);
                auto it = std::remove_if(v.begin(), v.end(),
                    [&](Zlecenie& z) {return z.getCylinder() == curr;});
                v.erase(it, v.end());
            }
        }
        else
        {
            int temp = curr;
            curr = v.front().getCylinder();
            result += abs(temp-curr);
            v.erase(v.begin());
        }
    }

    std::cout << result << std::endl;
    std::cout << canceled << std::endl;
}