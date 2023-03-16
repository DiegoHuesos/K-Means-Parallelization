<h1> Experimento de paralelización del algoritmo K-means implementado en lenguaje de programación C++ y el estándar OpenMP </h1>

<h2> Instituto Tecnológico Autónomo de México </h2>

<h2> Cómputo Paralelo y en la Nube </h2>



<h3> Profesor </h3>

<h5> Dr. José Octavio Gutiérrez García </h5>


<h3> Integrantes </h3>

<h5> Diego Hernández Delgado - 176262 </h5>

<h5> Isaías Jesús García Moreno - 179474 </h5>



<h2> Introducción </h2>
 
El presente proyecto consiste en la comparación entre la eficiencia de la implementación serial y la implementación paralela del algoritmo de clusterización conocido como K-means. El algoritmo K-means es un algoritmo de aprendizaje no supervisado que agrupa datos en K clusters, donde K es un número predefinido. 

Dicho algoritmo consiste en la asignación aleatoria de los centroides correspondientes a cada cluster,posteriormente, la asignación de los puntos al centroide más cercano y, finalmente, la actualización de la posición de los centroides al obtener el promedio de las posiciones de todos sus puntos. Este proceso se repite hasta que los centroides no se muevan más o hasta que se alcance un número límite de iteraciones.

<h2> Objetivos </h2>

- Implementar el algoritmo K-means de forma serial en lenguaje de programación C++, medir su tiempo de ejecución y almacenar los resultados.

- Implementar el algoritmo K-means de forma paralela en lenguaje de programación C++ y el estándar OpenMP, medir su tiempo de ejecución y almacenar los resultados.

- Ejecutar pruebas automatizadas con diferentes valores de entrada para el algoritmo K-means como el número de puntos, el número de clusters, el número máximo de iteraciones y el número de hilos (para la implementación paralela) por medio de scripts de bash.

- Cada prueba debe ser ejecutada diez veces y se debe calcular el promedio de los tiempos de ejecución.

- Comparar la eficiencia de la implementación serial y la implementación paralela del algoritmo K-means, mediante la obtención de la gráfica de speedups.

- Realizar un análisis de resultados y determinar las conclusiones correspondientes.

<h2> Estructura del proyecto </h2>

- .vscode/
    * launch.json
    * settings.json
    * tasks.json

- Analysis/
    * Parallel/
        * Execution_Times/
            * 100_Points/
                * 1_threads.csv
                * 6_threads.csv
                * 12_threads.csv
                * 24_threads.csv
            * 100000_Points
                * ...
            * ...
    * Serial/
        * Execution_TImes/
            * 100_times.csv
            * 100000_times.csv
            * ...
- CODE/
    * .ipynb_checkpoints/
    * generate_data.py
    * parallel_experiment.sh
    * parallel_kmeans
    * parallel_kmeans.cpp
    * pipeline.sh
    * serial_experiment.sh
    * serial_kmeans
    * serial_kmeans.cpp
    * syntheticclusters.ipynb
- Data/
    * 100_data.csv
    * 100000_data.csv
    * ...
- Results/
    * Parallel/
        * 100_Points/
            * 1_threads/
                * 1_100_1_results.csv
                * 2_100_1_results.csv
                * ...
            * 6_threads/
                * ...
            * ...
    * Serial/
        * 100_Points/
            * 1_100_results.csv
            * 2_100_results.csv
            * ...
        * ...
- README.md


<h2> Ejecución del experimento </h2>

Para la implementación del algoritmo K-means en lenguaje de programación C++ se utilizó la biblioteca de OpenMP para la paralelización del algoritmo.

Para ejecutar el proceso completo del experimento, se ejecuta el archivo **pipeline.sh** que, a su vez, ejecuta el archivo **generate_data.py**, el archivo **serial_experiment.sh** y el archivo **./parallel_kmeans.sh**. 

