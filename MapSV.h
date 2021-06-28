#include "ADTMap.h"

class MapSV : public ADTMap
{
private:
    vector<pair<string, int>> v;
    int MapSV ::bs(string, int, int);

public:
    MapSV();
    ~MapSV();
    void insert(pair<string, int>);
    void erase(string);
    int at(string);
    int size();
    bool empty();
};
