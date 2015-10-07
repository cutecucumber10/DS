//File name : main.cpp

#include "idq_c.h"
#include "idq_i.h"
#include "event.h"
#include "item.h"
#include "customer.h"

#include <string>
#include <list>   
#include <fstream>    //in_str and out_str
#include <iostream>   //cin and cout

//prototype of functions
//happens when a customer rent something.....
void rent_tool(const Event& event, std::list<Item>& items, \
	std::list<Customer>& customers);
//happens when someone return something....
void return_tool(const Event& event, std::list<Item>& items, \
	std::list<Customer>& customers);
//happens when someone returns something and amounts add.....
void handle_pending(Item& a_item, std::list<Customer>& customers);
//a function to deal with the unactivted customers after every action
//finish.....
void clean_customers(std::list<Customer>& customers);

//implement of previous prototype;

void clean_customers(std::list<Customer>& customers) {
	//if rental.size() and pending.size() == 0, remove the customer
	std::list<Customer>::iterator unactive_c;
	for (unactive_c = customers.begin(); unactive_c != customers.end(); \
		unactive_c++) {
		std::list<IDQ_C> a_rental;
		std::list<IDQ_C> a_pending;
		(*unactive_c).get_rental(a_rental);
		(*unactive_c).get_pending(a_pending);
		if (a_rental.size() == 0 && \
			a_pending.size() == 0) {
			unactive_c = customers.erase(unactive_c);
		}
	}
}

