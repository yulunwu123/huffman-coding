a.out: huffman.o huffNode.o heap.o
	clang++ -O2 huffman.o huffNode.o heap.o -o a.out

heap.o: heap.h heap.cpp
	clang++ -c -Wall -O2 heap.cpp

huffman.o: huffman.cpp
	clang++ -c -Wall -O2 huffman.cpp

huffNode.o: huffNode.h huffNode.cpp
	clang++ -c -Wall -O2 huffNode.cpp

clean:
		rm *.o a.out