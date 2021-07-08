#include "ADTMap.h"

struct nodo{
    int value;
    int height;
    string key;
    nodo *hijoizq;
    nodo *hijoder;
};

class MapAVL : public ADTMap
{
private:
    int mysize;
    nodo *root;
    nodo *new_node(pair<string,int>); 
    void balance(string);   
    nodo* rotacion_derecha(nodo*);
    nodo* rotacion_izquerda(nodo*);
    nodo* dfs(nodo*, string);

public:
    MapAVL(int);
    ~MapAVL();
    void insert(pair<string, int>);
    void erase(string);
    int at(string);
    int size();
    bool empty();
};
