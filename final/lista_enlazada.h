#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para almacenar información de una canción
struct Cancionn {
    int id;
    string artist_name;
    string track_name;
    string track_id;
    int popularity;
    int year;
    string genre;
    float danceability;
    float energy;
    int key;
    float loudness;
    int mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int duration_ms;
    int time_signature;

    void mostrar() const;
};

// Nodo de la lista doblemente enlazada
struct Nodo {
    Cancionn cancion;
    Nodo* siguiente;
    Nodo* anterior;
};

// Declaraciones de funciones
void liberarMemoria();
void agregarCancion(const Cancionn& cancion);
void eliminarPorID(int id);
void eliminarPorNombre(const string& nombre);
void mostrarLista();
void ordenarPorCriterio(int criterio, int orden);
void buscarPorNombre(const string& nombre, bool& hay);
void buscarPorArtista(const string& artista, bool& hay);

#endif // LISTA_ENLAZADA_H
