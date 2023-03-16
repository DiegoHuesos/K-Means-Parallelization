# Serial K-Means Experiment
# Author: Diego Hernández Delgado
# Author: Jesús Isaías García Moreno
# Date: 2023-03-08

# Parameters
num_points=("100" "100000" "200000" "300000" "400000" "600000" "800000" "1000000")
num_points_size=${#num_points[@]}

n_clusters="5"
max_iterations="100"
        
# a) Run the experiment with different number of points
for((i=0; i<num_points_size; i++))
do
    #echo ${num_points[i]}
    ./serial_kmeans  $n_clusters ${num_points[i]} $max_iterations
done


# b) Run the experiment only once
# ./serial_kmeans  $n_clusters $num_points[0] $max_iterations