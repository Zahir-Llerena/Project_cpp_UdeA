# Motor de Simulacion de Dinamica de Particulas y Colisiones Colectivas en R^2

## Universidad de Antioquia
**Facultad de Ingenieria - Departamento de Telecomunicaciones**
* **Asignatura:** Informatica II (Guia de Laboratorio 5)
* **Autor:** Zahir Llerena
* **Email:** zahir.llerena@udea.edu.co

---

## Descripcion del Proyecto

Este repositorio contiene la implementacion en **C++** de un **Motor de Fisica Lineal Discreta de Particulas** que simula, en un espacio euclideo bidimensional ($R^2$), las interacciones cinematicas, rebotes amortiguados y fenomenos de mutuo acoplamiento inelastico (fusion) entre multiples cuerpos dinamicos en presencia de obstaculos geometricos fijos y fronteras perimetrales cerradas.

El software destaca por no depender de motores graficos comerciales ni librerias de colisiones de caja negra. En su lugar, el sistema resuelve vectorialmente las ecuaciones fundamentales de la mecanica clasica y las leyes de conservacion mediante integracion numerica iterativa por pasos discretos de tiempo (*Time-Stepping Loop*), exportando los resultados analiticos en un formato estructurado para su posterior visualizacion o tratamiento de datos.

---

## Modulos y Arquitectura de Software

El diseno esta estructurado bajo una cohesion modular orientada a objetos dividida en cuatro bloques logicos:

### 1. Primitiva Matematica (`Vector2D`)
* Encapsula los componentes cartesianos privados `x` e `y` de precision flotante doble (64 bits).
* Implementa las operaciones del algebra lineal analitica: adicion, sustraccion, producto por escalar y el **Producto Punto** ($\vec{a} \cdot \vec{b}$).
* Garantiza la inmutabilidad de lectura en contextos constantes firmando sus metodos con el calificador `const`, lo que elimina advertencias de optimizacion en compiladores modernos como Clang (Xcode).

### 2. Funciones Geometricas Globales (Algoritmos de Interseccion)
* **`obtenerPuntoMasCercano`:** Implementa una tecnica de sujecion logica (*Clamping*) en los ejes ortogonales para acotar el vector de posicion del centro de una particula circular respecto al perimetro de una caja de colision alineada a los ejes (AABB) de un obstaculo cuadrado.
* **`calcularNormalDelObstaculo`:** Evalua de forma analitica la proximidad hacia las cuatro caras de un bloque para calcular el vector director unitario (normal superficie $\vec{n}$) perpendicular al plano de impacto.

### 3. Entidades del Mundo Fisico (`Particle` y `Obstacle`)
* **`Particle`:** Almacena variables de estado de masa, radio, posicion, velocidad y un flag booleano de existencia. Aplica el metodo de Integracion Numerica de Euler para desplazar de forma discreta al cuerpo: $\vec{r}_{nuevo} = \vec{r}_{actual} + \vec{v} \cdot dt$.
* **`Obstacle`:** Define de forma automatica los limites absolutos de confinamiento espacial de un bloque cuadrado a partir de las coordenadas de su centro geometrico y la longitud de sus aristas.

### 4. Orquestador del Universo Fisico (`CollisionsSimulation`)
* Implementa el patron controlador, resguardando los contenedores dinamicos secuenciales de la STL (`std::vector<Particle>` y `std::vector<Obstacle>`) y canalizando el flujo de escritura persistente hacia el disco (`std::ofstream`).

---

## Logica Fisica y Resolucion de Colisiones

El motor computa y clasifica los impactos en tres niveles secuenciales independientes dentro del lazo de simulacion:

### A. Choques Elasticos Perimetrales (Paredes de la Caja)
Evalua si el radio perimetral de un circulo perfora las fronteras de confinamiento $[0, \text{boxWidth}]$ o $[0, \text{boxHeight}]$. Si se detecta la incursion, aplica una correccion geometrica instantanea para mitigar el atrapamiento numerico y refleja vectorialmente la componente de velocidad correspondiente (conservacion de energia pura, $e = 1.0$):
$v_x = -v_x \quad \text{o} \quad v_y = -v_y$

### B. Choques Inelasticos Amortiguados (Obstaculos Fijos)
Cuando una particula invade un bloque cuadrado, el motor aisla la componente de la velocidad perpendicular al plano proyectandola con el Producto Punto. Si los cuerpos se aproximan, se segmenta la velocidad en un componente tangencial y otro normal, aplicando el coeficiente de restitucion parcial ($e = 0.75$) solo a la fraccion ortogonal:
$\vec{v}_{final} = \vec{v}_{tangencial} - e \cdot (\vec{v} \cdot \vec{n})\vec{n}$

### C. Colisiones de Fusion con Acoplamiento de Masa (Inter-Particula)
Mediante un algoritmo combinatorio sin repeticion de complejidad $O(N^2)$, el motor evalua la distancia entre los centros de todas las particulas activas. Al ocurrir un traslape ($\text{distancia} \le r_1 + r_2$), los cuerpos experimentan un choque perfectamente inelastico:
1. **Conservacion de la Masa:** $M_{total} = m_1 + m_2$.
2. **Conservacion del Momento Lineal:** $\vec{V}_{final} = (m_1\vec{v}_1 + m_2\vec{v}_2) / M_{total}$.
3. **Conservacion de Volumen Plano (Ley de Areas):** $R_{final} = \sqrt{r_1^2 + r_2^2}$.
4. **Desactivacion Logica:** La particula absorbida apaga su bandera `active`, volviendose invisible para el resto de los bucles fisicos del sistema.

---

## Instrucciones de Compilacion y Ejecucion

Este codigo fue optimizado y blindado contra advertencias en entornos rigurosos bajo el compilador Clang/LLVM. Requiere soporte para el estandar **C++11** o superior.

### Compilacion Optimizada por Terminal
```bash
g++ -std=c++11 -O3 main.cpp -o MotorColisiones2D
```
