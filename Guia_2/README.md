# Practicas de Algoritmia Avanzada y Matrices en C++

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Laboratorio Practico 3)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este repositorio contiene la implementacion en **C++** de una serie de algoritmos de optimizacion, procesamiento de cadenas, operaciones con matrices estaticas y analisis numerico. Los ejercicios estan orientados a consolidar habilidades avanzadas de programacion estructurada, manejo de tipos de datos complejos y analisis de arreglos multidimensionales, sirviendo como base conceptual para asignaturas superiores de infraestructura y redes de telecomunicaciones.

El codigo incluye una interfaz interactiva por menues nativa en consola para ejecutar y auditar el comportamiento de cada subrutina de manera independiente.

---

## Contenido y Estructura del Codigo

El archivo principal implementa los siguientes modulos y retos algoritmicos:

* **Ejercicio 3.1 (Desglose de Efectivo):** Implementacion de un algoritmo codicioso (*Greedy*) para determinar la minima combinacion de denominaciones monetarias (billetes y monedas) para una cantidad escalar. Controla residuos residuales no transaccionables (menores a $50) etiquetandolos como "Faltantes".
* **Ejercicio 3.3 (Analisis Posicional de Cadenas):** Uso de la sobrecarga del operador de igualdad (`==`) sobre objetos `std::string` para validar identidad absoluta, y desarrollo de un bucle de busqueda vectorial acotado por la cadena mas corta para extraer coincidencias por indices cartesianos.
* **Ejercicio 3.5 (Conversion Escalar a Cadena por Referencia):** Algoritmo de descomposicion por divisiones modulares sucesivas en base 10 para transformar variables de tipo `int` en objetos `std::string` mediante aritmetica ASCII (mapeo con el caracter base `'0'`). Implementa paso de parametros por referencia (`&`) para evitar duplicacion en la pila de ejecucion (*Stack*).
* **Ejercicio 3.7 (Filtrado de Duplicados / Conjuntos):** Algoritmo de busqueda lineal anidada para depurar caracteres repetidos dentro de un texto. Modela de forma nativa la operacion de pertenencia a un conjunto sin utilizar contenedores externos de la STL.
* **Ejercicio 3.9 (Segmentacion y Suma de Cifras):** Proceso de normalizacion de strings numéricos aplicando insercion de caracteres de relleno (*Padding* con ceros a la izquierda) mediante congruencia modular. Posteriormente, realiza divisiones de memoria (*Slicing*) con `.substr()` y conversion de gran capacidad con `std::stoll`.
* **Ejercicio 3.11 (Gestion Matricial de un Cine):** Control y renderizado interactivo de un espacio bidimensional estatico de 15 x 20 bytes. Mapea coordenadas complejas ingresadas por el usuario (ej: "B10") a indices numericos directos en memoria aplicando operaciones con el caracter base `'A'`.
* **Ejercicio 3.13 (Analisis Astronomico NGC 1300):** Algoritmo de convolucion espacial basico empleando el Vecindario de Von Neumann para la deteccion de picos de intensidad luminica (estrellas) en una matriz de pixeles. Optimiza el rendimiento de la CPU al transformar operaciones de punto flotante en multiplicaciones escalares (Suma > 30).
* **Ejercicio 3.15 (Colision de Rectangulos - Optimizacion Min-Max):** Implementacion del Teorema del Eje Separador (SAT) para dos dimensiones, calculando el rectangulo resultante de la interseccion en $R^2$ mediante operaciones de comparacion directa en lugar de arboles de decision complejos.
* **Ejercicio 3.17 (Suma de Numeros Amigables):** Implementacion de un algoritmo optimizado de busqueda de divisores con complejidad de tiempo acotada a $O(\sqrt{N})$. Emplea poda logica de bifurcacion (`b > a`) para eliminar duplicaciones y omitir numeros perfectos.

---

## Conceptos de Ingenieria y Optimizacion Implementados

El script destaca por la incorporacion explicita de buenas practicas de diseno de software de infraestructura:

1. **Aritmetica de Punteros en Arreglos 2D:** En el Ejercicio 3.13 (`analizar_estrellas`), la matriz bidimensional de la imagen es procesada pasando la direccion fisica de la primera celda (`&imagen[0][0]`). La navegacion por las filas se realiza mediante desplazamientos lineales directos de punteros:
   $$\text{offset} = (i \times \text{columnas}) + j$$
   Esto elimina la sobrecarga de saltos dobles en memoria que generan las matrices convencionales.
2. **Uso Eficiente de Pasaje por Referencia:** El metodo `convertir_entero_a_cadena` modifica directamente el objeto `std::string` del hilo invocador al recibirlo como `std::string &resultado`. Esto previene el *overhead* de copia de memoria del Stack que ocurre en llamadas por valor.
3. **Optimizacion de Bucles Complejos:** En el calculo de divisores (Ejercicio 3.17), el limite de busqueda se restringe logicamente evaluando `i * i <= n`, reduciendo drásticamente las iteraciones necesarias frente a un ciclo lineal convencional $O(N)$.

---

## Requisitos del Sistema y Herramientas

Para compilar, auditar y ejecutar este banco de pruebas, se requiere un compilador compatible con el estandar de **C++11** o superior:
* **macOS:** Xcode Command Line Tools (**Clang** / Apple LLVM compiler).
* **Linux:** GNU Compiler Collection (**GCC** / `g++`).
* **Windows:** MinGW-w64 o Visual Studio (MSVC).

---

## Compilacion y Ejecucion por Terminal

### Comando de Compilacion Portable
Ejecute la siguiente instruccion en la terminal para compilar el codigo activando las optimizaciones de segundo nivel (`-O2`):

```bash
g++ -std=c++11 -O2 main.cpp -o BancoEjerciciosAvanzados
```
