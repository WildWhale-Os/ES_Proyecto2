#include "MapH.h"

MapH::MapH(int n) {
  mysize = 0;
  colisionesat = 0;
  colisionesins = 0;
  n = n / 2;
  if (n % 2 == 0) {
    n++;
  }
  v.resize(n);
}

MapH::~MapH() { v.clear(); }

int MapH::HashG1(string s) {
  long long int numH = 0;
  int n;
  for (int i = 0; i < s.size(); i++) {
    numH = numH + s[i] * pow(13, i);
  }
  n = (int)numH % v.size();
  return n;
}

int MapH::HashG2(int s) {
  int numH = (s / 7) + 3;
  return numH % v.size();
}

int MapH::getcit() { return colisionesins; }

int MapH::getcat() { return colisionesat; }

void MapH::agrandar() {
  double load_factor = (double)mysize / (double)v.size();
  if (load_factor > 0.5) {
    int n = v.size() * 2;
    if (n % 2 == 0) {
      n++;
    }
    vector<pair<string, int>> v1;
    v1 = v;
    v.clear();
    v.resize(n);
    for (int i = 0; i < v1.size(); i++) {
      if (v1[i].first != "" and v1[i].first != "##") {
        int ins = HashG1(v1[i].first);
        int j = 0, pos;
        int hash2 = HashG2(ins);
        do {
          pos = (ins + j * hash2) % v.size();
          j++;
        } while (v[pos].first != "");
        v[pos] = v1[i];
      }
    }
  }
}

void MapH::insert(pair<string, int> p) {
  agrandar();
  int h1 = HashG1(p.first);
  int h2 = HashG2(h1);
  int j = 0, pos, auxpos = -1;
  do {
    pos = (h1 + j * h2) % v.size();
    j++;
    if (v[pos].first == p.first)
      return;
    if (v[pos].first == "##" && auxpos == -1)
      auxpos = pos;
  } while (v[pos].first != "");
  if (auxpos == -1)
    v[pos] = p;
  else
    v[auxpos] = p;
  colisionesins += (j - 1);
  mysize++;
}

void MapH::erase(string key) {
  int h1 = HashG1(key);
  int h2 = HashG2(h1);
  int pos, j = 0;
  do {
    pos = (h1 + j * h2) % v.size();
    if (v[pos].first == "")
      return;
    j++;
  } while (v[pos].first != key);
  v[pos].first = "##";
  mysize--;
}

int MapH::at(string key) {
  int h1 = HashG1(key);
  int h2 = HashG2(h1);
  int j = 0, pos;
  do {
    pos = (h1 + j * h2) % v.size();
    if (v[pos].first == key) {
      colisionesat += j;
      return v[pos].second;
    }
    j++;
  } while (v[pos].first != "");
  colisionesat += j;
  return -1;
}

int MapH::size() { return mysize; }

bool MapH::empty() { return mysize == 0; }