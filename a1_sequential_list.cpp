#include "a1_sequential_list.hpp"
#include <iostream>

SequentialList::SequentialList(unsigned int cap)
{
	capacity_ = cap;
	size_ = 0;
	data_ = new DataType[cap];
}

SequentialList::~SequentialList()
{
	delete data_;
}

unsigned int SequentialList::size() const
{
	return size_;
}

unsigned int SequentialList::capacity() const
{
	return capacity_;
}

bool SequentialList::empty() const
{
	return (size_ == 0);
}

bool SequentialList::full() const
{
	return (size_ == capacity_);
}


SequentialList::DataType SequentialList::select(unsigned int index) const
{
	if(index > size_ - 1)	
		return data_[size_-1];
	else
		return data_[index];
}


unsigned int SequentialList::search(DataType val) const
{
	for(int i = 0; i < size_; i++){
		if(data_[i] == val)
			return i;	
	}
	return size_;
}
void SequentialList::print() const
{
	std::cout << "(";
	
		for(int i = 0; i < size_; i++){
			std::cout << data_[i] << ", ";
		}
		
	std::cout << ")";
	
}

bool SequentialList::insert(DataType val, unsigned int index)
{
	//Case 1: empty list
	if(size_==index&&size_<capacity_){
		size_++;
		data_[index]=val;
		return true;
	}
	//Verify index validity
	if(size_ + 1 > capacity_ || index > size_ -1){
		return false;
	}
	//Case 2: Insert anywhere but the front
	else if(index != 0){
		size_ ++;
		for(int i = size_ - 1; i >= index; i--){
			data_[i] = data_[i-1];		
		}
		data_[index] = val; 
		return true;
	}
	//Case 3: Insert at the front 
	else{
		size_++;
		for(int i = size_ - 1; i > index; i--){
			data_[i] = data_[i-1];
		}
		data_[index] = val; 
		return true;
	}
}

bool SequentialList::insert_front(DataType val)
{
	return insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
	return insert(val, size_);
}

bool SequentialList::remove(unsigned int index)
{
	//Nothing to remove
	if(size_==0){
		return false;
	}
	//Invalid index
	if(index > size_){
		return false;
	}
	//Valid index
	else{
		for(int i = index; i < size_ ; i++){
			data_[i] = data_[i+1];
		}
		size_--;
		return true;
	}
}

bool SequentialList::remove_front()
{
	return remove(0);
}

bool SequentialList::remove_back()
{
	return remove(size_ - 1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
	
	if(data_[index]){
		data_[index] = val;
		return true;
	}
	return false;
	
}

bool SequentialList::is_sorted_asc() const {
	if(size_==0){
		return true;
	}
	for(int i = 0; i < size_; i++){
		if(i>0){
			if(data_[i]<data_[i-1]){
				return false;
			}
		}
	}
	return true;
	
}

bool SequentialList::is_sorted_desc() const {
	if(size_==0){
		return true;
	}
	for(int i = 0; i < size_; i++){
		if(i>0){
			if(data_[i]>data_[i-1]){
				return false;
			}
		}
	}
	return true;
	
}

bool SequentialList::insert_sorted_asc(DataType val) {
	
	if(is_sorted_asc()){
		for(int i = 0; i < size_; i++){
			if(val<data_[i]){
				insert(val, i);
				return true;
			}
		}
		insert_back(val);
		return true;
	}
	
}

bool SequentialList::insert_sorted_desc(DataType val) {
	
	if(is_sorted_desc()){
		for(int i = 0; i < size_; i++){
			if(val>data_[i]){
				insert(val, i);
				return true;
			}
		}
		insert_back(val);
		return true;
	}
	
}

void SequentialList::sort_asc() {
	
	bool isSorted = new bool;
	isSorted = false;
	while(!isSorted){
		isSorted = true;
		for(int i = 0; i < size_; i++){
			if(i>0){
				if(data_[i]<data_[i-1]){
					isSorted = false;
					int temp = data_[i];
					data_[i] = data_[i-1];
					data_[i-1] = temp;
				}
			}
		}
	}
	
}
    
void SequentialList::sort_desc() {
	
	bool isSorted = new bool;
	isSorted = false;
	while(!isSorted){
		isSorted = true;
		for(int i = 0; i < size_; i++){
			if(i>0){
				if(data_[i]>data_[i-1]){
					isSorted = false;
					int temp = data_[i];
					data_[i] = data_[i-1];
					data_[i-1] = temp;
				}
			}
		}
	}
	
}


