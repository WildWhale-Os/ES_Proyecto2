#include "ADTMap.h"
#include <math.h>

class MapH{
    private:
        int mysize;
        double alfa=0.5;
        vector <pair <string,int>> v;
        void agrandar();
        int HashG1(string s);
        int HashG2(int s);
        int colisionesins,colisionesat;
    public:
        MapH(int n);
        ~MapH();
        int getcit();
        int getcat();
        void insert(pair <string,int> p);
        void erase(string s);
        int at(string s);
        int size();
        bool empty();
};