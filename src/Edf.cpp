#include "Edf.h"
#include <cmath>

#define MAX_MIN 1000

Edf::Edf() = default;
Edf::~Edf() = default;

int Edf::run(std::vector<Zlecenie>& v, int curr, int& result)
{
	Zlecenie curr_zlecenie;
	Zlecenie next_zlecenie;
	for (Zlecenie element : v)
	{
		if (element.getCylinder() == curr) curr_zlecenie = element;
		break;
	}
	int min = MAX_MIN;
	for (Zlecenie element : v)
	{
		if (element.getRealTime())
		{
			if (element.getDeadline() < min)
			{
				min = element.getDeadline();
				next_zlecenie = element;
			}
		}
	}
	int odleglosc = next_zlecenie.getCylinder() - curr_zlecenie.getCylinder();
	odleglosc = abs(odleglosc);
	result += odleglosc > min ? min : odleglosc;
	return next_zlecenie.getCylinder();
}

bool Edf::hasRT(std::vector<Zlecenie>& v)
{
	for (Zlecenie element : v)
	{
		if (element.getRealTime()) return true;
	}
	return false;
}

bool Edf::tooFar(std::vector<Zlecenie>& v, int curr)
{
	Zlecenie curr_zlecenie;
	Zlecenie next_zlecenie;
	for (Zlecenie element : v)
	{
		if (element.getCylinder() == curr) curr_zlecenie = element;
		break;
	}

	int min = MAX_MIN;
	for (Zlecenie element : v)
	{
		if (element.getRealTime())
		{
			if (element.getDeadline() < min)
			{
				min = element.getDeadline();
				next_zlecenie = element;
			}
		}
	}
	int odleglosc = curr_zlecenie.getCylinder() - next_zlecenie.getCylinder();
	odleglosc = abs(odleglosc);
	if (odleglosc > min) return true;
	return false;
}