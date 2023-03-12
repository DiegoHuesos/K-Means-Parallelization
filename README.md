<h1> Experimento de paralelización del algoritmo K-means implementando OMP en C++ </h1>


<h2> Integrantes </h2>

<h5> Diego Hernández Delgado - 176262 </h5>

<h5> Isaías Jesús García Moreno - 179474 </h5>



<h2> Introducción </h2>

<p> Programa </p>
 
| Nombre | Mini Clasificador de Declaraciones |
| Lenguaje de las declaraciones | [Kotlin](https://kotlinlang.org/docs/home.html) |
| Tipos de datos de las declaraciones | Tipos de datos básicos del lenguaje |
| Lenguaje de implementación | Java o Python |
| Entregable | Código fuente documentado y archivo README |
| Fecha de entrega | 15 de marzo de 2023 |

- Explicación detallada de la definición del experimento.
- Descripción del equipo donde se ejecutaron los experimentos en términos de hardware y software.
- Interpretación y análisis de resultados.
- Incluir gráficas
 
Experimento:

Parametrizar el programa
• Número de puntos
{100000, 200000, 300000, 400000, 600000, 800000, 1000000}
• Número de hilos
{1, (número de cores virtuales)/2, número de cores virtuales, número de cores virtuales*2}
• En búsqueda de un speedup, es posible explorar más o menos hilos.
• Promediar diez iteraciones para cada configuración
• Comparar contra version serial
• Obtener gráfica de Speed Ups


<h2> Especificaciones Funcionales </h2>

El programa lee los datos de entrada de un archivo que se pasa por medio de la línea de comandos o se carga por medio de una ventana de dialogo de abrir archivo.

El programa utiliza expresiones regulares para realizar el análisis de la entrada, particularmente, utiliza las bibliotecas estándar de expresiones regulares de Python.

El programa reconoce todos los tipos de declaraciones de variables del lenguaje Kotlin en su versión 1.8.10.

El programa analiza las declaraciones que recibe y omite aquellas que no sean válidas. Así, el programa es capaz de recopilar las siguientes estadísticas sobre dichas declaraciones:

- Numero total de variables declaradas.
- Numero total de tipos utilizados en las declaraciones encontradas.
- Numero total de variables declaradas de cada tipo.
- Numero total de variables inicializadas.
- Numero total de variables de tipo arreglo.
- Número total de declaraciones constantes (es decir, el valor no se puede cambiar después de la inicialización).
- Clasificación de todos los nombres de variables por tipo declarado.
- El formato de salida es una impresión en consola de los resultados obtenidos.

![Interaction of Lexxical Analyser with Parser](./maxresdefault.jpg "Title")

<h2> Especificaciones de Hardware </h2>

Sistema Operativo: Linux Ubuntu 20.04 LTS

Procesador: AMD Ryzen 5 3600 6-Core Processor

Cantidad de núcleos físicos: 6

Cantidad de núcleos lógicos: 12

Memoria RAM: 16 GB



<h2> Funcionamiento </h2>

<p>
Para poder utilizar el programa, es necesario que las variables declaradas se encuentren escritas con los espacios necesarios como se considera en una escritura de Kotlin correcta.

El programa podrá tomar como válida una declaración del tipo: **int a = 12;**

Sin embargo, no tomará como válida una declaración del tipo **int a=12;**


Al correr el archivo *Proyecto.py* la consola pedirá el nombre del archivo para analizar. Hemos proporcionado un archivo con todos los tipos de declaraciones posibles, nombrado "*test.txt*", para poder probar el programa, este archivo se encuentra en el presente directorio junto con el archivo ejecutable de Python. 

Se presenta un menú interactivo donde se podrá elegir qué estadística se gusta obtener al proporcionar un número del 1 al 7. El número 7 está reservado para obtener en una misma llamada todos los resultados mencionados en las especificaciones. 

Dentro del código fuente se encuentra una breve descripción de cada función implementada para la operación del programa. 
</p>

<h2> Restricciones </h2>

 - Únicamente se utilizan expresiones regulares para implementar el programa.
 - No se coloca el código fuente del programa en un repositorio público (e.g. Github).


<h2> Conclusiones </h2>

<p> El proyecto fue implementado en Python 3.8 haciendo uso de la biblioteca regex para el reconocimiento de expresiones regulares. El programa es capaz de reconocer todas las declaraciones de variables del lenguaje Kotlin en su versión 1.8.10. </p>


<h2> Referencias </h2>

- [Kotlin](https://kotlinlang.org/docs/home.html)
- [Python](https://www.python.org/)
- [Regex](https://docs.python.org/3/library/re.html)
- [Regex](https://docs.python.org/3/library/re.html)
- [Regex](https://docs.python.org/3/howto/regex.html)
- [Regex](https://docs.python.org/3/library/re.html)
- [Regex](https://docs.python.org/3/howto/regex.html)

