#pragma once
#include "mergingTreeNode.h"
#include "heap.h"
#include <string>
#include <vector>

using namespace std;

// forward declaration of class heap
template< typename TYPE > class Heap;

// mergingTree class-template interface
template< typename TYPE > class mergingTree
{
public:
	mergingTree();                                      // constructor
	~mergingTree();                                     //destructor
	mergingTree &operator=(const mergingTree &);        //assignment operator
	bool operator==(const mergingTree &) const;         //equality operator
	void insertNode(const TYPE);						//insert new item into tree's heap
	void createTree();                                  //create tree with items inside heap
	bool isEmpty() const                                //check if tree is empty
	{
		return rootPtr == NULL;
	}
	void createHuffmanArrays();                         //create arrays used with huffman compression method
	vector<string> getHuffmanNumbers() const;           //return a vector containing numbers
														//  created with createHuffmanArrays
	vector<TYPE> HuffmanElements() const;				 //return a vector containing elements
														// created with createHuffmanArrays
	Node< TYPE > *getRootCopy();						 //get a copy of created tree
private:
	Node< TYPE > *root;									//root's pointer
	Heap < TYPE > *hp;									 //heap
	int size;                                           //size of tree

	vector<TYPE> elements;								 //vector containing elements
														//  created with createHuffmanArrays
	vector<string> numbers;                             //vector containing elements created with createHuffmanArrays
	string tmp;                                         //string object to hold string created with createHuffmanArrays
	bool created;                                       //check if the tree is created or not


														// utility functions      
	void destroy(Node<TYPE> *);							//used to destory tree
	int max(int, int);                                  //returns maximum of it's arguments
	void createHuffmanArraysHelper(Node< TYPE > *);		//used with createHuffmanArray														 
	Node< TYPE > *mergingTree<TYPE>::copy(Node< TYPE > *othermergingTreeRoot); //creates copy of tree
	bool equal(Node <TYPE> *, Node <TYPE> *) const;     //checks for equality
};

