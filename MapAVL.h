#include "ADTMap.h"

class MapAVL : public ADTMap
{
private:
    int mysize;

public:
    MapAVL(int);
    ~MapAVL();
    void insert(pair<string, int>);
    void erase(string);
    int at(string);
    int size();
    bool empty();
};
