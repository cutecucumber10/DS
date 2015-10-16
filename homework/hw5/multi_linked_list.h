/*
File name: multi_linked_list.h
Arthor: Xinyue Yan(yanx3)
Purpose: an implementation of a multilinked list
		 The list can be sorted in three orders: 
		 chronological, alphabetical and random.
		 The chronological and alphabetical order
		 is double linked(not circular), the rand
		 -om order is single and circular linked.
		 There is a fake node after every tail_ to
		 access tail from decrementing the one 
		 behind the tail.
*/
#ifndef multi_linked_list_h_
#define multi_linked_list_h_

#include "mtrand.h"

#include <cassert>
#include <iostream>
#include <ctime>
#include <cstdlib>
//Node class------------------------------------------------------
//----------------------------------------------------------------
template <class T>
class Node {
	public:
		//default node....
		Node() : chrono_next(NULL), chrono_prev(NULL), sorted_next(NULL), \
		sorted_prev(NULL), random_next(NULL) {}
		//have value
		Node(const T& v) : value(v), chrono_next(NULL), chrono_prev(NULL), \
		sorted_next(NULL), sorted_prev(NULL), random_next(NULL) {}

		//representation 
		T value;
		Node<T>* chrono_next;
		Node<T>* chrono_prev;
		Node<T>* sorted_next;
		Node<T>* sorted_prev;
		Node<T>* random_next;
};

// A "forward declaration" of this class is needed
template <class T> class MultiLL;


// LIST ITERATOR----------------------------------------------------
// -----------------------------------------------------------------
template <class T>
class list_iterator {
	public:
		// default constructor, copy constructor, assignment operator, & destructor
		list_iterator() : ptr_(NULL) {}
		list_iterator(Node<T>* p, int order) : ptr_(p), an_order(order) {} 
		list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_)\
		, an_order(old.an_order) {}
		list_iterator<T>& operator=(const list_iterator<T>& old) {
			ptr_ = old.ptr_;  
			an_order = old.an_order;
			return *this;
		}
		~list_iterator() {}

		// dereferencing operator gives access to the value at the pointer
		T& operator*()  { return ptr_->value;  }

		// increment & decrement operators
		//pre-increment; ++itr...
		//return itr+1
		//1 means chronological order
		//2 means sort(alphabetical) order
		//3 means random order
		list_iterator<T>& operator++() { 
			if (an_order == 1) {
				ptr_ = ptr_ -> chrono_next;
				return *this;
			}
			else if (an_order == 2) {
				ptr_ = ptr_ -> sorted_next;
				return *this;
			}
			else if (an_order == 3) {
				ptr_ = ptr_ -> random_next;
				return *this;
			}
		}
		//post-increment e.g itr++
		//return itr
		list_iterator<T> operator++(int) {
			if (an_order == 1) {
				list_iterator<T> temp(*this);
				ptr_ = ptr_ -> chrono_next;
				return temp;
			}
			else if (an_order == 2) {
				list_iterator<T> temp(*this);
				ptr_ = ptr_ -> sorted_next;
				return temp;
			}
			else if (an_order == 3) {
				list_iterator<T> temp(*this);
				ptr_ = ptr_ -> random_next;
				return temp;
			}
		}
		//Random iterator does not support decrement 
		//because it is single linked list....
		//pre-decrement --itr
		list_iterator<T>& operator--() {
			if (an_order == 1) {
				ptr_ = ptr_ -> chrono_prev;
				return *this;
			}
			else if (an_order == 2) {
				ptr_ = ptr_ -> sorted_prev;
				return *this;
			}
			else if (an_order == 3) {
				std::cerr << "Random order is a single linked list!" << std::endl;
			}
		}
		//post-decrement itr--
		list_iterator<T> operator--(int) {
			if (an_order == 1) {
				list_iterator<T> temp(*this);
				ptr_ = ptr_ -> chrono_prev;
				return temp;
			}
			else if (an_order == 2) {
				list_iterator<T> temp(*this);
				ptr_ = ptr_ -> sorted_prev;
				return temp;
			}
			else if (an_order == 3) {
				std::cerr << "Random order is a single linked list!" << std::endl;
			}
		}
		// the MultiLL class needs access to the private ptr_ member variable
		friend class MultiLL<T>;

		//comparison operators are straightforward
		bool operator==(const list_iterator<T>& r) const {
			return (ptr_ == r.ptr_ && an_order == r.an_order);
		}

		bool operator!=(const list_iterator<T>& r) const {
			return (ptr_ != r.ptr_ || an_order != r.an_order);
		}


	private:
		//ptr to node in the list
		Node<T>* ptr_;
		//a variable set depends on which iterator
		int an_order;


};

