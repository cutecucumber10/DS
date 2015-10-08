//File name: item.h
//Purpose: contain every items in the inventory and their avalibility and customers. 
//arthor: Xinyue Yan(yanx3)

#ifndef item_h
#define item_h

#include "idq_i.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>

class Item {
	public:
		//Accessors 
		const std::string& get_i_id() const {return i_id;}
		const int get_num() const {return num;}
		const std::string& get_description() {return description;} 
		void get_rental(std::list<IDQ_I>& a_rental) const; 
		void get_pending(std::list<IDQ_I>& a_pending) const;
		IDQ_I get_popularity() const; 

		//Modifier
		void add_rental(IDQ_I a_customer);
		void add_pending(IDQ_I a_customer);
		void erase_rental(int a);
		void set_rental(int b, std::string a, int number);
		void erase_pending(int a);
		void set_pending(int a, int number);
		void count_up(int number) {count += number;}

		//Other member function
		bool read(std::istream& in_str);
		void outputs(std::ostream& out_str) ;

	private:
		std::string i_id;
		int num;
		std::string description;
		std::list<IDQ_I> rental;
		std::list<IDQ_I> pending;
		int count; //determine the popularity....of the item.....


};

#endif