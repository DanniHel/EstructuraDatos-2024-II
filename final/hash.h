#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>

using namespace std;

// Estructura para almacenar la información de una canción
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

    // Función hash simple que calcula el índice en la tabla
    int funcionHash(string idCancion);

public:
    // Constructor
    TablaHash(int tamanio);

    // Función para insertar un par clave-valor
    void insertar(string idCancion, Cancion cancion);

    // Función para buscar la canción por su idCancion
    Cancion buscar(string idCancion);

    // Función para mostrar el contenido de la tabla hash
    void mostrar();
};

// Función para leer los datos del archivo CSV y cargar las canciones en la tabla hash
void cargarDatosDesdeArchivo(string nombreArchivo, TablaHash& tablaHash);

#endif
