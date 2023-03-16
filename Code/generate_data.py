from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# List of number of points to generate
n_points_list = [100, 100000, 200000, 300000, 400000, 600000, 800000, 1000000]

# Looping over the number of points to generate and storing them into csv files
for n_points in n_points_list:

    # randomly generating data points and noise 
    points, y_true = make_blobs(n_samples=n_points, 
                                centers=5, 
                                cluster_std=0.04, 
                                random_state=7,
                                center_box=(0, 1.0))

    # only positive points and with three decimals
    points = np.round(np.abs(points), 3)

    # storing points into a csv file
    np.savetxt("./../Data/"+str(n_points)+"_data.csv", points, delimiter=",",  fmt="%.3f")


