//File: champion.h
//Purpose: Header for declaration of champion/win/loss/minion death class and associated functions.

#ifndef champion_h
#define champion_h

#include <string>
#include <iostream>

class Champion { 
	public:
		Champion();
		Champion(std::string Achampion_name, int Awin, int Aloss, double Awin_p,int Amini_death);

		//Accessors
		const std::string&  get_champion_name() const {return championname;}
		const int get_win() const {return win;}
		const int get_loss() const {return loss;}
		const double get_win_p() const {return win_p;}
		const int get_minion_d() const {return minion_d;}

		//Modifiers
		void set_champion_name(std::string a);
		void set_win(int Awin);
		void set_loss(int Aloss);
		void set_win_p();
		void set_minion_d(int aMinion);

		//other functions
		std::ostream& outputs(std::ostream& out_str) const ;


	private:
		//Representations
		std::string championname;
		int win;
		int loss;
		double win_p;
		int minion_d;
};

bool operator< (const Champion& champion1, const Champion& champion2);

#endif