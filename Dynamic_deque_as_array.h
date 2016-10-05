#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H

#include "ece250.h"
#include "Exception.h"

#include <iostream>
using namespace std;

class Dynamic_deque_as_array
{

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;
		
		void print() const;
		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
	
	private:
		int theCapacity;
		int count;
		int headIndex;
		int tailIndex;	
		int *array;
		
		int mod(int n, int m) const;
		void doubleCapacity();
};


/*
Dynamic_deque_as_array (int n=10) - The constructor takes an argument as the capacity of the array and
allocates memory for that array. The default capacity (or number of entries) is 10. If the argument n is less
than one, use an array size of 1. Other class members should be assigned appropriate values.
*/
Dynamic_deque_as_array::Dynamic_deque_as_array( int n):
	theCapacity(n), count(0), headIndex(0), tailIndex(0) {
	if (n < 1){
		theCapacity = 1;
	}
		
	array = new int[theCapacity];
}

/*
The destructor deletes the memory allocated for the array.
*/
Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	delete [] array;
}

/*
The % operation was giving my negative numbers so I implemented my own
*/
int Dynamic_deque_as_array::mod(int n, int m) const{
	if (n < 0){
		return n + m;
	}else if (n >= m){
		return n - m;
	}else{
		return n;
	}
}


/*
Return the number of elements currently stored in the deque in O(1).
*/
int Dynamic_deque_as_array::size() const {
	return count;
}

/*
Return the capacity of deque in O(1).
*/
// Ask for clarification on the definition of capacity
int Dynamic_deque_as_array::capacity() const {
	return theCapacity;
	/* 
	Note that the actual number of elements is theCapacity - 1
	But the allocated memory is theCapacity
	This is because the tail pointer points to a null space
	*/
}

/*
Return true if deque is empty false otherwise in O(1).
*/
bool Dynamic_deque_as_array::empty() const {
	return count == 0;
}

/*
Return the integer at the head of the data deque in O(1). It may throw an
underflow exception.
*/
int Dynamic_deque_as_array::head() const {
	if (empty()){
		throw underflow();
	}else{
		return array[headIndex];
	}
}

/*
Return the integer at the tail of the data deque in O(1). It may throw an
underflow exception
*/
int Dynamic_deque_as_array::tail() const {
	if (empty()){
		throw underflow();
	}else{
		int index = mod(tailIndex-1, theCapacity);
		return array[index];
	}
}


/*
Prints the contents of the dequeue from head to tail
*/
void Dynamic_deque_as_array::print() const{
	for (int i = 0; i < count; i++){
		cout << array[mod(headIndex + i, theCapacity)] << ", ";
	}
	cout << " " << endl;
}

/*
Doubles the capacity of the array
*/
void Dynamic_deque_as_array::doubleCapacity(){

	int *newArray = new int[2*theCapacity];

	for (int i = 0; i < count; i ++){
		int index = mod(headIndex + i, theCapacity);
		newArray[i] = array[index];
	}
		
	delete [] array;	
	array = newArray;
	theCapacity = 2*theCapacity;	
	headIndex = 0;
	tailIndex = count; // remember the tail point to a blank
	
}

/*
Insert a new item at the head of the deque in O(1). If the array
is full, create a new array with size 2n (where n is current size of the array) and copy the elements
from the current array to the new array in O(n).
*/
void Dynamic_deque_as_array::enqueue_head( const int &obj ) {
	
	if (count == (theCapacity -1)){
		doubleCapacity();
	}

	headIndex = mod((headIndex - 1),theCapacity);
	array[headIndex] = obj;
	count++;
	
}

/*
Insert a new item at the tail of the deque in O(1). If the array is
full, create a new array with size 2n (where n is current size of the array) and copy the elements
from the current array to the new array in O(n).
*/
void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	if (count == theCapacity -1){
		doubleCapacity();
	}
	
	//cout << "Enqueue tail the value " << obj << endl; 
	array[tailIndex] = obj;
	tailIndex = mod((tailIndex + 1), theCapacity);
	count++;
}

/*
Remove the element at the head of the deque in O(1). This may throw an
underflow exception.
*/
int Dynamic_deque_as_array::dequeue_head() {
	if (empty()){
		throw underflow();
	}else{
		int copy = headIndex;
		headIndex = mod((headIndex + 1),theCapacity);
		count--;
		return array[copy];
	}
}

/*
 Remove the element at the tail of the deque in O(1). This may throw an
underflow exception.
*/
int Dynamic_deque_as_array::dequeue_tail() {
	if (empty()){
		throw underflow();
	}else{
		
		tailIndex = mod((tailIndex - 1), theCapacity);
		count--;
		return array[tailIndex];
	}
}

// Remove all elements from the deque in O(1).
void Dynamic_deque_as_array::clear() {
	//don't need to delete! its costly to deallocate and reallocate memory
	// if we just reset everything all your function should work as normal? Just overwrite the data. 
	//don't quote me but its better not to think of allocate as O(1)
	//delete [] array;
	//array = new int[theCapacity];
	headIndex = 0;
	tailIndex = 0;
	count = 0;
}

#endif


