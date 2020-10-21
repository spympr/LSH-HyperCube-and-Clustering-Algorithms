lsh: main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o
	g++ main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o -o lsh

cube: main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o
	g++ main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o -o cube

main.o:	src/main.cpp 
	g++ -c src/main.cpp

read_binary_file.o:	src/read_binary_file.cpp
	g++ -c src/read_binary_file.cpp

bucket.o:	src/bucket.cpp
	g++ -c src/bucket.cpp

exhausting.o:	src/exhausting.cpp
	g++ -c src/exhausting.cpp

lsh.o:	src/lsh.cpp
	g++ -c src/lsh.cpp 

hypercube.o:	src/hypercube.cpp
	g++ -c src/hypercube.cpp
	
clean:
	rm cube lsh *.o