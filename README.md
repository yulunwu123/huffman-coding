# Huffman Encoding and Decoding

## Overview
The Huffman coding algorithm is used to compress data by assigning shorter codes to more frequently occurring characters and longer codes to less frequently occurring characters. 

This implementation uses heap to construct the Huffman tree. The heap is used to repeatedly select the two smallest frequency nodes from the set of remaining nodes, until only one node remains, which is the root of the Huffman tree.

The encoding algorithm uses the Huffman tree to encode the input data as a binary string. The decoding algorithm uses the Huffman tree to decode the binary string back into the original data.

## Usage
The driver code takes in two parameters: operation (decode or encode) and a text file (the data to decode or encode).
```
make

./a.out decode encodedtexts/encoded4a.txt
```
Output:
> With the help of Rolls-Royce, University Engineering and Commerce students will enjoy new opportunities from a partnership that is part of the company's statewide investment in the aerospace industry, Gov. Tim Kaine announced last week.

```
make

./a.out encode normaltexts/normal1.txt
```
Output:
```
c 111
b 110
d 10
a 0
----------------------------------------
10 110 0 111 0 0 10  
----------------------------------------
There are a total of 7 symbols that are encoded.
There are 4 distinct symbols used.
There were 56 bits in the original file.
There were 13 bits in the compressed file.
This gives a compression ratio of 4.30769.
The cost of the Huffman tree is 1.85714 bits per character.
```