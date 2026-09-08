#include <iostream>
#include <vector>
#include <fstream> //herramienta para leer y escribir archivos .txt
#include <chrono>  //cronometro 
#include <string>
#include <sys/resource.h> //para ver lo de la memoria

using namespace std;
void MergeSort(vector<int>& A, vector<int>& T, int left, int right);
void QuickSort(vector<int> & A, int i, int d);
vector<int> sortArray(vector<int>& arr);
void PatienceSort(vector<int>& A);

int main(int cant_argumentos, char* texto_argumento[]){

    // para lo de la terminal y si lo escribe mal
    if(cant_argumentos < 3){
        cout << "Error. Uso correcto: ./sorting archivo.txt merge" << endl;
        return 0;
    }

    ifstream archivo(texto_argumento[1]);
    if(!archivo.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }
    
    vector<int> arreglo;
    int numero;
    while(archivo >> numero){
        arreglo.push_back(numero);
    }

    //guardo la palabra que el usario eligio
    string algoritmo = texto_argumento[2];

    //iniciar cronometro
    auto inicio = chrono::steady_clock::now();

    if(algoritmo == "merge"){
        vector<int> T(arreglo.size());
        MergeSort(arreglo, T, 0, arreglo.size() - 1);
    }
    else if(algoritmo == "quick"){
        QuickSort(arreglo, 0, arreglo.size() - 1);
    } 
    else if(algoritmo == "sort"){
       arreglo = sortArray(arreglo);
    } else if(algoritmo == "patience"){
        PatienceSort(arreglo);
    } else{
        cout << "Error: Algoritmo no reconocido :C" << endl;
        return 0;
    }
    //termina el cronometro
    auto fin = chrono::steady_clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);

    struct rusage uso_memoria;
    getrusage(RUSAGE_SELF, &uso_memoria);
    long memoria_kb = uso_memoria.ru_maxrss; // el valor en kb

    //guardamos el nombre original del archivo
    string nombre_archivo_entrada = texto_argumento[1];
    string nombre_salida = nombre_archivo_entrada;
    size_t pos_carpeta = nombre_salida.find("array_input");
    if(pos_carpeta != string::npos){
        nombre_salida.replace(pos_carpeta, string("array_input").length(), "array_output"); //lo guardamos en el output
    }
 
    //le quitamos el ".txt" y le pegamos el "_out.txt"
    nombre_salida = nombre_salida.substr(0, nombre_salida.find_last_of('.')) + "_" + algoritmo + "_out.txt";
    ofstream archivo_salida(nombre_salida);
    if(archivo_salida.is_open()){
        for(size_t i = 0; i < arreglo.size(); i++){
            archivo_salida << arreglo[i] << " ";
        }
        archivo_salida.close();
        cout << "Resultado guardado en: " << nombre_salida << endl;
    } else{
        cout << "Error al crear el archivo de salida" << endl;
    }
 
    cout << "El algoritmo " << algoritmo << " tardo: " << duracion.count() << " us | memoria usada: " << memoria_kb << " KB" << endl;
    return 0;
}