#include <iostream>
#include "trie.h"
#include "hash.h"
#include "lista_enlazada.h"
using namespace std;

// Función que muestra el menú principal
void menu_principal(){
    cout << endl;
    cout << "____________Menu____________" << endl;
    cout << "1. Listar todas las musicas" << endl;
    cout << "2. Buscar por nombre en todo" << endl;
    cout << "3. PlayList" << endl;
    cout << endl << "0. Salir" << endl << endl;
    cout << "Elige una opcion: ";
}

// Función que muestra el menú de la PlayList
void mostrarMenu() {
    cout << endl;
    cout << "____________PlayList_____________" << endl;
    cout << "1. Agregar una nueva cancion\n";
    cout << "2. Mostrar lista de canciones\n";
    cout << "3. Ordenar canciones por criterio\n";
    cout << "4. Buscar cancion por nombre\n";
    cout << "5. Buscar canciones por artista\n";
    cout << endl;
    cout << "0. Salir\n";
    cout << endl;
    cout << "Ingrese su opcion: ";
}

// Función para cargar canciones desde un archivo CSV
void cargarCancionesDesdeArchivo(const string& nombreArchivo, TablaHash& tablaHash, NodoTrie*& raiz) {

}

// Función para agregar una canción a la PlayList
void agregarCancionAPlayList(NodoTrie* raiz, TablaHash& tablaHash) {
    int key_2 = 1;
    while (key_2 == 1) {
        // Buscar canciones con un prefijo dado
        string prefijo;
        cout << "Ingrese un prefijo para buscar canciones: ";
        cin >> prefijo;
        cout << endl;
        cout << "Canciones que comienzan con ('" << prefijo << "'): \n";
        cout << endl;

        vector<string> track_ids = buscar_prefijo(raiz, prefijo);
        if (!track_ids.empty()) {
            // Imprimir lista de canciones encontradas
            cout << left << setw(8) << "IdCancion" << setw(60) << "Cancion" << setw(30) << "Artista" << setw(7) << "Anio" << setw(12) << "Genero" << setw(10) << "Duracion" << endl;
            cout << string(131, '-') << endl;

            int num_id = 0;
            for (const string& track_id : track_ids) {
                try {
                    Cancion cancion = tablaHash.buscar(track_id);
                    cout << left << setw(8) << ++num_id << setw(60) << cancion.nombreCancion << setw(30) << cancion.artista << setw(7)
                         << cancion.anio << setw(12) << cancion.genero << setw(10) << cancion.duracion << endl;
                } catch (const runtime_error& e) {
                    cout << e.what() << endl;
                }
            }
            cout << "Agregar Cancion a la PlayList (1/0): ";
            cin >> key_2;

            if (key_2 == 1) {
                int llave;
                cout << "Digite el ID de la Cancion: ";
                cin >> llave;

                Cancion unaCancion = tablaHash.buscar(track_ids[llave-1]);
                string atri_02, atri_03, atri_04, atri_07;
                int atri_01, atri_05, atri_06, atri_10, atri_12, atri_19, atri_20;
                float atri_08, atri_09, atri_11,atri_13, atri_14, atri_15, atri_16, atri_17, atri_18;
                atri_01 = unaCancion.id;
                atri_02 = unaCancion.artista;
                atri_03 = unaCancion.nombreCancion;
                atri_04 = unaCancion.idCancion;
                atri_05 = unaCancion.popularidad;
                atri_06 = unaCancion.anio;
                atri_07 = unaCancion.genero;
                atri_08 = unaCancion.danceabilidad;
                atri_09 = unaCancion.energia;
                atri_10 = unaCancion.clave;
                atri_11 = unaCancion.volumen;
                atri_12 = unaCancion.modo;
                atri_13 = unaCancion.discurso;
                atri_14 = unaCancion.acustica;
                atri_15 = unaCancion.instrumentalidad;
                atri_16 = unaCancion.vivacidad;
                atri_17 = unaCancion.valencia;
                atri_18 = unaCancion.tempo;
                atri_19 = unaCancion.duracion;
                atri_20 = unaCancion.firmaTiempo;

                Cancionn nuevaCancion;

                nuevaCancion.id=atri_01;
                nuevaCancion.artist_name=atri_02;
                nuevaCancion.track_name=atri_03;
                nuevaCancion.track_id=atri_04;
                nuevaCancion.popularity=atri_05;
                nuevaCancion.year=atri_06;
                nuevaCancion.genre=atri_07;
                nuevaCancion.danceability=atri_08;
                nuevaCancion.energy=atri_09;
                nuevaCancion.key=atri_10;
                nuevaCancion.loudness=atri_11;
                nuevaCancion.mode=atri_12;
                nuevaCancion.speechiness=atri_13;
                nuevaCancion.acousticness=atri_14;
                nuevaCancion.instrumentalness=atri_15;
                nuevaCancion.liveness=atri_16;
                nuevaCancion.valence=atri_17;
                nuevaCancion.tempo=atri_18;
                nuevaCancion.duration_ms=atri_19;
                nuevaCancion.time_signature=atri_20;

                agregarCancion(nuevaCancion);
                cout<<"la cancion: "<<atri_03<<", fue agregada"<<endl;
                key_2=0;
            }
        } else {
            cout << "No se encontraron canciones con el prefijo '" << prefijo << "'.\n";
            key_2=0;
        }
    }
}


