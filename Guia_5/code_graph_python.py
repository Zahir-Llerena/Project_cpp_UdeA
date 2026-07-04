# ============================================================================
# IMPORTACIÓN DE LIBRERÍAS DE LA SUITE CIENTÍFICA DE PYTHON
# EXPLICACIÓN: C++ requiere compilar cabeceras estáticas (#include). Python utiliza
# un intérprete dinámico que importa módulos y les asigna un alias (as) corto 
# para optimizar la escritura y mantener la limpieza sintáctica del script.
# ============================================================================
import pandas as pd  # Importa la librería 'Pandas'. Su función es estructurar archivos planos 
                     # en tablas indexadas en memoria RAM denominadas DataFrames. Su alias estándar es 'pd'.
import numpy as np   # Importa la librería 'NumPy'. Diseñada para el cómputo numérico de matrices. 
                     # Permite vectorizar operaciones matemáticas (raíces, potencias) a bajo nivel en C. Su alias es 'np'.
import matplotlib.pyplot as plt  # Importa la interfaz 'pyplot' de 'Matplotlib'. Contiene las funciones 
                                 # de abstracción para diseñar, pintar y configurar lienzos e interfaces gráficas. Su alias es 'plt'.

# ============================================================================
# 1. INGENIERÍA DE DATOS: CARGA EXPLICITADA Y FILTRADO MATRICIAL
# ============================================================================
# Variable de tipo string que almacena la ruta de acceso absoluta del sistema de archivos Unix de macOS.
# Apunta al directorio de Google Drive donde el programa de C++ exportó la base de datos cinemática.
ruta_archivo = "/Users/zahir_llerena/My Drive/UdeA/Semestre_3/Informatica_II/Laboratorio_Git/Guia_5L/simulation_output.txt"

# EXPLICACIÓN PEDAGÓGICA: pd.read_csv() abre el archivo, detecta los saltos de línea y el separador por defecto (coma).
# El parámetro (comment='[') es una directiva condicional de lectura. Le indica al motor de Pandas que si una fila 
# inicia con el carácter '[', debe interpretarla como un comentario descriptivo y descartarla de la carga. 
# De este modo, las líneas de eventos como "[COLISIÓN FUSIÓN]" se eliminan automáticamente en milisegundos.
df = pd.read_csv(ruta_archivo, comment='[') # Almacena el resultado numérico puro en la variable estructurada 'df'.

# MÁSCARA BOOLEANA Y FILTRADO: 
# 1. df['Activa'] == 1 inspecciona la columna 'Activa' y genera un arreglo de valores lógicos (True si es 1, False si es 0).
# 2. Al envolver esa condición dentro de los corchetes exteriores del DataFrame df[ ... ], Pandas extrae únicamente 
#    las filas que coincidan con la condición lógica True (es decir, elimina los registros de las partículas fusionadas inactivas).
# 3. El método .copy() obliga al intérprete a duplicar físicamente los datos filtrados en una nueva dirección de memoria 
#    independiente, evitando que Python lance un aviso de advertencia por asignación secundaria (SettingWithCopyWarning).
df_vivas = df[df['Activa'] == 1].copy() # Guarda la nueva sub-tabla limpia en la variable 'df_vivas'.


# ============================================================================
# 2. CÁLCULO VECTORIAL: DERIVACIÓN NUMÉRICA Y MOMENTO LINEAL TOTAL
# ============================================================================

# EXPLICACIÓN DE LA DERIVADA DISCRETA VECTORIZADA: 
# En física, la velocidad instantánea se define mediante el límite de la razón de cambio espacial sobre el tiempo. 
# En entornos computacionales discretos, esto se aproxima mediante diferencias finitas: v = (r_actual - r_anterior) / (t_actual - t_anterior).
# 1. .groupby('ID') fragmenta temporalmente la tabla en sub-tablas independientes ordenadas por el identificador de cada partícula.
#    Esto evita que la última posición de la partícula 1 se reste erróneamente con la primera posición de la partícula 2.
# 2. ['PosX'].diff() calcula la diferencia aritmética entre la fila actual y la fila inmediatamente anterior de la columna de posición X.
# 3. El operador barra diagonal '/' divide de manera indexada el cambio de espacio (Δx) sobre el cambio de tiempo (Δt) de cada fila.
df_vivas['VelX'] = df_vivas.groupby('ID')['PosX'].diff() / df_vivas.groupby('ID')['Tiempo'].diff() # Calcula la componente vx y crea la columna 'VelX'.
df_vivas['VelY'] = df_vivas.groupby('ID')['PosY'].diff() / df_vivas.groupby('ID')['Tiempo'].diff() # Calcula la componente vy y crea la columna 'VelY'.

