/*
 + Implementacion de QuickSort.
 + Fuente: GeeksforGeeks [https://www.geeksforgeeks.org/dsa/quick-sort-algorithm/].
 + Optimizacion: Seleccion de un pivote central sacado del ppt: 
  "Dividir y Conquistar (Parte 1)",J.P.Castillo, para evitar el peor caso O(n**2), ya que si se elige de pivote al mas chico o mas grande
  del subarreglo el arbol de recursion quedara desbalanceado.
 + Autor: Christopher Patricio Becerra Catalan
 */
#include "quicksort.hpp"
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& A, int i, int d, int p) {
    //Se almacena el valor del pivote directamente para evitar problemas de referencia
    int pivotValue = A[p]; 
    i--;
    d++;
    do {
        i++;
        while (A[i] < pivotValue) i++;
        d--;
        while (i < d && A[d] > pivotValue) d--;
        if (i < d) {
            swap(A[i], A[d]);
        }
    } while (i < d);
    
    return i;
}

void quickSortRec(vector<int>& A, int i, int d) {
    int n = d - i + 1;
    if (n <= 1) return;
    
    //Seleccion del pivote central para evitar el peor caso
    int p = i + n / 2; 
    swap(A[p], A[d]);
    
    int k = partition(A, i, d - 1, d);
    swap(A[k], A[d]);
    
    if (k == d - 1) k = d;
    
    quickSortRec(A, i, k - 1);
    quickSortRec(A, k + 1, d);
}

//Funcion principal llamada desde sorting.cpp
void quickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSortRec(arr, 0, arr.size() - 1);
    }
}