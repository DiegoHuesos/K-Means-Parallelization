/**
 * @file serial_kmeans.cpp
 * @date 2023-03-08
 * @author Diego Hernández Delgado
 * @author Jesús Isaías García Moreno
 * @brief Código serial del algoritmo k-means que lee los datos de un archivo .csv, los agrupa en k clusters y escribe los resultados en un archivo .csv implementado en lenguaje de programación C++
 * @param n_clusters Número de clusters o centroides
 * @param max_iterations Número máximo de iteraciones
 * @param input_file_path Ruta del archivo de entrada
 * */

#include <omp.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <bits/stdc++.h>

using namespace std;


/**
 * @name euclidean_distance 
 * @brief Función para calcular la distancia euclidiana entre dos puntos
 * @param point1 Punto 1 - Arreglo de floats [X, Y] 
 * @param point2 Punto 2 - Arreglo de floats [X, Y]
 * @param point_dimension_size Dimensiones de los puntos, es decir, el número de coordenadas de cada punto
 * @return Distancia euclidiana entre los dos puntos dados
 * */
float euclidean_distance(float* point1, float* point2, int point_dimension_size) {
    float distance = 0;
    for (int i = 0; i < point_dimension_size; i++) {
        distance += pow((point1[i] - point2[i]), 2);
    }
    return sqrt(distance);
}

/**
 * @name find_nearest_centroid
 * @brief Función para encontrar el índice del centroide más cercano para un punto dado
 * @param centroids Arreglo de centroides - Arreglo de arreglos de floats [[X, Y, cant_puntos_cluster], [X, Y, cant_puntos_cluster], ...]
 * @param point Punto - Arreglo de floats [X, Y]
 * @param n_clusters Número de clusters o centroides
 * @param point_dimension_size Dimensiones de los puntos, es decir, el número de coordenadas de cada punto
 * @return Índice del centroide más cercano al punto dado
 * */
int find_nearest_centroid(float** centroids, float* point, int n_clusters, int point_dimension_size) {
    float min_distance = euclidean_distance(centroids[0], point, point_dimension_size);
    int nearest_centroid_index = 0;
    for (int i = 1; i < n_clusters; i++) {
        float distance = euclidean_distance(centroids[i], point, point_dimension_size);
        if (distance < min_distance) {
            min_distance = distance;
            nearest_centroid_index = i;
        }
    }
    return nearest_centroid_index;
}

/**
 * @name update_centroids
 * @brief Función para actualizar los centroides basados en los clusters actuales
 * @param centroids Arreglo de centroides - Arreglo de arreglos de floats [[X, Y, cant_puntos_cluster], [X, Y, cant_puntos_cluster], ...]
 * @param points Arreglo de puntos - Arreglo de arreglos de floats [[X, Y, cluster], [X, Y, cluster], ...]
 * @param n_clusters Número de clusters o centroides
 * @param num_points Número de puntos
 * */
void update_centroids(float** centroids, float** points, int n_clusters, long long int num_points) {
    float** new_centroids = new float*[n_clusters];
    for (size_t i = 0; i < n_clusters; i++)
    {
        new_centroids[i] = new float[3];
        new_centroids[i][0] = 0;
        new_centroids[i][1] = 0;
        new_centroids[i][2] = 0;
    }
    // Se iteran todos los puntos y se suman las X y Y de cada cluster
    int cluster;
    for(long long int i =0; i < num_points; i++){
        cluster = (int) points[i][2];  // Cluster/Centroide al que pertenece el punto
        new_centroids[cluster][0] += points[i][0]; // Se suman las X de ese cluster en particular
        new_centroids[cluster][1] += points[i][1]; // Se suman las Y de ese cluster en particular
    }
    // Para obtener la nueva X del centroide, se divide la suma de las X de los puntos del cluster entre la cantidad de puntos en el cluster
    // Para obtener la nueva Y del centroide, se divide la suma de las Y de los puntos del cluster entre la cantidad de puntos en el cluster
    for(int i =0; i < n_clusters; i++){
        if(centroids[i][2] != 0){
            centroids[i][0] = new_centroids[i][0] / centroids[i][2]; 
            centroids[i][1] = new_centroids[i][1] / centroids[i][2]; 
        }
    }
    // Liberar memoria al borrar matriz temporal new_centroids utilizada para calcular los nuevos centroides
    for (int i = 0; i < n_clusters; i++) {
        delete[] new_centroids[i];
    }
    delete[] new_centroids;
}