# TRATAMIENTO DE VALORES NULOS DE ARRANQUE (NaN - Not a Number):
# Debido a que la función .diff() requiere obligatoriamente una fila previa para restar, el primer instante de tiempo (T=0.0) 
# de cada partícula no tiene con qué operarse, produciendo una casilla con un valor indefinido de falta de datos (NaN).
# El método .bfill() significa "Backward Fill" (relleno hacia atrás). Detecta los NaN de la columna y les asigna el valor 
# numérico válido de la fila inmediatamente posterior (T=0.01), permitiendo que la simulación gráfica inicie sin errores sintácticos.
df_vivas['VelX'] = df_vivas['VelX'].bfill() # Limpia y sobreescribe los valores indefinidos de la velocidad en X.
df_vivas['VelY'] = df_vivas['VelY'].bfill() # Limpia y sobreescribe los valores indefinidos de la velocidad en Y.

# CÁLCULO DE CANTIDAD DE MOVIMIENTO (p = m * v):
# A diferencia de C++, aquí no iteramos con un bucle para multiplicar celda por celda. Pandas toma toda la columna
# de la 'Masa' y la multiplica de forma paralela en el procesador (operación elemental por elementos) por la columna de la velocidad.
df_vivas['Px'] = df_vivas['Masa'] * df_vivas['VelX'] # Instancia la columna de momento lineal en el eje horizontal X.
df_vivas['Py'] = df_vivas['Masa'] * df_vivas['VelY'] # Instancia la columna de momento lineal en el eje vertical Y.

# SUMATORIA GENTIL DE INVARIANTES DEL SISTEMA GLOBAL:
# Para demostrar la ley de conservación en un sistema aislado, debemos sumar los momentos individuales de todas las partículas concurrentes.
# 1. .groupby('Tiempo') unifica en un solo bloque todos los registros que pertenezcan exactamente al mismo instante cronológico.
# 2. .agg({'Px': 'sum', 'Py': 'sum'}) es una función de agregación. Ejecuta la operación de sumatoria simultánea: ΣPx y ΣPy.
# 3. .reset_index() rompe la estructura jerárquica de la agrupación y devuelve la variable 'Tiempo' a una columna estándar indexada.
sistema_global = df_vivas.groupby('Tiempo').agg({'Px': 'sum', 'Py': 'sum'}).reset_index() # Almacena el resumen en 'sistema_global'.

# NORMACALIZACIÓN DEL VECTOR DE MOMENTO NETO TOTAL:
# Aplica de forma directa el Teorema de Pitágoras sobre las columnas completas de sumatorias de momento: |P_neto| = sqrt( (ΣPx)^2 + (ΣPy)^2 ).
# np.sqrt() es la función de raíz cuadrada de NumPy optimizada para arrays vectorizados de gran tamaño.
sistema_global['P_Neto'] = np.sqrt(sistema_global['Px']**2 + sistema_global['Py']**2) # Crea la columna de control analítico absoluto.


# ============================================================================
# 3. DISEÑO Y CONSTRUCCIÓN DEL PANEL GRÁFICO SIMÉTRICO (1 Fila, 2 Columnas)
# ============================================================================

# plt.subplots() inicializa el entorno gráfico. Define una cuadrícula de visualización científica.
# Parámetros: 1 renglón, 2 columnas de visualización. figsize=(16,7) define las dimensiones en pulgadas de la ventana del editor.
# constrained_layout=True activa un algoritmo automático que ajusta los márgenes para que los títulos no se encimen con los ejes.
# La función retorna dos objetos: la ventana contenedora (fig) y un arreglo indexado con los ejes de dibujo (axs).
fig, axs = plt.subplots(1, 2, figsize=(16, 7), constrained_layout=True) 

# Instanciación de un diccionario llave-valor (ID: Código Hexadecimal) para fijar el color estricto de cada partícula.
# Esto garantiza que el color de la trayectoria en el panel 1 coincida con las convenciones analíticas del informe escrito.
colores = {1: '#1f77b4', 2: '#ff7f0e', 3: '#2ca02c', 4: '#d62728'}


