#ifndef MULTI_LINKED_LIST_H
#define MULTI_LINKED_LIST_H
#include <ctime>
#include <cassert>
#include "mtrand.h"


// random seed
MTRand_int32 mtrand_autoseed(time(NULL));

// ----------------------------------------------------------------------------------------------------
// NODE CLASS

template <class T>
class Node {
public:
	Node(): sorted_next(NULL), sorted_prev(NULL), chrono_next(NULL), chrono_prev(NULL), random_next(NULL) {}
	Node(const T& v): value(v), sorted_next(NULL), sorted_prev(NULL), chrono_next(NULL), chrono_prev(NULL), random_next(NULL) {}
	// REPRESENTATION
	T value;
	Node<T>* sorted_next;
	Node<T>* sorted_prev;
	Node<T>* chrono_next;
	Node<T>* chrono_prev;
	Node<T>* random_next;
};

// A FORWARD DECLARATION
template <class T> class MultiLL;

// ----------------------------------------------------------------------------------------------------
// LIST ITERATION
template <class T>
class list_iterator {
public:
	// default constructor, copy constructor, assignment constructor, destructor
	list_iterator(): ptr(NULL) {}
	list_iterator(Node<T>* p, int i): ptr(p),type(i) {}
	list_iterator(const list_iterator<T>& old): ptr(old.ptr),type(old.type) {}
	list_iterator<T>& operator=(const list_iterator<T>& old) {ptr = old.ptr; type = old.type; return *this;}
	~list_iterator() {} 
	
	// dereferencing operator gives access to the value at the pointer
	T& operator*() {return ptr->value;}
	
	// increment and decrement operators
	list_iterator<T> operator++() {
		if (type == 0)
			ptr = ptr -> chrono_next;
		else if (type == 1)
			ptr = ptr -> sorted_next;
		else if (type == 2)
			ptr = ptr -> random_next;
		return *this;
	}
	list_iterator<T> operator++(int) {
		list_iterator<T> temp(*this);
		if (type == 0)
			ptr = ptr -> chrono_next;
		else if (type == 1)
			ptr = ptr -> sorted_next;
		else if (type == 2)
			ptr = ptr -> random_next;
		return temp;
	}
	list_iterator<T> operator--() {
		if (type == 0)
			ptr = ptr -> chrono_prev;
		else if (type == 1)
			ptr = ptr -> sorted_prev;
		return *this;
	}
	list_iterator<T> operator--(int) {
		list_iterator<T> temp(*this);
		if (type == 0)
			ptr = ptr -> chrono_prev;
		else if (type == 1)
			ptr = ptr -> sorted_prev;
		return temp;
	}
	
    // the MultiLL class needs access to the private ptr_ member variable
    friend class MultiLL<T>;
	
	// compartison
	bool operator==(const list_iterator<T>& r) const {return ((ptr == r.ptr)&&(type == r.type));}
	bool operator!=(const list_iterator<T>& r) const {return ((ptr != r.ptr)||(type != r.type));}
	
private:
	// REPRESENTATION
	Node<T>* ptr;
	int type;
};

template <class T>
class MultiLL {
public:
	// default constructor, copy constructor, assignment constructor, destructor
	MultiLL(): chrono_head(NULL), chrono_tail(NULL), sorted_head(NULL), sorted_tail(NULL), random_head(NULL), dummy_node(NULL), size_(0) {}
	MultiLL(const MultiLL<T>& old) {this->copy_list(old);}
	MultiLL& operator=(const MultiLL<T>& old);
	~MultiLL() {this->destroy_list();}
	
	// simple accessors & modifiers
	unsigned int size() const {return size_;}
	bool empty() const {return chrono_head == NULL;}
	void clear() {this -> destroy_list();}
	
	// modify the list structure
	typedef list_iterator<T> iterator;
	iterator begin_chronological() {return iterator(chrono_head, 0);}
	iterator end_chronological() {return iterator(dummy_node, 0);}
	iterator begin_sorted() {return iterator(sorted_head, 1);}
	iterator end_sorted() {return iterator(dummy_node, 1);}
	iterator begin_random();
	void add(const T& v);
	iterator erase(iterator itr);
	
private:
	// private helper functions
	void copy_list(const MultiLL<T>& old);
	void destroy_list();
	// REPRESENTATION
	Node<T>* chrono_head;
	Node<T>* chrono_tail;
	Node<T>* sorted_head;
	Node<T>* sorted_tail;
	Node<T>* random_head;
	Node<T>* dummy_node;
	unsigned int size_;
};

