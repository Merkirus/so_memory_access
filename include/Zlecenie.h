#ifndef ZLECENIE_H
#define ZLECENIE_H

#include <vector>

class Zlecenie
{
public:
    Zlecenie(unsigned);
    Zlecenie()=default;
    ~Zlecenie();
    static bool isUsed(unsigned);
    unsigned getCylinder() const;
    void setCylinder(unsigned);
    bool getRealTime() const;
    void setRealTime(unsigned);
    unsigned getDeadline() const;
    void setDeadline(unsigned);
    bool operator==(const Zlecenie& p);
private:
    static std::vector<unsigned> used;
    unsigned cylinder;
    bool real_time;
    unsigned deadline;
};

#endif
