#include "MapSV.h"
#include <queue>
#include "Comparador.cpp"

typedef priority_queue<pair<string, int>, vector<pair<string, int>>, Comparador> pq;
typedef vector<pair<string, int>> vp;

MapSV ::MapSV()
{
}

MapSV ::~MapSV()
{
}

int MapSV ::bs(string s, int inicio, int final)
{
    int a = (final + inicio) / 2; // posicion del centro del vector
    if (final < inicio)           // condicion de termino sin no esta el elemento buscado
    {
        return -1;
    }
    if (v[a].first == s) // condicion de termino si el elemento es presente en el vector
    {
        return a;
    }
    else if (v[a].first > s)
    {
        bs(s, inicio, a - 1);
    }
    else
    {
        bs(s, a + 1, final);
    }
}

void heapSort(vector<pair<string, int>> &v)
{
    pq cola;
    for (vp::iterator it = v.begin(); it != v.end(); ++it)
        cola.push(*it);

    v.clear();
    while (!cola.empty())
    {
        v.push_back(cola.top());
        cola.pop();
    }
}

void MapSV ::insert(pair<string, int> p)
{
    if (bs(p.first, 0, v.size() - 1) >= 0) // metodo de busquda binaria
    {
        v.push_back(p);
        heapSort(v);
    }
}

void MapSV ::erase(string key)
{
    int pos = bs(key, 0, v.size() - 1); // busqueda binaria de la clave
    if (pos >= 0)
    {
        v[pos] = v.back(); // cambiamos el elemto en la posicion por el ultimo elemento del vector
        v.pop_back();      // eliminamos el ultimo elemento del vector
        heapSort(v);       // reodernamos el arreglo
    }
}

int MapSV ::at(string key)
{
    int pos = bs(key, 0, v.size() - 1);
    if (pos >= 0)
        return v[pos].second;
}
int MapSV ::size()
{
    return v.size();
}
bool MapSV ::empty()
{
    return v.size() == 0;
}
