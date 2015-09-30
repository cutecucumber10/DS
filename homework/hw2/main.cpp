//File: main.cpp
//Purpose: Main program to do three tables "players","champions" and "custom"...
//useful code not std::setprecision(int) <Sets the decimal precision to be used to format floating-point values on output operations.>.
//std::fixed   std::left std::right

#include <fstream>   //std::ifstream  //std::ofstream
#include <iostream>
#include <string>
#include <vector>
#include "event.h"  
#include "player.h"
#include "match.h"
#include "champion.h"
#include "popular.h"
#include <iomanip>
#include <algorithm>


int main(int argc, char* argv[]) {
	//argc is fixed, should be 4...
	if (argc != 4) {
		std::cerr << "Not the correct number of arguments";
		return 1;
	}
	//open the input file and check if the status of the file is okkk
	std::ifstream in_str(argv[1]);
	if (!in_str.good()) {
		std::cerr << "Could not open" << argv[1] << "to read\n";
		return 1;
	}
	//check if the output file's status is good
	std::ofstream out_str(argv[2]);
	if (!out_str.good()) {
		std::cerr << "Could not open" << argv[2] << "to write\n";
		return 1;
	}
	//read files start zzz...
	std::vector<Match> matches; //read matches in a single file
	Match one_match;             //define a single match one_match, and add it to the vector matches one by one

	while(one_match.read(in_str)) {     //if the function does not return false, keep going.
		matches.push_back(one_match);     
	}

    // while the third term equals players
    std::string a = "players";
  	if (!a.compare(argv[3])) {
	    //have a player and an event collection first
	    std::vector<Player> all_players;
        std::vector<Event> all_events;
	    //use loop to read from vector matches
        for (unsigned int i = 0 ; i < matches.size(); ++i ) {
	        for (unsigned int j = 0 ; j < (matches[i].get_players()).size() ; ++j) {
	     	    all_players.push_back((matches[i].get_players())[j]);
		      }
		      for (unsigned int k = 0 ; k < (matches[i].get_events()).size() ; ++k) {
			      all_events.push_back((matches[i].get_events())[k]);
	     	  }
        }
	    //use loop to detect if killers/victims in events is equal to playername in players, and calculate the KDR
	    for (unsigned int i = 0 ; i < all_players.size() ; ++i ) {
		    int killing = 0;
        int died = 0;
		    for (unsigned int j = 0 ; j < all_events.size() ; ++j ) {
			    if (all_players[i].get_player_name() == all_events[j].get_killer()) {
				    killing += 1;
		    	}
          if (all_players[i].get_player_name() == all_events[j].get_victim()) {
            died += 1;
          }
        }
		    all_players[i].set_kills(killing);
        all_players[i].set_deaths(died);
        all_players[i].set_KDR();
	    } 
   	    //sort the vector
    	sort(all_players.begin(),all_players.end());
        //construct the header
  		const std::string header = "PLAYER NAME" + std::string(12, ' ') + "KILLS" + std::string(2, ' ') +  "DEATHS" + std::string(5, ' ')+"KDR"+std::string(3, ' ')+   "PLAYED WITH CHAMPION(S)";
  		out_str << header << "\n";
        // add a vector to store all the champions a player played
  		std::vector<std::string> players_champ;
      players_champ.push_back(all_players[0].get_champion_name()); 
      unsigned int i = 0;
      while (i < all_players.size()) {
          if (i == all_players.size()-1) {
            all_players[i].outputs(out_str); 
            //sort champions, alphabetically
            sort(players_champ.begin(),players_champ.end());
            for (unsigned int p = 0; p < players_champ.size(); ++p) {
              if (p == players_champ.size() -1) {
                  out_str << players_champ[p];
              }
              else {
                out_str << players_champ[p] <<", ";
              }
            }
            out_str << std::endl;
            break;
          }
          if (all_players[i+1].get_player_name() != all_players[i].get_player_name()) {
            all_players[i].outputs(out_str); 
            //sort champions, alphabetically
            sort(players_champ.begin(),players_champ.end());
            for (unsigned int p = 0; p < players_champ.size(); ++p) {
              if (p == players_champ.size() -1) {
                  out_str << players_champ[p];
              }
              else {
                out_str << players_champ[p] <<", ";
              }
            }
            out_str << std::endl;
            players_champ.clear();
            players_champ.push_back(all_players[i+1].get_champion_name());
            i++;
          }
          else {
            unsigned int position = (std::find(players_champ.begin(),players_champ.end(),all_players[i+1].get_champion_name()) - players_champ.begin());
            if( position >= players_champ.size()) { // not in the vector   
                players_champ.push_back(all_players[i+1].get_champion_name());
            }      
            all_players.erase(all_players.begin()+i+1);   //delete the term....         } 
          }  
    }
  }
    

    //while the third equals champion
    std::string b = "champions";
  	if (!b.compare(argv[3])) {
  		//set a vector contain champion class,use temporary one_champ to do push_back, insert all the champs!
  		//the all champ contains champion name, win or lose, and minionkilled in one match
  		std::vector<Champion> all_champs;
  		//temporary varible
  		Champion one_champ;
  		for (unsigned int i = 0 ; i < matches.size() ; ++i ) {
  			for (unsigned int j = 0 ; j < matches[i].get_players().size() ; ++j) {
  				int a = 0; // count minion in one match 
  				one_champ.set_champion_name(matches[i].get_players()[j].get_champion_name());
  				//set win or lose in a single match/champion
  				if (matches[i].get_players()[j].get_results() == 0) {
  					one_champ.set_win(0);
  					one_champ.set_loss(1);
  				}
  				else {
  					one_champ.set_win(1);
  					one_champ.set_loss(0);
  				}
  				for (unsigned int k = 0 ; k < matches[i].get_events().size() ; ++k) {
  					if (matches[i].get_events()[k].get_killer() == "minion" && matches[i].get_players()[j].get_player_name() == matches[i].get_events()[k].get_victim()) {
  						a += 1;
  					}
  				}
  			one_champ.set_minion_d(a); //set how many times the player killed by a minion in a single match..
  			//std::cout<<a<<std::endl;
  		    all_champs.push_back(one_champ); //collect the result
  			}
  		}

  		//another loop to erase duplicated terms and calc win percent
  		for (unsigned i = 0 ; i < all_champs.size() ; ++i ) {
  			for (unsigned j = 0 ; j < all_champs.size() ; ++j ) {
  				if (j != i && all_champs[i].get_champion_name() == all_champs[j].get_champion_name()) {
  					all_champs[i].set_win(all_champs[i].get_win()+all_champs[j].get_win()) ;
  					all_champs[i].set_loss(all_champs[i].get_loss()+all_champs[j].get_loss()) ;
  					all_champs[i].set_minion_d(all_champs[i].get_minion_d()+all_champs[j].get_minion_d());
  					all_champs.erase(all_champs.begin()+j);
  				}
  				else {
  				}
  			}
  			all_champs[i].set_win_p();  //calculate the win_p
  		}
        //sort the all_champs vector
        sort(all_champs.begin(),all_champs.end());
        const std::string header = "CHAMPION NAME" + std::string(11, ' ') + "WINS" + std::string(2, ' ') +  "LOSSES" + std::string(4, ' ')+"WIN%"+std::string(3, ' ')+   "MINION DEATHS";
        out_str << header << "\n";
  	    for (unsigned int i = 0 ; i < all_champs.size(); ++i) {
  		    all_champs[i].outputs(out_str);
  	    }	
  	} 

  	//while the third term equal custom
  	std::string c = "custom"; 
  	if (!c.compare(argv[3])) {
  		//set a vector to store all popular champions in the matches
  		std::vector<Popular> popular_champs;
  	    Popular one_pop;
  		for (unsigned int i = 0 ; i < matches.size() ; ++i ) {
  			for (unsigned int j = 0 ; j < matches.at(i).get_players().size() ; ++j) {
  				int a = 0; // count number of killers 
  				int b = 0; // count number of assistants
  				one_pop.set_champion_name(matches.at(i).get_players().at(j).get_champion_name()); //set names first 
  				for (unsigned int k = 0 ; k < matches.at(i).get_events().size() ; ++k) {
  					// killer: when the name appears, the count be one
  					if (matches.at(i).get_events().at(k).get_killer() == matches.at(i).get_players().at(j).get_player_name()) {
  						a = 1;
  					}
  					else {
  					}
  					for (unsigned int m = 0 ; m < matches.at(i).get_events().at(k).get_assistant().size() ; ++m) {
  						// assistant: when the name appears, the count be one, no matter how many times..
  						if (matches.at(i).get_events().at(k).get_assistant().at(m) ==  matches.at(i).get_players().at(j).get_player_name()) {
  							b = 1;
  						} 
  					}
  				}
  			one_pop.set_killer(a);   //set killer
  			one_pop.set_assistant(b);  //set assistant
  		    popular_champs.push_back(one_pop);  //store in the vector
  			}
  		}
      sort(popular_champs.begin(),popular_champs.end(),alphabetically);  //sort to be alphabetically first
      unsigned int i = 0;
      while (i < popular_champs.size()) {
          if ( i == popular_champs.size() - 1 ) {
              popular_champs[i].set_KAR();
              break;
          }
          else {
              if (popular_champs[i+1].get_champion_name() != popular_champs[i].get_champion_name()){
                  popular_champs[i].set_KAR();
                  ++i;
              } 
              else {
                  popular_champs[i].set_killer(popular_champs[i].get_killer()+popular_champs[i+1].get_killer()) ;
                  popular_champs[i].set_assistant(popular_champs[i].get_assistant()+popular_champs[i+1].get_assistant()) ;
                  popular_champs.erase(popular_champs.begin()+i+1);
              }
          }
      }

  		//sort to be nice
  		sort(popular_champs.begin(),popular_champs.end());
  		
  		const std::string header = "CHAMPION NAME" + std::string(11, ' ') + "KILLER" + std::string(2, ' ') +  "ASSISTANT" + std::string(4, ' ')+"KAR"+std::string(3, ' ');
  		out_str << header << "\n";
  	    for (unsigned int i = 0 ; i < popular_champs.size(); ++i) {
  		    popular_champs[i].outputs(out_str);
        }
  	}
    return 0; 
}

