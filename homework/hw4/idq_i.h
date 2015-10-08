//File name: idq.h
//idq ==> id_and_quantitie
//Purpose: a container to hold an id, a name and a quantity(in use for item class)
//arthor: Xinyue Yan(yanx3)

#ifndef idq_i_h
#define idq_i_h

#include <string>
#include <fstream>


class IDQ_I {
	public:
		IDQ_I(std::string aID, std::string aName, int aNumber);
		//Accessors
		const int get_num() const {return num;}
		const std::string &get_c_id() const {return ID;}
		const std::string &get_name() const {return name;}
		//Modifiers
		void set_num(std::string a, int number);
		void outputs(std::ostream& out_str);

	private:
		std::string ID;
		std::string name;
		int num;
};

#endif