template <class T>
class MultiLL {
	public:
		// default constructor, copy constructor, assignment operator, & destructor
		MultiLL(): chrono_head(NULL), chrono_tail(NULL), sorted_head(NULL)\
		, sorted_tail(NULL), random_head(NULL), end(NULL), size_(0) {}
		MultiLL(const MultiLL<T>& old) { this->copy_list(old); }
		MultiLL& operator= (const MultiLL<T>& old); 
		~MultiLL() { this->destroy_list(); }

		// simple accessors & modifiers
		unsigned int size() const { return size_; }
		bool empty() const { return (chrono_head == NULL && \
			sorted_head == NULL && random_head == NULL); }
		void clear() { this->destroy_list(); }
		void print_chrono();
		void print_sort();
		void print_random();

		//different types of iterators...
		typedef list_iterator<T> iterator;
		//main functions...
		iterator erase(iterator itr);
		iterator add(const T& v);
		//initialize each of the iterator....
		iterator begin_chronological() {return iterator(chrono_head, 1);}
		//not NULL because NULL does not support going back to tail..
		iterator end_chronological() {return iterator(end,1);}
		iterator begin_sorted() {return iterator(sorted_head, 2);}
		//not NULL because NULL does not support going back to tail..
		iterator end_sorted() {return iterator(end, 2);}
		iterator begin_random();

	private:
		void copy_list(const MultiLL<T>& old);
		void destroy_list();
		Node<T>* chrono_head;
		Node<T>* chrono_tail;
		Node<T>* sorted_head;
		Node<T>* sorted_tail;
		Node<T>* random_head;
		//a pointer to accesss the one past tail
		Node<T>* end;
		unsigned int size_;

};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
//put inside the begin_random will result produce same order every time
MTRand_int32 mtrand_autoseed(time(NULL));
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::begin_random() {
	//every time call begin_random the random list will be relinked
	//for every nodes
	//use chronological order
	//to find the generating numbers' corresponding position
	//if the size is 0, no need to generate random number
	if (size_ == 0) {
		random_head = NULL;
	}
	//else if the size is one, just link the only one elements's next
	//to itself
	else if (size_ == 1) {
		typename MultiLL<T>::iterator only_one = begin_chronological();
		random_head = only_one.ptr_;
		random_head -> random_next = random_head;
	}
	//else
	//the situation might be complex...
	else {
		//create an array with regular numbers of each node's position
		//in chronological order.....
		int arr[size_];	
		for (int i = 0; i < size_; ++i ) { 
			arr[i] = i; 
		}
		//generate unique random number
		//use modified Fisher-Yates algorithm
		//the explanation comes from a page on stackoverflow
		//provided in readme source 
		//MTRand_int32 mtrand_autoseed(time(NULL));
		for (int i = size_ -1; i >= 0 ; --i ) {
			//create a random number using mtrand
			int r = mtrand_autoseed() % (size_);
			int temp = i;
			//find the index of max number i, which is j;
			int j = 0;
			for (j; j < size_; ++j) {
				if (arr[j] == i) 
					break;
			}
			//swap the position of [j] and [r]
			arr[j] = arr[r];
			arr[r] = temp;
			//the total number of swap will be size-1;
		}
		for (int i = 0; i < size_ - 1 ; ++i ) {
			//find two nodes.....of position arr[i] in chronological order 
			//and postion arr[i+1] in chronological, and link them together	
			int count = 0;
			//arr[j] is the one next to arr[i]
			int j = i+1;
			//the iterator of arr[i];
			typename MultiLL<T>::iterator chronos = begin_chronological();
			//the iterator of arr[j];
			typename MultiLL<T>::iterator chronos_ne  = begin_chronological();
			for (chronos; chronos != end_chronological(); ++chronos) {
				if (count == arr[i]) {
					break;
				}
				count++;
			}
			int count2 = 0;
			for (chronos_ne; chronos_ne != end_chronological(); ++chronos_ne) {
				if (count2 == arr[j]) {
					break;
				}
				count2++;
			}
			//set the first found iterator based on the array to the random_head
			if (i == 0) {
				random_head = chronos.ptr_;
			}
			//link the two
			chronos.ptr_ -> random_next = chronos_ne.ptr_;
		}

		//find the last one to connect its next to head...
		//because we did not loop to the last one just now
		//we just loop to the one before last one 
		//and set the one before last one's next to the last one
		typename MultiLL<T>::iterator chronos_last = begin_chronological();
		//count for count position, for matching arr[-1];
		int count_last = 0;
		for (chronos_last; chronos_last != end_chronological(); ++chronos_last) {
			if (count_last == arr[size_-1]) {
				break;
			}
			count_last++;
		}
		//link the last one to the first one to be circular
		chronos_last.ptr_ -> random_next = random_head; 
	}
	return iterator(random_head, 3);

} 