/**
 * @name kmeans
 * @brief Función para llevar a cabo la el agrupamiento o clustering con el algoritmo de k-means
 * @param points Arreglo de puntos - Arreglo de arreglos de floats [[X, Y, cluster], [X, Y, cluster], ...]
 * @param n_clusters Número de clusters o centroides
 * @param num_points Número de puntos
 * @param max_iterations Número máximo de iteraciones
 * */
void kmeans(float** points, int n_clusters, long long int num_points, long long int max_iterations) {

    // Paso 1. Crear k centroides y distribuirlos aleatoriamente sobre los datos
    //cout << "Paso 1. Crear k centroides y distribuirlos aleatoriamente sobre los datos" << "\n";
    float** centroids = new float*[n_clusters];
    for (int i = 0; i < n_clusters; i++) {
        srand(time(NULL));
        centroids[i] = new float[3];  //{cantidad de puntos en el cluster, x position, y position}
        centroids[i][0] = points[rand() % num_points][0]; // position x
        centroids[i][1] = points[rand() % num_points][1]; // position y
        //centroids[i][0] = RandomFloat(0.0, 1.5); // position x
        //centroids[i][1] = RandomFloat(0.0, 1.5); // position y
        centroids[i][2] = 0; // cantidad de puntos en el cluster
    }

    // Paso 2. Asignar los puntos al centroide / cluster más cercano
    //cout << "Paso 2. Asignar los puntos al centroide / cluster más cercano" << "\n";
    for (long long int i = 0; i < num_points; i++) {
        int nearest_centroid_index = find_nearest_centroid(centroids, points[i], n_clusters, 2);
        points[i][2] = nearest_centroid_index;
        centroids[nearest_centroid_index][2]++; //Incrementar la cantidad de puntos en ese cluster
    }


    // Paso 3. Actualizar la posición de los centroides
        // Centroide X = Promedio de todas las posiciones X de los puntos del cluster correspondiente a ese centroide
        // Centroide Y = Promedio de todas las posiciones Y de sus puntos del cluster correspondiente a ese centroide
    //cout << "Paso 3. Actualizar la posición de los centroides" << "\n";
    update_centroids(centroids, points, n_clusters, num_points);
  

    // Paso 4. Repetir pasos 1 y 2 y 3hasta que ningún punto cambie de cluster o hasta un número dado.
    //cout << "Paso 4. Repetir pasos 1 y 2 hasta que ningún punto cambie de cluster o hasta un número dado." << "\n";
    long long int iteration = 0;
    int index;
    bool changed = true;
    int nearest_centroid_index;
    // Iterar hasta que no haya cambios en los clusters o hasta que se alcance el número máximo de iteraciones
    while (changed && iteration < max_iterations) {
        changed = false;
        // Asignar los puntos a los clusters más cercanos si es que ha cambiado el centroide más cercano
        for (long long int i = 0; i < num_points; i++) {
            nearest_centroid_index = find_nearest_centroid(centroids, points[i], n_clusters, 2);
            if (points[i][2] != nearest_centroid_index) {
                index = (int) points[i][2];
                centroids[index][2]--;// Decrementa la cantidad de puntos en el cluster en el que estaba anteriormente 
                centroids[nearest_centroid_index][2]++; // Incrementa la cantidad de puntos en el cluster al que ahora pertenece
                points[i][2] = nearest_centroid_index; // Asigna el nuevo cluster al punto
                changed = true;
            }
        }
        /*
        cout << "Iteration " << iteration <<  " centroids: " << "\n";
        cout << "0:  " << centroids[0][0] <<  ", " << centroids[0][1] <<  ", "  << centroids[0][2]  << "\n";
        cout << "1:  " << centroids[1][0] <<  ", " << centroids[1][1] <<  ", "  << centroids[1][2]  << "\n";
        cout << "2:  " << centroids[2][0] <<  ", " << centroids[2][1] <<  ", "  << centroids[2][2]  << "\n";
        cout << "3:  " << centroids[3][0] <<  ", " << centroids[3][1] <<  ", "  << centroids[3][2]  << "\n";
        cout << "4:  " << centroids[4][0] <<  ", " << centroids[4][1] <<  ", "  << centroids[4][2]  << "\n";
        cout << changed << "\n";
        cout << max_iterations << "\n";
        */
        // Actualizar la posición de los centroides
        update_centroids(centroids, points, n_clusters, num_points);
        iteration++;
    }


    // Imprimie los centroides y los puntos asignados a cada uno para debugear
    /*
    cout << "Step 5" << "\n";
    for (int i = 0; i < n_clusters; i++) {
        cout << "Centroid " << i << ": (" << centroids[i][0] << ", " << centroids[i][1] << ", " << centroids[i][2] << ")\n";
    }
    for (long long int i = 0; i < num_points; i++) {
        cout << "Point " << i << ": (" << points[i][0] << ", " << points[i][1] << ") -> Cluster " << points[i][2] << "\n";
    }
    */

    // Liberar memoria de la matriz de centroides
    for (int i = 0; i < n_clusters; i++) {
        delete[] centroids[i];
    }
    delete[] centroids;
}


