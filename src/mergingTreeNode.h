#pragma once

template< typename TYPE > class mergingTree;

// TreeNode class-template definition
template< typename TYPE >
class Node
{
	friend class mergingTree< TYPE >;
	friend class HuffmanCoding;
public:
	// constructor
	Node(const TYPE &d): leftPtr(0), rightPtr(0) // pointer to the left and right substree
	{
		data = d;
	}
	// return node's data
	TYPE getData() const
	{
		return data;
	}
private:
	Node< TYPE > *leftPtr; // pointer to left subtree
	TYPE data;
	Node< TYPE > *rightPtr; // pointer to right subtree
};

