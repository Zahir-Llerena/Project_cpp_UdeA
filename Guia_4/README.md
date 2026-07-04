# Simulador de Red de Enrutadores y Optimizacion de Caminos Minimos

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Guia de Laboratorio 4)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este proyecto consiste en el diseno y desarrollo de un **Simulador Centralizado de Redes de Enrutamiento**, programado en **C++** utilizando estructuras avanzadas de la Libreria de Plantillas Estandar (STL). La aplicacion modela el comportamiento autonomo y global de una topologia de red dinamica (representada como un grafo pesado bidireccional), calculando de manera determinista las tablas de enrutamiento optimas para la transmision eficiente de paquetes de datos.

El core del sistema computa de forma automatica el **Algoritmo de Dijkstra** ante cualquier mutacion fisica de la infraestructura (adicion/remocion de nodos o alteracion de costos en los enlaces), garantizando la convergencia del sistema en tiempo real.

---

## Arquitectura de Software y Clases Involucradas

El backend del simulador esta estructurado bajo un paradigma orientado a objetos enfocado en la modularidad y el aislamiento de responsabilidades:

### 1. Clase `Enrutador` (Unidad de Capa Fisica/Enlace)
* **Encapsulamiento:** Almacena de forma privada su identidad (`nombre`) y su lista de adyacencia local (`std::map<std::string, int> enlaces`), donde la clave representa el nodo vecino y el valor el costo metrico de la arista.
* **Eficiencia:** La busqueda, insercion y modificacion de vecinos directos se ejecuta en un tiempo logaritmico $O(\log n)$ gracias al diseno basado en arboles balanceados de `std::map`.

### 2. Clase `Red` (Unidad de Capa de Red y Administracion Global)
* **Topologia Global:** Administra el mapa completo de nodos de la red (`std::map<std::string, Enrutador> enrutadores`).
* **Matriz de Enrutamiento 2D:** Gestiona una matriz asociativa anidada de tres niveles que almacena la solucion de los caminos minimos:
  `std::map<std::string, std::map<std::string, std::pair<int, std::vector<std::string>>>> tablasEnrutamiento`
  Estructura: `[Origen] -> [Destino] -> [Costo Total, Secuencia Vectorial de Nodos]`.

### 3. Funciones Auxiliares de Robustez (Capa de Control de Flujo)
* Subrutinas independientes como `limpiarBuffer()` y `esperarTecla()` que gestionan de forma preventiva las banderas de error de `std::cin` y descartan caracteres residuales corruptos, impidiendo que el menu colapse ante entradas no numericas.

---

## Funcionalidades Principales y Teoremas Implementados
