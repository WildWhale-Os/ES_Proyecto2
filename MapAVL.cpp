#include "MapAVL.h"
#include <stack>
#include <utility>

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
    mysize = 1;
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

nodo *minimo(nodo *actual) {
  if (actual->hijoizq == nullptr)
    return actual;
  return minimo(actual->hijoizq);
}
nodo *maximo(nodo *actual) {
  if (actual->hijoder == nullptr)
    return actual;
  return maximo(actual->hijoder);
}

void MapAVL::erase(string key) {
  nodo *actual = root;
  stack<nodo *> path;
  path.push(nullptr);

  while (actual && actual->key != key) {
    path.push(actual);
    if (actual->key < key)
      actual = actual->hijoder;
    else if (actual->key > key)
      actual = actual->hijoizq;
  }
  // (la llave buscada no esta) si actual == nullptr no esta la key
  if (!actual)
    return;
  // buscamos succesor o antescesor
  nodo *change = nullptr;
  nodo *borrado = actual;
  nodo *padre = nullptr;
  actual = nullptr;
  bool succesor;
  if (borrado->hijoder) {
    change = minimo(borrado->hijoder);
    succesor = true;
  } else if (borrado->hijoizq) {
    change = maximo(borrado->hijoizq);
    succesor = false;
  }
  // llave buscada esta une una hoja
  if (!change) {
    padre = path.top();
    if (padre) {
      if (padre->key < borrado->key)
        padre->hijoder = nullptr;
      else
        padre->hijoizq = nullptr;
    } else
      root = nullptr;
  }
  // la llave a borrar en la raiz del AVL
  else if (borrado == root) {
    path.push(change);
    nodo *travel;
    // para que lada tienemos que llevar el path
    if (succesor) {
      // derecha
      travel = borrado->hijoder;
    } else {
      // izquierda
      travel = borrado->hijoizq;
    }
    // bajar por el AVL hasta llegar al succesor o hasta el antescesor
    while (travel != change) {
      padre = travel;
      path.push(padre);
      if (succesor)
        travel = travel->hijoizq;
      else
        travel = travel->hijoder;
    }
    // si llegamos al succesor o anteccesor y el valor de padre es distinto de
    // null si padre es null entonces el padre de change es borrado
    if (padre) {
      if (succesor)
        padre->hijoizq = change->hijoder;
      else
        padre->hijoder = change->hijoizq;
      change->hijoder = root->hijoder;
      change->hijoizq = root->hijoizq;
    } else {
      if (succesor)
        change->hijoizq = root->hijoizq;
      else
        change->hijoder = root->hijoder;
    }
    // desconectar subarboles del nodo borrado
    borrado->hijoizq = nullptr;
    borrado->hijoder = nullptr;
    // cambiar root
    root = change;
  }

  // si actual != root path como minimo posee nullptr y root
  // si es nodo interno no root
  else { 
    padre = path.top();
    path.push(change);
    // nodo viajero
    nodo *travel;
    // primera posicion del viajero
    if (succesor)
      travel = borrado->hijoder;
    else
      travel = borrado->hijoizq;
    // viajamos por el arbol hasta encontrar al succesor o antescesor
    while (travel != change) {
      actual = travel;
      path.push(actual);
      if (succesor)
        travel = travel->hijoizq;
      else
        travel = travel->hijoder;
    }
    // si cambio el valor de padre
    if (actual) {
      // actualizamos los punteros del padre
      if (succesor)
        actual->hijoizq = change->hijoder;
      else
        actual->hijoder = change->hijoizq;
      // actualizamos los punteros hijos del succesor o antescesor
      change->hijoder = borrado->hijoder;
      change->hijoizq = borrado->hijoizq;
    } else {
      // padre es el nodo borrado
      // actualizamos un unico nodo hijo del antecesor o sucesor
      if (succesor)
        change->hijoizq = borrado->hijoizq;
      else
        change->hijoder = borrado->hijoder;
    }
    // actuilizamos uno de los hijos del padre del borrado
    if (padre->hijoizq == borrado)
      padre->hijoizq = change;
    else
      padre->hijoder = change;
    // desconectar el nodo borrado del AVL
    borrado->hijoizq = nullptr;
    borrado->hijoder = nullptr;
  }
  delete borrado;
  mysize--;
  while (path.top()) {
    // balance
    actual = path.top();
    path.pop();
    actual->height = 1 + max(height(actual->hijoizq), height(actual->hijoder));
    int balance = abs(height(actual->hijoder) - height(actual->hijoizq));
    if (balance > 1) {
      // derecha
      if (height(actual->hijoder) > height(actual->hijoizq)) { // derecha
        // derecha
        nodo *hijo = actual->hijoder;
        if (height(hijo->hijoder) >= height(hijo->hijoizq)) { // derecha
          // zig zig izquerda
          zigzigDerecha(actual, path.top());
        }
        // izquierda
        else if (height(hijo->hijoder) < height(hijo->hijoizq)) { //
                                                                  // izquierda
          // zig zag derecha
          zigzagDerecha(actual, path.top());
        }
      }
      // izquerda
      else if (height(actual->hijoder) < height(actual->hijoizq)) { //
        // izquierda
        nodo *hijo = actual->hijoizq;
        // izquierda
        if (height(hijo->hijoder) <= height(hijo->hijoizq)) { // izquierda
          // zig zig izquierda
          zigzigIzquierda(actual, path.top());
        }
        // derecha
        else if (height(hijo->hijoder) > height(hijo->hijoizq)) { // derecha
          // zig zag izquierda derecha
          zigzagIzquierda(actual, path.top());
        }
      }
    }
  }
}