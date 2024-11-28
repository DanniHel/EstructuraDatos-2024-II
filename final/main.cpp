#include <iostream>
#include "trie.h"
#include "hash.h"
using namespace std;


void menu_principal(){
    cout<<"____________Menu____________"<<endl;
    cout<<"1. Cargar datos a la estructura"<<endl;
    cout<<"2. Listar todas las musicas"<<endl;
    cout<<"3. Buscar por nombre en todo"<<endl;
    cout<<"4. Salir"<<endl;

    cout<<"Elige una opcion: ";
}

int main() {

    string nombreArchivo="spotify_data_mini.csv";

    // Crear una tabla hash con 10 posiciones
    TablaHash tablaHash(10);

    NodoTrie* raiz = nullptr;//nodo trie

    int key=0;
    int opcion;


    while(key==0){
        menu_principal();
        cin >> opcion;
        switch (opcion){
        case 1:
            // Cargar datos desde el archivo CSV para tabla HAHS
            cargarDatosDesdeArchivo(nombreArchivo, tablaHash);
            // Procesar el archivo CSV y cargar las canciones en el Trie
            raiz = procesar_archivo(nombreArchivo, raiz);
            break;

        case 2:
            /*
            // HASH
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
            // TRIE
            //Imprimir el Trie completo (todas las canciones con su track_id)
            std::cout << "Contenido del Trie: \n";
            imprimir_trie(raiz);

            break;

        case 3:
            {
            int key_2=1;
            while(key_2==1){
                // Buscar canciones con un prefijo dado
                string prefijo;
                cout << "Ingrese un prefijo para buscar canciones: ";
                cin >> prefijo;
                cout << "Canciones que comienzan con '" << prefijo << "': \n";
                buscar_por_prefijo(raiz, prefijo, tablaHash);

                cout<<endl;
                cout<<".Seguir Buscando? 1.(si), 0.(no): ";

                cin >> key_2;
            }
            }
            break;

        case 4:
            key=1;
            break;

        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }
    // Liberar la memoria del Trie
    liberar_trie(raiz);
    return 0;

}
