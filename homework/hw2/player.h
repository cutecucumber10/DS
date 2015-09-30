//File: player.h
//Purpose: Header for declaration of player-champion class and associated functions.
// this file will realize which player played which champion

#ifndef player_h
#define player_h

#include <string>
#include <iostream>

class Player {
	public:
		Player();
		Player(std::string Aplayername, std::string Achampionname, int Aresults, int Akills, int Adeaths, double KDR);

		//Accessors
		const std::string& get_player_name() const { return playername; }
		const std::string& get_champion_name() const { return championname; }
		const int get_results() const { return results; }
		const int get_kills() const {return kills; }
		const int get_deaths() const {return deaths;}
		const double get_KDR() const {return KDR;}


        //Modifiers
		void set_results(std::string a); //check win/lose depend on the term winning or losing in match class reading function
		void set_kills(int Akill);
		void set_deaths(int Adeath);
		void set_KDR();



        //non member functions
		bool read(std::istream& in_str);   // a function to read from file
		void print() const;
		std::ostream& outputs(std::ostream& out_str) const;


	private:
		//Representations
		std::string playername;  // a string collect player's name
		std::string championname;  // a string collect the champion the player play
		int results;  // 1 means win, 0 means lose
		int kills;
		int deaths;
		double KDR;

};

bool operator< (const Player& player1, const Player& player2);

#endif