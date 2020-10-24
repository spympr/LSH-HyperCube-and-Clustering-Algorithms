lsh: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o
	g++ build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o -o lsh

cube: build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o
	g++ build/main.o build/read_binary_file.o build/bucket.o build/exhausting.o build/lsh.o build/hypercube.o -o cube

build/main.o: src/main.cpp 
	g++ -c src/main.cpp -o build/main.o

build/read_binary_file.o: src/read_binary_file.cpp headers/read_binary_file.h
	g++ -c src/read_binary_file.cpp -o build/read_binary_file.o

build/bucket.o: src/bucket.cpp headers/bucket.h
	g++ -c src/bucket.cpp -o build/bucket.o

build/exhausting.o: src/exhausting.cpp headers/exhausting.h
	g++ -c src/exhausting.cpp -o build/exhausting.o

build/lsh.o: src/lsh.cpp headers/lsh.h
	g++ -c src/lsh.cpp -o build/lsh.o

build/hypercube.o: src/hypercube.cpp headers/hypercube.h
	g++ -c src/hypercube.cpp -o build/hypercube.o
	
clean:
	rm cube lsh build/*.o