#include <iostream>

using namespace std;

class Comparador
{
    bool reverse;

public:
    Comparador(const bool &revparam = false)
    {
        reverse = revparam;
    }
    bool operator()(const pair<string, int> x, const pair<string, int> y) const
    {
        if (reverse)
            return (x.first > y.first);
        else
            return (x.first < y.first);
    }
};