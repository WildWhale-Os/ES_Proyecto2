#include "ADTMap.h"

class MapH : public ADTMap
{
private:
    vector<pair<string, int>> v;

public:
    MapH();
    ~MapH();
    void insert(pair<string, int>);
    void erase(string);
    int at(string);
    int size();
    bool empty();
};