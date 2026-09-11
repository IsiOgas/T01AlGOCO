# Documentación

## Entrega
La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## ¿Qué hay aquí?
Dos carpetas: `sorting/` (los 4 algoritmos de ordenamiento) y
`matrix_multiplication/` (naive y strassen). Ambas están armadas igual:

- `algorithms/` → el código de cada algoritmo.
- `data/measurements/` → los tiempos y memoria que quedaron guardados al correr todo.
- `data/plots/` → los gráficos ya generados.
- `data/array_input` / `data/array_output` (o `matrix_input` / `matrix_output`) → **están vacías a propósito**, las borré porque los archivos grandes (arreglos de 10 millones, matrices de 1024x1024) pesaban demasiado para el .zip. Más abajo dejo cómo regenerarlas.
- `scripts/` → los .py que generan los datos de entrada y los gráficos.

Importante: en data/measurements/ y data/plots/ ya están los tiempos, memoria y gráficos de todas mis ejecuciones (los que usé en el informe). Si 
quieren revisarlos antes de correr algo de nuevo, échenles un ojo ahí directo, porque make run y plot_generator.py sobrescriben/borran lo que ya está.

## Multiplicación de matrices
- `algorithms/naive.cpp`: el clásico, 3 for anidados, Theta de N^3, se implemento de un video de Youtube -> link en el comentario del mismo código.
- `algorithms/strassen.cpp`: divide la matriz en 4 y hace 7 multiplicaciones en vez de 8, theta de N ^2.81 aprox, se implemento de GeeksforGeeks.

## Ordenamiento
- `mergesort.cpp`, `quicksort.cpp`, `patiencesort.cpp`: tanto merge y quick las implemente siguiendo las clases del profesor JP. Catillo, para patience
se uso Wikibooks.
- `sort.cpp`: usa el `std::sort` de C++, este ya venía dado en la base de la tarea.

## Cómo correr todo de una

Ojo: hay que ir cambiando de carpeta porque los scripts de Python usan rutas relativas
(`../data/...`), así que estos SÍ o SÍ hay que correrlos desde adentro de `scripts/`, y
el `make` hay que correrlo desde la carpeta de arriba (`sorting/` o
`matrix_multiplication/`, donde está el makefile). Ejemplo completo para `sorting/`
(es lo mismo para `matrix_multiplication/`, solo cambia `array_generator.py` por
`matrix_generator.py`):

1. Generar los datos (parado en `sorting/scripts/`):
   ```
   python3 array_generator.py
   ```
   (o `matrix_generator.py` según corresponda)

2. Compilar (volviendo a `sorting/`):
   ```
   make
   ```

3. Correr todos los algoritmos sobre todos los casos, esto llena `data/measurements/`
   ```
   make run
   ```

4. Generar los gráficos, esto llena `data/plots/` (hay que volver a entrar a `scripts/`):
   ```
   python3 plot_generator.py
   ```

5. Si quieres limpiar el ejecutable y las mediciones (parado en `sorting/`):
   ```
   make clean
   ```
## Sobe el report
Mi visual no ejecutaba latex así que copie la carpeta report y la pase a overleaf, luego esa misma carpeta la traje a la tarea, agregue mi pdf que ahora es report.pdf y le cambie el nombre al pdf que venia llamandose report_q_venia.pdf.

## Otros
Se eliminaron archivos, tipos los pdf o img que venian por defecto... ya que me molestaban al momento de trabajar, tambien elimine los arrays y matrices que venian de prueba
para que se pudiera ejecutar bien los archivos. Si hay algo que no especifique no duden en contactarme :c.

## Datos personales
Isidora Martina Ogas Pavez
Rol: 202473654-K
