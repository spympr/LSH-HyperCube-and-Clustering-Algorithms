make cluster 
time ./cluster -i data/train-images-idx3-ubyte -c data/cluster.conf -o output -complete no -m Classic
# time valgrind --track-origins=yes ./cluster -i data/train-images-idx3-ubyte -c data/cluster.conf -o output -complete no -m Classic