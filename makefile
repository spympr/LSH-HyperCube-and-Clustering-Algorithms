lsh: main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o
	g++ main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o -o lsh

cube: main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o
	g++ main.o read_binary_file.o bucket.o exhausting.o lsh.o hypercube.o -o cube

main.o:	src/main.cpp 
	g++ -c src/main.cpp

read_binary_file.o:	src/read_binary_file.cpp headers/read_binary_file.h
	g++ -c src/read_binary_file.cpp

bucket.o: src/bucket.cpp headers/bucket.h
	g++ -c src/bucket.cpp

exhausting.o: src/exhausting.cpp headers/exhausting.h
	g++ -c src/exhausting.cpp

lsh.o: src/lsh.cpp headers/lsh.h
	g++ -c src/lsh.cpp 

hypercube.o: src/hypercube.cpp headers/hypercube.h
	g++ -c src/hypercube.cpp
	
clean:
	rm cube lsh *.o