template <class T>
void MultiLL<T>::copy_list(const MultiLL<T>& old) {
	Node<T>* current = old.chrono_head;
	//set all the nodes to NULL, size to zero
	chrono_head = chrono_tail = NULL;
	sorted_head = sorted_tail = NULL;
	random_head = NULL;
	end = NULL;
	size_ = 0;
	//add from old list one by one....
	//no need to worry about the fake point
	//the loop is based on size
	//it will not go to that point....
	for (int i = 0; i < old.size(); ++i) {
		add(current -> value);
		current = current -> chrono_next;
	}

}

template <class T>
void MultiLL<T>::destroy_list() {
	//loop over chronological 
	if (size_ == 0) {
	}
	else {
		//set a current
		Node<T>* current = chrono_head;
		//move the pointer one by one...
		//this will also delete the fake 
		//pointer.....
		while (current != NULL) {
			//a temporary pointer to delete memory
			//current moves.
			Node<T>* temp = current;
			current = current -> chrono_next;
			//std::cout <<temp -> value<<std::endl;
			delete temp;
		}
	}
	//make sure!
	size_ = 0;
	chrono_head = chrono_tail = NULL;
	sorted_head = sorted_tail = NULL;
	random_head = NULL;
	end = NULL;
}

//ease for print out....
template <class T>
void MultiLL<T>::print_chrono() {
	for (typename MultiLL<T>::iterator chrono = begin_chronological(); \
		chrono != end_chronological(); ++chrono) {
		std::cout << *chrono << std::endl;
	}
}

template <class T>
void MultiLL<T>::print_sort() {
	for (typename MultiLL<T>::iterator sorting = begin_sorted(); \
		sorting != end_sorted(); ++sorting) {
		std::cout << *sorting << std::endl;
	}
}

template <class T>
void MultiLL<T>::print_random() {
	typename MultiLL<T>::iterator rands = begin_random();
	for (unsigned int i = 0; i < size_ ; i++, rands++ ) {
		std::cout << *rands << std::endl;
	}
}


//assignment operator
template <class T> 
MultiLL<T>& MultiLL<T>::operator= (const MultiLL<T>& old) {
	//check for self-assignment
	if (&old != this) {
		this -> destroy_list();
		this -> copy_list(old);
	}
	return *this;
}