/**
 * @name load_CSV
 * @brief Función para leer un archivo CSV y guardar los puntos en una matriz llamada puntos
 * @param file_name Nombre del archivo CSV
 * @param points Matriz donde se guardarán los puntos
 * @param num_points Cantidad de puntos que se leerán del archivo
 * */
void load_CSV(string file_name, float** points, long long int num_points) {
    fstream myfile;
    myfile.open(file_name, ios::in);
    string row = "";

    for(long long int i=0; i<num_points; i++){
        getline(myfile,row);
        //cout << stof(row.substr(0, 5)) << " - " << stof(row.substr(6, 5)) << "\n\n";
        points[i][0] = stof(row.substr(0, 5));
        points[i][1] = stof(row.substr(6, 5));
    }
    myfile.close();
}


/**
 * @name save_to_CSV
 * @brief Función para guardar los puntos con su respectivo centroide resultante en un archivo CSV 
 * @param file_name Nombre del archivo CSV
 * @param points Matriz donde se guardarán los puntos
 * @param size Cantidad de puntos que se leerán del archivo
 * */
void save_to_CSV(string file_name, float** points, long long int size) {
    fstream fout;
    fout.open(file_name, ios::out);
    for (long long int i = 0; i < size; i++) {
        fout << points[i][0] << ","
             << points[i][1] << ","
             << points[i][2] << "\n";
    }
}

void save_array_to_CSV(string file_name, float* times,  int size) {
    fstream fout;
    fout.open(file_name, ios::out);
    for (int i = 0; i < size; i++) {
        fout << times[i] << "\n";
    }
}


/**
 * @name main
 * @brief Función main del programa 
 * @param argc Cantidad de argumentos de entrada (STDIN)
 * @param argv Argumentos de entrada (STDIN) [nombre del programa, número de clusters, número de puntos, número máximo de iteraciones]
 * @return 0 si el programa termina correctamente
 * */
