// CSCI 1200 Data Structures
// Homework 5: Multi-Linked Lists


// NOTE: You should not need to make any changes to this file, except
// to add your own test cases at the bottom of the file where
// indicated.


#include <iostream>
#include <cmath>
#include <string>
#include <list>
#include <vector>
#include <cassert>
#include <cstdlib>

#include "multi_linked_list.h"

void ProvidedTests();
void StudentTests();


// ================================================================================
// A simple function to test if two STL lists contain the "same" elements
// returns true if it contains the same number of elements in the same order
// otherwise returns false
template <class T> bool same(const std::list<T> &a, const std::list<T> &b) {
  if (a.size() != b.size()) return false;
  typename std::list<T>::const_iterator a_itr = a.begin();
  typename std::list<T>::const_iterator b_itr = b.begin();
  while (a_itr != a.end()) {
    if (*a_itr != *b_itr) return false;
    a_itr++;
    b_itr++;
  }
  return true;
}



// ================================================================================
// This program stress tests the templated MultiLL container class


int main() {
  ProvidedTests();
  StudentTests();
}


// ================================================================================
// ================================================================================

void ProvidedTests() {

  std::cout << "Begin ProvidedTests..." << std::endl;

  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();


  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
	  my_list.add(*itr);
  }
  assert (songs.size() == my_list.size());



  // -------------------
  // iterator tests

  // test the chronological iterator (forwards)
  std::cout << "chronological order" << std::endl;
  std::list<std::string> chrono_order;
  MultiLL<std::string>::iterator itr = my_list.begin_chronological();
  while (itr != my_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    chrono_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,chrono_order));

  // test the sorted order iterator (forwards)
  std::cout << "sorted order" << std::endl;
  std::list<std::string> sorted_order;
  itr = my_list.begin_sorted();
  while (itr != my_list.end_sorted()) {
	std::cout << "  " << *itr << std::endl;
    sorted_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(sorted_songs,sorted_order));
 
  
  // test the random order iterator
  std::cout << "random order" << std::endl;
  std::list<std::string> random_order;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order.push_back(*itr);
  }
  std::cout << std::endl;
  // loop through the elements a second time (the order should be the same!)
  std::list<std::string>::iterator itr2 = random_order.begin();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++,itr2++) {
	std::cout << *itr << "  " << *itr2 << std::endl;  
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements appeared in the initial loop
  assert (same(sorted_songs,random_order_check));

  // test the re-randomization by creating a new random iterator
  std::cout << "random order 2" << std::endl;
  std::list<std::string> random_order2;
  itr = my_list.begin_random();
  for (unsigned int i = 0; i < my_list.size(); i++,itr++) {
    std::cout << "  " << *itr << std::endl;
    random_order2.push_back(*itr);
  }
  std::cout << std::endl;
  // with over 3 million different possible permutations of 10
  // elements, it is highly unlikely they will be the same!
  assert (!same(random_order,random_order2));
  
  // -------------------
  // erase tests

  // erase the first element inserted
  itr = my_list.begin_chronological();
  assert (*itr == "hound dog");
  itr = my_list.erase(itr);
  assert (*itr == "poker face");
  assert (my_list.size() == 9);
  std::cout << "erased: hound dog" << std::endl;

  // erase the second to last element in sorted order
  itr = my_list.begin_sorted();
  for (int i = 0; i < 7; i++) { itr++; }
  assert (*itr == "stairway to heaven");
  itr = my_list.erase(itr);
  assert (*itr == "walk like an egyptian");
  assert (my_list.size() == 8);  
  std::cout << "erased: stairway to heaven" << std::endl;

  // erase the third element in the random order
  itr = my_list.begin_random();
  itr++;
  itr++;
  std::string tmp = *itr;
  // note that the return value of erase with a random iterator is undefined
  my_list.erase(itr);
  std::cout << "erased: " << tmp << std::endl;
  assert (my_list.size() == 7);
  assert (!my_list.empty());
  
  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  std::cout << "cleared the whole list!" << std::endl << std::endl;

  std::cout << "Finished ProvidedTests." << std::endl << std::endl;
}