# ----------------------------------------------------------------------------
# ---------- PANEL 1 (IZQUIERDO): ESPACIO DE FASE CARTESIANO R² --------------
# ----------------------------------------------------------------------------
ax_espacio = axs[0] # Extrae el eje de la primera posición del arreglo (índice 0) y lo asigna a la variable descriptiva 'ax_espacio'.
# Configura el título principal del panel izquierdo, definiendo un tamaño de fuente de 12 puntos y tipografía en negrita (bold).
ax_espacio.set_title("Espacio de Fase R²: Trayectorias y Evolución Geométrica", fontsize=12, fontweight='bold')

# DIBUJO DE PAREDES DE LA CAJA DE EXPERIMENTACIÓN:
# El método .plot() recibe una lista de coordenadas X y una lista de coordenadas Y. Al unir las esquinas consecutivas del entorno
# (0,0) -> (100,0) -> (100,100) -> (0,100) -> (0,0), dibuja físicamente las líneas negras sólidas que representan los muros de colisión.
ax_espacio.plot([0, 100, 100, 0, 0], [0, 0, 100, 100, 0], color='black', linewidth=2, label='Límites de la Caja')

# DIBUJO DE LOS 4 OBSTÁCULOS CUADRADOS ESTÁTICOS EXIGIDOS:
# Definimos una lista que almacena las coordenadas de los centros geométricos de los 4 cuadrados definidos en el código de C++.
obstaculos = [(30, 30), (70, 30), (30, 70), (70, 70)] 

# BUCLE FOR: Recorre cada tupla de coordenadas de centro (cx, cy) presentes en la lista 'obstaculos'.
for cx, cy in obstaculos: # Inicio del ciclo iterativo de obstáculos.
    # plt.Rectangle() es una función constructora de geometrías. Requiere: (punto_esquina_inferior_izquierda, ancho, alto).
    # Como conocemos el centro (cx, cy) y sabemos que el lado mide 10 unidades, calculamos la esquina restando el radio (10 / 2 = 5).
    # Parámetros adicionales: color gris (#A9A9A9), transparencia del 70% (alpha=0.7) y un patrón de relleno diagonal (hatch='//').
    cuadrado = plt.Rectangle((cx - 5, cy - 5), 10, 10, color='#A9A9A9', alpha=0.7, hatch='//')
    # .add_patch() inyecta la geometría del rectángulo creado directamente sobre el Lienzo del panel izquierdo.
    ax_espacio.add_patch(cuadrado) # Termina la inserción del bloque actual.

# BUCLE DE TRAZADO CINEMÁTICO POR PARTÍCULA:
# .groupby('ID') separa los registros de la tabla por su identificador numérico.
# El bucle for extrae de forma secuencial el número identificador ('p_id') y la sub-tabla con sus coordenadas particulares ('datos').
for p_id, datos in df_vivas.groupby('ID'): # Inicio del ciclo iterativo de graficación de trayectorias.
    # .plot() mapea de forma continua las columnas cronológicas 'PosX' y 'PosY'. 
    # Extrae el color correspondiente del diccionario de colores, asigna una opacidad del 60% (alpha=0.6) y un grosor de línea de 1.5.
    ax_espacio.plot(datos['PosX'], datos['PosY'], color=colores[p_id], alpha=0.6, linewidth=1.5)
    
    # EXPLICACIÓN DE RECONSTRUCCIÓN GEOMÉTRICA DE LA FUSIÓN:
    # datos.iloc[-1] es un método de indexación posicional pura. Extrae exclusivamente la última fila registrada de la partícula 
    # antes de que finalizara el tiempo de la simulación o antes de ser absorbida inelásticamente por otro cuerpo.
    ultimo = datos.iloc[-1] # Almacena el vector de estado terminal en la variable 'ultimo'.
    
    # .scatter() dibuja un punto aislado en el plano cartesiano (marcador posicional terminal).
    # EXPLICACIÓN DEL PARÁMETRO DE TAMAÑO 's': Para reflejar pedagógicamente el Requerimiento 3 de la guía (acreción y cambio de volumen),
    # el tamaño del punto 's' se define multiplicando el atributo dinámico de la masa final (`ultimo['Masa']`) por un factor de escala (60).
    # De este modo, si la partícula absorbió la masa de otro cuerpo, su círculo terminal aumentará de área de forma proporcional en la gráfica.
    ax_espacio.scatter(ultimo['PosX'], ultimo['PosY'], color=colores[p_id], s=ultimo['Masa'] * 60, 
                       edgecolors='black', label=f'Partícula {p_id} (M_f = {ultimo["Masa"]} u)', zorder=5) # zorder=5 la posiciona encima de las líneas.

