#include <iostream>
#include "trie.h"
#include "hash.h"
#include "lista_enlazada.h"
using namespace std;


void menu_principal(){
    cout<<endl;
    cout<<"____________Menu____________"<<endl;
    cout<<"1. Cargar datos a la estructura"<<endl;
    cout<<"2. Listar todas las musicas"<<endl;
    cout<<"3. Buscar por nombre en todo"<<endl;
    cout<<"4. PlayList"<<endl;
    cout<<endl<<"0. Salir"<<endl<<endl;

    cout<<"Elige una opcion: ";
}


void mostrarMenu() {
    cout << endl;
    cout << "____________PlayList_____________"<<endl;
    cout << "1. Agregar una nueva cancion\n";
    cout << "2. Mostrar lista de canciones\n";
    cout << "3. Ordenar canciones por criterio\n";
    cout << "4. Buscar cancion por nombre\n";
    cout << "5. Buscar canciones por artista\n";
    cout<<endl;
    cout << "0. Salir\n";
    cout<<endl;
    cout << "Ingrese su opcion: ";
}

int main() {

    string nombreArchivo="spotify_data_mini.csv";

    // Crear una tabla hash con 10 posiciones
    TablaHash tablaHash(10);

    NodoTrie* raiz = nullptr;//nodo trie

    Cancionn nuevaCancion;//lista enlazada

    agregarCancion({0, "Jason Mraz", "I Won't Give Up", "53QF56cjZA9RTuuMZDrSA6", 68, 2012, "acoustic", 0.483, 0.303, 4, -10.058, 1, 0.0429, 0.694, 0.0, 0.115, 0.139, 133.406, 240166, 3});
    agregarCancion({1, "Jason Mraz", "93 Million Miles", "1s8tP3jP4GZcyHDsjvw218", 50, 2012, "acoustic", 0.572, 0.454, 3, -10.286, 1, 0.0258, 0.477, 1.37e-05, 0.0974, 0.515, 140.182, 216387, 4});
    agregarCancion({2, "Joshua Hyslop", "Do Not Let Me Go", "7BRCa8MPiyuvr2VU3O9W0F", 57, 2012, "acoustic", 0.409, 0.234, 3, -13.711, 1, 0.0323, 0.338, 5e-05, 0.0895, 0.145, 139.832, 158960, 4});
    agregarCancion({3, "Boyce Avenue", "Fast Car", "63wsZUhUZLlh1OsyrZq7sz", 58, 2012, "acoustic", 0.392, 0.251, 10, -9.845, 1, 0.0363, 0.807, 0.0, 0.0797, 0.508, 204.961, 304293, 4});
    agregarCancion({4, "Andrew Belle", "Sky's Still Blue", "6nXIYClvJAfi6ujLiKqEq8", 54, 2012, "acoustic", 0.43, 0.791, 6, -5.419, 0, 0.0302, 0.0726, 0.0193, 0.11, 0.217, 171.864, 244320, 4});
    agregarCancion({5, "Chris Smither", "What They Say", "24NvptbNKGs6sPy1Vh1O0v", 48, 2012, "acoustic", 0.566, 0.57, 2, -6.42, 1, 0.0329, 0.688, 1.73e-06, 0.0943, 0.96, 83.403, 166240, 4});
    agregarCancion({6, "Matt Wertz", "Walking in a Winter Wonderland", "0BP7hSvLAG3URGrEvNNbGM", 48, 2012, "acoustic", 0.575, 0.606, 9, -8.197, 1, 0.03, 0.0119, 0.0, 0.0675, 0.364, 121.083, 152307, 4});
    agregarCancion({7, "Green River Ordinance", "Dancing Shoes", "3Y6BuzQCg9p4yH347Nn8OW", 45, 2012, "acoustic", 0.586, 0.423, 7, -7.459, 1, 0.0261, 0.252, 5.83e-06, 0.0976, 0.318, 138.133, 232373, 4});
    agregarCancion({8, "Jason Mraz", "Living in the Moment", "3ce7k1L4EkZppZPz1EJWTS", 44, 2012, "acoustic", 0.65, 0.628, 7, -7.16, 1, 0.0232, 0.0483, 0.0, 0.119, 0.7, 84.141, 235080, 4});
    agregarCancion({9, "Boyce Avenue", "Heaven", "2EKxmYmUdAVXlaHCnnW13o", 58, 2012, "acoustic", 0.619, 0.28, 8, -10.238, 0, 0.0317, 0.73, 0.0, 0.103, 0.292, 129.948, 250063, 4});
    agregarCancion({10, "Tristan Prettyman", "Say Anything", "1RjEDlhTp2iJXWPdLpa8OM", 45, 2012, "acoustic", 0.657, 0.43, 1, -10.202, 1, 0.0314, 0.534, 0.000238, 0.12, 0.335, 91.967, 236379, 4});
    agregarCancion({11, "David Gray", "Money (That's What I Want) - From Jim Beam's Live Music Series", "38sSJ12azM6Mic7ajbHKBi", 45, 2012, "acoustic", 0.655, 0.692, 5, -6.217, 1, 0.0326, 0.568, 2.34e-05, 0.119, 0.547, 121.455, 234270, 4});
    agregarCancion({12, "Boyce Avenue", "Someone Like You", "6VtoP2sJt5oCmPOQIve2sf", 55, 2012, "acoustic", 0.439, 0.207, 1, -9.573, 1, 0.0297, 0.608, 0.0, 0.186, 0.264, 136.514, 276147, 4});
    agregarCancion({13, "Jason Mraz", "The Woman I Love", "0AYG9AcwqEeqgAw3OvshPC", 40, 2012, "acoustic", 0.591, 0.647, 4, -8.34, 1, 0.0277, 0.067, 6.57e-05, 0.231, 0.678, 79.68, 190752, 4});
    agregarCancion({14, "Eddie Vedder", "I Shall Be Released", "0J1iFISejodqBIy0Q9AS0N", 44, 2012, "acoustic", 0.45, 0.713, 6, -7.503, 0, 0.0386, 0.157, 0.0, 0.992, 0.36, 74.71, 283587, 4});
    agregarCancion({15, "The Civil Wars", "Kingdom Come", "1IZc5f9ulw7Ge2eOpQH7w6", 41, 2012, "acoustic", 0.497, 0.277, 4, -11.382, 0, 0.0373, 0.846, 4.77e-06, 0.111, 0.179, 81.367, 222560, 4});
    agregarCancion({16, "Gabrielle Aplin", "Home", "20kpTTSvI4ok6Gm1uZqtcz", 57, 2012, "acoustic", 0.439, 0.265, 2, -10.72, 1, 0.0343, 0.736, 0.0, 0.093, 0.382, 140.494, 247002, 4});
    agregarCancion({17, "Harley Poe", "Transvestities Can Be Cannibals Too", "46KacVTVWMkyXS0jf7TwOX", 39, 2012, "acoustic", 0.499, 0.614, 7, -8.175, 1, 0.0621, 0.151, 3.52e-06, 0.0555, 0.605, 89.038, 276973, 4});
    agregarCancion({18, "Ron Pope", "One Grain of Sand", "3yqJGfvXtPZLiWHVeLWtm8", 49, 2012, "acoustic", 0.713, 0.824, 3, -7.168, 1, 0.0393, 0.106, 8.03e-05, 0.13, 0.696, 120.028, 207240, 4});
    agregarCancion({19, "Sara Bareilles", "Once Upon Another Time", "7KG9zriC6iP8F1CNihtR8Y", 39, 2012, "acoustic", 0.275, 0.216, 2, -14.504, 1, 0.0493, 0.896, 0.0, 0.231, 0.0551, 95.421, 324333, 5});
    agregarCancion({20, "Harley Poe", "The Hearse Song", "09ibWmdrePCN2E2Gbm4Aen", 39, 2012, "acoustic", 0.512, 0.375, 11, -9.525, 0, 0.0652, 0.527, 0.0, 0.109, 0.445, 183.452, 166467, 3});


    int key=0;
    int opcion;

    while(key==0){
        menu_principal();
        cin >> opcion;
        cout<<endl;
        switch (opcion){
        case 1:
            {
            cout<<"Procesando archivo| "<<nombreArchivo<<endl<<endl;
            // Cargar datos desde el archivo CSV para tabla HAHS
            cargarDatosDesdeArchivo(nombreArchivo, tablaHash);
            int cont1=0;
            int cont2=0;
            // Procesar el archivo CSV y cargar las canciones en el Trie
            raiz = procesar_archivo(nombreArchivo, raiz, cont1, cont2);
            cout<<"TRIE: Lineas Procesadas ("<<cont1<<") - lineas omitidas ("<<cont2<<")"<<endl;
            }
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
                cout<<endl;
                cout << "Canciones que comienzan con -|> '" << prefijo << "': \n";
                cout<<endl;
                buscar_por_prefijo(raiz, prefijo, tablaHash);

                cout<<endl<<endl;
                cout<<"Continuar buscando? (1/0): ";
                cin >> key_2;
            }
            }
            break;
        case 4:
            {
            int elige;
            do {
                mostrarMenu();
                cin >> elige;

                switch (elige) {
                    case 1: {

                        int key_2=1;
                        while(key_2==1){
                            // Buscar canciones con un prefijo dado
                            string prefijo;
                            cout << "Ingrese un prefijo para buscar canciones: ";
                            cin >> prefijo;
                            cout<<endl;
                            cout << "Canciones que comienzan con -|> '" << prefijo << "': \n";
                            cout<<endl;
                            buscar_por_prefijo(raiz, prefijo, tablaHash);

                            cout<<endl;
                            cout<<"Continuar buscando? (1/0): ";
                            cin >> key_2;
                        }
                        /*
                        cout << "Ingrese los datos de la canción:\n";
                        cout << "ID: "; cin >> nuevaCancion.id;
                        cin.ignore();
                        cout << "Nombre del artista: "; getline(cin, nuevaCancion.artist_name);
                        cout << "Nombre de la canción: "; getline(cin, nuevaCancion.track_name);
                        cout << "Track ID: "; cin >> nuevaCancion.track_id;
                        cout << "Popularidad: "; cin >> nuevaCancion.popularity;
                        cout << "Año: "; cin >> nuevaCancion.year;
                        cout << "Género: "; cin >> nuevaCancion.genre;
                        cout << "Duración (ms): "; cin >> nuevaCancion.duration_ms;
                        agregarCancion(nuevaCancion);
                        cout << "Canción agregada exitosamente.\n";
                        */
                        break;
                    }
                    case 2:
                        mostrarLista();
                        break;
                    case 3: {
                        string criterio;
                        cout << "Ingrese el criterio para ordenar (popularity, year, artist_name): ";
                        cin >> criterio;
                        ordenarPorCriterio(criterio);
                        break;
                    }
                    case 4: {
                        string nombre;
                        bool hay;
                        cout << "Ingrese el nombre de la canción a buscar: ";
                        cin.ignore();
                        getline(cin, nombre);
                        buscarPorNombre(nombre, hay);
                        if (!hay) cout << "No se encontraron coincidencias.\n";
                        break;
                    }
                    case 5: {
                        string artista;
                        bool hay;
                        cout << "Ingrese el nombre del artista a buscar: ";
                        cin.ignore();
                        getline(cin, artista);
                        buscarPorArtista(artista, hay);
                        if (!hay) cout << "No se encontraron coincidencias.\n";
                        break;
                    }
                    case 0:
                        cout << "Saliendo del programa...\n";
                        break;
                    default:
                        cout << "Opción inválida. Intente de nuevo.\n";
                }
            } while (elige != 0);
            }
            break;
        case 0:
            key=1;
            break;

        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    }
    //de la lista enlazada
    liberarMemoria();
    // Liberar la memoria del Trie
    liberar_trie(raiz);
    return 0;

}
