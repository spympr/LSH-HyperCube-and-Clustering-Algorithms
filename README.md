# LSH-HyperCube-and-Clustering-Algorithms.

> A very popular technique for finding near neighbors in the big data is to apply algorithms, which have probalistic behavior, such as Locality Sensitive Hashing and Random Projections to HyperCube. So the first part of this project is to compare the performance (time and accuracy) of LSH, HyperCube and BruteForce algorithms applied on nearest neighbor problem. We feed to those algoritmhs images from MNIST dataset (which has a lot of 28x28 vectors, that represents images) 

> Afterwards, we are trying to solve clustering problem with some different techniques.First step of clustering is initialization step (with k_means approach), then it comes step in which we update centroids using either Lloyd's Algorithm, or reverse assignment based on LSH or HyperCube Range-Search Algorithm.

## Compilation & Execution
> After a series of experiments, we tune hyperparameters for the best result so if you want to compile and run you can simply run one of the above commands from root directory:
./scripts/lsh.sh
./scripts/cube.sh
./scripts/cluster.sh
