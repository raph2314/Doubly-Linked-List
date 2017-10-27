#include "a1_big_int.hpp"
#include <iostream>

using namespace std;
//Constructor 1
BigInt::BigInt(bool B[], int size){
	data = new DoublyLinkedList();
	for(int i = size; i>0; i--){
		int index = (size-i)%32;
		int nodeIndex = (size-i)/32;
		//cout<<"Node index: "<<nodeIndex;
		if(index==0){
			data->insert_back(0);
		}
		/*
		cout<<"\nIndex: "<<i-1;
		cout<<", Value: "<<B[i-1]<<", Place: "<<index;
		*/
		if(B[i-1]){
			data->replace(nodeIndex ,data->select(nodeIndex) + pow(2, index));
		}
		size_ = nodeIndex;
	}
}

//Constructor 2
BigInt::BigInt(string value){
	
}

//Constructor 3
BigInt::BigInt(){
	data = new DoublyLinkedList();
	size_= -1;
}

//add together, return pointer
BigInt* BigInt::add(BigInt* rhs){
	BigInt* output = new BigInt();
	int *bigger = new int;
	if(size_>rhs->size_){
		*bigger = size_;
	}
	else{
		*bigger = rhs->size_;
	}
	output->size_ = *bigger;
	ulli *carry = new ulli;
	*carry = 0;
	for(int i = 0; i<=*bigger;i++){
		//cout<<"value1: "<<data->select(i)<<"value2: "<<rhs->data->select(i)<<"\n";
		ulli v1 = (ulli) rhs->data->select(i);
		ulli v2 = (ulli) data->select(i);
		ulli sum = v1+v2;
		unsigned int store = (int) sum;
		//cout << "store: "<<store<<"\n";
		store += (int) *carry;
		//cout<< "store + carry: "<<store<<"\n";
		*carry = sum >> 32;
		//cout<< "new carry: "<<*carry<<"\n";
		output->data->insert_back(store);
	}
	if(*carry!=0){
		int carryf = (int) *carry;
		output->data->insert_back(carryf);
	}
	return output;
}

//subtract rhs from this
BigInt* BigInt::sub(BigInt* rhs){
	BigInt* output = new BigInt();
	
	//this will only matter if we let negative numbers exist
	int *bigger = new int;
	bool *isPositive = new bool;
	if(size_==rhs->size_){
		if(data->select(size_)>=rhs->data->select(size_)){
			*isPositive = true;
		}
		else{
			*isPositive = false;
		}
	}
	else if(size_>rhs->size_){
		*isPositive = true;
		*bigger = size_;
	}
	else{
		*isPositive = false;
		*bigger = rhs->size_;
	}
	//
	
	unsigned int *carry = new unsigned int;
	*carry = 0;
	for(int i = 0; i<=size_ || i<=rhs->size_; i++){
		ulli v1 = (ulli) data->select(i);
		ulli v2 = (ulli) rhs->data->select(i);
		v1 -= *carry;
		//cout <<"\n"<<v1<<"\n"<<v2;
		if(v1>=v2){
			ulli diff = v1 - v2;
			unsigned int num = (int) diff;
			output->data->insert_back(num);
			*carry = 0;
		}
		else{
			ulli tempnum = (long long)1;
			tempnum = tempnum<<32;
			v1 += (tempnum);
			ulli diff = v1 - v2;
			unsigned int num = (int) diff;
			output->data->insert_back(num);
			*carry = 1;
		}
		output->size_+=1;
	}
	return output;
}

//multiply
BigInt* BigInt::mul(BigInt* rhs){
	BigInt* output = new BigInt();
	ulli *carry = new ulli;
	*carry = 0;
	for(int i = 0; i<=size_; i++){
		BigInt* tempNum = new BigInt();
		for(int k = 0; k<i; k++){
			tempNum->data->insert_back(0);
			tempNum->size_ += 1;
		}
		for(int j = 0; j<=rhs->size_; j++){
			ulli v1 = (ulli) data->select(j);
			ulli v2 = (ulli) rhs->data->select(j);
			ulli prod = v1*v2 + *carry;
			unsigned int num = (int) prod;
			tempNum->data->insert_back(num);
			tempNum->size_ += 1;
			*carry = prod >> 32;
		}
		if(*carry!=0){
			unsigned int num = (int) *carry;
			tempNum->data->insert_back(num);
			tempNum->size_ += 1;
		}
		output = output->add(tempNum);
	}
	return output;
}

//bitwise and
BigInt* BigInt::and_(BigInt* rhs){
	BigInt* output = new BigInt();
	int *bigger = new int;
	if(size_>rhs->size_){
		*bigger = size_;
	}
	else{
		*bigger = rhs->size_;
	}
	output->size_ = *bigger;
	for(int i = 0; i<=*bigger;i++){
		unsigned int v1 = data->select(i);
		unsigned int v2 = rhs->data->select(i);
		unsigned int val = v1 & v2;
		output->data->insert_back(val);
	}
	return output;
}

//bitwise or
BigInt* BigInt::or_(BigInt* rhs){
	BigInt* output = new BigInt();
	int *bigger = new int;
	if(size_>rhs->size_){
		*bigger = size_;
	}
	else{
		*bigger = rhs->size_;
	}
	output->size_ = *bigger;
	for(int i = 0; i<=*bigger;i++){
		unsigned int v1 = data->select(i);
		unsigned int v2 = rhs->data->select(i);
		unsigned int val = v1 | v2;
		output->data->insert_back(val);
	}
	return output;
}

//bitwise xor
BigInt* BigInt::xor_(BigInt* rhs){
	BigInt* output = new BigInt();
	int *bigger = new int;
	if(size_>rhs->size_){
		*bigger = size_;
	}
	else{
		*bigger = rhs->size_;
	}
	output->size_ = *bigger;
	for(int i = 0; i<=*bigger;i++){
		unsigned int v1 = data->select(i);
		unsigned int v2 = rhs->data->select(i);
		unsigned int val = v1 ^ v2;
		output->data->insert_back(val);
	}
	return output;
}

unsigned int BigInt::value(int index){
	return data->select(index);
}

//for debug
void BigInt::Print(){
	for(int i = 0; i<=size_; i++){
		cout << data->select(i) <<", ";
	}
}