void rent_tool(const Event& event, std::list<Item>& items, \
	std::list<Customer>& customers) {
	//first check if the item id in the event is in the inventory
	//loop in the items list to find
	bool found_item = false;
	std::list<Item>::iterator in_item = items.begin(); 
	while ( in_item != items.end()) {
		if ((*in_item).get_i_id() == event.get_i_id()) {
			found_item = true;
			break;
		}
		else {
			++in_item;
		}
	}
	//if not in_item, error appears, and do nothing..... 
	if (found_item == false) {
			std::cerr<<"Customer "<<event.get_c_id()<<" requested item "\
			<<event.get_i_id()<<" which is not in the inventory.\n";
	}
	//if item in_item
	else {
		//check if the number the customer requested is enough
		//if there is enough items, rent tool to the customer
		//reduce the amount and add to rental list 
		if ((*in_item).get_num() >= event.get_num()) {
			//change the avalibility
			//(*in_item).set_num(event.get_action(), event.get_num());
			//check if the customer is in the item rental list
			bool found_i_rental = false;
			std::list<IDQ_I> i_rental;
			(*in_item).get_rental(i_rental);
			int count_i_rental = 0;
			std::list<IDQ_I>::iterator in_i_rental;
			for (in_i_rental = i_rental.begin(); in_i_rental != i_rental.end() ; ) {
				if ((*in_i_rental).get_name() == event.get_name()) {
					found_i_rental = true;
					break; }
				else {
					in_i_rental++;
					count_i_rental++;
				}
			}
			//if he is in the rental list, add renting amount(directly change 
			//rental member number)
			if (found_i_rental == true) {
				(*in_item).set_rental(count_i_rental, event.get_action(), event.get_num());
			}
			//else(the customer is not in the item rental list) 
			//push back the customer in the rental list
			else {
				IDQ_I a_customer(event.get_c_id(), event.get_name(), event.get_num());
				(*in_item).add_rental(a_customer);
			}
			//check if the new customer is in the customer lists
			bool found_customer = false;
			std::list<Customer>::iterator in_item_cus;
			for (in_item_cus = customers.begin(); in_item_cus != customers.end(); ) {
				if ((*in_item_cus).get_c_id() == event.get_c_id()) {
					found_customer = true;
					break;}
				else
					in_item_cus++;
			}
			//if the customer already in the customer list. check if the item is in the rental list
			if (found_customer == true) {
				//check if the item in customer rental list 
				bool found_c_rental = false;
				std::list<IDQ_C> c_rental;
				(*in_item_cus).get_rental(c_rental);
				int count_c_rental;
				for (std::list<IDQ_C>::iterator in_c_rental = c_rental.begin() ; \
					in_c_rental != c_rental.end(); ) {
					if ((*in_c_rental).get_i_id() == event.get_i_id()) {
						found_c_rental = true;
						break; }
					else {
						in_c_rental++;
						count_c_rental++;
					}
				}
				//if the item is in the customer rental list, add number to the rental amount
				if (found_c_rental == true) {
					(*in_item_cus).set_rental(count_c_rental, event.get_action(), event.get_num());
				}
				//if not in the rental list, push back the idq_c 
				else {
					IDQ_C new_item(event.get_i_id(), event.get_num());
					(*in_item_cus).add_rental(new_item);
				}
			}
			//if not find... add this customer to be activated and add it's rental lists = =!
			else {
				Customer new_customer(event.get_c_id(),event.get_name());
				IDQ_C new_item(event.get_i_id(), event.get_num());
				new_customer.add_rental(new_item);
				bool if_last_one = true;
				for (std::list<Customer>::iterator p = customers.begin(); \
					p != customers.end(); ++p) {
					if (event.get_c_id() < (*p).get_c_id()) {
						customers.insert(p, new_customer);
						if_last_one = false;
						break;
					}
				}
				if (if_last_one == true) {
					customers.push_back(new_customer);
				} 
			} 
		}
		//there is not enough items to rent....the customer needs wait
		else {
			//check if pending customer is in the item pending list......
			//add to pending list....
			//no need to change amount of avalibility
			//add both to inventoty and customer lists
			std::list<IDQ_I> i_pending;
			(*in_item).get_pending(i_pending);
			std::list<IDQ_I>::iterator in_i_pending;
			bool found_i_pending = false;
			int count_i_pending = 0;
			for (in_i_pending = i_pending.begin(); in_i_pending != i_pending.end();) {
				if ((*in_i_pending).get_c_id() == event.get_c_id()) {
					found_i_pending = true;
				}
				else {
					in_i_pending++;
					count_i_pending++;
				}
			}
			if (found_i_pending == true) {
				//set the pending number of the original customer..
				(*in_item).set_pending(count_i_pending, event.get_num());
				//find the customer iterator.....
				bool found_p_customer = false;
				std::list<Customer>::iterator in_item_cus;
				for (in_item_cus = customers.begin(); in_item_cus != customers.end(); ) {
					if ((*in_item_cus).get_c_id() == event.get_c_id()) {
						found_p_customer = true;
						break;}
					else
						in_item_cus++;
				}
				//the customer itr in_item_cus....
				//find itr of pending items in the customer pending list....
				std::list<IDQ_C>::iterator in_c_pending;
				std::list<IDQ_C> c_pending;
				(*in_item_cus).get_pending(c_pending);
				int count_c_pending;
				for (in_c_pending = c_pending.begin(); in_c_pending != c_pending.end(); ) {
					if ((*in_c_pending).get_i_id() == event.get_i_id()) {
						break;
					}
					else {
						in_c_pending++;
						count_c_pending++;
					}
				}
				//set the number of customer pending items.....
				(*in_item_cus).set_pending(count_c_pending, event.get_num());
			}
			else {
				//if not find...push back pending customers to pending list of customer and item
				IDQ_I a_customer(event.get_c_id(), event.get_name(), event.get_num());
				IDQ_C an_item(event.get_i_id(), event.get_num());
				(*in_item).add_pending(a_customer);
				//check if the customer is activated :D
				bool found_customer = false;
				std::list<Customer>::iterator in_item_cus;
				for (in_item_cus = customers.begin(); in_item_cus != customers.end(); ) {
					if ((*in_item_cus).get_c_id() == event.get_c_id()) {
						found_customer = true;
						break;}
					else
						in_item_cus++;
				} 
				//if activated, add to that pending list
				if (found_customer == true) {
					(*in_item_cus).add_pending(an_item);
				}
				//if not, add a new customer and add pending list 
				else {
					Customer activate_cus(event.get_c_id(), event.get_name());
					activate_cus.add_pending(an_item);
					bool if_last_one = true;
					for (std::list<Customer>::iterator p = customers.begin(); \
						p != customers.end(); ++p) {
						if (event.get_c_id() < (*p).get_c_id()) {
							customers.insert(p, activate_cus);
							if_last_one = false;
							break;
						}
					}
					if (if_last_one == true) {
						customers.push_back(activate_cus);
					}
				}
			}
		}
	}
}

