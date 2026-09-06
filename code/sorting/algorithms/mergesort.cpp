#include <vector>
using namespace std;

/*
 * Algoritmo: Merge Sort
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Código adaptado de las diapositivas de clase del profesor JP. Castillo.
 */

 
 // 1. Funcion para combinar
 // Su trabajo es tomar dos mini-arreglos, que ya estan ordenados por 
 // separado y juntarlos en un solo arreglo grande totalmente ordenado.
void Merge(vector<int> &T, vector<int> &A, int left, int mid, int right){
    int i1 = left; //indice para recorrer la mitad izq.
    int i2 = mid; //indice para recorrer la mitad der.
    int i = left; //indice para saber donde guardar el "ganador" en el arreglo principal

    //comparamos los elementos de ambas mitades, el mas pequeño pasa al arreglo prin.
    while(i1 < mid && i2 <= right){
        if(T[i1] <= T[i2]){
            A[i++] = T[i1++]; //gana el de la izq
        }else{
            A[i++] = T[i2++]; //gana el de la der
        }
    }

    // si la mitad der. se acabo primero metemos todo lo que sobro a la izq.
    while(i1 < mid){
        A[i++] = T[i1++];
    }

    // si la mitad izq. se acabo primero metemos todo lo que sobre a la der.
    while(i2 <= right){
        A[i++] = T[i2++];
    }
}

// 2. Funcion recursiva dividir
// su trabajo es partir el arreglo original por la mitad una y otra vez
// hasta que queden sub-arreglos de solo 1 elemento
void MergeSort(vector<int> &A, vector<int> &T, int left, int right){
    //calculamos cuantos elem tiene el arreglo actual
    int n= right - left +1;

    //caso base: si el arreglo tiene 1 o 0 elem, significa que ya esta ordenado
    if(n<=1){
        return;
    }

    //dividimos justamente donde esta el centro del arreglo
    int mid = left + n/2;

    //conquista, llamamos recursivamente para partir la mitad izq, genera un sub-arreglo que va 
    //del inicio (left) hasta antes del medio ( mid - 1)
    MergeSort(A, T, left, mid - 1);
    //conquista, llamamos recursivamente para partir la mitad der, genera un sub-arreglo que va 
    //del medio (mid) hasta el final (right)
    MergeSort(A, T, mid, right);

    //antes de mezclar hacemos una copia en el arreglo temporal T
    for(int i = left; i <= right; i++){
        T[i] = A[i];
    }

    //combinar: llamamos a merge para juntar las dos mitades ordenadas
    Merge(T, A, left, mid, right);
}