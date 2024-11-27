#include <iostream>
#include "trie.h"
#include "hash.h"

int main() {



    //¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

    // Crear una tabla hash con 10 posiciones
    TablaHash tablaHash(10);

    // Cargar datos desde el archivo CSV
    cargarDatosDesdeArchivo("spotify_data_mini.csv", tablaHash);
/*
    // Mostrar el contenido de la tabla hash
    cout << "Contenido de la tabla hash:" << endl;
    tablaHash.mostrar();

    // Buscar una canción por su idCancion
    try {
        Cancion cancion = tablaHash.buscar("0W2HX4PEW1faQKCwnlio3y");
        cout << "\nCanción encontrada: " << cancion.nombreCancion << " de " << cancion.artista << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
*/
    //___________________________________________________________

    NodoTrie* raiz = nullptr;

    // Procesar el archivo CSV y cargar las canciones en el Trie
    raiz = procesar_archivo("spotify_data_mini.csv", raiz);


    //Imprimir el Trie completo (todas las canciones con su track_id)
    //std::cout << "Contenido del Trie: \n";
    //imprimir_trie(raiz);

    // Buscar canciones con un prefijo dado
    std::string prefijo;
    std::cout << "Ingrese un prefijo para buscar canciones: ";
    std::cin >> prefijo;
    std::cout << "Canciones que comienzan con '" << prefijo << "': \n";
    buscar_por_prefijo(raiz, prefijo, tablaHash);

    // Liberar la memoria del Trie
    liberar_trie(raiz);

    return 0;
}
