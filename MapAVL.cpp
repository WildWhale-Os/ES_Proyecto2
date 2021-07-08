#include "MapAVL.h"
#include <stack>

MapAVL ::MapAVL(int) {
  mysize = 0;
  root = nullptr;
}

MapAVL ::~MapAVL() {}

nodo *MapAVL::new_node(pair<string, int> item) {
  nodo *actual = new nodo();
  actual->value = item.second;
  actual->key = item.first;
  actual->hijoizq = nullptr;
  actual->hijoder = nullptr;
  actual->height = 1;

  return actual;
}

int height(nodo *actual) { return actual == nullptr ? 0 : actual->height; }

nodo *MapAVL::dfs(nodo *actual, string key) {
  if (!actual)
    return actual;
  dfs(actual->hijoizq, key);

  dfs(actual->hijoder, key);

  actual->height = 1 + max(height(actual->hijoizq), height(actual->hijoder));
  int dif = height(actual->hijoizq) - height(actual->hijoder);

  if (abs(dif) <= 1)
    return actual;
  // caso izquerda izquerda
  if (dif > 1 && key < actual->hijoizq->key)
    return rotacion_derecha(actual);
  // caso derecha derecha
  if (dif < -1 && key > actual->hijoder->key)
    return rotacion_izquerda(actual);
  // caso izquierda derecha
  if (dif > 1 && key > actual->hijoizq->key) {
    actual->hijoizq = rotacion_izquerda(actual->hijoizq);
    return rotacion_derecha(actual);
  }
  // caso derecha izquerda
  // if (dif < -1 && key < root->hijoder->key) {
  actual->hijoder = rotacion_derecha(actual->hijoder);
  return rotacion_izquerda(actual);
  //}
}

int max(int x, int y) { return x > y ? x : y; }

void MapAVL ::balance(string key) {
  if (root->key > key)
    root->hijoizq = dfs(root->hijoizq, key);
  else
    root->hijoder = dfs(root->hijoder, key);
  root->height = 1 + max(height(root->hijoizq), height(root->hijoder));
  int dif = height(root->hijoizq) - height(root->hijoder);
  if (abs(dif) <= 1)
    return;
  // caso izquierda izquierda
  if (dif > 1 && key < root->hijoizq->key) {
    root = rotacion_derecha(root);
    return;
  }
  // caso derecha derecha
  if (dif < -1 && key > root->hijoder->key) {
    root = rotacion_izquerda(root);
    return;
  }
  // izquerda derecha
  if (dif > 1 && key > root->hijoizq->key) {
    root->hijoizq = rotacion_izquerda(root->hijoizq);
    root = rotacion_derecha(root);
    return;
  }
  // derecha izquierda
  if (dif < -1 && key < root->hijoder->key) {
    root->hijoder = rotacion_derecha(root->hijoder);
    root = rotacion_izquerda(root);
  }
}

void MapAVL ::insert(pair<string, int> item) {
  nodo *actual = root;
  stack<nodo *> pila;

  while (actual != nullptr) {
    if (actual->key == item.first)
      return;
    pila.push(actual);
    if (actual->key > item.first)
      actual = actual->hijoizq;
    else
      actual = actual->hijoder;
  }
  actual = new_node(item);
  while (!pila.empty()) {
    actual = pila.top();
    pila.pop();
    int balance = abs()
  }
}

void MapAVL ::erase(string) {}

int MapAVL ::at(string key) {
  nodo *actual = root;
  while (actual != nullptr) {
    if (actual->key == key)
      return actual->value;
    if (actual->key > key)
      actual = actual->hijoizq;
    else
      actual = actual->hijoder;
  }
  return -1;
}
int MapAVL ::size() { return mysize; }
bool MapAVL ::empty() { return mysize == 0; }