// ----------------------------------------------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::begin_random() {
	// Use Fisher-Yates shuffle modern algorithm to generate a non-repeated random array
	// reference: https://www.youtube.com/watch?v=tLxBwSL3lPQ
	// The array stores a non-repeated random sequence 
	int array[size_];
	for (int i = 0; i < size_; ++i) {
		array[i] = i;
	}
	int i = size_;
	while (--i > 0) {
		int j = mtrand_autoseed() % (i+1);
		// swap
		int temp = array[j];
		array[j] = array[i];
		array[i] = temp;
	}
	// Create the single-linked list
	if (size_ == 0) {
		random_head = NULL;
	} else if (size_ == 1) {
		MultiLL<T>::iterator itr(chrono_head,0);
		itr.ptr->random_next = itr.ptr;
		random_head = itr.ptr;
	} else {
		for (int i = 0; i < size_-1; ++i) {
			// find the node correspoonding to the number
			MultiLL<T>::iterator itr1(chrono_head,0);
			for (int j = 0; j < array[i]; ++j) {
				itr1++;
			}
			MultiLL<T>::iterator itr2(chrono_head,0);
			for (int j = 0; j < array[i+1]; ++j) {
				itr2++;
			}
			if (i == 0) {
				// head
				random_head = itr1.ptr;
			}
			// middle
			itr1.ptr->random_next = itr2.ptr;
			if (i == size_ - 2) {
				// "tail"
				itr2.ptr->random_next = random_head;
			}
		}
	}
	return iterator(random_head,2);
}

template <class T>
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
	if (&old != this) {
		this -> destroy_list();
		this -> copy_list(old);
	}
	return *this;
}

template <class T>
bool operator== (MultiLL<T>& left, MultiLL<T>& right) {
	if (left.size_() != right.size_()) return false;
	typename MultiLL<T>::iterator left_itr = left.begin_chronological();
	typename MultiLL<T>::iterator right_itr = right.begin_chronological();
	while (left_itr != left.end()) {
		if (*left_itr != *right_itr) return false;
		left_itr++; right_itr++;
	}
	return true;
}

template <class T>
bool operator != (MultiLL<T>& left, MultiLL<T>& right) {return !(left == right);}

template <class T>
void MultiLL<T>::add(const T& v) {
	Node<T>* newp = new Node<T>(v);
	// initially empty list
	if (size_) {
		chrono_head = chrono_tail = newp;
		sorted_head = sorted_tail = newp;
		dummy_node = new Node<T>;
		dummy_node->chrono_next = NULL;
		dummy_node->sorted_next = NULL;
		dummy_node->chrono_prev = chrono_tail;
		chrono_tail->chrono_next = dummy_node;
		dummy_node->sorted_prev = sorted_tail;
		sorted_tail->sorted_next = dummy_node;
	} else {
		// chronological
		newp->chrono_prev = chrono_tail;
		chrono_tail->chrono_next = newp;
		chrono_tail = newp;
		dummy_node->sorted_prev = sorted_tail;
		sorted_tail->sorted_next = dummy_node;
		// sorted
		// Before inserting, the list is already in a sorted order
		// we need to decide whether it should be inserted to the end
		MultiLL<T>::iterator itr(sorted_head,1);
		bool greatest = true;
		for (unsigned int i = 0; i < size_; ++i, ++itr) {
			if (v <= *itr) {
				greatest = false;
				if (i == 0) {
					// special case: v should be the first one
					newp->sorted_next = itr.ptr;
					itr.ptr->sorted_prev = newp;
					sorted_head = newp;
				} else {
					MultiLL<T>::iterator temp = itr;
					--temp;
					newp->sorted_next = itr.ptr;
					itr.ptr->sorted_prev = newp;
					newp->sorted_prev = temp.ptr;
					temp.ptr->sorted_next = newp;
				}
				break;
			} 
		}
		if (greatest) {
			// special case: v should be the last one
			newp->sorted_prev = sorted_tail;
			sorted_tail->sorted_next = newp;
			sorted_tail = newp;
		}
	}
	// since the tail node may be changed, we need to reconnect the dummy node and the tail node
	
	++size_;
}

