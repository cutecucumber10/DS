/*
HOMEWORK 1: MORPHOLOGICAL IMAGE PROCESSING
NAME:  < Xinyue Yan  yanx3>
*/

#include <iostream>
#include <fstream>  //Input file stream class <http://www.cplusplus.com/reference/fstream/ifstream/>
#include <string>
#include <vector>
#include <cstdlib>

std::vector<std::string> replace(std::vector<std::string> inputs, char exist, char after) {
	std::vector<std::string> results(inputs) ; //create a copy of inputs
	for (unsigned int k = 0 ; k < inputs.size() ; ++k ) {   //loop to find the point equal exist
		for (unsigned int j = 0 ; j < inputs[k].size() ; ++j) {
			if (inputs[k][j] == exist) {
				results[k][j] = after;
			}
		}	
	}
	return results;
}

std::vector<std::string> dilation(std::vector<std::string> inputs, char exist) {
	std::vector<std::string> results(inputs) ;
	// loop inside the box
	for (unsigned int k = 1 ; k < inputs.size()-1 ; ++k ){
		for (unsigned int j = 1 ; j < inputs[k].size()-1 ; ++j ) {
			if (inputs[k][j] != exist) {
				if (inputs[k+1][j] == exist ) {
					results[k][j] = exist;
				}
				else if (inputs[k-1][j] == exist ) {
					results[k][j] = exist;
				}
				else if (inputs[k][j-1] == exist ) {
					results[k][j] = exist;
				}
				else if (inputs[k][j+1] == exist) {
					results[k][j] = exist;
				}
			}
		}
	}
	// left top 
	if ((inputs[0][1] == exist) or (inputs[1][0] == exist)) {
		results[0][0] = exist;
	}
	// right top
	if ((inputs[0][inputs[0].size()-2] == exist) or (inputs[1][inputs[0].size()-1] == exist)) {
		results[0][inputs[0].size()-1] = exist;
	}
	// right down 
	if ((inputs[inputs.size()-2][inputs[0].size()-1] == exist) or (inputs[inputs.size()-1][inputs[0].size()-2] == exist)) {
		results[inputs.size()-1][inputs[0].size()-1] = exist;
	}
	// left down
	if ((inputs[inputs.size()-2][0] == exist) or (inputs[inputs.size()-1][1] == exist)) {
		results[inputs.size()-1][0] = exist;
	}
	// first row  right left down// last row  right left up
	for (unsigned int i = 1; i < inputs[0].size()-1; ++i ) {  
		if ((inputs[0][i+1] == exist) or (inputs[0][i-1] == exist) or (inputs[1][i] == exist)) {
			results[0][i] = exist;
		}
		if ((inputs[inputs.size()-1][i+1] == exist) or (inputs[inputs.size()-1][i-1] == exist) or (inputs[inputs.size()-2][i] == exist)) {
			results[inputs.size()-1][i] = exist;
		}
	}
	// first col   down up right// last col  down up left
	for (unsigned int i = 1; i < inputs.size()-1; ++i ) {  
		if ((inputs[i+1][0] == exist) or (inputs[i-1][0] == exist) or (inputs[i][1] == exist)) {
			results[i][0] = exist;
		}
		if ((inputs[i+1][inputs[i].size()-1] == exist) or (inputs[i-1][inputs[i].size()-1] == exist) or (inputs[i][inputs[i].size()-2] == exist)) {
			results[i][inputs[i].size()-1] = exist;
		}
	}
	return results;
}

