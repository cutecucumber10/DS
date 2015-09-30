//File: match.h
//Purpose: Header for declaration of match class of different functions

#ifndef match_h
#define match_h

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "event.h"

class Match {
	public:
		//Accessors
		const unsigned long long int get_match_id() const { return match_id; }
		const std::vector<Player> get_players() const { return players; }
		const std::vector<Event> get_events() const {return events; }

		bool read(std::istream& in_str);  //a function to read a single match from file ^^
		void print() const;

	private:
		//Representations
		unsigned long long int match_id;
		std::vector<Player> players;
		std::vector<Event> events;
};



#endif
