#include <iostream>
#include <list>
#include <string>

// ===========================================================================

// A SIMPLE LINKED LIST CLASS
// (note: it's ok that all the member variables are public for this tiny class)

class Node {
public:
  int value;
  Node* ptr;
};


// ===========================================================================

// a helper function to print the contents of a linked list of Nodes
void print_linked_list(const std::string &name, Node *my_linked_list) {
  // print the name of this list
  std::cout << name;
  // use a temporary pointer to walk down the list
  Node *tmp = my_linked_list;
  while (tmp != NULL) {
    // print out each element
    std::cout << " " << tmp->value;
    tmp = tmp->ptr;
  }
  std::cout << std::endl;
}


// YOU NEED TO WRITE THIS FUNCTION
Node* make_linked_list_from_STL_list(const std::list<int> &lst) {
    if (lst.size() == 0) {
    	return NULL;
    } else {
		Node* a = new Node;
		Node* head = a;
		std::list<int>::const_iterator itr = lst.begin();

		for (int n = 0; n < lst.size() - 1; ++n) {
			a->value = *itr;
			a->ptr = new Node;
			a = a->ptr;
			++itr;
		}
		a->value = *itr;
		a->ptr = NULL;
	
		return head;
    }

}


// YOU NEED TO WRITE THIS FUNCTION
Node* reverse_nodes_in_linked_list(Node *input) {
	if (input == NULL) {
		return NULL;
	} else if (input->ptr == NULL) {
		return input;
	} else {
		Node* end = input;
		Node* ptr1 = input;
		Node* ptr2 = input;
		++ptr2;
		while (ptr2->ptr != NULL) {
			ptr2 -> ptr = ptr1;
			ptr1 = ptr2;
			ptr2++;
		
		}
		ptr2 -> ptr = ptr1;
		Node* head = ptr2;
		end->ptr = NULL;
		return head;
	}
	


}


// ===========================================================================

int main() {

  // manually create a linked list of notes with 4 elements
  Node* a = new Node; 
  a->value = 6; 
  a->ptr = new Node;
  a->ptr->value = 7;
  a->ptr->ptr = new Node;
  a->ptr->ptr->value = 8;
  a->ptr->ptr->ptr = new Node;
  a->ptr->ptr->ptr->value = 9;
  a->ptr->ptr->ptr->ptr = NULL;
  // print out this list
  print_linked_list("a",a);

  // create an STL list with 4 elements
  std::list<int> b;
  b.push_back(10);
  b.push_back(11);
  b.push_back(12);
  b.push_back(13);

  // use the STL list as input to a creator function that creates
  // linked lists with the same data
  Node* c = make_linked_list_from_STL_list(b);
  // print that data
  print_linked_list("c",c);

  // WRITE A FEW MORE TEST CASES OF make_linked_list_from_STL_list
  std::cout << "=====TEST CASE: EMPTY LIST======\n";
  std::list<int> bb;
  bb.clear();
  Node* cc = make_linked_list_from_STL_list(bb);
  print_linked_list("cc",cc);
  std::cout << "=====TEST CASE: ONE-ELEMENT LIST======\n";
  bb.push_back(1);
  cc = make_linked_list_from_STL_list(bb);
  print_linked_list("cc",cc);

  // reverse a linked list of nodes
  std::cout << "=======TEST CASE: REVERSING C========\n";
  Node* d = reverse_nodes_in_linked_list(c);
  print_linked_list("d",d);
  
  std::cout << "=======TEST CASE: REVERSING AN EMPTY LIST========\n";
  std::list<int> temp;
  Node* dd = make_linked_list_from_STL_list(temp);
  dd = reverse_nodes_in_linked_list(dd);
  print_linked_list("dd",dd);
  
  std::cout << "=======TEST CASE: REVERSING A ONE-ELEMENT LIST========\n";
  temp.push_back(1);
  dd = make_linked_list_from_STL_list(temp);
  std::cout << "linked list:\n";
  print_linked_list("dd",dd);
  std::cout << "reversed list:\n";
  dd = reverse_nodes_in_linked_list(dd);
  print_linked_list("dd",dd);
  

}

// ===========================================================================
