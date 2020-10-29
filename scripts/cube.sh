make cube 
time ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 13 -R 1000 -N 1 -probes 3 -M 20
# time valgrind --track-origins=yes --leak-check=full ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 13 -R 1000 -N 5 -probes 3 -M 20