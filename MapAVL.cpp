#include "MapAVL.h"
#include <stack>

MapAVL ::MapAVL() {
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

int MapAVL::height(nodo *actual) {
  return actual == nullptr ? 0 : actual->height;
}

int MapAVL::max(int x, int y) { return x > y ? x : y; }

void MapAVL::zigzigIzquierda(nodo *z, nodo *padre) {
  nodo *y = z->hijoizq;
  // rotacion hacia la derecha
  z->hijoizq = y->hijoder;
  y->hijoder = z;

  // cambios de altura
  z->height = 1 + max(height(z->hijoizq), height(z->hijoder));
  y->height = 1 + max(height(y->hijoizq), height(y->hijoder));

  if (padre) {
    if (padre->hijoder == z)
      padre->hijoder = y;
    else
      padre->hijoizq = y;
  }
  if (z == root)
    root = y;
}
void MapAVL::zigzigDerecha(nodo *z, nodo *padre) {
  nodo *y = z->hijoder;
  // rotacion hacia la derecha
  z->hijoder = y->hijoizq;
  y->hijoizq = z;

  // cambios de altura
  z->height = 1 + max(height(z->hijoizq), height(z->hijoder));
  y->height = 1 + max(height(y->hijoizq), height(y->hijoder));

  if (padre) {
    if (padre->hijoder == z)
      padre->hijoder = y;
    else
      padre->hijoizq = y;
  }
  if (z == root)
    root = y;
}

void MapAVL::zigzagDerecha(nodo *z, nodo *padre) {
  nodo *y = z->hijoder;
  nodo *x = y->hijoizq;

  y->hijoizq = x->hijoder;
  x->hijoder = y;
  z->hijoder = x->hijoizq;
  x->hijoizq = z;

  z->height = 1 + max(height(z->hijoizq), height(z->hijoder));
  y->height = 1 + max(height(y->hijoizq), height(y->hijoder));
  x->height = 1 + max(height(x->hijoizq), height(x->hijoder));

  if (padre) {
    if (padre->hijoder == z)
      padre->hijoder = x;
    else
      padre->hijoizq = x;
  }

  if (z == root)
    root = x;
}

void MapAVL::zigzagIzquierda(nodo *z, nodo *padre) {
  nodo *y = z->hijoizq;
  nodo *x = y->hijoder;

  y->hijoder = x->hijoizq;
  x->hijoizq = y;
  z->hijoizq = x->hijoder;
  x->hijoder = z;

  z->height = 1 + max(height(z->hijoizq), height(z->hijoder));
  y->height = 1 + max(height(y->hijoizq), height(y->hijoder));
  x->height = 1 + max(height(x->hijoizq), height(x->hijoder));

  if (padre) {
    if (padre->hijoder == z)
      padre->hijoder = x;
    else
      padre->hijoizq = x;
  }

  if (z == root)
    root = x;
}

void MapAVL ::insert(pair<string, int> item) {
  if (root == nullptr) {
    root = new_node(item);
    return;
  }
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
  actual = pila.top();
  if (actual->key > item.first)
    actual->hijoizq = new_node(item);
  else
    actual->hijoder = new_node(item);
  mysize++;
  while (!pila.empty()) {
    actual = pila.top();
    pila.pop();
    actual->height = 1 + max(height(actual->hijoizq), height(actual->hijoder));
    int balance = abs(height(actual->hijoder) - height(actual->hijoizq));
    if (balance > 1) {
      // derecha
      if (actual->key < item.first) { // derecha
        // derecha
        nodo *hijo = actual->hijoder;
        if (hijo->key < item.first) { // derecha
          // zig zig izquerda
          if (actual == root)
            zigzigDerecha(actual, nullptr);
          else
            zigzigDerecha(actual, pila.top());
        }
        // izquierda
        else if (hijo->key > item.first) { // izquierda
          // zig zag derecha
          if (actual == root)
            zigzagDerecha(actual, nullptr);
          else
            zigzagDerecha(actual, pila.top());
        }
      }
      // izquerda
      else if (actual->key > item.first) { // izquierda
        nodo *hijo = actual->hijoizq;
        // izquierda
        if (hijo->key > item.first) { // izquierda
          // zig zig derecha
          if (actual == root)
            zigzigIzquierda(actual, nullptr);
          else
            zigzigIzquierda(actual, pila.top());
        }
        // derecha
        else if (hijo->key < item.first) { // derecha
          // zig zag izquierda derecha
          if (actual == root)
            zigzagIzquierda(actual, nullptr);
          else
            zigzagIzquierda(actual, pila.top());
        }
      }
    }
  }
}

void MapAVL ::erase(string key) {
  nodo *actual = root;
  stack<nodo *> pila;

  while (actual != nullptr) {
    if (actual->key == key) {
      delete actual;
      mysize--;
      break;
    }
    pila.push(actual);
    if (actual->key > key)
      actual = actual->hijoizq;
    else
      actual = actual->hijoder;
  }

  if (actual == nullptr)
    return;

  while (!pila.empty()) {
    actual = pila.top();
    pila.pop();
    actual->height = 1 + max(height(actual->hijoizq), height(actual->hijoder));
    int balance = abs(height(actual->hijoder) - height(actual->hijoizq));
    if (balance > 1) {
      // derecha
      if (height(actual->hijoder) > height(actual->hijoizq)) { // derecha
        // derecha
        nodo *hijo = actual->hijoder;
        if (height(hijo->hijoder) > height(hijo->hijoizq)) { // derecha
          // zig zig izquerda
          zigzigDerecha(actual, pila.top());
        }
        // izquierda
        else if (height(hijo->hijoder) < height(hijo->hijoizq)) { // izquierda
          // zig zag derecha
          zigzagDerecha(actual, pila.top());
        }
      }
      // izquerda
      else if (height(actual->hijoder) < height(actual->hijoizq)) { // izquierda
        nodo *hijo = actual->hijoizq;
        // izquierda
        if (height(hijo->hijoder) < height(hijo->hijoizq)) { // izquierda
          // zig zig derecha
          zigzigIzquierda(actual, pila.top());
        }
        // derecha
        else if (height(hijo->hijoder) > height(hijo->hijoizq)) { // derecha
          // zig zag izquierda derecha
          zigzagIzquierda(actual, pila.top());
        }
      }
      root = actual;
    }
  }
}

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
