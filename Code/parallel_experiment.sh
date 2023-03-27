# Parallel K-Means Experiment
# Author: Diego Hernández Delgado
# Author: Jesús Isaías García Moreno
# Date: 2023-03-08

# Parameters
num_points=("100" "100000" "200000" "300000" "400000" "600000" "800000" "1000000")
num_points_size=${#num_points[@]}
num_threads=("1" "6" "12" "24")
num_threads_size=${#num_threads[@]}
n_clusters="13"
max_iterations="5" #"90000000"
        
# a) Run the experiment with different number of points
for((i=0; i<num_points_size; i++))
do
    for((j=0; j<num_threads_size; j++))
    do
        echo "Experiment:  ${num_points[i]} points, ${num_threads[j]} threads"
        ./parallel_kmeans  $n_clusters ${num_points[i]} $max_iterations ${num_threads[j]}
    done
done


# b) Run the experiment only once
# ./parallel_kmeans  $n_clusters ${num_points[0]} $max_iterations ${num_threads[0]}