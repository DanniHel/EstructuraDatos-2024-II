// trie.h
#ifndef TRIE_H
#define TRIE_H

#include <string>
#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
using namespace std;

// Definir el número de caracteres imprimibles (desde espacio hasta '~')
#define MAX_CHARACTERS 95

// Estructura de un nodo en el Trie
struct NodoTrie {
    char dato;                   // Caracter almacenado en el nodo
    NodoTrie* hijos[MAX_CHARACTERS]; // Array de punteros a los hijos (95 caracteres posibles)
    bool es_hoja;                // Flag que indica si es un nodo hoja (es una palabra completa)
    std::string track_id;        // track_id de la canción asociada a este nodo

    // Constructor para inicializar el nodo
    NodoTrie(char dato);
};

// Declaraciones de funciones
NodoTrie* crear_nodo_trie(char dato);
void liberar_trie(NodoTrie* raiz);
int obtener_indice_char(char c);
NodoTrie* insertar_palabra(NodoTrie* raiz, const std::string& palabra, const std::string& track_id, int & cont1);
void imprimir_trie(NodoTrie* raiz, std::string palabra = "");
void imprimir_trie_mas(NodoTrie* raiz, std::string palabra, TablaHash& tablaHash);
void buscar_por_prefijo(NodoTrie* raiz, const std::string& prefijo, TablaHash& tablaHash);
NodoTrie* procesar_archivo(const std::string& archivo, NodoTrie* raiz,int& cont1, int& cont2);
void recolectar_track_ids(NodoTrie* nodo, const string& palabra, vector<string>& track_ids);
vector<string> buscar_prefijo(NodoTrie* raiz, const string& prefijo);

#endif // TRIE_H