void return_tool(const Event& event, std::list<Item>& items, \
	std::list<Customer>& customers) {
	//check if item is in the inventory list
	bool found_item = false;
	std::list<Item>::iterator in_inventory;
	for (in_inventory = items.begin(); in_inventory != items.end(); ) {
		if ((*in_inventory).get_i_id() == event.get_i_id()) {
			found_item = true;
			break;
		}
		else
			in_inventory++;
	}
	//if not in the item list
	if (found_item == false) {
		std::cerr << "Customer "<< event.get_c_id() << " attempted to return item "<< \
		event.get_i_id() << " which is not in the inventory.\n";
	}
	//if in the item list
	else {
		//check if it is in the list customers
		//if he is an activated customer, check if i_id is in rental list
		//if he is not an activated customer, error message...
		bool found_customer = false;
		std::list<Customer>::iterator return_cus;
		for (return_cus = customers.begin(); return_cus != customers.end(); ) {
			if ((*return_cus).get_c_id() == event.get_c_id()) {
				found_customer = true;
				break;
			}
			else
				return_cus++;
		}
		//not activated...no rent books(this is an error)
		if (found_customer == false) {
			std::cerr << "Customer " << event.get_c_id() << " is not a activated customer\n";
		}
		//activated, if i_id in the customers rental list
		else {
			//find the customer rental book iterator 
			bool found_c_rental = false;
			std::list<IDQ_C> c_rental;
			(*return_cus).get_rental(c_rental);
			int count_c_rental = 0;
			std::list<IDQ_C>::iterator in_c_rental ;
			for (in_c_rental= c_rental.begin(); \
				in_c_rental != c_rental.end() ; ) {
				if ((*in_c_rental).get_i_id() == event.get_i_id()) {
					found_c_rental = true;
					break;
				}
				else {
					in_c_rental++;
					count_c_rental++;
				}
			}
			//if not in the customer rental list, it is an error
			if (found_c_rental == false) {				
				std::cerr << "Customer " << event.get_c_id() << " attempted to return item " \
				<< event.get_i_id() << " which she/he did not rent.\n";
			}
			//if in the rental list
			else {
				//find the iterator of the customer in the item rental list....
				std::list<IDQ_I> i_rental;
				(*in_inventory).get_rental(i_rental);
				int count_i_rental = 0;
				for (std::list<IDQ_I>::iterator in_i_rental = i_rental.begin(); \
				in_i_rental != i_rental.end(); ) {
					if ((*in_i_rental).get_c_id() == (event.get_c_id())) {
						break;
					}
					else {
						in_i_rental++;
						count_i_rental++;
					}
				}
				//check the number of returning, if is equal, bigger or less than rent amount
				//if bigger ? problem....
				if (event.get_num() > (*in_c_rental).get_num() ) {
					std::cerr << "Customer attempted to return latger amount of item.\n " <<\
					event.get_i_id() << "to the store.";
				}
				//if equal...just erase the rental term....
				else {
					if (event.get_num() == (*in_c_rental).get_num()) {
						//if equal...just erase the rental term....
						//erase in item rental list
						(*in_inventory).erase_rental(count_i_rental);
						//erase in customer rental list
						(*return_cus).erase_rental(count_c_rental);

					}
					//if smaller, set the number......
					else {
						(*in_inventory).set_rental(count_i_rental, event.get_action(), event.get_num());
						(*return_cus).set_rental(count_c_rental, event.get_action(), event.get_num());
					}
					//doing handle pending.
					//maybe put in main function......
				}//end with else 
			}
			handle_pending((*in_inventory),customers);
		}
	}
}