std::vector<std::string> erosion(std::vector<std::string> inputs, char exist, char after) {
	std::vector<std::string> results(inputs) ;
	// loop inside the box
	for (unsigned int k = 1 ; k < inputs.size()-1 ; ++k ){
		for (unsigned int j = 1 ; j < inputs[k].size()-1 ; ++j ) {
			if (inputs[k][j] == exist) {
				if (inputs[k+1][j] == after ) {
					results[k][j] = after;
				}
				else if (inputs[k-1][j] == after ) {
					results[k][j] = after;
				}
				else if (inputs[k][j-1] == after ) {
					results[k][j] = after;
				}
				else if (inputs[k][j+1] == after) {
					results[k][j] = after;
				}
			}
		}
	}
	// left top 
	if ((inputs[0][0] == exist) and ((inputs[0][1] == after) or (inputs[1][0] == after))) {
		results[0][0] = after;
	}
	// right top
	if ((inputs[0][inputs[0].size()-1] == exist) and ((inputs[0][inputs[0].size()-2] == after) or (inputs[1][inputs[0].size()-1] == after))) {
		results[0][inputs[0].size()-1] = after;
	}
	// right down 
	if ((inputs[inputs.size()-1][inputs[0].size()-1]) and ((inputs[inputs.size()-2][inputs[0].size()-1] == after) or (inputs[inputs.size()-1][inputs[0].size()-2] == after))) {
		results[inputs.size()-1][inputs[0].size()-1] = after;
	}
	// left down
	if ((inputs[inputs.size()-1][0] == exist) and ((inputs[inputs.size()-2][0] == after) or (inputs[inputs.size()-1][1] == after))) {
		results[inputs.size()-1][0] = after;
	}
	// first row  right left down// last row  right left up
	for (unsigned int i = 1; i < inputs[0].size()-1; ++i ) {  
		if (inputs[0][i] == exist) {
			if ((inputs[0][i+1] == after) or (inputs[0][i-1] == after) or (inputs[1][i] == after)) {
				results[0][i] = after;
			}
		}
		if (inputs[inputs.size()-1][i] == exist) {
			if ((inputs[inputs.size()-1][i+1] == after) or (inputs[inputs.size()-1][i-1] == after) or (inputs[inputs.size()-2][i] == after)) {
				results[inputs.size()-1][i] = after;
			}
		}
	}
	// first col   down up right// last col  down up left
	for (unsigned int i = 1; i < inputs.size()-1; ++i ) { 
		if (inputs[i][0] == exist) { 
			if ((inputs[i+1][0] == after) or (inputs[i-1][0] == after) or (inputs[i][1] == after)) {
				results[i][0] = after;
			}
		}
		if (inputs[i][inputs[i].size()-1]) {
			if ((inputs[i+1][inputs[i].size()-1] == after) or (inputs[i-1][inputs[i].size()-1] == after) or (inputs[i][inputs[i].size()-2] == after)) {
				results[i][inputs[i].size()-1] = after;
			}
		}
	}
	return results;
}

void floodfill(std::vector<std::string> &inputs,unsigned int a, unsigned int b, char after) {
	// if outside the matrix or not valid, return inputs
	unsigned int row = inputs.size(), col = inputs[0].size();
	if ((a < 0) || (a > (row-1)) || (b < 0) || (b > (col-1)) || (inputs[a][b] != 'X')) {
	}
	else {
		//replace with new char
		inputs[a][b] = after;
		//up down left right
		floodfill(inputs, a-1, b, after);
		floodfill(inputs, a+1, b, after);
		floodfill(inputs, a, b-1, after);
		floodfill(inputs, a, b+1, after);
	}
}

int main(int argc, char* argv[]) {
	//error messagea
	if  (argc != 5 and argc != 6 and argc != 7) {
		std::cerr << "arguments can not be fit in" << argv[0] ;
		return 1;
	}
	std::string row;
	std::ifstream myFile(argv[1]);

	if (!myFile.good()) {
		std::cerr << "The file is not correct!" << argv[1] << "\n";
	}
	//std::string row; //input each row to a string
	std::vector<std::string> inputs; //Input vectors to hold all the points
	while (std::getline(myFile, row)) {
		inputs.push_back(row);
	}
	std::cout << "The input:"<<std::endl; //print out the input
	for (unsigned int i = 0 ; i < inputs.size() ; ++i ) {
		std::cout << inputs[i] << std::endl;
	}
///////////starts to do the replace, dialation, erosion and floodfill
	std::vector<std::string> results; // create a vector called results for later print out 
	// dilation
	if (argc == 5) {
		results = dilation(inputs, argv[4][0]);
		for (unsigned int i = 0 ; i < results.size() ; ++i ) {
			std::cout << results[i] << std::endl;
		}
	}
	//replace+erosion
	if (argc == 6) {
		std::string a = "replace";
		std::string b = "erosion";
		if (!a.compare(argv[3])) {
			results = replace(inputs, argv[4][0], argv[5][0]);
		}
		if (!b.compare(argv[3])) {
			results = erosion(inputs, argv[4][0], argv[5][0]);
		}
	}
	//floodfill
	if (argc ==7) {
		//convert the string in arguments to integers
		int r = atoi(argv[4]);
		int c = atoi(argv[5]);
		char temp = argv[6][0];
		floodfill(inputs, r, c, temp);
		results = inputs;
	}
	std::cout << "The output:"<<std::endl;
	//print out the output
	for (unsigned int i = 0 ; i < results.size() ; ++i ) {
		std::cout << results[i] << std::endl;
	}
	//output to a file
	std::ofstream outputs;
	outputs.open(argv[2]);
	for (unsigned int i = 0 ; i < results.size() ; ++i) {
		outputs << results[i] <<"\n" ;
	}
	outputs.close();
	return 0;
}