//erase function
template <class T>
typename MultiLL<T>::iterator MultiLL<T>::erase(iterator itr) {
	Node<T>* temp;
	//temp is the one needed to be return....later on
	//but we will first delete itr before return.
	if (size_ == 1) {
		//will an empty list
		//delete the pointer and set everything to NULL
		delete itr.ptr_;
		chrono_head = chrono_tail = NULL;
		sorted_head = sorted_tail = NULL;
		random_head = NULL;
		//the end is also a memory in heap
		//it is create when add first item in the list
		//also need to be deleted....
		delete end;
		//set end to NULL
		end = NULL;
		//decrease size
		size_--;
		//return different type of iterator......
		return iterator(end,itr.an_order);
	}
	//no way to erase sth from an empty list
	//it must be an error
	else if (size_ == 0) {
		std::cerr << "There is only zero items in the list!\n";
	}
	//third situation, normal case......
	else {
		if (itr.an_order == 1) {
			//if the item is the first item in chronological order..
			if (itr.ptr_ == chrono_head) {
				//return the iterator of the second item
				temp = chrono_head -> chrono_next;
				chrono_head = chrono_head -> chrono_next;
				chrono_head -> chrono_prev = NULL;
			}
			//if the item the last item in chronological order...
			//reset the tail and relink tail and end;
			else if (itr.ptr_ == chrono_tail) {
				//return NULL, no more items behind the last one
				temp = chrono_tail -> chrono_next;
				//reset tail
				chrono_tail = chrono_tail -> chrono_prev;
				//relink
				chrono_tail -> chrono_next = end;
				end -> chrono_prev = chrono_tail;
			}
			//normal case
			else {
				//return the one after the erase one....
				temp = itr.ptr_ -> chrono_next;
				itr.ptr_ -> chrono_prev -> chrono_next = itr.ptr_ -> chrono_next;
				itr.ptr_ -> chrono_next -> chrono_prev = itr.ptr_ -> chrono_prev;
				}
			//check if the item in alphebetical order 
			//is the last one or the first one...
			//this case no return, because the iterator 
			//is not about sort iterator....
			//though differnet iterators, the node is the same one....
			//if it is the last one in sort order..
			if (itr.ptr_ == sorted_tail) {
				//reset the tail
				sorted_tail = sorted_tail -> sorted_prev;
				//relink the tail and sort....
				sorted_tail -> sorted_next = end;
				end -> sorted_prev = sorted_tail;
			}
			else if (itr.ptr_  == sorted_head ) {
				sorted_head = sorted_head -> sorted_next;
				sorted_head -> sorted_prev = NULL;
			}
			//if not, rearrange the pointers...
			else {
				itr.ptr_ -> sorted_prev -> sorted_next = itr.ptr_ -> sorted_next;
				itr.ptr_ -> sorted_next -> sorted_prev = itr.ptr_ -> sorted_prev;
			}
			//delete memory..
			delete itr.ptr_;
			//decrease the size
			--size_;
			//return temp....
			return iterator(temp,1);
		}
		//if the iterator is sort iterator...
		else if (itr.an_order ==2) {
			//if it is the first in sort order....
			if (itr.ptr_ == sorted_head) {
				temp = sorted_head -> sorted_next;
				sorted_head = sorted_head -> sorted_next;
				sorted_head -> sorted_prev = NULL;
			}
			//if it is the last in sort order
			else if (itr.ptr_ == sorted_tail) {
				temp = sorted_tail -> sorted_next;
				//reset tail
				sorted_tail = sorted_tail -> sorted_prev;
				//relink the fake point
				sorted_tail -> sorted_next = end;
				end -> sorted_prev = sorted_tail;
			}
			//normal case
			else {
				temp = itr.ptr_ -> sorted_next;
				itr.ptr_ -> sorted_prev -> sorted_next = itr.ptr_ -> sorted_next;
				itr.ptr_ -> sorted_next -> sorted_prev = itr.ptr_ -> sorted_prev;
			}
			//if it is the last one....
			if (itr.ptr_  == chrono_tail ) {
				//reset
				chrono_tail = chrono_tail -> chrono_prev;
				//relink....
				chrono_tail -> chrono_next = end;
				end -> chrono_prev = chrono_tail;
			}
			//if it is first one....
			else if (itr.ptr_  == chrono_head ) {
				chrono_head = chrono_head -> chrono_next;
				chrono_head -> chrono_prev = NULL;
			}
			//if not, rearrange the prev and next pointers....
			else {
				itr.ptr_ -> chrono_prev -> chrono_next = itr.ptr_ -> chrono_next;
				itr.ptr_ -> chrono_next -> chrono_prev = itr.ptr_ -> chrono_prev;
			}
			//delete memory 
			delete itr.ptr_;
			//decrease size
			--size_;
			//return iterator....
			return iterator(temp,2);
		}
		//if it is a random iterator
		//random iterator is kind of differnt than other two
		//we do not need to search the random list to delete
		//the iterator
		//because everytime we use begin_random(), the itr will
		//change, and everything will relink and reallocated.
		//we just use the provided itr's ptr_ to delete and relink
		//in chronological and sort order....
		else if (itr.an_order ==3) {

			temp = itr.ptr_ -> random_next;
			//check if there is corner case in chronological order
			//if it is the last one in chronological order...
			if (itr.ptr_ == chrono_tail) {
				//reset tail
				chrono_tail = chrono_tail -> chrono_prev;
				//relink tail and end...
				chrono_tail -> chrono_next = end;
				end -> chrono_prev = chrono_tail;
			}
			//if it is the first one in chronological order...
			else if (itr.ptr_ == chrono_head) {
				chrono_head = chrono_head -> chrono_next;
				chrono_head -> chrono_prev = NULL;
			}
			//normal case... in the middle of the list...
			else {
				itr.ptr_ -> chrono_prev -> chrono_next = itr.ptr_ -> chrono_next;
				itr.ptr_ -> chrono_next -> chrono_prev = itr.ptr_ -> chrono_prev;
			}
			//check if there is corner case in sort order
			//if it is last one in sort order
			if (itr.ptr_ == sorted_tail) {
				//reset the tail
				sorted_tail = sorted_tail -> sorted_prev;
				//relink the tail
				sorted_tail -> sorted_next = end;
				end -> sorted_prev = sorted_tail;
			}
			//if it is first one in sort order
			else if (itr.ptr_ == sorted_head) {
				sorted_head = sorted_head -> sorted_next;
				sorted_head -> sorted_prev = NULL;
			}
			//normal case
			else {
				itr.ptr_ -> sorted_prev -> sorted_next = itr.ptr_ -> sorted_next;
				itr.ptr_ -> sorted_next -> sorted_prev = itr.ptr_ -> sorted_prev;
			}
			//delete the memory since we already changed all 
			//the pointers need to change..
			delete itr.ptr_;
			//decrease size
			--size_;
			//return iterator
			return iterator(temp,3);
		}
	}
}


