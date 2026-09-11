#include <iostream>
#include <vector>

using namespace std;

/*
 * Algoritmo: strassen
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Lógica adaptada de la web GeeksforGeeks (https://www.geeksforgeeks.org/dsa/easy-way-remember-strassens-matrix-equation/)
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



//función principal recursiva de Strassen
vector<vector<int>> strassen(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    int n = A.size();

    //CASO BASE
    //Si la matriz es de 1x1, simplemente multiplicamos los dos unicos num
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    //PREPARAR LOS CUADRANTES
    int mid = n / 2;
    
    //creamos un vector fila lleno de ceros para inicializar rapido las sub-matrices
    vector<int> inner(mid, 0);
    
    //declaramos los 4 cuadrantes para A y los 4 para B
    vector<vector<int>> A11(mid, inner), A12(mid, inner), A21(mid, inner), A22(mid, inner);
    vector<vector<int>> B11(mid, inner), B12(mid, inner), B21(mid, inner), B22(mid, inner);

    //DIVIDIR LAS MATRICES ORIGINALES
    //recorremos solo hasta la mitad pero usamos sumas en los indices para extraer los datos de la mitad inferior o der de la matriz original
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            //cuadrante superior izquierdo
            A11[i][j] = A[i][j];
            //cuadrante superior izquierdo
            A12[i][j] = A[i][j + mid];
            //cuadrante superior izquierdo
            A21[i][j] = A[i + mid][j];
            //cuadrante inferior derecho
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }
    }

    //LAS 7 MULTIPLICACIONES (Llamadas recursivas)
    vector<vector<int>> M1 = strassen(addMatrix(A11, A22), addMatrix(B11, B22));
    vector<vector<int>> M2 = strassen(addMatrix(A21, A22), B11);
    vector<vector<int>> M3 = strassen(A11, subMatrix(B12, B22));
    vector<vector<int>> M4 = strassen(A22, subMatrix(B21, B11));
    vector<vector<int>> M5 = strassen(addMatrix(A11, A12), B22);
    vector<vector<int>> M6 = strassen(subMatrix(A21, A11), addMatrix(B11, B12));
    vector<vector<int>> M7 = strassen(subMatrix(A12, A22), addMatrix(B21, B22));

    //CALCULAR LOS CUADRANTES DE LA MATRIZ RESULTADO (C)
    // C11 = M1 + M4 - M5 + M7
    vector<vector<int>> C11 = addMatrix(subMatrix(addMatrix(M1, M4), M5), M7); 
    
    // C12 = M3 + M5
    vector<vector<int>> C12 = addMatrix(M3, M5);                               
    
    // C21 = M2 + M4
    vector<vector<int>> C21 = addMatrix(M2, M4);                               
    
    // C22 = M1 - M2 + M3 + M6
    vector<vector<int>> C22 = addMatrix(addMatrix(subMatrix(M1, M2), M3), M6); 

    //JUNTAR LOS 4 CUADRANTES EN LA MATRIZ FINAL (C)
    vector<vector<int>> C(n, vector<int>(n, 0));
    for(int i = 0; i < mid; i++) {
        for(int j = 0; j < mid; j++) {
            C[i][j] = C11[i][j];
            C[i][j + mid] = C12[i][j];
            C[i+mid][j] = C21[i][j];
            C[i+mid][j + mid] = C22[i][j];
        }
    }

    return C;

}