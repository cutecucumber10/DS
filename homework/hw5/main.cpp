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
    // verify that the elements repeat the order
    assert (*itr == *itr2);
  }
  std::list<std::string> random_order_check(random_order);
  random_order_check.sort();
  // verify that all of the elements acheared in the initial loop
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

  std::cout << "Finished ProvidedTests." << std::endl;

  
}

// ================================================================================
// ================================================================================

void StudentTests() {

  std::cout << "Begin StudentTests..." << std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout << "\n";

  //--------------------------------------------------------------
  // ADD YOUR OWN TEST CASES BELOW
  //--------------------------------------------------------------
  //   copy constructor
  std::cout << "Begin copy constructor test...\n";
  std::cout<<"----------------------------------------------------"<<std::endl;
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
  std::cout << "Copy my_list from STL list \
  songs chronological order: " << std::endl;
  MultiLL<std::string> my_list;
  for (std::list<std::string>::iterator itr = songs.begin()\
    ; itr != songs.end(); itr++) {
    my_list.add(*itr);
  }
  std::cout << "Copy new_list(my_list):" << std::endl;
  MultiLL<std::string> new_list(my_list);
  assert (new_list.size() == my_list.size());
  //test if the new list has the same elements as my list...
  std::list<std::string> new_order;
  std::cout<< "print out new list...\n";
  MultiLL<std::string>::iterator itr = new_list.begin_chronological();
  while (itr != new_list.end_chronological()) {
    std::cout << "  " << *itr << std::endl;
    new_order.push_back(*itr);
    itr++;
  }
  std::cout << std::endl;
  assert (same(songs,new_order));
  std::cout<<"\n\n";

  //--------------------------------------------------------------
  //   assignment operator
  std::cout<<"Begin assignment operator test: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::list<std::string> songs2;
  std::cout << "Create a new STL list songs and \
  add it to my_list2 " << std::endl;
  songs2.push_back("life is like a boat");
  songs2.push_back("turnin'");
  songs2.push_back("una thurman");
  songs2.push_back("bare min");
  songs2.push_back("fa va bra");
  songs2.push_back("reality");
  songs2.push_back("shine");
  songs2.push_back("juliet");
  songs2.push_back("with you");
  songs2.push_back("when can i see you again");
  songs2.push_back("dragon night");
  std::list<std::string> sorted_songs2(songs2);
  sorted_songs2.sort();
  // create an empty multi-linked list and fill it with the test data
  MultiLL<std::string> my_list2;
  for (std::list<std::string>::iterator itr = songs2.begin(); \
    itr != songs2.end(); itr++) {
    my_list2.add(*itr);
  }
  std::cout << "Make my_list = my_list2: " << std::endl;
  my_list = my_list2;
  assert (my_list.size() == my_list2.size());
  std::list<std::string> new_my_list;
  std::cout << "Print out my_list in chronological order: " << std::endl;
  MultiLL<std::string>::iterator itr2 = my_list.begin_chronological();
  while (itr2 != my_list.end_chronological()) {
    std::cout << "  " << *itr2 << std::endl;
    new_my_list.push_back(*itr2);
    itr2++;
  }


  //--------------------------------------------------------------
  //   destructor
  std::cout<<"\n\n";
  std::cout<<"Begin destructor test: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout << "destruct the precious new_list! " << std::endl;
  new_list.clear();
  assert (new_list.empty());
  assert (new_list.size() == 0);
  std::cout << "cleared the new list!" << std::endl << std::endl;
  //
  //--------------------------------------------------------------
  //   all corner cases of erase
  std::cout<<"\n\n";
  std::cout<<"Begin erase corner case test: "<<std::endl;
  //first it is a list with only one element
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"1. A list with only one item:  "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> one_item;
  one_item.add("colgando en tus manos");
  assert (one_item.size() == 1);
  MultiLL<std::string>::iterator one_chrono = one_item.begin_chronological();
  std::cout<<"a. erased by chronological iterator: "<< *one_chrono << std::endl;
  one_item.erase(one_chrono);
  assert (one_item.size() == 0);
  one_item.add("secrets");
  assert (one_item.size() == 1);
  MultiLL<std::string>::iterator one_sort = one_item.begin_sorted();
  std::cout<<"b. erased by sort iterator: " << *one_sort << std::endl;
  one_item.erase(one_sort);
  assert (one_item.size() == 0);
  one_item.add("one's scope");
  assert (one_item.size() == 1);
  MultiLL<std::string>::iterator one_random = one_item.begin_random();
  std::cout<<"c. erased by random iterator: " << *one_random << std::endl;
  one_item.erase(one_random);
  assert (one_item.size() == 0);
  one_item.clear();
  assert (one_item.empty());
  assert (one_item.size() == 0);
  std::cout<<"list for test list with only one item cleared!"<<std::endl;



  //create a new list containing three elements..good for corner test case
  //there must be the case of being the first one or last one
  //and also can check the order...
  //both for iterators 
  MultiLL<std::string> c_tri_item;
  c_tri_item.add("rpg");
  c_tri_item.add("alejate de mi");
  c_tri_item.add("pigments");
  assert (c_tri_item.size()==3);
  //use chronological iterator
  std::cout << std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"2. The item is erased using chronological iterator: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  //the first in chronological order
  std::cout<<"a. the item is the first in chronological order "<<std::endl;
  MultiLL<std::string>::iterator c_first_add = c_tri_item.begin_chronological();
  std::cout<<"      erased : " << *c_first_add << std::endl;
  c_tri_item.erase(c_first_add);
  assert (c_tri_item.size() == 2 );


  c_tri_item.add("data structures");
  assert (c_tri_item.size() == 3 );
  //the last in chronological order

  std::cout<<"b. the item is the last in chronological order "<<std::endl;
  MultiLL<std::string>::iterator c_last_add = c_tri_item.begin_chronological();
  c_last_add++;
  c_last_add++;
  std::cout<<"      erased : " << *c_last_add << std::endl;
  c_tri_item.erase(c_last_add);
  assert (c_tri_item.size() == 2 );


  //it is the first in sort order
  std::cout<<"c. the item is the first in sort order \
but using chronological iterator "<<std::endl;
  c_tri_item.add("dragon night");
  assert (c_tri_item.size() == 3 );
  //the first in sort is adejate de mi
  //the iterator is begin_chronological()
  MultiLL<std::string>::iterator c_first_sort = c_tri_item.begin_chronological();
  std::cout<<"      erased : " << *c_first_sort << std::endl;
  c_tri_item.erase(c_first_sort);
  assert (c_tri_item.size() == 2);


  //it is the last in sort order
  std::cout<<"d. the item is the last in sort order \
but using chronological iterator "<<std::endl;
  c_tri_item.add("sunny everyday");
  assert (c_tri_item.size() == 3 );
  //the last sort is sunny everyday
  //the iterator for it is the tail of the chronological order....
  MultiLL<std::string>::iterator c_last_sort = c_tri_item.begin_chronological();
  c_last_sort++;
  c_last_sort++;
  std::cout<<"      erased : " << *c_last_sort << std::endl;
  c_tri_item.erase(c_last_sort);
  assert (c_tri_item.size() == 2);

  c_tri_item.clear();
  assert (c_tri_item.empty());
  assert (c_tri_item.size() == 0);
  std::cout<<"list for test chronological iterator corner case cleared!"<<\
  std::endl;
  std::cout << std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  //use sort iterator
  std::cout<<"3. The item is erased using sort iterator: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> s_tri_item;
  s_tri_item.add("lupinus");
  s_tri_item.add("binary");
  s_tri_item.add("calc");
  assert (s_tri_item.size() == 3 );
  //the first in sort order
  std::cout<<"a. the item is the first in sort order "<<std::endl;
  MultiLL<std::string>::iterator s_first_sort = s_tri_item.begin_sorted();
  std::cout<<"      erased : " << *s_first_sort << std::endl;
  s_tri_item.erase(s_first_sort);
  assert (s_tri_item.size() == 2);

  s_tri_item.add("future fish");
  assert (s_tri_item.size() == 3 );
  //the last in sort order
  std::cout<<"b. the item is the last in sort order "<<std::endl;
  MultiLL<std::string>::iterator s_last_sort = s_tri_item.begin_sorted();
  s_last_sort++;
  s_last_sort++;
  std::cout<<"      erased : " << *s_last_sort << std::endl;
  s_tri_item.erase(s_last_sort);
  assert (s_tri_item.size() == 2);

  s_tri_item.add("ah yeah");
  assert (s_tri_item.size() == 3);
  //it is the first in chronological order
  std::cout<<"c. the item is the first in chronological order \
but use sort iterator "<<std::endl;
  MultiLL<std::string>::iterator s_first_add = s_tri_item.begin_sorted();
  s_first_add++;
  std::cout<<"      erased : " << *s_first_add << std::endl;
  s_tri_item.erase(s_first_add);
  assert (s_tri_item.size() == 2);

  s_tri_item.add("drama grand prix");
  assert (s_tri_item.size() == 3 );
  //it is the last in chronological order
  std::cout<<"d. the item is the last in chronological order \
but use sort iterator "<<std::endl;
  MultiLL<std::string>::iterator s_last_add = s_tri_item.begin_sorted();
  s_last_add++;
  std::cout<<"      erased : " << *s_last_add << std::endl;
  s_tri_item.erase(s_last_add);
  assert (s_tri_item.size() == 2);
  s_tri_item.clear();
  assert (s_tri_item.empty());
  assert (s_tri_item.size() == 0);
  std::cout<<"list for test sort iterator corner case cleared!"<<std::endl;

  //--------------------------------------------------------------
  //   decrement operator for the chronological & sorted iterators
  std::cout<<"\n\n";
  std::cout<<"Begin decrement operator for the chronological & sorted \
iterators test: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"Using decrement to print reverser order of chronological \
and sort...\n";
  //create a new multiLL first
  //include 10 items..
  MultiLL<std::string> decre_test;
  decre_test.add("computer science 1");
  decre_test.add("world on display");
  decre_test.add("calculus");
  decre_test.add("basic drawing");
  decre_test.add("interactive data visualization");
  decre_test.add("give me five");
  decre_test.add("oh it is a test");
  decre_test.add("of decrement iterators");
  decre_test.add("dancings stars on me");
  decre_test.add("lovelive!!");

  std::cout<<"The chronological right order: \n";
  decre_test.print_chrono();
  std::cout<<std::endl;
  std::cout<<"The chronological reverse order: \n";
  MultiLL<std::string>::iterator reve_chrono = decre_test.end_chronological();
  while (reve_chrono!=decre_test.begin_chronological()) {
    reve_chrono--;
    std::cout << *reve_chrono << std::endl;
  }
  std::cout<<std::endl;
  std::cout<<"The sort right order:\n";
  decre_test.print_sort();
  std::cout<<std::endl;
  std::cout<<"The sort reverse order:\n";
  MultiLL<std::string>::iterator reve_sort = decre_test.end_sorted();
  while (reve_sort != decre_test.begin_sorted()) {
    reve_sort--;
    std::cout << *reve_sort << std::endl;
  }
  decre_test.clear();
  std::cout<<"list for test decrement operator for the chronological & \
sorted iterators cleared!"<<std::endl;

  //first print in correct order
  //then print it in reverse order
  //--------------------------------------------------------------
  //   pre vs. post increment & decrement operations for iterators
  std::cout<<"\n\n";
  std::cout<<"Begin pre vs. post increment & decrement operations for \
iterators test: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> pre_post;
  pre_post.add("sage dining hall");
  pre_post.add("commons dining hall");
  pre_post.add("blitman commons");
  std::cout<<"chronological test: \n";
  MultiLL<std::string>::iterator itr_ch = pre_post.begin_chronological();
  std::cout << "Original: "<< *itr_ch << std::endl;
  MultiLL<std::string>::iterator itr2_ch = ++itr_ch;
  assert (*itr2_ch == "commons dining hall");
  std::cout << "Pre increment: "<< *itr2_ch << std::endl;
  MultiLL<std::string>::iterator itr3_ch = itr_ch++;
  assert (*itr3_ch == "commons dining hall");
  std::cout << "Post increment: " << *itr3_ch << std::endl;
  MultiLL<std::string>::iterator itr4_ch = --itr_ch;
  assert (*itr4_ch == "commons dining hall");
  std::cout << "Pre decrement: " << *itr4_ch << std::endl;
  MultiLL<std::string>::iterator itr5_ch = itr_ch--;
  assert (*itr5_ch == "commons dining hall");
  std::cout << "Post decrement: " << *itr5_ch << std::endl;
  std::cout<<"\nsort test: \n";
  MultiLL<std::string>::iterator itr_so = pre_post.begin_chronological();
  std::cout << "Original: "<< *itr_so << std::endl;
  MultiLL<std::string>::iterator itr2_so = ++itr_so;
  assert (*itr2_so == "commons dining hall");
  std::cout << "Pre increment: "<< *itr2_so << std::endl;
  MultiLL<std::string>::iterator itr3_so = itr_so++;
  assert (*itr3_so == "commons dining hall");
  std::cout << "Post increment: " << *itr3_so << std::endl;
  MultiLL<std::string>::iterator itr4_so = --itr_so;
  assert (*itr4_so == "commons dining hall");
  std::cout << "Pre decrement: " << *itr4_so << std::endl;
  MultiLL<std::string>::iterator itr5_so = itr_so--;
  assert (*itr5_so == "commons dining hall");
  std::cout << "Post decrement: " << *itr5_ch << std::endl;
  pre_post.clear();
  std::cout<<"list for test pre vs. post increment & decrement operations \
for iterators cleared!"<<std::endl;


  //--------------------------------------------------------------
  //   MultiLL containing types other than std::string
  std::cout<<"\n\n";
  std::cout<<"Begin MultiLL containing types other than std::string \
test: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"The list of integers: "<<std::endl;
  MultiLL<int> int_list;
  for (unsigned int i = 0; i < 7; ++i) {
    int_list.add(i);
  }
  for(unsigned int i = 10; i > 7; --i) {
    int_list.add(i);
  }
  std::cout << "The chronological order: \n";
  int_list.print_chrono();
  std::cout << "\nThe sort order: \n";
  int_list.print_sort();
  std::cout << "\nThe random order: \n";
  int_list.print_random(); 
  int_list.clear();
  assert (int_list.empty());
  assert (int_list.size() == 0);
  std::cout<<"list for test MultiLL containing types other than std::string\
 cleared!"<<std::endl;
  //--------------------------------------------------------------
  //   anything else that is necessary
  std::cout<<"\n\n";
  std::cout<<"Begin other tests "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"1. Corner case for random "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  std::cout<<"a. the list only havs one item \n";
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> one_ran;
  one_ran.add("opppps");
  std::cout<<"The original list: \n";
  one_ran.print_chrono();
  std::cout<<"The random order: \n";
  one_ran.print_random();
  one_ran.clear();
  std::cout<<"b. the list has no item: \n";
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> no_ran;
  std::cout<<"The original list: \n";
  no_ran.print_chrono();
  std::cout<<"The random order: \n";
  no_ran.print_random();
  no_ran.clear();
  std::cout<<"\n";
  std::cout<<"2. Access something_end() after erase...: "<<std::endl;
  std::cout<<"----------------------------------------------------"<<std::endl;
  MultiLL<std::string> erase_end;
  erase_end.add("k");
  erase_end.add("o");
  erase_end.add("t");
  erase_end.add("o");
  erase_end.add("r");
  erase_end.add("i");
  std::cout<<"the original list is: \n";
  erase_end.print_chrono();
  std::cout<<"remove last one of the list\n";
  MultiLL<std::string>::iterator remove_t = erase_end.end_chronological();
  remove_t--;
  std::cout<<"this term should be removed: " <<*remove_t<<std::endl;
  MultiLL<std::string>::iterator new_end = erase_end.erase(remove_t);
  assert(new_end == erase_end.end_chronological());
  std::cout<<"after removing, the reverse order: \n";
  while (new_end != erase_end.begin_chronological()) {
    --new_end;
    std::cout<<*new_end<<std::endl;
  }
  erase_end.clear();
  std::cout << "Finished StudentTests." << std::endl;
}

// ================================================================================
