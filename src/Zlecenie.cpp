#include "Zlecenie.h"
#include "Random.h"
#include <vector>

#define MAX_CYLINDER 200

Zlecenie::Zlecenie(unsigned cylinder)
{
    this->cylinder = cylinder;
    used.push_back(cylinder);
    this->real_time = randnum(0,5) == 1 ? true : false;
    this->deadline = real_time ? randnum(1,100) : 0;
    this->oczekiwanie = 0;
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

int Zlecenie::getDeadline() const
{
    return deadline;
}

void Zlecenie::setDeadline(int deadline)
{
    this->deadline -= deadline;
}

int Zlecenie::getOczekiwanie() const
{
    return oczekiwanie;
}

void Zlecenie::setOczekiwanie(int oczekiwanie)
{
    this->oczekiwanie += oczekiwanie;
}

bool Zlecenie::operator==(const Zlecenie& p)
{
    return (this == &p);
}

Zlecenie Zlecenie::makeZlecenie()
{
    unsigned cylinder;
    do
    {
        cylinder = rand()%MAX_CYLINDER;
    } while (Zlecenie::isUsed(cylinder));
    return Zlecenie{cylinder};
}

std::vector<unsigned> Zlecenie::used = std::vector<unsigned>();
