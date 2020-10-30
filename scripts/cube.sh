make cube 

time ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 14 -R 10000 -N 1 -probes 2 -M 10
# time valgrind --leak-check=full ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 14 -R 10000 -N 1 -probes 2 -M 10