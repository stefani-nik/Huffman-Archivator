#pragma once
#include <vector>

using namespace std;
template< class TYPE > class Heap
{
public:
	Heap();										//constructor
	Heap(Heap<TYPE> &);							 //copy constructor
	Heap &operator=(const Heap &);               // assignment operator
	void insert(const TYPE);					 //insert new item to the heap
	TYPE omit();								 //omit the root of the heap and return omited

	size_t getSize() const { return root.size(); }  //get the size of the heap
	
	bool empty() const { return root.empty(); }	//check if the heap is empty
	
private:
	vector < TYPE > root;						//the vector containing the elements
 								
	bool compare(int, int) const;               //depending on status compares two items
	int father(int) const;                     //returns father's location of an item
	int leftChild(int) const;                  //returns left child's location of an item
	int rightChild(int) const;                 //returns right child's location of an item
	void adjust(int);						   //adjust algorithm
	void swap(int, int);                       //swaps two elements
	void heapify();							   //heapify algorithm
};
#include "heap.cpp"

