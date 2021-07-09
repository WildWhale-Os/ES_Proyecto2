#include "ADTMap.h"

struct nodo {
  int value;
  int height;
  string key;
  nodo *hijoizq;
  nodo *hijoder;
};

class MapAVL : public ADTMap {
private:
  int mysize;
  nodo *root;
  nodo *new_node(pair<string, int>);
  void balance(string);
  void zigzagIzquierda(nodo *, nodo *);
  void zigzagDerecha(nodo *, nodo *);
  void zigzigIzquierda(nodo *, nodo *);
  void zigzigDerecha(nodo *, nodo *);
  int height(nodo *);
  int max(int, int);

public:
  MapAVL();
  ~MapAVL();
  void insert(pair<string, int>);
  void erase(string);
  int at(string);
  int size();
  bool empty();
};
