#include <iostream>
#include <vector>
#include <fstream> //herramienta para leer y escribir archivos .txt
#include <chrono>  //cronometro 
#include <string>
#include <sys/resource.h> //para ver lo de la memoria
#include <sstream>

using namespace std;

void naive(const vector<vector<int>> &a, const vector<vector<int>> &b, vector<vector<int>> &c, int n);

int main(int cant_argumentos, char* texto_argumento[]){
    // para lo de la terminal y si lo escribe mal
    if(cant_argumentos < 4){
        cout << "Error. Uso correcto: ./matrix archivo1.txt archivo2.txt naive" << endl;
        return 0;
    }

    //lectura primera matriz
    ifstream archivo1(texto_argumento[1]);
    if(!archivo1.is_open()){
        cout << "No se pudo abrir el archivo" << endl;
        return 0;
    }

    vector<vector<int>> matriz1;
    string linea1;
    //leemos linea x linea
    while(getline(archivo1, linea1)){
        vector<int> fila;
        stringstream ss(linea1); //permite leer tanto como escribir
        int numero;
        //saco cda numero separado por espacion en la linea actual
        while(ss >> numero){
            fila.push_back(numero);
        }
        //si la linea tenia numeros. agregamos la fila a la matriz
        if(!fila.empty()){
            matriz1.push_back(fila);
        }
    }

    // Lectura de la segunda matriz (M2)
    ifstream archivo2(texto_argumento[2]);
    if(!archivo2.is_open()){
        cout << "No se pudo abrir el archivo 2" << endl;
        return 0;
    }
    //es lo mismo que la 1
    vector<vector<int>> matriz2;
    string linea2;
    while(getline(archivo2, linea2)){
        vector<int> fila;
        stringstream ss(linea2); 
        int numero;
        while(ss >> numero){
            fila.push_back(numero);
        }
        if(!fila.empty()){
            matriz2.push_back(fila);
        }
    }

    string algoritmo = texto_argumento[3];
    int n = matriz1.size(); //sacamos el tamaño exacto de la matriz
    vector<vector<int>> matriz_resultado(n, vector<int>(n, 0)); //creo una matriz solo con 0
    //iniciar cronometro
    auto inicio = chrono::steady_clock::now();

    if(algoritmo == "naive"){
        naive(matriz1, matriz2, matriz_resultado, n);
    } else if(algoritmo == "strassen"){
        //agregar funcion strassen cuando este lista :)
    } else{
        cout << "Error: Algoritmo no reconocido :C" << endl;
        return 0;
    }
    //termina el cronometro
    auto fin = chrono::steady_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);

    struct rusage uso_memoria;
    getrusage(RUSAGE_SELF, &uso_memoria);
    long memoria_kb = uso_memoria.ru_maxrss; // el valor en kb

    //usamos el nombre de la primera matriz (m1) para crear el archivo de salida
    string nombre_archivo_entrada = texto_argumento[1];
    string nombre_salida = nombre_archivo_entrada;
    size_t pos_carpeta = nombre_salida.find("matrix_input");
    if(pos_carpeta != string::npos){
        nombre_salida.replace(pos_carpeta, string("matrix_input").length(), "matrix_output");
    }
    nombre_salida = nombre_salida.substr(0, nombre_salida.rfind("_1.txt")) + "_out.txt";
    ofstream archivo_salida(nombre_salida);
    if(archivo_salida.is_open()){
        //recorremos las filas
        for(size_t i = 0; i < matriz_resultado.size(); i++){
            //recorremos las columnas
            for(size_t j = 0; j < matriz_resultado[i].size(); j++){
                archivo_salida << matriz_resultado[i][j] << " ";
            }
            archivo_salida << "\n"; //salto de linea al terminar cada fila
        }
        archivo_salida.close();
        cout << "Matriz resultado guardada en: " << nombre_salida << endl;
    } else {
        cout << "Error al crear el archivo de salida." << endl;
    }
 
    cout << "El algoritmo " << algoritmo << " tardo: " << duracion.count() << " ms | memoria usada: " << memoria_kb << " KB" << endl;
    return 0;
}
 
