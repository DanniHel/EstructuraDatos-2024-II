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
void TablaHash::insertar(string idCancion, Cancion cancion,int &num2) {
    int indice = funcionHash(idCancion);  // Obtiene el índice en la tabla
    tabla[indice].push_back(make_pair(idCancion, cancion));  // Inserta el par (idCancion, cancion)
    num2++;
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
    //tiempo de ejecucion de la funcion en nanosegundos
    auto inicio = chrono::steady_clock::now();
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    string linea;

    // Ignorar la primera línea (cabecera)
    getline(archivo, linea);

    int num1 = 0; // Contar errores al cargar líneas
    int num2 = 0; // procesados correctamente
    // Leer cada línea del archivo y procesarla
    while (getline(archivo, linea)) {
        //primero buscamos dos grupo de 4 ("),
        //a los dos primeros del primer grupo lo reemplazamos con un / invertido a cada uno
        //a los dos ultimos del segundo grupo lo reemplazamos con un / invertido a cada uno
        int incre1=0;
        int pos2;
        for(int i=0;i<linea.size();i++){
            if(linea[i]=='"' && linea[i+1]=='"' && linea[i+2]=='"' && linea[i+3]=='"'){
                incre1++;
                if(incre1==2){
                    //seleccionamos el primero y el ultimo
                    linea[pos2]='\\';
                    linea[pos2+1]='\\';
                    linea[i+2]='\\';
                    linea[i+3]='\\';
                }
                pos2=i;
            }

        }

        //segundo cambiamos la (,) por otro caracter
        //reemplazar la coma (,) de entre ("" , "")
        int incre=0;
        int pos1;
        for(int i=0;i<linea.size();i++){
                if(linea[i]=='"' && linea[i+1]=='"'){//buscamos dos ("") juntas
                    incre++;//cada vez que hay dos ("") juntas contamos
                    if(incre>=2){
                        //si encontramos el segundo grupo de comilas dobles,
                        //buscamos cualquier (,) entre las dos comillas y lo reemplazamos con (¯)
                        for(int j=pos1+2;j<i;j++){
                            if(linea[j]==','){
                                linea[j]='\\';
                            }
                            //cout<<"("<<linea[j]<<")";
                        }
                    }
                    pos1=i;
                }
        }
        //eliminamos todos los "
        linea.erase(remove(linea.begin(), linea.end(), '"'), linea.end());

        stringstream ss(linea);
        string token;
        Cancion cancion;
        try {
            // Extraemos los datos de la línea
            getline(ss, token, ','); cancion.id = stoi(token);  // id
            getline(ss, cancion.artista, ',');  // artista
            getline(ss, token, ',');  // track_name

            //¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
            // si encontramos dos /)invertida, reemplazamos el segundo (/)invertida por un (")
            for(int i=0;i<token.size();i++){
                if(token[i]=='\\' && token[i+1]=='\\'){
                    token[i+1]='"';
                }
            }
            //si encontramos un (/)invertida y un espacio
            //reemplazamos por una coma(,)
            for(int i=0;i<token.size();i++){
                if(token[i]=='\\' && token[i+1]==' '){
                    token[i]=',';
                }
            }
            //eliminamos todo los (/)invertidas que quedaron
            token.erase(remove(token.begin(), token.end(), '\\'), token.end());

            cancion.nombreCancion=token;
            //________________________________________________________________________________________

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
            tablaHash.insertar(cancion.idCancion, cancion, num2);

        } catch (const exception& e) {
            num1++;
            //cerr << "Error en la linea: " << linea << endl;
        }
    }




    auto fin = chrono::steady_clock::now();
    auto tiempo=chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    cout << "HASH: Lineas Procesadas correctamente (" << num2 << ") - ";
    cout << "Lineas omitidas (" << num1 <<") | tiempo: "<<tiempo<<" milisegundos"<< endl;
}
