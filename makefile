cluster: build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o build/ra_lsh.o build/ra_hypercube.o build/main.o
	g++ build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o build/ra_lsh.o build/ra_hypercube.o -o cluster

lsh: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o
	g++ build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o -o lsh

cube: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o
	g++ build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o -o cube

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/read_binary_file.o: src/read_binary_file.cpp 
	g++ -c src/read_binary_file.cpp -o build/read_binary_file.o

build/bucket.o: src/bucket.cpp 
	g++ -c src/bucket.cpp -o build/bucket.o

build/exhausting.o: src/exhausting.cpp 
	g++ -c src/exhausting.cpp -o build/exhausting.o

build/lsh.o: src/lsh.cpp 
	g++ -c src/lsh.cpp -o build/lsh.o

build/hypercube.o: src/hypercube.cpp 
	g++ -c src/hypercube.cpp -o build/hypercube.o

build/kmeans.o: src/kmeans.cpp 
	g++ -c src/kmeans.cpp -o build/kmeans.o

build/cluster.o: src/cluster.cpp 
	g++ -c src/cluster.cpp -o build/cluster.o

build/ra_lsh.o: src/ra_lsh.cpp
	g++ -c src/ra_lsh.cpp -o build/ra_lsh.o

build/ra_hypercube.o: src/ra_hypercube.cpp
	g++ -c src/ra_hypercube.cpp -o build/ra_hypercube.o
	
clean:
	rm cube lsh cluster build/*.o

############################################################

# cluster: build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o build/ra_lsh.o build/main.o
# 	g++ -Ofast build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o build/ra_lsh.o -o cluster

# lsh: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o
# 	g++ -Ofast build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o -o lsh

# cube: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o
# 	g++ -Ofast build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o build/kmeans.o build/cluster.o -o cube

# build/main.o: src/main.cpp
# 	g++ -Ofast -c src/main.cpp -o build/main.o

# build/read_binary_file.o: src/read_binary_file.cpp 
# 	g++ -Ofast -c src/read_binary_file.cpp -o build/read_binary_file.o

# build/bucket.o: src/bucket.cpp 
# 	g++ -Ofast -c src/bucket.cpp -o build/bucket.o

# build/exhausting.o: src/exhausting.cpp 
# 	g++ -Ofast -c src/exhausting.cpp -o build/exhausting.o

# build/lsh.o: src/lsh.cpp 
# 	g++ -Ofast -c src/lsh.cpp -o build/lsh.o

# build/hypercube.o: src/hypercube.cpp 
# 	g++ -Ofast -c src/hypercube.cpp -o build/hypercube.o

# build/kmeans.o: src/kmeans.cpp 
# 	g++ -Ofast -c src/kmeans.cpp -o build/kmeans.o

# build/cluster.o: src/cluster.cpp 
# 	g++ -Ofast -c src/cluster.cpp -o build/cluster.o

# build/ra_lsh.o: src/ra_lsh.cpp
# 	g++ -Ofast -c src/ra_lsh.cpp -o build/ra_lsh.o
	
# clean:
# 	rm cube lsh cluster build/*.o