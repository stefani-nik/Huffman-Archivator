#pragma once
#include "stdafx.h"
#include "heap.h"
#include <iterator>
#include <cmath>
#include <iostream>
#include <stdexcept>  
using namespace std;

//
// Constructor 
//
template< typename TYPE >
Heap< TYPE >::Heap(){}

//
// Copy constructor 
//
template< typename TYPE >
Heap< TYPE >::Heap(Heap<TYPE> &right)
{
	*this = right;
}

//
// Compare elements at given indexes
//
template< typename TYPE >
bool Heap< TYPE >::compare(int l, int r) const
{
		return root.at(l) < root.at(r);
}

//
// Assignment operator 
//
template< typename TYPE >
Heap< TYPE > &Heap< TYPE >::operator=(const Heap< TYPE > &right)
{
	root = right.root;
	return *this;
}

//
// Find father of element at a given index 
//
template< typename TYPE >
int Heap< TYPE >::father(int sub) const
{
	if ((sub % 2) == 0) // right child
	{
		sub /= 2;
		sub--;
	}
	else  // left child
	{
		sub /= 2;
	}

	return sub;
}

//
// Find left child 
//
template< typename TYPE >
int Heap< TYPE >::leftChild(int sub)  const
{
	return 2 * sub + 1;
}

//
// Find right child
//
template< typename TYPE >
int Heap<TYPE>::rightChild(int sub) const
{
	return 2 * sub + 2;
}

//
// Insert element into the heap
//
template< typename TYPE >
void Heap< TYPE >::insert(const TYPE item)
{
	root.push_back(item); //add new item at the end of the vector
	int i = (int)root.size() - 1;
	int j; 
	while (true)
	{
		try
		{
			j = father(i); // j is location of father of the item

			if (compare(i, j)) // check if the child is smaller than the father
			{
				swap(i, j); //swap them
			}

			i = j;
		}
		catch (...)
		{
			return; //we're at the root
		}
	}
}
//
// Adjust position
//
template< typename TYPE >
void Heap< TYPE >::adjust(int item)
{
	int left, right;

	while (true)
	{
		try
		{
			//find the location of the left and right children
			left = leftChild(item);
			right = rightChild(item);

			int size = (int)root.size();

			//if th index of the left child is bigger or even to the size of the vector 
			if (left >= size)
			{
				if (compare(right, item)) // if the index of the right child is bigger than item
				{
					swap(right, item);
				}
					
			}
			else if (right >= size)
			{
				if (compare(left, item))
				{
					swap(left, item);
				}
				
			}
				

			//compare and decide which one must be swapped
			if (compare(right, left))
			{
				swap(item, right);
				item = right;
			}
			else
			{
				swap(item, left);
				item = left;
			}
		}
		catch (...)
		{
			return;
		}
	}
}
//
// Swap two elements
//
template< typename TYPE >
void Heap< TYPE >::swap(int sub1, int sub2)
{
	TYPE tmp = root.at(sub1);
	root.at(sub1) = root.at(sub2);
	root.at(sub2) = tmp;
}
//
// Heapify function
//
template< typename TYPE >
void Heap< TYPE >::heapify()
{
	for (int i = (int)root.size() / 2; i > 1; i--)
	{
		adjust(i);
	}
		
}

//
// Swaps the last element with the root and returns the root
//
template< typename TYPE >
TYPE Heap< TYPE >::omit()
{
	if (root.empty()) //check if the vector is empty
	{
		TYPE *a;
		a = new TYPE;
		return *a;
	}

	TYPE b = root[0];
	swap(0, (int)root.size() - 1); //swap the last element with root
	root.pop_back();			// delete the last element (with value of root)
	adjust(0);					//use adjust for root
	return b;
}

