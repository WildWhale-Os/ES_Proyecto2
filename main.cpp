#include "ES_Proyecto2/MapAVL.h"
#include "ES_Proyecto2/MapH.h"
#include "ES_Proyecto2/MapSV.h"
#include <algorithm>
#include <fstream>
#include <time.h>

using namespace std;

int main() {
  ifstream in("words.txt");
  vector<string> words;
  clock_t start, stop;
  double time;
  while (!in.eof()) {
    string word;
    in >> word;
    words.push_back(word);
  }
  in.close();
  random_shuffle(words.begin(), words.end());
  ofstream insert("insert_data.csv");
  ofstream at("at_data.csv");
  ofstream no_at("noAt_data.csv");

  insert << "N,MapSV,MapH,MapAVL\n";
  insert << "0,0,0,0\n";
  at << "N,MapSV,MapH,MapAVL\n";
  no_at << "N,MapSV,MapH,MapAVL\n";
  at << "0,0,0,0\n";
  no_at << "0,0,0,0\n";

  for (int i = 99; i < words.size(); i += 100) {

    MapH h(i);
    MapSV sv;
    MapAVL av;
    insert << i;
    at << i;
    no_at << i;

    start = clock();
    for (int j = 0; j < i; ++j)
      sv.insert(pair<string, int>(words[j], j));
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    insert << "," << time;

    start = clock();
    for (int j = 0; j < i; ++j)
      h.insert(pair<string, int>(words[j], j));
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    insert << "," << time;

    start = clock();
    for (int j = 0; j < i; ++j)
      av.insert(pair<string, int>(words[j], j));
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    insert << "," << time << endl;
    // busquda
    start = clock();
    for (int j = 0; j < i; ++j)
      sv.at(words[j]);
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    at << "," << time;

    start = clock();
    for (int j = 0; j < i; ++j)
      h.at(words[j]);
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    at << "," << time;

    start = clock();
    for (int j = 0; j < i; ++j)
      av.at(words[j]);
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    at << "," << time << endl;

    // no at
    start = clock();
    for (int j = 0; j < i; ++j)
      sv.at("zapping");
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    no_at << "," << time;

    start = clock();
    for (int j = 0; j < i; ++j)
      h.at("zapping");
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    no_at << "," << time;
    start = clock();
    for (int j = 0; j < i; ++j)
      av.at("zapping");
    stop = clock();
    time = ((double)(stop - start) / CLOCKS_PER_SEC) / i;
    no_at << "," << time << endl;
  }
  // probando erase
  MapAVL av;
  for (int i = 0; i < 100; i++)
    av.insert(pair<string, int>(words[i], i));
  cout << av.size() << endl;
  for (int i = 30; i >= 0; i--) {
    cout << "Borrando " << words[i] << " " << i << endl;
    av.erase(words[i]);
  }
  for (int i = 0; i < 100; i++) {
    cout << "buscando " << words[i] << " " << i << endl;
    if (av.at(words[i]) != -1)
      cout << "se encuentra\n";
    else
      cout << "No se Encuentra en ningun lugar de la faz de la tierra\n";
  }
  cout << av.size() << endl;
  // insert.close();
  // at.close();
  return 0;
}