El archivo **generate_data.py** genera aleatoriamente los datos de prueba con las diferentes cantidades de puntos (100, 100000, 200000, 300000, 400000, 600000, 800000, 1000000) en archivos csv en la carpeta **Data/**.

El archivo **serial_experiment.sh** ejecuta el archivo ejecutable **./serial_kmeans** con diferentes parámetros (**num_clusters**, **num_points**, **num_max_iterations**) para las distintas pruebas del código serial.

El archivo **./parallel_kmeans.cpp** ejecuta el archivo ejecutable **./parallel_kmeans** (**num_clusters**, **num_points**, **num_max_iterations**, **num_threads**) con diferentes parámetros/argumentos para las distintas pruebas del código paralelo.

Argumentos:

- El número de clusters está asignado a 5 por defecto. El número máximo de iteraciones está asignado a 100 por defecto.

- El número de puntos se itera entre los siguientes valores: 100, 100000, 200000, 300000, 400000, 600000, 800000, 1000000

- El número de clusters se fijó en 5 para todas las pruebas aunque puede ser editado en los archivos **serial_experiment.sh** y **parallel_experiment.sh** e inclusive en el archivo **./parallel_kmeans.cpp** y **./serial_kmeans.cpp**.

- El número máximo de hilos se itera entre los siguientes valores: **1**, **6** (número de cores virtuales/2), **12** número de cores virtuales, **24** (número de cores virtuales*2)

<h2> Explicación detallada de la implementación </h2>

La implentación del algoritmo K-means en lenguaje de programación C++ se realizó en dos archivos: **./serial_kmeans.cpp** y **./parallel_kmeans.cpp** de forma similar.

La diferencia del archivo **./parallel_kmeans.cpp** es que se utilizó la biblioteca de OpenMP para la paralelización del algoritmo, algunos de las estructuras de control cícilicas for se paralelizaron con la directiva **#pragma omp parallel for** cuidando de no anidar directivas de paralelismo. 

Los métodos utilizados para la implementación del algoritmo K-means son los siguientes:

- **euclidean_distance**: Calcula la distancia euclidiana entre dos puntos.

- **find_nearest_centroid**: Encuentra el centroide más cercano a un punto dado, utilizando el método anterior y retorna el índice del centroide.

- **update_centroids**: Actualiza la posición de los centroides, calculando el promedio de las posiciones de todos los puntos asignados a cada centroide.

- **kmeans**: Ejecuta el algoritmo K-means, utilizando los métodos anteriores y retorna los centroides finales y los puntos asignados a cada centroide.

- **load_CSV**: Carga los datos de prueba desde un archivo csv.

- **save_to_CSV**: Guarda los resultados del algoritmo K-means en un archivo csv, es decir, los puntos con su respectivo centroide.

- **save_array_to_CSV**: Guarda los tiempos medidos de los 10 experimentos. En un renglón el tiempo de cada prueba de cada configuración particular de las variables de entrada. En el primer renglón se almacena el promedio de las 10 pruebas.

- **main**: se obtienen los argumentos de entrada del programa, se inicializan  los arreglos, se iteran los 10 experimentos, se guardan los resultados, se guardan los tiempos medidos y libera la memoria.


<h2> Estrategia de paralelización </h2>

- omp_set_num_threads(num_threads): Se establece el número de hilos a utilizar en la ejecución del programa principal **main**.

- el método **kmeans** se paraleliza con la directiva **#pragma omp parallel for** en algunos estructuras for explicitas o dentro de otros métodos auxiliares.


<h2> Instrucciones de ejecución </h2>

- Para ejecutar el experimento completo, se puede ejecutar el archivo **pipeline.sh**.

- Para ejecutar únicamente el experimento de la implementación serial, se puede ejecutar el archivo **serial_experiment.sh**.

- Para ejecutar únicamente el experimento de la implementación paralela, se puede ejecutar el archivo **parallel_experiment.sh**.

- Para ejecutar únicamente el código serial con una sola configuración de variables, se puede ejecutar el siguiente comando desde la terminal en la carpeta de CODE: **./serial_kmeans [num clusters] [num max iteraciones] [num puntos]** sustituyendo los valores deseados correspondientes.

- Para ejecutar únicamente el código paralelo con una sola configuración de variables, se puede ejecutar el siguiente comando desde la terminal en la carpeta de CODE: **./parallel_kmeans [num clusters] [num max iteraciones] [num puntos] [num hilos]** sustituyendo los valores deseados correspondientes.


<h2> Interpretación y análisis de resultados </h2>

<p> El speedup observado en la implementación paralela debería ser, en principio, directamente proporcional al número de cores utilizados. 
Sin emabrgo, en la implementación paralela se observó que el speedup no es directamente proporcional al número de cores utilizados en este experimento. 

Esto resultado inesperado se puede deber a que el algoritmo K-means no es fácil de paralelizar. Además, el overhead de la paralelización por la comunicación entre los hilos y la sincronización de los mismos, puede ser mayor que el beneficio de la paralelización. 

En un segundo momento, se debe revisar a fondo la documentación de la librería OMP para comprender mejor su funcionamiento a bajo nivel y poder determinar como generar un verdadero speed up. </p>
</p>


<h2> Conclusiones </h2>

<p> El proyecto fue implementado en Python 3.8 haciendo uso de la biblioteca regex para el reconocimiento de expresiones regulares. El programa es capaz de reconocer todas las declaraciones de variables del lenguaje Kotlin en su versión 1.8.10. </p>


![Interaction of Lexxical Analyser with Parser](./maxresdefault.jpg "Title")


<h2> Descripción del equipo donde se ejecutaron las pruebas</h2>

<h3> Hardware </h3>

- Computadora: Laptop Huawei Matebook 14
- Procesador: AMD Ryzen 5 3600 6-Core Processor
- Memoria RAM: 16 GB
- Disco duro: SSD 1 TB WD Blue SN550 NVMe M.2 2280
- Cores físicos: 6
- Cores lógicos: 12
- Velocidad del procesador: 3.6 GHz
- Velocidad de la memoria RAM: 3200 MHz

<h3> Software </h3>

- Sistema Operativo: Linux Ubuntu 20.04 LTS
- IDE: Visual Studio Code
- Lenguajes de programación: C++, Bash, Python
- Biblioteca de paralelización: OpenMP
- Compilador: g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
- Versión de C++: C++17
- Versión de Python: 3.8.5


<h2> Referencias </h2>

- [OpenMP](https://www.openmp.org/)

- [C++](https://docs.python.org/3/howto/regex.html)

- [G++](https://www.geeksforgeeks.org/compiling-with-g-plus-plus/)

- [Python](https://www.python.org/)

- [Bash](https://www.gnu.org/software/bash/)

- Robey, Robert, and Yuliana Zamora. Parallel and High Performance Computing. Simon and
Schuster, 2021.

- Tuomanen, Brian. Hands-On GPU Programming with Python and CUDA: Explore high-
performance parallel computing with CUDA. Packt Publishing Ltd, 2018.

- Wilt, Nicholas. The CUDA handbook: A comprehensive guide to gpu programming. Pearson
Education, 2013.