int main() {
    string nombreArchivo = "spotify_data_mini.csv";
    TablaHash tablaHash(10);
    NodoTrie* raiz = nullptr;

    cout << "Procesando archivo| " << nombreArchivo << endl << endl;
    // Cargar datos desde el archivo CSV para la tabla HASH
    cargarDatosDesdeArchivo(nombreArchivo, tablaHash);

    int cont1 = 0, cont2 = 0;
    // Procesar el archivo CSV y cargar las canciones en el Trie
    raiz = procesar_archivo(nombreArchivo, raiz, cont1, cont2);
    cout << "TRIE: Lineas Procesadas (" << cont1 << ") - lineas omitidas (" << cont2 << ")" << endl;

    // Agregar algunas canciones de ejemplo (opcional)
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
    agregarCancion({15613, "Stacey Pullen", "Circus Act - Original", "5TOnpib4YhHxeC7YG3Gdk5", 2, 2012, "detroit-techno", 0.619, 0.877, 1, -8.294, 1, 0.117, 0.000285, 0.936, 0.352, 0.226, 247.936, 481471, 4});
    agregarCancion({24423, "The Pebbles", "The Pebbles Twist", "54zobGxo8FPv5jX5LlTFLS", 10, 2012, "garage", 0.286, 0.963, 3, -6.353, 1, 0.0607, 0.531, 0.415, 0.306, 0.972, 232.814, 108560, 4});
    agregarCancion({66800, "Flux Pavilion", "Blow the Roof", "1DZfcSkibPHM9h8lPFT7LT", 33, 2013, "dance", 0.517, 0.978, 9, -4.053, 1, 0.381, 0.00351, 0.403, 0.0848, 0.38, 220.169, 247693, 4});
    agregarCancion({37188, "Claro Intelecto", "Reformed", "4K4dnmkdSorkjLyIOjPK6R", 6, 2012, "minimal-techno", 0.71, 0.586, 4, -14.306, 0, 0.273, 7.28e-05, 0.888, 0.105, 0.326, 220.041, 348236, 4});
    agregarCancion({48603, "Amy Macdonald", "Pride", "1wXwO8888WyTeXFBPs3hof", 43, 2012, "singer-songwriter", 0.36, 0.828, 1, -5.234, 1, 0.0426, 0.0463, 0, 0.168, 0.747, 219.974, 202800, 4});
    agregarCancion({91771, "Fariborz Lachini", "Hamechi Aroomeh", "7lFnZQcFRNvKdcgzgD1Frj", 4, 2013, "new-age", 0.447, 0.12, 7, -25.348, 0, 0.0502, 0.995, 0.948, 0.1, 0.118, 219.972, 212741, 3});
    agregarCancion({82987, "Ghost", "La Mantra Mori", "2lOz2PFKoK2cfViA5R6fRJ", 39, 2013, "hard-rock", 0.145, 0.746, 7, -8.796, 0, 0.0427, 0.0688, 0.623, 0.153, 0.426, 219.778, 314453, 4});
    agregarCancion({63615, "Glee Cast", "Nasty / Rhythm Nation (Glee Cast Version)", "0PEa5uu8xlCJHFb76rzpYA", 36, 2013, "club", 0.514, 0.966, 1, -4.753, 1, 0.0994, 0.124, 0.000196, 0.314, 0.927, 219.771, 188880, 4});
    agregarCancion({60141, "Krafty Kuts", "Feel Like Jumpin - Krossbow Remix", "61TE609sILpyLH3Q4aEDH2", 14, 2013, "breakbeat", 0.498, 0.737, 0, -6.655, 1, 0.0435, 5.12e-05, 0.767, 0.0351, 0.342, 219.693, 296000, 4});
    agregarCancion({33774, "Beach House", "Lazuli", "6HdMeOwJXD3oY1Thn1bsCY", 53, 2012, "indie-pop", 0.34, 0.812, 11, -5.783, 0, 0.0299, 0.0103, 0.626, 0.263, 0.724, 219.446, 301867, 4});
    agregarCancion({5390, "The Spits", "Brick by Brick", "69wG551hOd4TzGHUiZkV7C", 14, 2012, "blues", 0.253, 0.972, 4, -3.524, 1, 0.19, 0.243, 0.744, 0.18, 0.257, 218.983, 89040, 4});
    agregarCancion({19142, "Kid Koala", "Denouement", "5J2zriqSBgaIUkHKIYy7pI", 34, 2012, "electro", 0.352, 0.483, 1, -13.81, 0, 0.208, 0.386, 0.896, 0.155, 0.514, 218.775, 97173, 3});
    agregarCancion({65355, "Mr.B The Gentleman Rhymer", "In a Club", "3P18KZqpCuIBI42h67Hgtn", 9, 2013, "comedy", 0.525, 0.669, 10, -10.389, 0, 0.934, 0.182, 0, 0.401, 0.961, 218.676, 58003, 5});
    agregarCancion({12810, "Zara Larsson", "Rooftop", "4JKdEJW98WkBcBi6cB0d89", 38, 2012, "dance", 0.395, 0.798, 0, -4.032, 0, 0.388, 0.0825, 0.000174, 0.138, 0.392, 218.356, 239536, 4});
    agregarCancion({80398, "The Cemetary Girlz", "Chupacabra", "2kyxIJZ2wn56pPEx7cEOkw", 4, 2013, "goth", 0.266, 0.971, 7, -5.371, 1, 0.172, 0.00149, 0.234, 0.187, 0.314, 218.102, 192880, 4});
    agregarCancion({13216, "Popcaan", "Party Shot (Ravin Part. 2) - Major Lazer Remix", "5gq9HQrNzWCagqatprFUKm", 16, 2012, "dancehall", 0.736, 0.819, 10, -3.94, 0, 0.434, 0.0222, 0.000206, 0.0611, 0.639, 218.062, 200456, 4});
    agregarCancion({77690, "WE ARE TWIN", "The Way We Touch", "0pAbgUM52zwMJwimnju0tG", 30, 2013, "garage", 0.393, 0.743, 8, -4.989, 1, 0.0823, 0.00524, 3.88e-05, 0.182, 0.345, 217.987, 263320, 4});
    agregarCancion({35418, "The Electro Swingers", "Tesla Is Knockin' At My Door", "3AlWwKCUlyQHpLSOahmC3i", 19, 2012, "jazz", 0.738, 0.78, 1, -10.055, 1, 0.323, 0.252, 0.0136, 0.0997, 0.857, 217.985, 210120, 4});
    agregarCancion({1983, "The Offspring", "Secrets From The Underground", "1KblaMkte0ZEyk9k6kLW92", 50, 2012, "alt-rock", 0.287, 0.983, 7, -1.977, 1, 0.293, 0.000261, 0, 0.345, 0.375, 217.88, 189813, 4});



    int key = 0;
    int opcion;

    while (key == 0) {
        menu_principal();
        cin >> opcion;
        cout << endl;
        switch (opcion) {

            case 1:
                cout << "Contenido del Trie: \n";
                imprimir_trie(raiz);
                break;

            case 2: {
                int key_2 = 1;
                while (key_2 == 1) {
                    string prefijo;
                    cout << "Ingrese un prefijo para buscar canciones: ";
                    cin >> prefijo;
                    cout << endl;
                    cout << "Canciones que comienzan con -|> '" << prefijo << "': \n";
                    cout << endl;
                    buscar_por_prefijo(raiz, prefijo, tablaHash);

                    cout << endl << "Continuar buscando? (1/0): ";
                    cin >> key_2;
                }
            }
            break;

            case 3:
                int elige;
                do {
                    mostrarMenu();
                    cin >> elige;
                    switch (elige) {
                        case 1:
                            agregarCancionAPlayList(raiz, tablaHash);
                            break;
                        case 2:
                            mostrarLista();
                            break;
                        case 3: {
                            int criterio, orden;
                            cout<<"Elige una opcion para ordenar"<<endl;

                            cout << left <<setw(25)<<"1. N."<<setw(25)<<"12. mode"<<endl;
                            cout << left <<setw(25)<<"2. artist_name"<<setw(25)<<"13. speechiness"<<endl;
                            cout << left <<setw(25)<<"3. track_name"<<setw(25)<<"14. acousticness"<<endl;
                            cout << left <<setw(25)<<"4. track_id"<<setw(25)<<"15. instrumentalness"<<endl;
                            cout << left <<setw(25)<<"5. popularity"<<setw(25)<<"16. liveness"<<endl;
                            cout << left <<setw(25)<<"6. year"<<setw(25)<<"17. valence"<<endl;
                            cout << left <<setw(25)<<"7. genre"<<setw(25)<<"18. tempo"<<endl;
                            cout << left <<setw(25)<<"8. danceability"<<setw(25)<<"19. duration_ms"<<endl;
                            cout << left <<setw(25)<<"9. energy"<<setw(25)<<"20. time_signature"<<endl;
                            cout << left <<setw(25)<<"10. key"<<setw(25)<<"21. Aleatorio"<<endl;
                            cout << left <<setw(25)<<"11. loudness"<<setw(25)<<"22. Mueve una Cancion"<<endl;

                            cout<<endl;
                            cout << "--|: ";
                            cin >> criterio;
                            cout<<endl;
                            if(criterio!=21 && criterio!=22){
                                cout<<"0. Ascendente, 1. Descendente: ";
                                cin >> orden;
                                cout<<endl;
                            }else{
                                orden=0;
                            }
                            ordenarPorCriterio(criterio, orden);
                            cout<<endl;
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
                            cout << "Saliendo al Menu Principal...\n";
                            break;
                        default:
                            cout << "Opcion invalida. Intente de nuevo.\n";
                    }
                } while (elige != 0);
                break;

            case 0:
                key = 1;
                break;

            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }

    // Liberar memoria
    liberarMemoria();// lista enlazada
    liberar_trie(raiz);
    return 0;
}
