make cube 
<<<<<<< HEAD
time ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 13 -R 1000 -N 1 -probes 100 -M 500
=======
time ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 13 -R 1000 -N 1 -probes 100 -M 500
# time valgrind --track-origins=yes --leak-check=full ./cube -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 13 -R 1000 -N 5 -probes 3 -M 20
>>>>>>> 841ec984077f406b113cb34314f3a4e3fc93d3e4
