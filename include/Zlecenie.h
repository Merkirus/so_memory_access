#ifndef ZLECENIE_H
#define ZLECENIE_H

#include <vector>

class Zlecenie
{
public:
    Zlecenie(unsigned);
    Zlecenie()=default;
    ~Zlecenie();
    static Zlecenie makeZlecenie();
    static bool isUsed(unsigned);
    unsigned getCylinder() const;
    void setCylinder(unsigned);
    bool getRealTime() const;
    void setRealTime(unsigned);
    int getDeadline() const;
    void setDeadline(int);
    int getOczekiwanie() const;
    void setOczekiwanie(int);
    bool operator==(const Zlecenie& p);
private:
    static std::vector<unsigned> used;
    unsigned cylinder;
    bool real_time;
    int deadline;
    int oczekiwanie;
};

#endif
