make:
	g++ -o lsh src/main.cpp src/read_binary_file.cpp src/bucket.cpp src/exhausting.cpp && ./lsh -d data/train-images-idx3-ubyte -q data/t10k-images-idx3-ubyte -o output 
clean:
	rm lsh main

