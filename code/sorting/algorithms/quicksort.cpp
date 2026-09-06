#include <vector> 
#include <utility> // para el swap()

using namespace std;

/*
 * Algoritmo: Quick Sort
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Código adaptado de las diapositivas de clase del profesor JP. Castillo.
 */

 // 1. Funcion partición
 // su trabajo es elegir un "pivote" y ordenar el arreglo de tal forma que 
 // los elementos menores al pivote queden a la izquiera y los mayores a la derecha,
int partition(vector<int> &A, int i, int d, int p){
    i--;
    d++;

    do{
        //Avanzamos por la izq mientras los elem sean menores al pivote
        i++;
        while(A[i] < A[p]){
            i++;
        }

        //retrocedemos por la der mientras los elementos sean mayores al pivote
        d--;
        while(i<d && A[d] > A[p]){
            d--;
        }

        //si los indices NO se han cruzado, intercambiamos los elem mal ubicados
        if(i<d){
            swap(A[i], A[d]);
        }
    } while(i<d); //repetimos hasta q se crucen

    //retornamos la pos donde quedo el limite entre mayores y menores
    return i;
}

// 2. Funcion recursiva
// Su trabajo es aplicar la particion una y otra vez en los sub-arreglos
// que se van formando, hasta que todo quede ordenado.
void QuickSort(vector<int> &A, int i, int d){
    // calculamos el tamaño del sub arreglo actual
    int n = d - i + 1;

    //caso base: si tiene 1 o 0 elem, ya esta ordenado
    if(n<=1){
        return;
    } else{
        //elegimos el pivote (el profe dijo que era mucho mas "sencilo" partir por el elem a la mitad que el primero o el ult)
        // ademas, para este caso como ya incluye arreglos ordenados y de grandes cantidades para mi es mejor usar el pivote a la mitad
        int p= i + n/2;

        //escondemos el pivote al final del arreglo (temporalmente) para q no moleste xd
        swap(A[p],A[d]);

        //llamamos a la particion (le pasamos el pivote que ahora esta al final en la pos "d")
        int k= partition(A, i, d - 1, d);

        //devolvemos el pivote a su pos final definitiva
        swap(A[k],A[d]);

        //usamos este ajuste por si el pivote es el mayor de todos
        if(k == d -1){
            k = d;
        }

        //llamadas recursivas para ordenar la mitad izq y la mitad der
        QuickSort(A, i, k - 1);
        QuickSort(A, k + 1, d);
    }
}