// ================================================================================
// ================================================================================

void StudentTests() {

  std::cout << "Begin StudentTests..." << std::endl;
  
  // The test data (stored in STL lists)
  std::list<std::string> songs;
  songs.push_back("hound dog");
  songs.push_back("poker face");
  songs.push_back("brown eyed girl");
  songs.push_back("let it be");
  songs.push_back("walk like an egyptian");
  songs.push_back("man in the mirror");
  songs.push_back("stairway to heaven");
  songs.push_back("dancing in the street");
  songs.push_back("every breath you take");
  songs.push_back("hotel california");
  // the same data, sorted!
  std::list<std::string> sorted_songs(songs);
  sorted_songs.sort();
  // ========================================================================================
  
  // COPY CONSTRUCTOR
  std::cout << "Test copy constructor..." << std::endl;
  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin(); itr != songs.end(); itr++) {
	  my_list.add(*itr);
  }
  // copy the MultiLL
  MultiLL<std::string> clone_list(my_list);
  // assert they have the same sizes
  assert(clone_list.size() == my_list.size());
  // check if the clone of MultiLL is the same as the test data
  // check the chronological order
  MultiLL<std::string>::iterator my_itr1 = my_list.begin_chronological();
  MultiLL<std::string>::iterator my_itr2 = clone_list.begin_chronological();
  std::cout << "Checkpoint1: the chronological order\n";
  for (int i = 0; i < my_list.size(); ++i) {
	 std::cout << *my_itr1 << " <----------> " << *my_itr2 << std::endl;
	 assert(*my_itr1 == *my_itr2);
	 ++my_itr1;
	 ++my_itr2;
  }
  std::cout << std::endl;
  // check the sorted order
  std::cout << "Checkpoint2: the sorted order\n";
  my_itr1 = my_list.begin_sorted();
  my_itr2 = clone_list.begin_sorted();
  for (int i = 0; i < my_list.size(); ++i) {
	 std::cout << *my_itr1 << " <----------> " << *my_itr2 << std::endl;
	 assert(*my_itr1 == *my_itr2);
	 ++my_itr1;
	 ++my_itr2;
  }
  // random order is not copied, therefore no need to test random order
  std::cout << std::endl;
  // ========================================================================================
  
  // ASSIGNMENT OPERATOR
  std::cout << "Test assignment operator..." << std::endl;
  MultiLL<std::string> assign_list = my_list;
  // assert they have the same sizes
  assert(assign_list.size() == my_list.size());
  std::cout << "Checkpoint1: the chronological order\n";
  my_itr1 = my_list.begin_chronological();
  my_itr2 = assign_list.begin_chronological();
  for (int i = 0; i < my_list.size(); ++i) {
	 std::cout << *my_itr1 << " <----------> " << *my_itr2 << std::endl;
	 assert(*my_itr1 == *my_itr2);
	 ++my_itr1;
	 ++my_itr2;
  }
  std::cout << std::endl;
  // check the sorted order
  std::cout << "Checkpoint2: the sorted order\n";
  my_itr1 = my_list.begin_sorted();
  my_itr2 = clone_list.begin_sorted();
  for (int i = 0; i < my_list.size(); ++i) {
	 std::cout << *my_itr1 << " <----------> " << *my_itr2 << std::endl;
	 assert(*my_itr1 == *my_itr2);
	 ++my_itr1;
	 ++my_itr2;
  }
  // random order is not copied, therefore no need to test random order
  std::cout << std::endl;
  // ========================================================================================
  
  // DESTRUCTOR
  std::cout << "Test destructor...\n";
  my_list.clear();
  assert (my_list.empty());
  assert (my_list.size() == 0);
  // at this point, clone_list should be fine
  assert (!clone_list.empty());
  assert (clone_list.size());
  clone_list.clear();
  assert (clone_list.empty());
  assert (clone_list.size() == 0);
  // at this point, assign_list should be fine
  assert (!assign_list.empty());
  assert (assign_list.size());
  assign_list.clear();
  assert (assign_list.empty());
  assert (assign_list.size() == 0);
  std::cout << std::endl;
  // ========================================================================================
  
  // ALL CORNER CASES OF ERASE
  std::cout << "Test all corner cases of erase..." << std::endl;
  // Initially only one node
  std::cout << "Checkpoint1: List with only one node\n";
  std::list<std::string>::iterator itr_songs = songs.begin();
  my_list.add(*itr_songs);
  clone_list.add(*itr_songs);
  assign_list.add(*itr_songs);
  MultiLL<std::string>::iterator itr0 = my_list.begin_chronological();
  MultiLL<std::string>::iterator itr1 = clone_list.begin_sorted();
  MultiLL<std::string>::iterator itr2 = assign_list.begin_random();
  // use three different ways to remove 
  itr0 = my_list.erase(itr0);
  itr1 = clone_list.erase(itr1);
  itr2 = assign_list.erase(itr2);
  assert (my_list.empty());
  assert (clone_list.empty());
  assert (assign_list.empty());
  std::cout << std::endl;
  // Initially two nodes, remove the head
  std::cout << "Checkpoint1: List with two nodes, erase the head\n";
  for (int i = 0; i < 2; ++i, ++itr_songs) {
	  my_list.add(*itr_songs);
	  clone_list.add(*itr_songs);
	  assign_list.add(*itr_songs);
  }
  itr0 = my_list.begin_chronological();
  itr1 = clone_list.begin_sorted();
  itr2 = assign_list.begin_random();
  itr0 = my_list.erase(itr0);
  itr1 = clone_list.erase(itr1);
  itr2 = assign_list.erase(itr2);
  assert((my_list.size()==1));
  assert((my_list.size()==1)&&(*itr0 == "poker face"));
  assert((clone_list.size()==1)&&(*itr0 == "poker face"));
  assert(assign_list.size()==1);
  my_list.clear();
  clone_list.clear();
  assign_list.clear();
  std::cout << std::endl;
  // Initially two nodes, remove the tail
  std::cout << "Checkpoint2: List with two nodes, erase the tail\n";
  itr_songs = songs.begin();
  for (int i = 0; i < 2; ++i, ++itr_songs) {
	  my_list.add(*itr_songs);
	  clone_list.add(*itr_songs);
	  assign_list.add(*itr_songs);
  }
  itr0 = ++my_list.begin_chronological();
  itr1 = ++clone_list.begin_sorted();
  itr2 = ++assign_list.begin_random();
  itr0 = my_list.erase(itr0);
  itr1 = clone_list.erase(itr1);
  itr2 = assign_list.erase(itr2);
  assert(my_list.size()==1);
  assert(my_list.size()==1);
  assert(clone_list.size()==1);
  assert(assign_list.size()==1);
  my_list.clear();
  clone_list.clear();
  assign_list.clear();
  std::cout << std::endl;
  // ========================================================================================
  
  // DECREMENT OPERATOR FOR THE CHRONOLOGICAL AND SORTED ITERATORS
  std::cout << "Testing decrement operator for the chronological and sorted iterators...\n";
  std::cout << "Checkpoint1: decrement operator for chronological iterator\n";
  itr_songs = songs.begin();
  for (itr_songs = songs.begin(); itr_songs != songs.end(); ++itr_songs) {
	  my_list.add(*itr_songs);
  }
  std::list<std::string>::reverse_iterator r;
  MultiLL<std::string>::iterator itr_r = my_list.end_chronological();
  for (r = songs.rbegin(); r != songs.rend(); r++) {
	  itr_r--;
	  std::cout << *r << " <----------> " << *itr_r << std::endl;
	  assert(*r == *itr_r);
  }
  std::cout << std::endl;
  std::cout << "Checkpoint2: decrement operator for sorted iterator\n";
  itr_r = my_list.end_sorted();
  for (r = sorted_songs.rbegin(); r != sorted_songs.rend(); r++) {
	  itr_r--;
	  std::cout << *r << " <----------> " << *itr_r << std::endl;
	  assert(*r == *itr_r);
  }
  std::cout << std::endl;
  // ========================================================================================
  
  // PRE VS. POST INCREMENT & DECREMENT OPERATIONS FOR ITERATORS
  std::cout << "Testing pre vs. post increment & decrement operations...\n";
  std::cout << "Checkpoint1: pre and post increment/decrement for chronological iterator\n";
  itr0 = my_list.begin_chronological();
  itr2 = ++itr0;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "poker face")&&(*itr2 == "poker face"));
  itr2 = --itr0;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "hound dog")&&(*itr2 == "hound dog"));
  itr0 = my_list.begin_chronological();
  itr2 = itr0++;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "poker face")&&(*itr2 == "hound dog"));
  itr2 = itr0--;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "hound dog")&&(*itr2 == "poker face"));
  std::cout << std::endl;
  
  std::cout << "Checkpoint2: pre and post increment/decrement for sorted iterator\n";
  itr0 = my_list.begin_sorted();
  itr2 = ++itr0;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "dancing in the street")&&(*itr2 == "dancing in the street"));
  itr2 = --itr0;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "brown eyed girl")&&(*itr2 == "brown eyed girl"));
  itr0 = my_list.begin_sorted();
  itr2 = itr0++;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "dancing in the street")&&(*itr2 == "brown eyed girl"));
  itr2 = itr0--;
  std::cout << *itr0 << "  " << *itr2 << std::endl;
  assert((*itr0 == "brown eyed girl")&&(*itr2 == "dancing in the street"));
  std::cout << std::endl;
  // ========================================================================================
  
  //   MultiLL containing types other than std::string
  std::cout << "Testing MultiLL containing integers...\n";
  MultiLL<int> multi_list;
  std::list<int> v;
  v.push_back(8);
  v.push_back(10);
  v.push_back(4);
  v.push_back(3);
  v.push_back(7);
  std::list<int>::iterator itr_v = v.begin();
  for (int i = 0; i < v.size(); ++i) {
	  multi_list.add(*itr_v);
	  itr_v++;
  }
  std::list<int> sorted_v(v);
  sorted_v.sort();
  std::cout << "Checkpoint1: chronological order\n";
  MultiLL<int>::iterator chrono_itr = multi_list.begin_chronological();
  MultiLL<int>::iterator sorted_itr = multi_list.begin_sorted();
  itr_v = v.begin();
  for (;chrono_itr != multi_list.end_chronological(); chrono_itr++, itr_v++) {
	  std::cout << *chrono_itr << std::endl;
	  assert(*chrono_itr == *itr_v);
  }
  std::cout << std::endl;
  
  std::cout << "Checkpoint2: sorted order\n";
  itr_v = sorted_v.begin();
  for (;sorted_itr != multi_list.end_sorted(); sorted_itr++, itr_v++) {
	  std::cout << *sorted_itr << std::endl;
	  assert(*sorted_itr == *itr_v);
  }
  std::cout << std::endl;
  
  std::cout << "Checkpoint3: random order\n";
  // The first two random orders should be the same
  MultiLL<int>::iterator random_itr = multi_list.begin_random();
  std::list<int> temp1, temp2;
  for (int i = 0; i < multi_list.size(); ++i) {
	  std::cout << *random_itr << std::endl;
	  temp1.push_back(*random_itr);
	  random_itr++;
  }
  std::cout << std::endl;
  for (int i = 0; i < multi_list.size(); ++i) {
	  std::cout << *random_itr << std::endl;
	  temp2.push_back(*random_itr);
	  random_itr++;
  }
  assert(same(temp1,temp2));
  std::cout << std::endl;
  // The second two random orders should be different
  random_itr = multi_list.begin_random();
  for (int i = 0; i < multi_list.size(); ++i) {
	  std::cout << *random_itr << std::endl;
	  temp1.push_back(*random_itr);
	  random_itr++;
  }
  std::cout << std::endl;
  random_itr = multi_list.begin_random();
  for (int i = 0; i < multi_list.size(); ++i) {
	  std::cout << *random_itr << std::endl;
	  temp2.push_back(*random_itr);
	  random_itr++;
  }
  assert(!(same(temp1,temp2)));
  std::cout << std::endl;
  // ========================================================================================
  




  std::cout << "Finished StudentTests." << std::endl;
}

// ================================================================================
