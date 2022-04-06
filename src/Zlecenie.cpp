#include "Zlecenie.h"
#include <vector>

#define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))

Zlecenie::Zlecenie(unsigned cylinder)
{
    this->cylinder = cylinder;
    this->real_time = randnum(0,20) == 1 ? true : false;
    this->deadline = real_time ? randnum(1,100) : 0;
}

Zlecenie::~Zlecenie()
{
    auto it = std::remove_if(used.begin(), used.end(),
        [this](unsigned x) {return this->cylinder==x;});
    used.erase(it, used.end());
}

bool Zlecenie::isUsed(unsigned cylinder)
{
    for (unsigned element : used)
    {
        if (element == cylinder)
        {
            return true;
        }
    }
    return false;
}

unsigned Zlecenie::getCylinder() const
{
    return cylinder;
}

bool Zlecenie::getRealTime() const
{
    return real_time;
}

unsigned Zlecenie::getDeadline() const
{
    return deadline;
}

bool Zlecenie::operator==(const Zlecenie& p) {
    return (this == &p);
}

std::vector<unsigned> Zlecenie::used = std::vector<unsigned>();
