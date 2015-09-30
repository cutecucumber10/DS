//File: match.cpp
//Purpose: Implementation of the class Match

#include <iostream>
#include <string>
#include <vector>
#include "match.h"
#include "event.h"
#include "player.h"

bool Match::read(std::istream& in_str) {
	std::string trash;
	Player one_player;
	Event one_event;
	players.clear();  //remove data 
	events.clear();   //inserted before  //use in line 64
	in_str >> trash;
	if (trash != "MATCH") {
		return false;
	}
	in_str >> trash;
	if (trash != "ID") {
		return false;
	}
    in_str >> match_id;
	in_str >> trash;  //"LOSING"
    // here starts to parse player file
	if (trash == "LOSING") {
		in_str >> trash; //"TEAM"
		for (unsigned int i = 0; i < 5; ++i ) {
			one_player.read(in_str);
			one_player.set_results("LOSING");
			players.push_back(one_player);
		}
	}
	else if (trash == "WINNING") {  //some inputs file winning is before losing 
		in_str >> trash; //"TEAM"
		for (unsigned int i = 0; i < 5; ++i ) {
			one_player.read(in_str);
			one_player.set_results("WINNING");
			players.push_back(one_player);
		}
	}
	in_str >> trash; //"WINNING"
	if (trash == "WINNING") {
		in_str >> trash; //"TEAM"
		for (unsigned int i = 0; i < 5; ++i ) {
			one_player.read(in_str);
			one_player.set_results("WINNING");
			players.push_back(one_player);
		}
	}
	else if (trash == "LOSING") {
		in_str >> trash; //"TEAM"
		for (unsigned int i = 0; i < 5; ++i ) {
			one_player.read(in_str);
			one_player.set_results("LOSING");
			players.push_back(one_player);
		}
	}

	in_str >> trash; //"EVENTS"
	while (one_event.read(in_str)) {
		events.push_back(one_event);
	}
	return true;
}

/*
void Match::print() const {
	for (unsigned int i = 0; i < players.size(); ++i) {
		players[i].print();
	}
	for (unsigned int j = 0; j < events.size(); ++j) {
		events[j].print();
	}

}
*/