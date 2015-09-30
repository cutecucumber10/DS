//File: Popular.h
//Purpose: Header for declaration of champion/win/loss/minion death class and associated functions.

#ifndef popular_h
#define popular_h

#include <string>
#include <iostream>

class Popular { 
	public:
		Popular();
		Popular(std::string Achampion_name, int Akiller, int Aassistant, double AKAR);

		//Accessors
		const std::string&  get_champion_name() const {return championname;}
		const int get_killer() const {return killer;}
		const int get_assistant() const {return assistant;}
		const double get_KAR() const {return KAR;}

		//Modifiers
		void set_champion_name(std::string a);
		void set_killer(int Akiller);
		void set_assistant(int Aassistant);
		void set_KAR();

		//other functions
		std::ostream& outputs(std::ostream& out_str) const ;


	private:
		//Representations
		std::string championname;
		int killer;
		int assistant;
		double KAR;
};

bool operator< (const Popular& pop1, const Popular& pop2);
bool alphabetically(const Popular& pop1, const Popular& pop2 ) ;


#endif