template <class T>
typename MultiLL<T>::iterator MultiLL<T>::add(const T& v) {
	//push back.....in chronological order
	//need insert between the end node and tail...
	//create a new node to store the value
	Node<T> *temp = new Node<T>(v);
	//normal case, that the list is not a empty list
	if (size_ > 0) {
		//tail reset will be written at the last of the function
		//since no matter it is empty or not
		//the add node will always be the tail of the chrono

		//link temp's prev and next
		temp -> chrono_prev = chrono_tail;
		temp -> chrono_next = end;
		//relink end prev
		end -> chrono_prev = temp;
		//relink tail
		chrono_tail -> chrono_next = temp;
		end -> chrono_next = NULL;

		//loop over the sort lists...
		//find the iterator of insert..
		bool last_alphabet = true;	
		bool first_alphabet = false;	
		typename MultiLL<T>::iterator sorting = begin_sorted();
		for (sorting; sorting != end_sorted(); ++sorting) {
			if ((sorting.ptr_ -> value) > (temp ->value)) {
				if (sorting == begin_sorted()) 
					first_alphabet = true;
				last_alphabet = false;
				break;
			} 
		}
		//if last one in the sort lists, push back
		//if it should be last one of the sort list
		//insert the item between end and tail....
		if (last_alphabet == true) {
			//link the temp
			temp -> sorted_next = end;
			temp -> sorted_prev = sorted_tail;
			sorted_tail -> sorted_next = temp;
			//relink temp
			end -> sorted_prev = temp;
			end -> sorted_next = NULL;
			//reset sort tail
			sorted_tail = temp;
		}
		//if the first in the sort list
		else if (first_alphabet == true) {
			temp -> sorted_next = sorted_head;
			sorted_head -> sorted_prev = temp;
			sorted_head = temp;
		}
		//else, change the pointer points....
		else {
			//point add item's sort prev to the one before sorting
			temp -> sorted_prev = sorting.ptr_ -> sorted_prev;
			//point add item;s sort next to sorting....
			temp -> sorted_next = sorting.ptr_;
			//point sort prev's next to new item...
			(sorting.ptr_ -> sorted_prev) -> sorted_next = temp;
			//point sorting's sort prev to new item...
			sorting.ptr_ -> sorted_prev = temp;
		}
	}
	else {
		//create a new node in heap while it is an empty list....
		//once first element add to the list
		//create a fake node(end)
		end = new Node<T>;
		//set head and head
		chrono_head = temp;
		sorted_head = temp;
		//link temp
		temp -> chrono_next = end;
		temp -> sorted_next = end;
		//link tails
		end -> chrono_prev = temp;
		end -> sorted_prev = temp;
		//set sort tail
		sorted_tail = temp;
	}
	//set the tail of chrono as mentioned before
	chrono_tail = temp;
	//increase size
	++size_;
}

#endif