int main(int argc, char** argv) {

    // Se definen las variables 
    int n_clusters;
    long long int num_points;
    long long int max_iterations;

    // Se obtienen los argumentos de entrada del programa (número de clusters, número de puntos, número máximo de iteraciones)
    try{
        // Si no se pasan argumentos, se usan los valores por defecto
        if(argc == 1){
            n_clusters = 5;
            num_points = 100;
            max_iterations = 100;
        }else
            // Si se pasan argumentos, se usan esos valores
            if(argc == 4){
                n_clusters = stoi(argv[1]);
                num_points = (long long int) stoi(argv[2]);
                max_iterations = (long long int) stoi(argv[3]);
                if (n_clusters < 1) 
                    throw std::invalid_argument("Invalid number of clusters");
                if (num_points < 1) 
                    throw std::invalid_argument("Invalid number of points");
                if (max_iterations < 1) 
                    throw std::invalid_argument("Invalid number of iterations");
            }else
                // Si se pasan más o menos argumentos, se lanza una excepción
                throw std::invalid_argument("Invalid number of arguments");
    } catch (const std::exception& e) {
        // Se imprime el mensaje de error y se muestra la forma correcta de ejecutar el programa
        cout << e.what() << "\n";
        cout << "Usage: ./kmeans <n_clusters> <num_points> <max_iterations>" << "\n";
        return 1;
    }
    
    // Inicializa el arreglo de puntos con ceros y sin cluster con -1
    float** points = new float*[num_points];
    for(long long int i = 0; i < num_points; i++) {
        points[i] = new float[3]{0.0, 0.0, -1}; 
        // index 0: position x
        // index 1: position y 
        // index 2: cluster
    }

    // Crea el directorio de resultados correspondiente al número de puntos del experimento  
    string dir_str = "./../Results/Serial/"+ to_string(num_points) +"_Points/";
    char* dir = new char[dir_str.length() + 1];
    strcpy(dir, dir_str.c_str());
    struct stat sb;
    try{
        if (stat(dir, &sb) == 0)
        mkdir(dir, 0777);
    }catch(const std::exception& e){
        cout << "Error: mkdir()" << "\n";
        cout << e.what() << "\n";
    }
    delete[] dir;


    // Lee los puntos del archivo csv  y se guardan en la matriz de puntos
    string input_file_name = "./../Data/" + to_string(num_points)+"_data.csv";
    try{
        load_CSV(input_file_name, points, num_points);
    } catch (const std::exception& e) {
        cout << "Error: load_CSV()" << "\n";
        cout << e.what() << "\n";
    }
    
    string output_file_name;
    float* times = new float[11]{0.0}; // Arreglo para guardar los tiempos de ejecución de cada experimento
    float sum_times = 0.0; // Variable para guardar la suma de los tiempos de ejecución de los 10 experimentos
    float avg_time = 0.0; // Variable para guardar el promedio de los tiempos de ejecución de los 10 experimentos
    // Se itera 10 veces para repetir el experimento con esta configuración de parámetros
    for(int i = 1; i < 11; i++){

        // Invoca el método de kmeans con la matriz de puntos, el número de clusters deseados y el número total de puntos
        try{
            const clock_t begin_time = clock();
            kmeans(points, n_clusters, num_points, max_iterations); 
            times[i] = float( clock () - begin_time ) /  CLOCKS_PER_SEC;
            sum_times += times[i];
        } catch (const std::exception& e) {
            cout << "Error: kmeans()" << "\n";
            cout << e.what() << "\n";
        }
            
        // Guarda el resultado de los puntos con su respectivo centroide/cluster en el archivo de salida
        output_file_name = dir_str + to_string(i) +"_"+ to_string(num_points)+"_results.csv"; 
        try{
            save_to_CSV(output_file_name, points, num_points);
        } catch (const std::exception& e) {
            cout << "Error: save_to_CSV()" << "\n";
            cout << e.what() << "\n";
        }
    }

    // Guarda los tiempos de ejecución de los 10 experimentos y el promedio en la primera fila en un archivo csv 
    avg_time = sum_times / 10.0;
    times[0] = avg_time;
    output_file_name = "./../Analysis/Serial/Execution_Times/"+ to_string(num_points)+"_times.csv"; 
    try{
        save_array_to_CSV(output_file_name, times, 11);
    } catch (const std::exception& e) {
        cout << "Error: save_to_CSV()" << "\n";
        cout << e.what() << "\n";
    }


    // Libera la memoria al borrar la matriz de puntos
    for(long long int i = 0; i < num_points; i++) {
        delete[] points[i];
    }
    delete[] points;
    return 0;
}