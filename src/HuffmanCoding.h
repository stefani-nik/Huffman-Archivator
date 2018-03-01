#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include "mergingTree.h"
#include "mergingTree.cpp"
#include "mergingType.h"
#include <string>
#include <iostream>

using namespace std;
//HuffmanCoding class interface
class HuffmanCoding
{
public:
	void compress(string, string, string);               //compress input file to output file
	void decompress(string, string);             //decompress input file to output file
private:
	mergingTree<mergingType> *codeTree;         //  mergingTree object to calculate strings
												//  for Huffman compression method
												//  note: we use pointer so we're able
												//  to new and delete it for each operation

	char *buffer, zeros;                        //zeros: number of bits filled with zero 
												//   at the last character
												//buffer: array to hold characters representing bits
	int *counts,                                //characters count (256 element array)
		bufferSize,                             //number of written bits to buffer
		fileBufferSize,                         //number of bits written to file's buffer
		fileBufferSize2,                        //number of bits readed form input file
		*fileBuffer,                            //file buffer holding characters to be written to output file
		*fileBuffer2;                           //file buffer holding read characters from input file
	ios::pos_type readChars;                    //current position of file in bytes
	bool readDone;                              //we read all of input file (used in decompress operation)
	string *strings,                            //strings created with codeTree (used in compress operation)
		inFile,                                 //input file path
		outFile;                                //outPut file path

												//utility functions
	void count();                               //count file's characters
	void flushBuffer();                         //write the buffer to file's buffer
	void setVariables();                        //set needed variable for compress operation
	void writeBits(string);                     //write bits to buffer
	void writeTheFile();                        //write file's buffer to file
	void writeSignature();                      //write file's signature (used in compress operation)
	void readSignature();                       //read file's signature (used in decompress operation)
	void readFile();                            //read 1000 bytes from file to file's buffer
	unsigned long fileSize();                   //return size of file (bytes)
};
#endif

