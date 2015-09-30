#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "champion.h"


Champion::Champion() {
	championname = "";
	win = 0;
	loss = 0;
	win_p = 0.00;
}

void Champion::set_champion_name(std::string a) {
	championname = a;
}

void Champion::set_win(int Awin) {
	win = Awin;
}  

void Champion::set_loss(int Aloss) {
	loss = Aloss;
}

void Champion::set_win_p() {
	if (win != 0) {
		win_p = (double)win/((double)win+(double)loss);
	}
	else {
		win_p = 0.00;
	}
}

void Champion::set_minion_d(int aMinion) {
	minion_d = aMinion;
}

std::ostream& Champion::outputs(std::ostream& out_str) const{
	out_str.width(24); 
	out_str << std::left << championname;
	out_str.width(4); 
	out_str << std::right << win;
	out_str.width(8); 
	out_str << std::right << loss; 
	out_str.width(8); 
	out_str << std::right << std::fixed << std::setprecision(2) << win_p;
	out_str.width(16);
	out_str << std::right << minion_d << "\n";
	return out_str;
}

bool operator< (const Champion& champion1, const Champion& champion2) {
	return (champion1.get_win_p() > champion2.get_win_p() ||
		(champion1.get_win_p() == champion2.get_win_p() && champion1.get_win() > champion2.get_win()) ||
		(champion1.get_win_p() == champion2.get_win_p() && champion1.get_win() == champion2.get_win() && champion1.get_champion_name() < champion2.get_champion_name()));
}
