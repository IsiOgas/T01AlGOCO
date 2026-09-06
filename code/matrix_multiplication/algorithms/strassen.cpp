#include <iostream>
#include <vector>

using namespace std;

/*
 * Algoritmo: strassen
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Lógica adaptada de la web GeeksforGeeks
 */

//funcion para sumar dos matrices
vector<vector<int>> addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); //crea una matriz de tamaño nxn y la rellena con 0
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}
//funcion para restar dos matrices
vector<vector<int>> subMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B){
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0)); //crea una matriz de tamaño nxn y la rellena con 0
    for(int i=0; i<n;i++){
        for(int j=0; j<n; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}
