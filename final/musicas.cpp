#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
using namespace std;

// Estructura para almacenar la informacion de una cancion
struct Cancion {
    int id;
    string artista;
    string nombreCancion;
    string idCancion;
    int popularidad;
    int anio;
    string genero;
    float danceabilidad;
    float energia;
    int clave;
    float volumen;
    int modo;
    float discurso;
    float acustica;
    float instrumentalidad;
    float vivacidad;
    float valencia;
    float tempo;
    int duracion;
    int firmaTiempo;
};

// Clase TablaHash
class TablaHash {
private:
    vector<list<pair<string, Cancion>>> tabla;
    int tamanioTabla;

    // Funcion hash simple que calcula el indice en la tabla
    int funcionHash(string idCancion) {
        int suma = 0;
        for (char c : idCancion) {
            suma += c;  // Sumar los valores ASCII de los caracteres de la clave
        }
        return suma % tamanioTabla;  // Devuelve el indice
    }

public:
    // Constructor
    TablaHash(int tamanio) {
        tamanioTabla = tamanio;
        tabla.resize(tamanioTabla);
    }

    // Funcion para insertar un par clave-valor
    void insertar(string idCancion, Cancion cancion) {
        int indice = funcionHash(idCancion);  // Obtiene el indice en la tabla
        tabla[indice].push_back(make_pair(idCancion, cancion));  // Inserta el par (idCancion, cancion)
    }

    // Funcion para buscar la cancion por su idCancion
    Cancion buscar(string idCancion) {
        int indice = funcionHash(idCancion);  // Obtiene el indice en la tabla
        // Recorre la lista en esa posicion para encontrar la cancion
        for (auto& elemento : tabla[indice]) {
            if (elemento.first == idCancion) {
                return elemento.second;
            }
        }
        throw runtime_error("Cancion no encontrada");  // Si la cancion no existe
    }

    // Funcion para mostrar el contenido de la tabla hash
    void mostrar() {
        for (int i = 0; i < tamanioTabla; i++) {
            if (!tabla[i].empty()) {
                cout << "Indice " << i << ": ";
                int h=0;
                for (auto& elemento : tabla[i]) {
                    /*cout << "(ID: " << elemento.second.idCancion << ", Cancion: "
                         << elemento.second.nombreCancion << ", Artista: "
                         << elemento.second.artista << ") ";*/
                    cout <<h++<< " _ ID: " << elemento.second.id;
                    cout<<endl;
                }
                cout << endl;
            }
        }
    }
};

// Funcion para leer los datos del archivo CSV y cargar las canciones en la tabla hash
void cargarDatosDesdeArchivo(string nombreArchivo, TablaHash& tablaHash) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;

    // Ignorar la primera linea (cabecera)
    getline(archivo, linea);

    // Leer cada linea del archivo y procesarla
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;

        Cancion cancion;

        try {
            // Extraemos los datos de la linea
            getline(ss, token, ','); cancion.id = stoi(token);  // id
            getline(ss, cancion.artista, ',');  // artista
            getline(ss, cancion.nombreCancion, ',');  // track_name
            getline(ss, cancion.idCancion, ',');  // track_id
            getline(ss, token, ','); cancion.popularidad = stoi(token);  // popularity
            getline(ss, token, ','); cancion.anio = stoi(token);  // year
            getline(ss, cancion.genero, ',');  // genre
            getline(ss, token, ','); cancion.danceabilidad = stof(token);  // danceability
            getline(ss, token, ','); cancion.energia = stof(token);  // energy
            getline(ss, token, ','); cancion.clave = stoi(token);  // key
            getline(ss, token, ','); cancion.volumen = stof(token);  // loudness
            getline(ss, token, ','); cancion.modo = stoi(token);  // mode
            getline(ss, token, ','); cancion.discurso = stof(token);  // speechiness
            getline(ss, token, ','); cancion.acustica = stof(token);  // acousticness
            getline(ss, token, ','); cancion.instrumentalidad = stof(token);  // instrumentalness
            getline(ss, token, ','); cancion.vivacidad = stof(token);  // liveness
            getline(ss, token, ','); cancion.valencia = stof(token);  // valence
            getline(ss, token, ','); cancion.tempo = stof(token);  // tempo
            getline(ss, token, ','); cancion.duracion = stoi(token);  // duration_ms
            getline(ss, token, ','); cancion.firmaTiempo = stoi(token);  // time_signature

            // Insertar la cancion en la tabla hash
            tablaHash.insertar(cancion.idCancion, cancion);
        } catch (const exception& e) {
            cerr << "Error al procesar la linea: " << linea << endl;
        }
    }
}

int main() {
    // Crear una tabla hash con 10 posiciones
    TablaHash tablaHash(10);

    // Cargar datos desde el archivo CSV
    cargarDatosDesdeArchivo("spotify_data_mini.csv", tablaHash);

    // Mostrar el contenido de la tabla hash
    cout << "Contenido de la tabla hash:" << endl;
    tablaHash.mostrar();

    // Buscar una cancion por su idCancion
    try {
        Cancion cancion = tablaHash.buscar("6FOTKPUDbraZFeZD8FzBye");
        cout << "\nCancion encontrada: " << cancion.nombreCancion << " de " << cancion.artista << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
