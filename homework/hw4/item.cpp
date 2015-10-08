//File name: item.cpp
//Purpose: implement of item.h
//arthor: Xinyue Yan(yanx3)

#include "item.h"

#include <string>  
#include <list>
#include <iostream> 
#include <fstream>

//make a copy of rental list
void Item::get_rental(std::list<IDQ_I>& a_rental) const {
	a_rental = rental;
}

//make a copy of pending list
void Item::get_pending(std::list<IDQ_I>& a_pending) const {
	a_pending = pending;
}

IDQ_I Item::get_popularity() const {
	IDQ_I a_pop(i_id, description, count);
	return a_pop;
}

//add to rental list, amount reduces.....
void Item::add_rental(IDQ_I a_customer) {
	bool if_last_one = true;
	for (std::list<IDQ_I>::iterator p = rental.begin(); p != rental.end(); ++p) {
		if (a_customer.get_c_id() < (*p).get_c_id()) {
			rental.insert(p, a_customer);
			if_last_one = false;
			break;
		}
	}
	//corner case, if the term is ordered in the last one....
	if (if_last_one == true) {
		rental.push_back(a_customer);
	} 
	num -= a_customer.get_num();
}

//add to pending list, amount no change
void Item::add_pending(IDQ_I a_customer) {
	pending.push_back(a_customer);
}

//erase from rental list, amount increase
void Item::erase_rental(int a) {
	//int is LOCATION of the term in the list
	std::list<IDQ_I>::iterator p = rental.begin();
	for (int i = 0; i < a; i++) {
		p++;
	}
	num += (*p).get_num();
	rental.erase(p);
}

//change rental amounts, get action to find whether it needs increase or decrease.
void Item::set_rental(int b, std::string a, int number) {
	//int b is LOCATION of the term in the list, string is the action(rent or return)
	//int number is the amount they rent or return
	//find the iterator
	std::list<IDQ_I>::iterator p = rental.begin();
	for (int i = 0; i < b; i++) {
		p++;
	}
	(*p).set_num(a,number);
	if (a == "rent") 
		num -= number;
	else if (a == "return")
		num += number;
}

//erase from pending list, move it to rental list and amount reduces
void Item::erase_pending(int a) {
	//int is LOCATION of the term in the list
	//find the iterator
	std::list<IDQ_I>::iterator p = pending.begin();
	for (int i = 0; i < a; i++) {
		p++;
	}
	//add to rental list and reduce amount
	add_rental(*p);
	//remove from pending list
	pending.erase(p);
}

void Item::set_pending(int a, int number) {
	////int is LOCATION of the term in the list
	//number is how many they rent...
	std::list<IDQ_I>::iterator p = pending.begin();
	for (int i = 0; i < a; i++) {
		p++;
	}
	//when set pending, the pending number may change.
	(*p).set_num("rent",number);
}


bool Item::read(std::istream& in_str) {
	if (!(in_str >> i_id >> num >> description)) {
		//it goes to end of the file......
		return false;
	}
	if (i_id[0] != 'T' || num == 0) {
		//error but no need to stop....
		std::cerr << "Invalid inventory ID " << i_id <<  " found in the inventory file.\n";
	}
	count = 0; 
	return true;
}

void Item::outputs(std::ostream& out_str) {
	//output to the file.......
	out_str << i_id << ' ' << num << " available " << description;
	out_str << "\n";
	//if no Rental cus, skip this is if.......
	if (rental.size() != 0) {
		out_str << "Rental Customers: ";
		for (std::list<IDQ_I>::iterator a_rental = rental.begin(); a_rental != rental.end() ; ++a_rental) {
			out_str << (*a_rental).get_c_id() << ' ' <<(*a_rental).get_name()\
			<< " (" << (*a_rental).get_num() << ") ";
		}
		out_str << "\n";
	}
	//if no Pending cus, skip this is if.......
	if (pending.size() != 0) {
		out_str << "Pending Customers: ";
		for (std::list<IDQ_I>::iterator a_pending = pending.begin(); a_pending != pending.end() ; ++a_pending) {
			out_str << (*a_pending).get_c_id() << " " << (*a_pending).get_name()\
			<< " (" << (*a_pending).get_num() << ") ";
		}
		out_str << "\n";	
	}
	out_str << "\n";
}
