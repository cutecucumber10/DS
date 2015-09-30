//File: player.cpp
//Purpose: Implementation of the class Player

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"

//First to read information about players

Player::Player() {   //default value
	playername = "";
	championname = "";
	results = 0;
	kills = 0;
	deaths = 0;
	KDR = 0.00;
}

void Player::set_results(std::string a) {
	// lose return folse and win return true
	if ( a == "LOSING") {
		results = 0;
	}
	else if ( a == "WINNING") {
		results = 1; 
	}
}

void Player::set_kills(int Akill) {
	kills = Akill;
}

void Player::set_deaths(int Adeath) {
	deaths = Adeath;
}

void Player::set_KDR() {
	if (deaths == 0) {
		KDR = (double)kills;
	}
	else {
		KDR = (double)kills/(double)deaths;
	}
}

void Player::print() const {
	//std::cout << playername <<  ' ' << kills <<"    " << deaths << "   " << std::fixed << std::setprecision(2) << KDR <<"  " ;
	std::cout.width(23); 
	std::cout << std::left << playername;
	std::cout.width(5); 
	std::cout << std::right << kills;
	std::cout.width(8); 
	std::cout << std::right << deaths; 
	std::cout.width(8); 
	std::cout << std::right << std::fixed << std::setprecision(2) << KDR;
	std::cout << "   ";
}


bool Player::read(std::istream& in_str) {
	//useless information will be stored in the trash1 and trash2
	std::string trash1;
	std::string trash2;
	if(!(in_str >> playername >> trash1 >> trash2 >> championname)) {
		std::cerr << "not a player!" << std::endl;
		return false;
	}
	return true; //everything is fine
}

std::ostream& Player::outputs(std::ostream& out_str) const {
	out_str.width(23); 
	out_str << std::left << playername;
	out_str.width(5); 
	out_str << std::right << kills;
	out_str.width(8); 
	out_str << std::right << deaths; 
	out_str.width(8); 
	out_str << std::right << std::fixed << std::setprecision(2) << KDR;
	out_str << "   ";
	return out_str;
}


bool operator< (const Player& player1, const Player& player2) {
	return player1.get_KDR() > player2.get_KDR() || (
		player1.get_KDR() == player2.get_KDR() && player1.get_kills() > player2.get_kills()) ||  (
		player1.get_KDR() == player2.get_KDR() && player1.get_kills() == player2.get_kills() && player1.get_deaths() < player2.get_deaths()) ||(
		player1.get_KDR() == player2.get_KDR() && player1.get_kills() == player2.get_kills() && player1.get_deaths() == player2.get_deaths() && player1.get_player_name() < player2.get_player_name());
		 
}

