/*
 + Implementacion del algoritmo de Strassen para multiplicacion de matrices cuadradas.
 + Fuente: [https://www.geeksforgeeks.org/dsa/strassens-matrix-multiplication/#expected-approach-using-strassens-method-on-3-time-and-on-2-space].
 + Modificado para que funcione para cualquier entrada (de matrices), ya no es solo el codigo que sale en la pagina de ejemplo.
 + Autor: Christopher Patricio Becerra Catalan
 */

#include "strassen.hpp"
#include <cmath>
#include <algorithm>

using namespace std;

//Retorna la siguiente potencia de 2 mayor o igual a n
int nextPowerOfTwo(int n) {
    return pow(2, ceil(log2(n)));
}

//Redimensiona la matriz a newR x newC rellenando con ceros
vector<vector<int>> resizeMatrix(const vector<vector<int>> &mat, int newR, int newC) {
    vector<vector<int>> resized(newR, vector<int>(newC, 0));
    for (size_t i = 0; i < mat.size(); ++i)
        for (size_t j = 0; j < mat[0].size(); ++j)
            resized[i][j] = mat[i][j];
    return resized;
}

//Suma o resta de matrices
vector<vector<int>> add(const vector<vector<int>> &a, const vector<vector<int>> &b, int size, int sign = 1) {
    vector<vector<int>> res(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            res[i][j] = a[i][j] + sign * b[i][j];
    return res;
}

//Implementacion recursiva interna de Strassen
vector<vector<int>> strassenRecursive(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2) {
    int n = mat1.size();
    vector<vector<int>> res(n, vector<int>(n, 0));
    
    if (n == 1) {
        res[0][0] = mat1[0][0] * mat2[0][0];
        return res;
    }

    int newSize = n / 2;
    vector<vector<int>> a11(newSize, vector<int>(newSize)), a12(newSize, vector<int>(newSize)),
                        a21(newSize, vector<int>(newSize)), a22(newSize, vector<int>(newSize)),
                        b11(newSize, vector<int>(newSize)), b12(newSize, vector<int>(newSize)),
                        b21(newSize, vector<int>(newSize)), b22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            a11[i][j] = mat1[i][j];
            a12[i][j] = mat1[i][j + newSize];
            a21[i][j] = mat1[i + newSize][j];
            a22[i][j] = mat1[i + newSize][j + newSize];
            b11[i][j] = mat2[i][j];
            b12[i][j] = mat2[i][j + newSize];
            b21[i][j] = mat2[i + newSize][j];
            b22[i][j] = mat2[i + newSize][j + newSize];
        }
    }

    auto m1 = strassenRecursive(add(a11, a22, newSize), add(b11, b22, newSize));
    auto m2 = strassenRecursive(add(a21, a22, newSize), b11);
    auto m3 = strassenRecursive(a11, add(b12, b22, newSize, -1));
    auto m4 = strassenRecursive(a22, add(b21, b11, newSize, -1));
    auto m5 = strassenRecursive(add(a11, a12, newSize), b22);
    auto m6 = strassenRecursive(add(a21, a11, newSize, -1), add(b11, b12, newSize));
    auto m7 = strassenRecursive(add(a12, a22, newSize, -1), add(b21, b22, newSize));

    auto c11 = add(add(m1, m4, newSize), add(m7, m5, newSize, -1), newSize);
    auto c12 = add(m3, m5, newSize);
    auto c21 = add(m2, m4, newSize);
    auto c22 = add(add(m1, m3, newSize), add(m6, m2, newSize, -1), newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            res[i][j] = c11[i][j];
            res[i][j + newSize] = c12[i][j];
            res[i + newSize][j] = c21[i][j];
            res[i + newSize][j + newSize] = c22[i][j];
        }
    }
    return res;
}

//Funcion principal invocada desde matrix_multiplication.cpp
vector<vector<int>> strassen(const vector<vector<int>> &mat1, const vector<vector<int>> &mat2) {
    int n = mat1.size(), m = mat1[0].size(), q = mat2[0].size();
    int size = nextPowerOfTwo(max({n, m, q}));

    vector<vector<int>> aPad = resizeMatrix(mat1, size, size);
    vector<vector<int>> bPad = resizeMatrix(mat2, size, size);

    vector<vector<int>> cPad = strassenRecursive(aPad, bPad);

    vector<vector<int>> C(n, vector<int>(q));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < q; j++)
            C[i][j] = cPad[i][j];

    return C;
}