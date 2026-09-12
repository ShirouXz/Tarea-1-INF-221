/*
 * Implementación principal para la medicion de multiplicacion de matrices, el algoritmo se encarga de recibir los inputs generados
  y llamar a las funciones de naive y strassen.
 * Autor: Christopher Patricio Becerra Catalan
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <sys/resource.h>
#include "algorithms/naive.hpp"
#include "algorithms/strassen.hpp"

using namespace std;
using namespace std::chrono;

long getMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

vector<vector<int>> readMatrix(const string& filename, int n) {
    vector<vector<int>> mat(n, vector<int>(n));
    ifstream file(filename);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> mat[i][j];
        }
    }
    return mat;
}

void writeMatrix(const string& filename, const vector<vector<int>>& mat) {
    ofstream file(filename);
    for (const auto& row : mat) {
        for (int val : row) file << val << " ";
        file << "\n";
    }
}

int main() {
    //Parametros definidos en el Apendice A.2 del documento de la tarea
    vector<int> N_vals = {2, 4, 8, 16, 32, 64, 128, 256}; 
    vector<string> T = {"dispersa", "diagonal", "densa"};
    vector<string> D = {"D0", "D10"};
    vector<string> M = {"a", "b", "c"};

    ofstream results("data/measurements/results.csv");
    results << "Algoritmo,N,T,D,M,Tiempo_ms,Memoria_KB\n";

    for (int n_val : N_vals) {
        string n = to_string(n_val);
        for (const auto& t : T) {
            for (const auto& d : D) {
                for (const auto& m : M) {
                    string baseName = n + "_" + t + "_" + d + "_" + m;
                    string file1 = "data/matrix_input/" + baseName + "_1.txt";
                    string file2 = "data/matrix_input/" + baseName + "_2.txt";
                    
                    vector<vector<int>> mat1 = readMatrix(file1, n_val);
                    vector<vector<int>> mat2 = readMatrix(file2, n_val);
                    if (mat1.empty() || mat2.empty()) continue;

                    //Ruta donde se guardaran los resultados de los algoritmos
                    string outFile = "data/matrix_output/" + baseName + "_out.txt";

                    //1. Naive
                    long memBefore = getMemoryUsage();
                    auto start = high_resolution_clock::now();
                    vector<vector<int>> res_naive = naive(mat1, mat2);
                    auto end = high_resolution_clock::now();
                    long memAfter = getMemoryUsage();
                    auto duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "Naive," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeMatrix(outFile, res_naive);

                    //2. Strassen
                    memBefore = getMemoryUsage();
                    start = high_resolution_clock::now();
                    vector<vector<int>> res_strassen = strassen(mat1, mat2);
                    end = high_resolution_clock::now();
                    memAfter = getMemoryUsage();
                    duration = duration_cast<milliseconds>(end - start).count();
                    
                    results << "Strassen," << n << "," << t << "," << d << "," << m << "," 
                            << duration << "," << (memAfter - memBefore) << "\n";
                    writeMatrix(outFile, res_strassen);
                }
            }
        }
    }
    return 0;
}