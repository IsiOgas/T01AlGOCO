#include <iostream>
#include <vector>
#include <climits>
#include <queue>   // para el priority_queue
#include <utility> // para el pair

using namespace std;

/*
 * Algoritmo: Patience Sort
 * Implementado por: Isidora Ogas Pavez
 * Referencia: Adaptado de wikibooks (Patience Sort el de Java) (https://en.wikibooks.org/wiki/Algorithm_Implementation/Sorting/Patience_sort). pd: habia primero implementado la de GeeksforGeeks pero esa la hacia en O(n^2) y para la prueba gigante se demoraba caleta LOL Q MAL
 * este lo hace en O(n log n)
 */

// 1. Funcion busqueda binaria
//su trabajo es buscar, dentro de las pilas que ya tenemos armadas, la primera (la mas a la izq) cuyo tope sea >= al elem que estamos repartiendo.
//esto funciona pq las pilas siempre quedan ordenadas de forma ascendente segun su tope (osea que podemos hacer esto en O(log(cant pilas)) en vez de recorrerlas 1 por 1)
int BuscarPila(vector<vector<int>> &pilas, int x){
    int izq = 0;
    int der = pilas.size(); //si no encuentra ninguna, se queda apuntando al final (pilas.size())

    while(izq < der){
        int mid = izq + (der - izq)/2;

        if(pilas[mid].back() >= x){
            der = mid; //esta pila sirve, pero puede q haya otra mas a la izq q tambien sirva
        } else{
            izq = mid + 1; //esta pila no sirve, seguimos buscando mas a la derecha
        }
    }

    return izq; //si izq == pilas.size(), es q no habia ninguna pila q sirviera (hay q crear una nueva)
}

// 2. Funcion principal Patience Sort
// fase 1: repartimos las cartas en pilas, como en el solitario (patience/solitario)
// fase 2: juntamos todas las pilas con un heap, sacando siempre la carta mas chica disponible
void PatienceSort(vector<int> &A){
    int n = A.size();
    vector<vector<int>> pilas; //cada "pila" es un mini-mazo de cartas (un vector usado como stack)

    //fase 1
    for(int c = 0; c<n; c++){
        int x = A[c];
        //buscamos la primera pila cuyo tope sea >= x
        int i = BuscarPila(pilas, x);

        if(i != (int)pilas.size()){
            pilas[i].push_back(x); //esta pila la recibe, x pasa a ser su nuevo tope
        } else{
            pilas.push_back(vector<int>{x}); //no habia pila q sirviera, se crea una nueva al final
        }
    }

    //fase 2
    //guardamos pares (tope de la pila, indice de la pila). con greater<> el priority_queue
    //se comporta como MIN-heap en vez de max-heap 
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> heap;

    for(int i=0; i < (int)pilas.size(); i++){
        heap.push(make_pair(pilas[i].back(), i));
    }

    for(int c=0; c<n; c++){
        pair<int,int> menor = heap.top();
        heap.pop();

        int indicePila = menor.second;

        A[c] = pilas[indicePila].back(); //sacamos la carta mas chica q hay disponible
        pilas[indicePila].pop_back();

        //si a esa pila le quedan cartas, la devolvemos al heap con su nuevo tope
        if(!pilas[indicePila].empty()){
            heap.push(make_pair(pilas[indicePila].back(), indicePila));
        }
    }
}