# CONFIGURACIÓN TÉCNICA FINALES DEL PANEL IZQUIERDO:
ax_espacio.set_xlim(-2, 102)  # Fija los límites mínimos y máximos de visualización del eje X, dando un margen de tolerancia visual.
ax_espacio.set_ylim(-2, 102)  # Fija los límites mínimos y máximos de visualización del eje Y, evitando el corte de las líneas periféricas.
ax_espacio.set_xlabel("Coordenada X") # Asigna el rótulo de texto explicativo al eje horizontal de abscisas.
ax_espacio.set_ylabel("Coordenada Y") # Asigna el rótulo de texto explicativo al eje vertical de ordenadas.
ax_espacio.grid(True, linestyle='--', alpha=0.5) # Activa una cuadrícula de referencia cuadriculada con trazo discontinuo tenue.
ax_espacio.legend(loc='upper right', shadow=True) # Despliega el cuadro de convenciones con una sombra estética texturizada.


# ----------------------------------------------------------------------------
# ---------- PANEL 2 (DERECHO): VALIDACIÓN DE CONSERVACIÓN CINÉTICA -----------
# ----------------------------------------------------------------------------
ax_momento = axs[1] # Extrae el eje de la segunda posición del arreglo (índice 1) y lo asigna a la variable de control 'ax_momento'.
# Configura el encabezado del panel derecho fijando el tamaño de letra en 12 puntos y estilo de fuente en negrita.
ax_momento.set_title("Verificación Física: Conservación del Momento Lineal", fontsize=12, fontweight='bold')

# GRAFICACIÓN DE COMPONENTES VECTORIALES:
# Grafica la evolución temporal del momento lineal sumado en el eje horizontal X. Utiliza un color púrpura oscuro (#4B0082).
ax_momento.plot(sistema_global['Tiempo'], sistema_global['Px'], label=r'$\sum P_x$', color='#4B0082', linewidth=2)
# Grafica la evolución temporal del momento lineal sumado en el eje vertical Y. Utiliza un color verde azulado (#008080).
ax_momento.plot(sistema_global['Tiempo'], sistema_global['Py'], label=r'$\sum P_y$', color='#008080', linewidth=2)

# GRAFICACIÓN DEL VECTOR NETO INVARIANTE:
# Grafica el módulo de la cantidad de movimiento total combinada. El uso del estilo de línea de puntos (linestyle=':') 
# permite resaltar visualmente que, a pesar de los impactos inter-partículas e inversiones angulares, el módulo se conserva constante.
ax_momento.plot(sistema_global['Tiempo'], sistema_global['P_Neto'], label=r'$|P_{neto}|$', color='#D2691E', linestyle=':', linewidth=2)

# CONFIGURACIÓN TÉCNICA FINALES DEL PANEL DERECHO:
ax_momento.set_xlabel("Tiempo (s)") # Asigna el rótulo identificador de magnitud al eje de abscisas temporales.
ax_momento.set_ylabel("Cantidad de Movimiento (p)") # Asigna el rótulo identificador al eje de ordenadas de movimiento.
ax_momento.grid(True, linestyle='--', alpha=0.5) # Configura una cuadrícula idéntica a la del panel izquierdo para mantener simetría visual.
ax_momento.legend(loc='lower left', shadow=True) # Despliega la caja de convenciones en la esquina inferior izquierda del cuadrante.

# ============================================================================
# 4. LANZAMIENTO DEL LIENZO ANALÍTICO
# ============================================================================
# Comando imperativo final de la librería de visualización. Procesa todas las operaciones vectoriales previas,
# compila las capas geométricas y despliega de forma inmediata la ventana gráfica interactiva en el panel de Spyder.
plt.show() # Fin del flujo de ejecución del script de análisis de datos de la Práctica 5.