template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
	assert (size_ > 0);
	--size_;
	iterator result(itr);
	result++;
	// Special case: after erasing, the list becomes empty
	if (size_ == 0) {
		delete itr.ptr;
		delete dummy_node;
		chrono_head = chrono_tail = sorted_head = sorted_tail = random_head = NULL;
		dummy_node = NULL;
		return result;
	}
	// Find the position of the node in the chronological, sorted and random order
	iterator itr0(itr.ptr,0);
	iterator itr1(itr.ptr,1);
	iterator itr2(itr.ptr,2);
	// Next we can use these new iterators knowing their types
	// Any one of these three iterators may be the head (tail) in their corresponding order
	// So that we have 5 special cases to check
	// Declare three bools to indicate that the erasing is "normal" (in the middle)
	// in terms of chronological, sorted and random order
	bool isNormal0 = true, isNormal1 = true, isNormal2 = true;
	if (itr0.ptr == chrono_head){
		isNormal0 = false;
		chrono_head = chrono_head->chrono_next;
		chrono_head->chrono_prev = 0;
		
	} else if (itr0.ptr == chrono_tail) {
		isNormal0 = false;
		chrono_tail = chrono_tail->chrono_prev;
		chrono_tail->chrono_next = dummy_node;
		dummy_node->chrono_prev = chrono_tail;
	}
	if (itr1.ptr == sorted_head){
		isNormal1 = false;
		sorted_head = sorted_head->sorted_next;
		sorted_head->sorted_prev = 0;
	} else if (itr1.ptr == sorted_tail) {
		isNormal1 = false;
		sorted_tail = sorted_tail->sorted_prev;
		sorted_tail->sorted_next = dummy_node;
		dummy_node->sorted_prev = sorted_tail;
	}
	if (itr2.ptr == random_head){
		isNormal2 = false;
		// Find the imaginary tail
		Node<T>* random_tail = random_head;
		for (int i = 0; i < size_ - 1; ++i)
			random_tail = random_tail->random_next;
		random_head = random_head->random_next;
		random_tail->random_next = random_head;
	}
	// Normal cases (none of the iterators is pointing to head or tail)
	if (isNormal0) {
		itr0.ptr->chrono_prev->chrono_next = itr0.ptr->chrono_next;
		itr0.ptr->chrono_next->chrono_prev = itr0.ptr->chrono_prev;
	}
	if (isNormal1) {
		itr1.ptr->sorted_prev->sorted_next = itr1.ptr->sorted_next;
		itr1.ptr->sorted_next->sorted_prev = itr1.ptr->sorted_prev;
	}
	if (isNormal2) {
		if (random_head) {
			// Find the prev
			Node<T>* random_prev = itr.ptr;
			for (int i = 0; i < size_ - 1; ++i)
				random_prev = random_prev->random_next;
			random_prev->random_next = itr.ptr->random_next;
		}	
	}
	delete itr.ptr;
	return result;
}

template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>& old) {
	chrono_head = chrono_tail = NULL;
	sorted_head = sorted_tail = NULL;
	random_head = NULL;
	dummy_node = NULL;
	size_=0;
	// special case: empty list
	if (!old.size_)
		return;
	// normal case, add all the nodes one by one to a new list, except the dummy node
	Node<T>* old_p = old.chrono_head;
	while (old_p != old.dummy_node) {
		add(old_p->value);
		old_p = old_p->chrono_next;
	}	
}

template <class T>
void MultiLL<T>::destroy_list() {
	// special case: empty list
	if (size_ == 0) {
		return;
	}
	// normal case: delete all the nodes including dummy node
	MultiLL<T>::iterator itr1(chrono_head,0);
	MultiLL<T>::iterator itr2(chrono_head,0);
	itr2++;
	while (itr2.ptr->chrono_next) {
		delete itr1.ptr;
		itr1 = itr2;
		itr2++;
	}
	delete itr2.ptr;
	size_ = 0;
	chrono_head = chrono_tail = sorted_head = sorted_tail = random_head = dummy_node = 0;
}
#endif