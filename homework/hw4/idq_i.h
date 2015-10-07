//File name: idq.h
//idq ==> id_and_quantitie
//Purpose: a container to hold an id, a name and a quantity(in use for item class)

#ifndef idq_i_h
#define idq_i_h

#include <string>

class IDQ_I {
	public:
		IDQ_I(std::string aID, std::string aName, int aNumber);
		//Accessors
		const int get_num() const {return num;}
		const std::string &get_c_id() const {return ID;}
		const std::string &get_name() const {return name;}
		//Modifiers
		void set_num(std::string a, int number);

	private:
		std::string ID;
		std::string name;
		int num;
};

#endif