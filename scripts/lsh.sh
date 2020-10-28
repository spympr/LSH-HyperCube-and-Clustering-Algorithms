make lsh
<<<<<<< HEAD
time ./lsh -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 4 -L 5 -N 1 -R 10000
=======
time ./lsh -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 4 -L 5 -N 5 -R 10000
# time valgrind --track-origins=yes --leak-check=full ./lsh -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output -k 4 -L 5 -N 5 -R 10000
>>>>>>> 841ec984077f406b113cb34314f3a4e3fc93d3e4
