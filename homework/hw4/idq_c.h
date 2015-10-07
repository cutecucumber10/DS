//File name: idq.h
//idq ==> id_and_quantitie
//Purpose: a container to hold an id and a quantity(in use for customer class)

#ifndef idq_c_h
#define idq_c_h

#include <string>

class IDQ_C {
	public:
		IDQ_C(std::string aID, int aNumber);
		//Accessors
		const int get_num() const {return num;}
		const std::string &get_i_id() const {return ID;}
		//Modifiers
		void set_num(std::string a, int number);

	private:
		std::string ID;
		int num;
};

#endif