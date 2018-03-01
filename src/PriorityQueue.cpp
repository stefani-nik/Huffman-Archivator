#include "stdafx.h"
#include "PriorityQueue.h"
#include <iostream>

using namespace std;
template<class TYPE>
PriorityQueue<TYPE>::PriorityQueue(int d)
{
	if (d<2) d = 2; //min a 2-heap is supported
	D = d;
	back = 0;
	size = SIZE;
	arr = new T*[size];
}

// is PriorityQueue empty?
template<class TYPE>
bool PriorityQueue<TYPE>::empty(void) const
{
	return (back <= 0);
}

// is PriorityQueue full?
template<class TYPE>
bool PriorityQueue<TYPE>::full(void) const
{
	return (back >= size);
}

// the front element of the PriorityQueue 
template<class TYPE>
TYPE* PriorityQueue<TYPE>::deq(void)
{
	if (empty())
	{
		cerr << "deq error! exiting..." << endl;
		exit(1);
	}

	TYPE* rval = arr[0];
	arr[0] = arr[back - 1]; //the element in the back moved to front
	--back;
	reheapdown(0, back - 1); //reheapdown called to fix the order back 
	return rval;
}

// a copy of the front element is returned but the PriorityQueue is not changed
template<class TYPE>
TYPE* PriorityQueue<TYPE>::front(void)
{
	if (empty())
	{
		cerr << "deq error! exiting..." << endl;
		exit(1);
	}

	return arr[0];
}

// a new element to put in the PriorityQueue
template<class TYPE>
void PriorityQueue<TYPE>::enq(TYPE* foo)
{
	if (full()) //if the array is full then make it larger
	{
		int nsize = size + SIZE; //the size of the new array
		TYPE* *narr = new TYPE*[nsize]; //new array
		for (int i = 0; i<size; ++i) //copy old array to the new one
			narr[i] = arr[i];
		delete[] arr; //delete reserved old array mem
		arr = narr; //pointer update
		size = nsize; //size update
	}

	//the new element added to the back of the PriorityQueue
	//and the reheapup called to fix the order back
	arr[back++] = foo; //arr[back]=foo;++back;
	reheapup(0, back - 1);
}

// this is a recursive function to fix back the order in the PriorityQueue
// upwards after a new element added back (bottom) of the PriorityQueue 
template<class TYPE>
void PriorityQueue<TYPE>::reheapup(int root, int bottom)
{
	int parent; //parent node (in the virtual tree) of the bottom element

	if (bottom > root)
	{
		parent = (bottom - 1) / D;

		//compare the two node and if the order is wrong then swap them
		//and make a recursive call to continue upward in the virtual tree
		//until the whole tree heap order is restored   
		if (*arr[parent] > *arr[bottom])
		{
			swap(arr[parent], arr[bottom]);
			reheapup(root, parent);
		}
	}
}

// this is a recursive function to fix back the order in the PriorityQueue
// downwards after a new element added front (root) of the PriorityQueue 
template<class TYPE>
void PriorityQueue<TYPE>::reheapdown(int root, int bottom)
{
	int minchild, firstchild, child;

	firstchild = root*D + 1; //the position of the first child of the root

	if (firstchild <= bottom) //if the child is in the PriorityQueue
	{
		minchild = firstchild; //first child is the min child (temporarily)

		for (int i = 2; i <= D; ++i)
		{
			child = root*D + i; //position of the next child
			if (child <= bottom) //if the child is in the PriorityQueue
			{
				//if the child is less than the current min child
				//then it will be the new min child
				if (*arr[child] < *arr[minchild])
				{
					minchild = child;
				}
			}
		}

		//if the min child found is less then the root(parent node)
		//then swap them and call reheapdown() recursively and
		//continue to fix the order in the virtual tree downwards
		if (*arr[root] > *arr[minchild])
		{
			swap(arr[root], arr[minchild]);
			reheapdown(minchild, bottom);
		}
	}
}

// the values of 2 variables will be swapped
template<class TYPE>
void PriorityQueue<TYPE>::swap(TYPE* &a, TYPE* &b)
{
	TYPE* temp;
	temp = a;
	a = b;
	b = temp;
}

// destructor (because default dest. does not erase the array)
template<class TYPE>
PriorityQueue<TYPE>::~PriorityQueue(void)
{
	delete[] arr;
}