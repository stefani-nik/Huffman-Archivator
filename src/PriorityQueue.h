#pragma once
template<class TYPE>
class PriorityQueue
{
public:

	PriorityQueue(int d = 2); //constructor 
	~PriorityQueue(void); //destructor
	void enq(TYPE*); //enPriorityQueue (to push)
	TYPE* deq(void); //dePriorityQueue (to pop)
	TYPE* front(void); //the front element
	bool empty(void) const; //is empty?
	bool full(void) const; //is full?

private:

	int back; //the last element in the PriorityQueue
	TYPE* *arr; //dynamic array
	int size; //current size of the PriorityQueue array
	static const int SIZE = 10; //size increment step size  
	int D; //max number of children for a parent>=2 
		   //copy constructor and assignment are hidden to protect 
	PriorityQueue(const PriorityQueue &);
	const PriorityQueue & operator=(const PriorityQueue &);

	//utility functions to fix the heap
	//when an element added or removed 
	void reheapup(int, int); //fix heap upward
	void reheapdown(int, int); //fix heap downward
	void swap(TYPE* &, TYPE* &); //swap f. needed by reheapup/down functions

}; //end class
