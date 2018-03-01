#pragma once
#include "stdafx.h"
#include "mergingTree.h"
#include "mergingTreeNode.h"
#include <string>

using namespace std; 
template< typename TYPE >
//
//Constructor
//
mergingTree< TYPE >::mergingTree()
{
	root = NULL;
	hp = new Heap<TYPE>;
	size = 0;
	created = false;
} 
//
//Destructor
//
template< typename TYPE >
mergingTree< TYPE >::~mergingTree()
{
	destroy(root);
}

//
// Destroy tree nodes
//
template< typename TYPE >
void mergingTree< TYPE >::destroy(Node<TYPE> *ptr)
{
	if (ptr != NULL)
	{
		destroy(ptr->leftPtr);
		destroy(ptr->rightPtr);
		delete ptr;
	}
}

//
// Insert node in the tree
//
template< typename TYPE >
void mergingTree< TYPE >::insertNode(const TYPE value)
{
	hp->insert(value);
	size++;
}

//
// Build tree
//
template< typename TYPE >
void mergingTree< TYPE >::createTree()
{
	TYPE l, r; //value to hold minimums of heap
	int rootsSize = 0;
	bool rFound, lFound;
	//pointers to create tree
	Node<TYPE> *lChild, *rChild, *newRoot;

	//vector to hold created seperate roots so we don't lost any created root
	vector<Node<TYPE> *> roots;

	l = hp->omit(); //l is first minimum
	r = hp->omit(); //r is second minimum

	rChild = new Node<TYPE>(r);
	lChild = new Node<TYPE>(l);

	//create root with cost(l) + cost(r)
	newRoot = new Node<TYPE>(l + r);

	//link childs to father(dad)
	newRoot->leftPtr = lChild;
	newRoot->rightPtr = rChild;

	//inset root to vector
	roots.push_back(newRoot);
	//also into heap
	hp->insert(l + r);

	while ((hp->getSize()) > 1) //until the last element
	{
		rFound = lFound = false;
		l = hp->omit(); //l is first minimum
		r = hp->omit(); //r is second minimum

		rootsSize = (int)roots.size();

		//hold location of left and right roots inside the vector if found
		int rLocation, lLocation;
		//first try to find cost inside roots
		for (int w = 0; w < rootsSize; w++)
		{
			//  if the root inside the vector at this location
			//  holds a root with data equal to l so
			//  set this root at lChild and use it as left child
			//  of new root
			if ((l == roots[w]->data) && !lFound)
			{
				lFound = true;
				lChild = roots[w];
				lLocation = w;
			}
			else if ((r == roots[w]->data) &&
				!rFound)
			{
				rFound = true;
				rChild = roots[w];
				rLocation = w;
			}
		}

		//if we didn't found the left or right child
		// inside roots vecor so create new nodes
		if (!rFound)
			rChild = new Node<TYPE>(r);
		if (!lFound)
			lChild = new Node<TYPE>(l);

		//create new root
		newRoot = new Node<TYPE>(l + r);
		newRoot->leftPtr = lChild;
		newRoot->rightPtr = rChild;

		//if we used just one root of vector replace new root
		// with that root, but if we used both of childs of 
		// the vector roots so we must replace one with new root
		// and delete another from the vector
		if (rFound && !lFound)
			roots[rLocation] = newRoot;
		else if (!rFound && lFound)
			roots[lLocation] = newRoot;
		else if (rFound && lFound)
		{
			roots[lLocation] = newRoot;
			roots[rLocation] = roots[roots.size() - 1];
			roots.pop_back();
		}
		else
			roots.push_back(newRoot);

		//insert sum of costs inside the heap
		hp->insert(l + r);
	}
	root = roots[0];
}
//
// Create Huffman's array
//
template< typename TYPE >
void mergingTree< TYPE >::createHuffmanArrays()
{
	createHuffmanArraysHelper(root); //begin from root
	created = true;
} 

//
// Huffman array helper 
//
template< typename TYPE >
void mergingTree< TYPE >::createHuffmanArraysHelper(Node< TYPE > *ptr)
{
	if (ptr != NULL)
	{
		//if this is a leaf
		if ((ptr->leftPtr == NULL) &&
			(ptr->rightPtr == NULL))
		{
			//add element and it's string to arrays
			elements.push_back(ptr->data);
			numbers.push_back(tmp);
		}
		else
		{
			//while going to left add 0 to string
			tmp += "0";
			createHuffmanArraysHelper(ptr->leftPtr);
			//while going to right add 1 to string
			tmp += "1";
			createHuffmanArraysHelper(ptr->rightPtr);
		}
	}
	string newTmp = tmp.substr(0, tmp.size() - 1);
	tmp = newTmp;
} 
//
// Returns max index
//
template< typename TYPE >
int mergingTree<TYPE>::max(int a, int b)
{
	return (a > b) ? a : b;
}
//
// Copy function
//
template< typename TYPE >
Node< TYPE > *mergingTree<TYPE>::copy(Node< TYPE > *othermergingTreeRoot)
{
	Node<TYPE> *temp;

	if (othermergingTreeRoot == NULL)
		return NULL;

	temp = new Node<TYPE>(othermergingTreeRoot->data);
	temp->leftPtr = copy(othermergingTreeRoot->leftPtr);
	temp->rightPtr = copy(othermergingTreeRoot->rightPtr);
	return temp;
}
//
// Uses the copy function to get copy of the root
//
template< typename TYPE >
Node< TYPE > *mergingTree<TYPE>::getRootCopy()
{
	return copy(root); 
}
//
// Assignment operator
//
template< typename TYPE >
mergingTree< TYPE > &mergingTree< TYPE >::operator=(const mergingTree< TYPE > &right)
{
	//first destroy data
	while (root != NULL)
	{
		omitHelper(NULL, root, root->data);
	}

	root = copy(right.root);

	return *this;
}
//
// Equal function used in the comparison operator
//
template< typename TYPE >
bool mergingTree<TYPE>::equal(Node <TYPE> *n1, Node <TYPE> *n2) const
{
	Node <TYPE> *L1 = n1->leftPtr,
		*L2 = n2->leftPtr,
		*R1 = n1->rightPtr,
		*R2 = n2->rightPtr;

	if (n1->data != n2->data)
		return false;

	if ((L1 && L2) && (R1 && R2))
		return (equal(L1, L2) && equal(R1, R2));

	if ((L1 && !L2) ||
		(!L1 && L2) ||
		(R1 && !R2) ||
		(!R1 && R2))
		return false;

	return true;
}
//
// Comparison operator
//
template< typename TYPE >
bool mergingTree< TYPE >::operator==(const mergingTree< TYPE > &right) const
{
	return equal(root, right.root); 
}
//
// Returns vector of Huffman Numbers
//
template< typename TYPE >
vector<string> mergingTree< TYPE >::getHuffmanNumbers() const
{
	if (!created)
	{
		cout << "Array's Not Created!" << endl;
	}
	else
		return numbers;
}
//
// Return vector of Huffman Elements
//
template< typename TYPE >
vector<TYPE> mergingTree< TYPE >::HuffmanElements() const
{
	if (!created)
	{
		cout << "Array's Not Created!" << endl;
	}
	else
		return elements;
}

