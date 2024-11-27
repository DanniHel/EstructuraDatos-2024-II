#include "hash.h"

// Función hash simple que calcula el índice en la tabla
int TablaHash::funcionHash(string idCancion) {
    int suma = 0;
    for (char c : idCancion) {
        suma += c;  // Sumar los valores ASCII de los caracteres de la clave
    }
    return suma % tamanioTabla;  // Devuelve el índice
}

// Constructor
TablaHash::TablaHash(int tamanio) {
    tamanioTabla = tamanio;
    tabla.resize(tamanioTabla);
}

// Función para insertar un par clave-valor
void TablaHash::insertar(string idCancion, Cancion cancion) {
    int indice = funcionHash(idCancion);  // Obtiene el índice en la tabla
    tabla[indice].push_back(make_pair(idCancion, cancion));  // Inserta el par (idCancion, cancion)
}

// Función para buscar la canción por su idCancion
Cancion TablaHash::buscar(string idCancion) {
    int indice = funcionHash(idCancion);  // Obtiene el índice en la tabla
    // Recorre la lista en esa posición para encontrar la canción
    for (auto& elemento : tabla[indice]) {
        if (elemento.first == idCancion) {
            return elemento.second;
        }
    }
    throw runtime_error("Canción no encontrada");  // Si la canción no existe
}

// Función para mostrar el contenido de la tabla hash
void TablaHash::mostrar() {
    for (int i = 0; i < tamanioTabla; i++) {
        if (!tabla[i].empty()) {
            cout << "Índice " << i << ": ";
            for (auto& elemento : tabla[i]) {
                cout << "(ID: " << elemento.second.idCancion << ", Canción: "
                     << elemento.second.nombreCancion << ", Artista: "
                     << elemento.second.artista << ") "<<endl;
            }
            cout << endl;
        }
    }
}

// Función para leer los datos del archivo CSV y cargar las canciones en la tabla hash
void cargarDatosDesdeArchivo(string nombreArchivo, TablaHash& tablaHash) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;

    // Ignorar la primera línea (cabecera)
    getline(archivo, linea);

    int num = 0; // Contar errores al cargar líneas

    // Leer cada línea del archivo y procesarla
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string token;

        Cancion cancion;
        try {
            // Extraemos los datos de la línea
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

            // Insertar la canción en la tabla hash
            tablaHash.insertar(cancion.idCancion, cancion);

        } catch (const exception& e) {
            num++;
            //cerr << "Error al procesar la línea: " << linea << endl;
        }
    }

    cout << "Líneas omitidas (" << num << ")" << endl;
}