void handle_pending(Item& a_item, std::list<Customer>& customers) {
	std::list<IDQ_I> i_pending;
	a_item.get_pending(i_pending);
	int count_i_pend = 0;
	for (std::list<IDQ_I>::iterator pend_cus = i_pending.begin(); pend_cus != i_pending.end(); ++pend_cus) {
		if ((*pend_cus).get_num() <= a_item.get_num()) {
			//remove from customer pending list
			//add to customer rental list
			//find the iterator of customer...
			std::list<Customer>::iterator pend_cus_in_c;
			for (pend_cus_in_c = customers.begin(); \
				pend_cus_in_c != customers.end(); ) {
				if ((*pend_cus_in_c).get_c_id() == (*pend_cus).get_c_id()) {
					break;}
				else
					pend_cus_in_c++;
			}
			//remove *pen_cus from pending list
			//add to rental list
			a_item.erase_pending(count_i_pend);
			count_i_pend--;
			//find the iterator of that item in the pending list of c
			std::list<IDQ_C> c_pending;
			//a number to find the location of the element.....as an argument in the erase function....
			int count_c_pend = 0;
			(*pend_cus_in_c).get_pending(c_pending);
			for (std::list<IDQ_C>::iterator pend_item = c_pending.begin(); pend_item != c_pending.end(); ) {
				if ((*pend_item).get_i_id() == a_item.get_i_id()) { 
					break;}
				else {
					count_c_pend++;
					pend_cus_in_c++;
				}
			}
			(*pend_cus_in_c).erase_pending(count_c_pend);
		}
		count_i_pend++;
	}
}


int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr<<"Not the correct number of arguments....\n";
		return 1;
	}
	else {
		//open the files of inventory and customer to generate two lists
		//open the input file and check if the status of the file is okkk
		std::ifstream in_str_i(argv[1]);
		if (!in_str_i.good()) {
			std::cerr<<"Could not open inventory file " << argv[1] << " to read\n";
			return 1;
		}
		//Second list is event list(holds all the actions of customers)
		std::ifstream in_str_e(argv[2]);
		if (!in_str_e.good()) {
			std::cerr<<"Could not open event file " << argv[2] << " to read\n";
			return 1;
		}
		std::ofstream out_str_i(argv[3]);
		if (!out_str_i.good()) {
			std::cerr << "Could not open inventory output " << argv[3] << " to write\n";
			return 1;
		}
		std::ofstream out_str_c(argv[4]);
		if (!out_str_c.good()) {
			std::cerr << "Could not open customer output " << argv[4] << " to write\n";
			return 1;
		}
		//create three list....
		//first list is inventory list.....
		//including item id, avalibility, description
		std::list<Item> inventory;
		//second list....action list....
		//including customer id, action(rent/return), timestamp,
		//amount,item id, name......
		std::list<Event> events;
		//a list only contain activated customers ( in other words....)
		//the customer is in rental or pending list......
		//this list if not from the input files, it will be created as the 
		//event lists loops over......
		std::list<Customer> customers;
		//two variable to temperarily store input information
		Item one_item;
		Event one_event;
		//input inventory file
		//sort.....
		while (one_item.read(in_str_i) ) {
			if (one_item.get_i_id()[0] == 'T' and one_item.get_num() != 0) {
				bool if_last_one = true;
				for (std::list<Item>::iterator p = inventory.begin(); p != inventory.end(); ++p) {
					if (one_item.get_i_id() < (*p).get_i_id()) {
						inventory.insert(p, one_item);
						if_last_one = false;
						break;
					}
				}
				if (if_last_one == true) {
					inventory.push_back(one_item);	
				}
			}
		}
		//input event file...
		while (one_event.read(in_str_e) ) {
			//if (one_event.get_c_id()[0] == 'C') 
				events.push_back(one_event);
		}

		//start to loop event make updated customer and inventory lists.....
		std::list<Event>::iterator an_event;
		for (an_event = events.begin(); an_event != events.end(); ++an_event) {
			//first check if the action is rent or return
			if ((*an_event).get_c_id()[0] != 'C') {
				std::cerr << "Invalid customer information found for ID " << \
				(*an_event).get_c_id() <<" in the customer file \n";
			}
			else {
				if ((*an_event).get_action() == "rent") {
					rent_tool(*an_event, inventory, customers);
				}
				else {
					return_tool((*an_event), inventory, customers);
					clean_customers(customers);
				}
			}
		}

		//go for outputs...
		//inventory output 
		std::list<Item>::iterator out_item;
		std::list<Customer>::iterator out_customer;
		for (out_item = inventory.begin(); out_item != inventory.end(); ++out_item) {
			(*out_item).outputs(out_str_i);
		}
		//customer output
		for (out_customer = customers.begin(); \
			out_customer != customers.end(); ++out_customer) {
			(*out_customer).outputs(out_str_c);
		}
	}
	return 0;
}