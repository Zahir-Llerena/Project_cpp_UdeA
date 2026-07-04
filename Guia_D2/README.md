# UdeAWorldCup 2026: Motor de Simulacion Estadistica y Modelado de Datos en C++

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Desafio II)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este proyecto consiste en el diseno e implementacion de un **Motor de Simulacion Matematica** en **C++ puro** para modelar el desarrollo completo de la Copa Mundial de la FIFA 2026 (48 selecciones clasificadas, 12 grupos de 4 equipos y fase eliminatoria desde dieciseisavos de final con un total de 104 partidos). 

El sistema combina conceptos robustos de la Programacion Orientada a Objetos (POO), la gestion explicita de memoria dinamica y el parsing de archivos planos (`.csv`), con un nucleo estadistico fundamentado en la **Distribucion de Poisson**. El motor no solo predice los marcadores de forma determinista basandose en la fuerza historica ofensiva y defensiva de las selecciones, sino que integra variables estaticas de control para auditar el esfuerzo computacional y el consumo de bytes en el *Heap*.

---

## Modulos del Sistema y Arquitectura de Datos

El software se divide metodologicamente en cuatro etapas de infraestructura acopladas de manera modular:

### 1. Infraestructura de Almacenamiento Dinamico (`Lista<T>`)
* **Diseno Generico (Templates):** Implementa una plantilla de clase (*Class Template*) `Lista<T>` que actua como un contenedor generico, permitiendo reutilizar la logica estructural para tipos de datos primitivos (`int`) o complejos (`Equipo`, `Registro`).
* **Gestion del Heap:** Almacena los objetos en un arreglo dinamico apuntado por un puntero maestro (`T* elementos`). Cuando el volumen de datos alcanza el limite, el metodo privado `redimensionar()` duplica la capacidad, solicita un bloque de memoria contiguo al sistema operativo, muda los registros y libera el espacio viejo con `delete[]` para evitar fugas de memoria (*memory leaks*).
* **Auditoria de Hardware:** Utiliza variables de clase estaticas (`static`) para llevar un registro centralizado y acumulativo de las iteraciones de mudanza y los bytes exactos en uso dentro del *Heap*.

### 2. Modelado del Dominio (`Equipo`)
* **Encapsulamiento Estricto:** Restringe el acceso a los atributos basicos del equipo (ranking, historial de goles y promedios) bajo el modificador `private`.
* **Manejo de C-Strings:** Procesa los datos crudos del CSV empleando arreglos de caracteres estaticos de tamano fijo (`char[]`) para asegurar predictibilidad en la memoria. Desarrolla funciones vectoriales hechas a medida (funciones Lambda locales) para la copia segura de cadenas y la comparacion de texto letra por letra hasta el caracter nulo (`'\0'`).
* **Estadistica Local:** El objeto computa de forma autonoma su fuerza historica ofensiva y defensiva dividiendo los goles anotados y recibidos por el total de partidos jugados.

### 3. Orquestacion y Cumplimiento de Reglas
* **`GestorArchivos`:** Encargado del subsistema de Entrada/Salida (I/O). Fragmenta (*split*) las cadenas del archivo CSV usando la coma o punto y coma como delimitador, procesa los metadatos y pobla dinamicamente la coleccion maestra de equipos.
* **`ClasificadorLlaves`:** Encapsula el reglamento deportivo de competencia de la FIFA. Implementa algoritmos de ordenamiento por el Metodo de la Burbuja (*Bubble Sort*) para clasificar los equipos bajo criterios priorizados (Puntos $\to$ Diferencia de Goles).

---

## Motor Matematico de Simulacion (Distribucion de Poisson)

Para modelar la incertidumbre del futbol de manera estadistica coherente, la clase `MotorMundial` calcula la intensidad probabilistica de anotacion ($$\lambda$) para cada encuentro. En el futbol, los goles se comportan como eventos independientes de baja frecuencia, modelados perfectamente por la ecuacion de Poisson:

$$P(k; \lambda) = \frac{\lambda^k \cdot e^{-\lambda}}{k!}$$

Donde $k$ cuantifica el numero de goles y $\lambda$ representa el promedio esperado de anotaciones. El motor calcula las intensidades relativas ponderando los promedios con factores de correccion ofensiva y defensiva ($$\alpha = 0.6$ y $\beta = 0.4$). Las intensidades resultantes se inyectan en el motor pseudoaleatorio Mersenne Twister (`std::mt19937`) a traves de la plantilla `std::poisson_distribution<int>`.
