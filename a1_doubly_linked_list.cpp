#include "a1_doubly_linked_list.hpp"
#include <iostream>

DoublyLinkedList::Node::Node(DataType data)
{
	value = data;
	next = NULL;
	prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
	/*
	if(size_==0){
		
	}
	if(size_==1){
		delete head_;
	}
	if(size_==2){
		delete head_;
		delete tail_;
	}
	else{
		Node *temp;
		temp = head_;
		for(int i=1; i<size_; i++){
			temp = temp->next;
			delete temp->prev;
		}
		delete temp;
	}
	*/
	
	Node *temp = head_;
	while(temp){
		head_ = head_->next;
		delete temp;
		temp = head_;
	}
}

unsigned int DoublyLinkedList::size() const
{
	return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
	return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
	return (size_ == 0);
}

bool DoublyLinkedList::full() const
{
	return (size_ == CAPACITY);
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
	
	std::cout << getNode(index)->value;
	return getNode(index)->value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
	for(int i = 0; i < size_; i++){
		if(getNode(i)->value == value)
			return i;	
	}
	return size_;
}

void DoublyLinkedList::print() const
{
	std::cout << "(";
	
		for(int i = 0; i < size_; i++){
			std::cout << getNode(i)->value << ", ";
		}
		
	std::cout << ")";
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
	if(index+1>size_){
		return tail_;
	}
	Node *temp;
	temp = head_;
	for(int i=0; i<index; i++){
		temp = temp->next;
	}
	return temp;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
	if(index>=size_+1){
		return false;
	}
	if(size_==0){
		Node *newNode = new Node(value);
		head_ = newNode;
		tail_ = newNode;
		size_++;
		return true;
	}
	if(index==0){
		Node *newNode = new Node(value);
		newNode->next = head_;
		head_->prev = newNode;
		head_ = newNode;
		size_++;
		return true;
	}
	if(getNode(index-1)->next){
		Node *newNode = new Node(value);
		newNode->next = getNode(index-1)->next;
		newNode->prev = getNode(index-1);
		getNode(index-1)->next = newNode;
		size_ ++;
		getNode(index+1)->prev = newNode;
		return true;
	}
	else
	{
		Node *newNode = new Node(value);
		newNode->prev = getNode(index-1);
		getNode(index-1)->next = newNode;
		size_ ++;
		tail_ = newNode;
		return true;
	}
}

bool DoublyLinkedList::insert_front(DataType value)
{
	insert(value, 0);
	return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
	if(size_==0){
		Node *newNode = new Node(value);
		head_ = newNode;
		tail_ = newNode;
		size_++;
		return true;
	}
	Node *newNode = new Node(value);
	Node *prevTail = tail_;
	tail_ = newNode;
	tail_->prev = prevTail;
	prevTail->next = tail_;
	size_++;
	return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
	if(size_==0){
		return false;
	}
	if(index>=size_){
		return false;
	}
	Node *toRemove = getNode(index);
	if(size_==1){
		head_ = NULL;
		tail_ = NULL;
		delete toRemove;
		size_--;
		return true;
	}
	if(index==0){
		head_ = head_->next;
		head_->prev = NULL;
		delete toRemove;
		size_--;
		return true;
	}
	if(toRemove->next==NULL){
		tail_ = tail_->prev;
		tail_->next = NULL;
		delete toRemove;
		size_--;
		return true;
	}
	Node *prevNode = getNode(index-1);
	Node *nextNode = getNode(index+1);
	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	delete toRemove;
	size_--;
	return true;
}

bool DoublyLinkedList::remove_front()
{
	remove(0);
}

bool DoublyLinkedList::remove_back()
{
	if(size_==0){
		return false;
	}
	if(size_==1){
		Node *toRemove = tail_;
		head_ = NULL;
		tail_ = NULL;
		delete toRemove;
		size_--;
		return true;
	}
	Node *toRemove = tail_;
	tail_ = tail_->prev;
	tail_->next = NULL;
	delete toRemove;
	size_--; 
	return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
	if(getNode(index)){
		getNode(index)->value = value;
		return true;
	}
	return false;
}

bool DoublyLinkedList::is_sorted_asc() const {
		for(int i=0; i<size_; i++){
		if(i>0){
			if((getNode(i)->value) < (getNode(i-1)->value)){
			return false; 
			}
		}	
	}
	return true;
}

bool DoublyLinkedList::is_sorted_desc() const {
	for(int i=0; i<size_; i++){
		if(i>0){
			if(getNode(i)->value > getNode(i-1)->value){
				return false;
			}
		}
	}
	return true;
}

bool DoublyLinkedList::insert_sorted_asc(DataType val) {
		if(is_sorted_asc()){
		for(int i=0; i < size_; i++){
			if(getNode(i)->value > val){
				return insert(val, i);
			}
		}
		return insert_back(val);
	}
	return false;
}

bool DoublyLinkedList::insert_sorted_desc(DataType val) {
	if(is_sorted_desc()){
		for(int i=0; i < size_; i++){
			if(getNode(i)->value < val){
				return insert(val, i);
			}
		}
		return insert_back(val);
	}
	return false;
}

void DoublyLinkedList::sort_asc() {
	
	bool isSorted = new bool();
	isSorted = false;
	while(!isSorted){
		isSorted = true;
		for(int i=0; i < size_; i++){
			if(i>0){
				if(getNode(i)->value < getNode(i-1)->value){
					isSorted = false;
					DataType temp;
					temp = getNode(i)->value;
					getNode(i)->value = getNode(i-1)->value;
					getNode(i-1)->value = temp; 
				}
			}
		}
		
	}
}
    
void DoublyLinkedList::sort_desc() {
	
	bool isSorted = new bool();
	isSorted = false;
	while(!isSorted){
		isSorted = true;
		for(int i = 0; i < size_; i++){
			if(i>0){
				if(getNode(i)->value > getNode(i-1)->value){
					isSorted = false;
					DataType temp;
					temp = getNode(i)->value;
					getNode(i)->value = getNode(i-1)->value;
					getNode(i-1)->value = temp; 
				}
			}
		}
	}
	
	
	
}


