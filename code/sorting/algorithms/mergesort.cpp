/*
 + Implementacion de MergeSort.
 + Fuente: GeeksforGeeks [https://www.geeksforgeeks.org/dsa/merge-sort/].
 + Modificado para que funcione para cualquier entrada, ya no es solo el codigo que sale en la pagina de ejemplo.
 + Autor: Christopher Patricio Becerra Catalan
 */

#include "mergesort.hpp"

using namespace std;

//Funcion interna del algoritmo para mezclar dos subarreglos hace n+m-1 comparaciones para ordenarlos por lo que se demora O(n).
//Respecto al espacio el apartado de mezcla necesita guardarlo la informacion en un arreglo m+n por lo que no es in place.
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //Vectores temporales
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//Funcion recursiva interna de Merge Sort
void mergeSortRecursive(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

//Funcion principal invocada desde sorting.cpp
void mergeSort(vector<int>& arr) {
    if (!arr.empty()) {
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }
}