#include <vector>
using namespace std;

/*
 * Algoritmo: Naive
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Lógica adaptada del video "Time Complexity Part 3: Naive Matrix Multiplication" del canal At the Whiteboard (https://youtu.be/bxaWAje_g74?si=tuqerPkKgpaFZh2V)
 */

 //funcion que multiplica dos matrices (a y b) y guarda el resultado en "c", uso & para no fotocopiar TOD la matriz y gastar memoria extra.
 //recordar: const asegura que no lo modifiquemos por accidente
void naive(const vector<vector<int>> &a, const vector<vector<int>> &b, vector<vector<int>> &c, int n){
    //recorro las filas de la matriz a
    for(int i=0; i<n ; i++){
        //recorro las columnas de la matriz b
        for(int j=0; j<n; j++){
            //aseguramos que parta en 0
            c[i][j] = 0;
            for(int k=0; k<n; k++){
                //mult y vamos sumando para obtener el valor final 
                c[i][j] += a[i][k]*b[k][j]; //en el mult de matrices hago una matriz solo con 0 para esto sea mas limpio
            }
        }
    }
}