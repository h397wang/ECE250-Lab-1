#include "Dynamic_deque_as_array.h"
#include "Exception.h"
#include "ece250.h"
#include <stdlib.h> 
#include <time.h>
#include <iostream>

using namespace std;

int main(){
	

	srand (time(NULL));
	int successCounter = 0;
	int testCounter = 0;
	int size = rand() % 8 + 3;
	
	
	// Test default constructor
	cout << "Test the default constructor " << endl;
	Dynamic_deque_as_array *d1 = new Dynamic_deque_as_array();
	cout << "Capacity should be 10: " << d1->capacity() << endl;
	cout << "Size should be 0: " << d1->size() << "\n" << endl;
	
	
	
	// Test regular constructor
	cout << "Test the regular constructor with n = size " << endl;
	Dynamic_deque_as_array *d2 = new Dynamic_deque_as_array(size);	
	cout << "Capacity should be " << size << ": " << d2->capacity() << endl;
	cout << "Size should be 0: " << d2->size() << "\n" << endl;
	
	
	
	// Test enqueue of head and dequeue of tail
	cout << "Test enqueue head and dequeue tail " << endl;
	int *values = new int[size];
	
	for (int i = 0; i < size-1; i++){
		d2->enqueue_head(i);
		values[i] = i;
	}
	
	cout << "Size should be " << size - 1 << " : " << d2->size() << endl;
	cout << "Values retrieved from deque : What it should be " << endl; 
	
	for (int i = 0; i < size-1; i++){
		cout << d2->dequeue_tail() << " : ";
		cout << values[i] << endl;;
	}
	
	
	
	// Test enqueue of tail and dequeue of head
	cout << "Test enqueue tail and dequeue  head " << endl;
	delete d2;
	delete [] values;
	d2 = new Dynamic_deque_as_array(2*size);
	values = new int[2*size];
	
	for (int i = 0; i < size-1; i++){
		d2->enqueue_tail(i);
		values[i] = i;
	}
	
	cout << "Values retrieved from deque : What it should be " << endl; 
	for (int i = 0; i < size-1; i++){
		cout << d2->dequeue_head() << " : ";
		cout << values[i] << "\n" << endl;;
	}
	
	
	// Test head() and tail()
	cout << "Test head() and tail() normal cases" << endl;
	delete d2;
	delete [] values;
	d2 = new Dynamic_deque_as_array(size);
	values = new int[size];
	
	for (int i = 0; i < size-1; i++){
		d2->enqueue_tail(i);
		values[i] = i;
	}
	cout << "Head value should be " << values[0] << " : "  << d2->head() << endl;
	cout << "Tail value should be " << values[size-2] << " : "  << d2->tail() << endl;
	cout << " " << endl;
	
	
	// Test clear()
	cout << "Test clear() " << endl;
	cout << "Size of d2 is initially " << size-1 << " : " << d2->size() << endl;
	d2->clear();
	cout << "Size of d2 should now be 0: " << d2->size() << "\n " << endl;
	
	
	
	// Test empty()
	cout << "Test empty() " << endl;
	cout << "Empty() should now yield true " << d2->empty() <<  "\n" << endl;
	
	
	
	// Test for doubling
	cout << "Test for doubling " << endl;
	delete d2;
	delete [] values;
	d2 = new Dynamic_deque_as_array(size);
	values = new int[2*size];
	
	cout << "Enqueuing from head, values from 0 to " << 2*size -2 << endl;
	for (int i = 0; i < 2*size - 1; i++){
		d2->enqueue_head(i);
		values[i] = i;
	}
	
	// prints out values starting at head
	//d2->print();
	
	cout << "Capactiy should be " << size*2 << " : " << d2->capacity() << endl;	
	cout << "The size should be " << 2*size -1 << " : " << d2->size() << endl;
	
	cout << "Values retrieved from deque (with dq tail): What it should be " << endl; 
	for (int i = 0; i < 2*size - 1; i++){
		cout << d2->dequeue_tail() << " : ";
		cout << values[i] << endl;;
	}
	
	cout << "The size should be 0 after dequeing : " << d2->size() << "\n" << endl;
	
	
	
	// Error checks
	cout << "check for errors" << endl;
	d2->clear();
	
	try {
		d2->dequeue_head();
	}catch (underflow e){
		cout << "Underflow exception occured for dequeue head" << endl;
	}
	
	try {
		d2->dequeue_tail();
	}catch (underflow e){
		cout << "Underflow exception occured for dequeue tail" << endl;
	}
	
	try{
		d2->head();
	}catch (underflow e){
		cout << "Underflow exception has occured for head()" << endl;	
	}
	
	try{
		d2->tail();
	}catch (underflow e){
		cout << "Underflow exception has occured for tail()" << endl;	
	}
	
	return 0;
	
}



