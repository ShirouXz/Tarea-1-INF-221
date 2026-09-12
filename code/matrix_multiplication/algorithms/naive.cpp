/*
 + Implementacion del algoritmo Naive para multiplicacion de matrices cuadradas.
 + Fuente: [https://www.geeksforgeeks.org/dsa/strassens-matrix-multiplication/#naive-approach-using-nested-loops-on-3-time-and-on-2-space].
 + Modificado para que funcione para cualquier entrada (de matrices), ya no es solo el codigo que sale en la pagina de ejemplo.
 + Autor: Christopher Patricio Becerra Catalan
 */

#include <vector>

using namespace std;

vector<vector<int>> naive(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2) {
    int n = mat1.size();
    int m = mat1[0].size();
    int q = mat2[0].size();        

    //Inicializa la matriz resultante con dimensiones n×q, llena de 0s
    vector<vector<int>> res(n, vector<int>(q, 0));

    //Bucle a traves de cada fila de mat1
    for (int i = 0; i < n; i++) {
        //Bucle a traves de cada columna de mat2
        for (int j = 0; j < q; j++) {
            //Calcula el producto punto de la fila mat1[i] y la columna mat2[][j]
            for (int k = 0; k < m; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return res;
}