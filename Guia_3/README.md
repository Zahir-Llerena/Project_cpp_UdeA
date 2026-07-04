# Sistemas de Compresion de Datos y Criptografia Bitwise en C++

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Guia de Laboratorio 3)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este proyecto implementa un sistema modular de procesamiento de informacion enfocado en dos pilares fundamentales de las telecomunicaciones modernas: la **eficiencia en el ancho de banda** (mediante algoritmos de compresion de datos sin perdida) y la **seguridad de la informacion** (a traves de tecnicas de criptografia simetrica a nivel de bits).

A traves de este software, se analizan los principios teoricos de la codificacion de fuentes de informacion y la manipulacion directa de archivos planos (`.txt`) en C++, implementando estructuras analiticas personalizadas sin depender de librerias externas de compresion.

---

## Modulos y Algoritmos Implementados

El sistema integra componentes discretos controlados desde un panel centralizado (`main`):

### 1. Codificacion Run-Length Encoding (RLE) - Ejercicio 5.1
* **Compresion:** Escanea secuencias lineales de caracteres consecutivos repetidos y los reduce a un formato condensado del tipo `[conteo][caracter]`. Optimiza la transmision de datos con alta redundancia consecutiva.
* **Descompresion:** Reconstruye la cadena original decodificando la magnitud numerica (*tokenizacion* con `isdigit` y `std::stoi`) y replicando el simbolo en memoria dinamica.
* **Verificacion:** Implementa una compuerta de control de integridad que compara byte por byte la cadena restaurada contra la original, certificando la naturaleza *lossless* (sin perdida) del proceso.

### 2. Codificacion Lempel-Ziv 78 (LZ78) Manual - Ejercicio 5.2 & 5.2New
* **Restriccion de Ingenieria:** Prohibicion estricta de contenedores de la STL (`std::vector`, `std::map`, etc.) y de almacenamiento de frases en objetos string complejos.
* **Gestion en el Heap:** Construccion manual de un diccionario adaptativo utilizando **Arreglos Paralelos** dinámicos (`int*` para indices de prefijos y `char*` para caracteres), enlazados implicitamente por su posicion fisica en el Heap.
* **Evolucion del Motor (Version New):** Incorporacion de un modulo de busqueda dinamica de patrones secuenciales que asigna indices incrementales (`j + 1`) al detectar subcadenas redundantes en el flujo de entrada, generando codigos vectoriales formales del tipo `(prefijo, caracter)`.

### 3. Criptografia Simetrica Bitwise (Rotacion y XOR) - Ejercicio 5.3
* **Rotacion Circular de Bits (Bitwise Carousel):** Desplaza los bits de cada byte a la izquierda mediante el operador de corrimiento (`<<`). Los bits desbordados se recuperan por la derecha utilizando mascara logica y corrimiento derecho (`>>`), fusionandolos con el operador OR (`|`).
* **Mascara XOR:** Aplica una operacion logica distributiva OR Exclusiva (`^`) empleando una clave privada simetrica $K$ de 1 byte (Clave ASCII 65: `'A'`).
* **Reversibilidad:** El modulo descifra la informacion aplicando las propiedades simetricas involutivas del operador XOR ($X \oplus K \oplus K = X$) y revirtiendo la rotacion en sentido opuesto.

### 4. Flujo de Integracion de Archivos de Red - Ejercicio 5.4
* **Persistencia en Disco:** Enlaza flujos fisicos de entrada (`std::ifstream`) y salida (`std::ofstream`) mediante rutas de directorios absolutas.
* **Protocolo de Apertura:** Control preventivo de fallas de transmision; si el archivo de entrada no es localizado o carece de permisos de lectura, el flujo es abortado de forma segura para evitar excepciones en el Kernel.
* **Pipeline del Proceso:** Lee una linea original del dataset, aplica el motor de compresion seleccionado por el usuario, encripta el flujo resultante mediante la logica de rotacion circular, y escribe los datos transformados en un archivo de salida plano (`dataset_Encriptado0.txt`).

---

## Arquitectura del Sistema y Flujo de Datos

El pipeline de procesamiento simula el comportamiento de una pila de protocolos de red, donde los datos se transforman secuencialmente.
