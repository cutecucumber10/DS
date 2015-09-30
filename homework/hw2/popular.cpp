#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "popular.h"


Popular::Popular() {
	championname = "";
	killer = 0;
	assistant = 0;
	KAR = 0.00;
}

void Popular::set_champion_name(std::string a) {
	championname = a;
}

void Popular::set_killer(int Akiller) {
	killer = Akiller;
}  

void Popular::set_assistant(int Aassistant) {
	assistant = Aassistant;
}

void Popular::set_KAR() {
	if (assistant != 0) {
		KAR = (double)killer/(double)assistant;
	}
	else {
		KAR = (double)killer;
	}
}


std::ostream& Popular::outputs(std::ostream& out_str) const{
	out_str.width(24); 
	out_str << std::left << championname;
	out_str.width(6); 
	out_str << std::right << killer;
	out_str.width(11); 
	out_str << std::right << assistant; 
	out_str.width(7); 
	out_str << std::right << std::fixed << std::setprecision(2) << KAR << "\n";
	return out_str;
} 

bool operator< (const Popular& pop1, const Popular& pop2) {
	return (pop1.get_KAR() > pop2.get_KAR() ||
		(pop1.get_KAR() == pop2.get_KAR() && pop1.get_killer() > pop2.get_killer()) ||
		(pop1.get_KAR() == pop2.get_KAR() && pop1.get_killer() == pop2.get_killer() && pop1.get_champion_name() < pop2.get_champion_name()));
}

bool alphabetically(const Popular& pop1, const Popular& pop2 ) {
	return (pop1.get_champion_name() < pop2.get_champion_name());
}
