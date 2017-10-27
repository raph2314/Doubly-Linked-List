#ifndef A1_BIG_INT_HPP
#define A1_BIG_INT_HPP

#include <cmath>

#include "a1_doubly_linked_list2.hpp"
#include <string>

typedef unsigned long long int ulli;

class BigInt {
	private:
		friend class BigIntTest;
		DoublyLinkedList* data;
		int size_;
	public:
		//Constructor with bool array and size
		BigInt(bool B[], int size);
		//Constuctor with spring representation
		BigInt(std::string value);
		//empty Constructor
		BigInt();
		BigInt* add(BigInt* rhs); // computes “*this + *rhs” 
		BigInt* sub(BigInt* rhs); // computes “*this - *rhs” 
		BigInt* mul(BigInt* rhs); // computes “*this * *rhs” 
		BigInt* and_(BigInt* rhs); // computes bitwise AND of “*this & *rhs” 
		BigInt* or_(BigInt* rhs); // computes bitwise OR of “*this | *rhs”
		BigInt* xor_(BigInt* rhs); // computes bitwise XOR of “*this ^ *rhs”*/
		
		unsigned int value(int index);
		
		void Print();
};

#endif
