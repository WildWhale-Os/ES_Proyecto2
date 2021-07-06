#include "MapSV.h"
#include <algorithm>
#include <queue>


typedef vector<pair<string, int>> vp;

MapSV ::MapSV() {}

MapSV ::~MapSV() {}

int MapSV ::bs(string s, int inicio, int final) {
  if (final >= inicio) // condicion de termino sin no esta el elemento buscado
  {
    int a = (final + inicio) / 2; // posicion del centro del vector
    if (v[a].first == s)
      // condicion de termino si el elemento es presente en el vector
      return a;
    if (v[a].first > s)
      return bs(s, inicio, a - 1);

    return bs(s, a + 1, final);
  }
  return -1;
}

struct comparador {
  bool operator()(pair<string, int> x, pair<string, int> y) {
    return x.first < y.first;
  }
} comparador;

void MapSV ::insert(pair<string, int> p) {
  if (bs(p.first, 0, v.size() - 1) == -1) // metodo de busquda binaria
  {
    v.push_back(p);
    sort(v.begin(), v.end(), comparador);
  }
}

void MapSV::erase(string key) {
  int pos = bs(key, 0, v.size() - 1); // busqueda binaria de la clave
  if (pos >= 0) {
    v[pos] = v.back(); // cambiamos el elemto en la posicion por el ultimo
                       // elemento del vector
    v.pop_back();      // eliminamos el ultimo elemento del vector
                       // reodernamos el arreglo
    sort(v.begin(), v.end(), comparador);
  }
}

int MapSV::at(string key) {

  int pos = bs(key, 0, v.size() - 1);
  // int pos = binary_search(v, 0, v.size() - 1, key);
  if (pos == -1)
    return -1;
  return v[pos].second;
}

int MapSV ::size() { return v.size(); }
bool MapSV ::empty() { return v.size() == 0; }
