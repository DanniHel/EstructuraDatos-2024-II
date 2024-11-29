
<div align="center">

# Ingeniería de Software

# Proyecto 

![imagen](img/img-inf-01.png)

</div>


# Temas:

**Estructuras de Datos para Manejo de Canciones**



## Integrantes:

- Vizarreta Checya Carlos Adrian  (100%)
- Quispe Cjuiro  Danny  (100%)

**Curso:** ESTRUCTURA DE DATOS

**Semestre:** IV

**Docente:** Edson Francisco Luque Mamani

<div align="center">
2024 - II
</div>

---
### Informe del Proyecto - **Estructuras de Datos para Manejo de Canciones**

---

#### **Descripción General**

Este proyecto implementa una aplicación en C++ que maneja y organiza datos de canciones mediante tres estructuras de datos principales: **Tabla Hash**, **Trie** y una **Lista Enlazada**. El objetivo principal es cargar datos desde un archivo CSV, ofrecer métodos eficientes para búsqueda y organizar las canciones de diferentes maneras.

---

### **Estructuras de Datos Implementadas**

#### **1. Tabla Hash (`hash.h`, `hash.cpp`)**
- **Descripción:**
  - Implementada para almacenar canciones según su ID único (`track_id`).
  - Utiliza un vector de listas para manejar colisiones.
  - Función hash basada en la suma de los valores ASCII de los caracteres de `track_id`.

- **Funciones principales:**
  - `insertar`: Agrega una canción con su ID como clave.
  - `buscar`: Recupera una canción usando su `track_id`.
  - `mostrar`: Imprime todas las canciones almacenadas.
  - `cargarDatosDesdeArchivo`: Lee un archivo CSV, procesa cada línea e inserta los datos en la tabla.

- **Ventajas**: Búsqueda y almacenamiento eficientes para ID únicos.
- **Limitaciones**: Requiere manejo explícito de colisiones.

---

#### **2. Trie (`trie.h`, `trie.cpp`)**
- **Descripción:**
  - Estructura jerárquica que permite la búsqueda rápida de canciones por sus nombres.
  - Cada nodo representa un carácter, y las hojas contienen el `track_id` de la canción correspondiente.

- **Funciones principales:**
  - `insertar_palabra`: Inserta un nombre de canción junto con su `track_id`.
  - `buscar_por_prefijo`: Recupera canciones cuyo nombre comienza con un prefijo.
  - `imprimir_trie`: Imprime todas las canciones almacenadas en el Trie.
  - `procesar_archivo`: Procesa un archivo CSV e inserta los datos en el Trie.

- **Ventajas**: Búsqueda eficiente por prefijo, ideal para autocompletado.
- **Limitaciones**: Consume más memoria debido a la representación de caracteres individuales.

---

#### **3. Lista Enlazada (`main.cpp`)**
- **Descripción:**
  - Permite la creación y gestión de una playlist personalizada.
  - Ofrece métodos para agregar canciones, ordenarlas y buscar por nombre o artista.

- **Funciones principales:**
  - `agregarCancion`: Inserta canciones en la lista enlazada.
  - `mostrarLista`: Imprime todas las canciones en la playlist.
  - `ordenarPorCriterio`: Ordena las canciones según atributos como popularidad o año.

---

### **Flujo del Programa**

1. **Carga de Datos**:
   - Los datos se cargan desde un archivo CSV en la tabla hash y el Trie.
   - Se manejan errores durante la carga (líneas mal formateadas).

2. **Interacción con el Usuario**:
   - **Menú Principal**: Opciones para cargar datos, listar canciones, buscar por prefijo y gestionar playlists.
   - **Submenús**:
     - Gestión de playlists.
     - Búsqueda por prefijo para facilitar la selección de canciones.

3. **Opciones Avanzadas**:
   - Ordenar canciones por criterios personalizados.
   - Búsqueda eficiente por nombre o artista.

---

### **Aspectos Técnicos**

#### **Manejo de Archivos**
- Se utiliza `ifstream` para leer los datos del archivo CSV.
- Se procesan campos como popularidad, género, duración, y otros atributos para crear estructuras de canciones.

#### **Estructura de la Canción (`struct Cancion`)**
- Contiene campos clave como `id`, `artista`, `nombreCancion`, `idCancion`, `popularidad`, `año`, entre otros.

#### **Integración de Estructuras**
- La tabla hash y el Trie están interconectados:
  - El Trie almacena los nombres de las canciones y referencia al `track_id`.
  - La tabla hash almacena los datos completos de las canciones y permite la recuperación rápida basada en el `track_id`.

---

### **Consideraciones y Mejoras Futuras**
- **Optimización**:
  - Usar un mejor método de hash para reducir colisiones.
  - Mejorar la estructura del Trie para minimizar uso de memoria (por ejemplo, Trie comprimido).

- **Escalabilidad**:
  - Incorporar manejo de datos más grandes con estructuras de almacenamiento externo.
  - Implementar persistencia para guardar las playlists personalizadas.

- **Funcionalidades Adicionales**:
  - Filtrar canciones por rango de años, géneros o popularidad.
  - Implementar una interfaz gráfica o basada en web para mejorar la interacción.

---

Este proyecto demuestra el uso eficaz de estructuras de datos en aplicaciones prácticas, optimizando tanto el almacenamiento como la recuperación de información. Si necesitas ajustes o detalles específicos, no dudes en indicarlo.