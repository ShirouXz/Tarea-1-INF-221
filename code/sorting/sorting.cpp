/*
 * Implementacion para la medicion de de tiempo y almacenamiento en  algoritmos de ordenamiento.
 * Autor: Christopher Patricio Becerra Catalan
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include "algorithms/mergesort.hpp"
#include "algorithms/quicksort.hpp"
#include "algorithms/patiencesort.hpp"
#include "algorithms/sort.hpp"

using namespace std;
using namespace std::chrono;

long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

vector<int> readArray(const string& filename) {
    vector<int> arr;
    ifstream file(filename);
    int val;
    while (file >> val) arr.push_back(val);
    return arr;
}

void writeArray(const string& filename, const vector<int>& arr) {
    ofstream file(filename);
    for (int val : arr) file << val << " ";
}

int main() {
    //Parametros definidos en el Apendice A.1 del documento de la tarea
    vector<string> N = {"10", "1000", "100000", "10000000"};
    vector<string> T = {"ascendente", "descendente", "aleatorio"};
    vector<string> D = {"D1", "D7"};
    vector<string> M = {"a", "b", "c"};

    ofstream results("data/measurements/results.csv");
    results << "Algoritmo,N,T,D,M,Tiempo_ms,Memoria_KB\n";

    for (const auto& n : N) {
        for (const auto& t : T) {
            for (const auto& d : D) {
                for (const auto& m : M) {
                    string baseName = n + "_" + t + "_" + d + "_" + m;
                    
                    //Lectura desde la subcarpeta array_input
                    string inFile = "data/array_input/" + baseName + ".txt";
                    vector<int> original = readArray(inFile);
                    if (original.empty()) continue;

                    //Ruta donde se guardaran los archivos posterior a la ejecucion de los algoritmos, sobrescribirá el archivo en cada pasada
                    string outFile = "data/array_output/" + baseName + "_out.txt";

                    //1.Merge Sort
                    vector<int> arr = original;
                    long memBefore = getMemoryUsage();
                    auto start = high_resolution_clock::now();
                    mergeSort(arr);
                    auto end = high_resolution_clock::now();
                    long memAfter = getMemoryUsage();
                    auto duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "MergeSort," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeArray(outFile, arr);

                    //2.Quick Sort
                    arr = original;
                    memBefore = getMemoryUsage();
                    start = high_resolution_clock::now();
                    quickSort(arr);
                    end = high_resolution_clock::now();
                    memAfter = getMemoryUsage();
                    duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "QuickSort," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeArray(outFile, arr);

                    //3.Patience Sort
                    arr = original;
                    memBefore = getMemoryUsage();
                    start = high_resolution_clock::now();
                    patienceSort(arr);
                    end = high_resolution_clock::now();
                    memAfter = getMemoryUsage();
                    duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "PatienceSort," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeArray(outFile, arr);

                    //4.STL Sort
                    arr = original;
                    memBefore = getMemoryUsage();
                    start = high_resolution_clock::now();
                    sortArray(arr); 
                    end = high_resolution_clock::now();
                    memAfter = getMemoryUsage();
                    duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "STLSort," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeArray(outFile, arr);
                }
            }
        }
    }
    return 0;
}