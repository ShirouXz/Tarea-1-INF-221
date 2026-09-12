# Pasos para ejecutar el codigo:

   * Paso 1: Generacion casos de prueba:
      1.1 Ejecutar python array_generator.py (en el caso de usar conda, caso contrario python3 con esas librerias) dentro de 
          code/sorting/scripts/ para poblar la carpeta data/array_input.
      1.2 Ejecutar python matrix_generator.py dentro de 
          code/matrix_multiplication/scripts/ para poblar la carpeta data/matrix_input .

    * Paso 2: Medicion de rendimiento  temporal y de memoria.
    1.1 Estar en la carpeta code/sorting y ejecutar el make file mediante make run, que copilara y ejecutara todos los algoritmos de sorting y el archivo sorting principal.
    1.2 Mismo proceso para matrices pero en la carpeta code/matrix_multiplication.
    
    Observacion: crearan archivos de salida que se guardaran en data/matrix_output y ./data/matrix_output y ./data/array_output
    , ademas crearan un archivo results.csv respectivamente donde se encontraran los datos en el formato: "Algoritmo,N,T,D,M,Tiempo_ms,Memoria_KB" .

    * Paso 3: Creacion de Graficos y codigo de la tabla mediante los archivos plot_generator.py
    en code/../scripts  ejecutar python plot_generator.py , estos scripts toman el archivo results,csv para generar el grafico y la tabla que se imrpimira por consola y esa la copie despues en latex.


https://github.com/ShirouXz/Tarea-1-INF-221.git // Se encuentra la entrega de la tarea 1.

# Documentación
Las fuentes de los algoritmos se encuentran en cad aalgoritmo respectivamente.
los archivos .hpp declaran los programas y sus funciones, para despues ocuparlas en los progragramas principalemnte.
## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

### Programa principal

matrix_multiplication.cpp : incluye las funciones principales de cada algoritmo para llamar para su ejecucion.
make file // permite agilizar la ejecucion de todos los progrmas de matrices
### Scripts

 python3 plot_generator.py // o python plot_generator, ya que uso conda.

 python3 matrix_generator.py

Librerias de Python requeridas: (pandas, matplotlib).

Ejecucion: Comando para ejecutar el script directamente:
 python3 plot_generator.py // o python plot_generator, ya que uso conda.
 python3 matrix_generator.py 

## Ordenamiento de arreglo unidimensional

Algoritmos: MergeSort, QuickSort, PatienceSort, std::sort.

### Programa principal

sorting.cpp : incluye las funciones principales de cada algoritmo para llamar para su ejecucion.
make file // permite agilizar la ejecucion de todos los progrmas de sorting

### Scripts
 python3 plot_generator.py // o python plot_generator, ya que uso conda.

 python3 array_generator.py


 # Nombre:
   Christopher Patricio Becerra Catalan

# Rol: 
  202473584-5