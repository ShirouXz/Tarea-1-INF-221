/*
 + Implementacion de PatienceSort.
 + Fuente: GeeksforGeeks [https://www.geeksforgeeks.org/dsa/patience-sorting/].
 + Optimizacion: Busqueda binaria (lower_bound) y extraccion mediante Min-Heap 
  (priority_queue) basadas en el ppt de "Repaso Estructuras de Datos". Esta optimizacion permite pasar de O(n**2) a O(nlogn), ya que se recurre a la busqueda binaria, este algoritmo
  fue encontrado  en [https://www.baeldung.com/cs/patience-sort-algorithm] con formato de seudo codigo.
 + Autor: Christopher Patricio Becerra Catalan
 */

#include "patiencesort.hpp"
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

void patienceSort(vector<int>& arr) {
    if (arr.empty()) return;

    vector<vector<int>> piles;
    
    //1.Creacion de pilas en O(nlog n) usando busqueda binaria
    for (int val : arr) {
        auto it = lower_bound(piles.begin(), piles.end(), val,
                              [](const vector<int>& pile, int v) {
                                  return pile.back() < v;
                              });
        if (it == piles.end()) {
            piles.push_back({val});
        } else {
            it->push_back(val);
        }
    }

    //2.Mezcla de pilas usando Min-Heap (priority_queue de la STL)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (size_t i = 0; i < piles.size(); i++) {
        pq.push({piles[i].back(), i});
        piles[i].pop_back();
    }

    arr.clear();
    while (!pq.empty()) {
        auto [val, pile_idx] = pq.top();
        pq.pop();
        arr.push_back(val);

        if (!piles[pile_idx].empty()) {
            pq.push({piles[pile_idx].back(), pile_idx});
            piles[pile_idx].pop_back();
        }
    }
}