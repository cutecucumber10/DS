/*
Title: Homework 1
Author: Jie Cheng
Date: 09/08/2015
Description: This file contains 1 main function and 8 sub-functions. Its functions include
             replacing one kind of pixel with another
			 dilating an image
	         erosing an image
		     floodfilling an image
             opening an image
		     closing an image
	         outlining an image
*/

#include <iostream>
#include <vector>
#include <string> 
#include <fstream>
#include <sstream>

using namespace std;

void printImage(vector< vector<char> > image){
	int row = image.size(), col = image[0].size();
	// print the original image
	cout << "Printing the image:" << endl;
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			cout << image[i][j];
		}
		cout << endl;	
	}
}

bool replace(vector< vector<char> > &image, char oldChar, char newChar){
	int row = image.size(), col = image[0].size();
	if (row == 0 || col == 0){
		cout << "Error: Input image is not 2D!" << endl;
	}
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			if (image[i][j] == oldChar){
				image[i][j] = newChar;
			}
		}
	}
	return true;
}

bool dilation(vector< vector<char> > &image, char targetChar){
	int row = image.size(), col = image[0].size();
	if (row == 0 || col == 0){
		cout << "Error: Input image is not 2D!" << endl;
		return false;
	}
	// create a mirror of the input image
	vector< vector<char> > mirror;
	mirror = image;
	// corner pixels
	if ((mirror[0][1] == targetChar) || (mirror[1][0] == targetChar)) image[0][0] = targetChar; // upper left
	if ((mirror[0][col-2] == targetChar) || (mirror[1][col-1] == targetChar)) image[0][col-1] = targetChar; // upper right
	if ((mirror[row-2][0] == targetChar) || (mirror[row-1][1] == targetChar)) image[row-1][0] = targetChar; // lower left
	if ((mirror[row-1][col-2] == targetChar) || (mirror[row-2][col-1] == targetChar)) image[row-1][col-1] = targetChar; // lower right
	// boundary pixels
	for (int j = 1; j < (col - 1); j++){
		if ((mirror[0][j-1] == targetChar) || (mirror[0][j+1] == targetChar)){
			image[0][j] = targetChar;
		}
		if ((mirror[row-1][j-1] == targetChar) || (mirror[row-1][j+1] == targetChar)){
			image[row-1][j] = targetChar;
		}
	}
	for (int j = 1; j < (row - 1); j++){
		if ((mirror[j-1][0] == targetChar) || (mirror[j+1][0] == targetChar)){
			image[j][0] = targetChar;
		}
		if ((mirror[j-1][col-1] == targetChar) || (mirror[j+1][col-1] == targetChar)){
			image[j][col-1] = targetChar;
		}
	}
	// interior pixels
	for (int i = 1; i < (row - 1); i++){
		for (int j = 1; j < (col - 1); j++){
			if ((mirror[i-1][j] == targetChar) || (mirror[i+1][j] == targetChar) \
				|| (mirror[i][j-1] == targetChar) || (mirror[i][j+1] == targetChar)){
					image[i][j] = targetChar;
				}				
		}
	}
	return true;
}

bool erosion(vector< vector<char> > &image, char targetChar1, char targetChar2){
	int row = image.size(), col = image[0].size();
	if (row == 0 || col == 0){
		cout << "Error: Input image is not 2D!" << endl;
		return false;
	}
	// create a mirror of the input image
	vector< vector<char> > mirror;
	mirror = image;
	// corner pixels
	if ((mirror[0][1] == targetChar2) || (mirror[1][0] == targetChar2)) image[0][0] = targetChar2; // upper left
	if ((mirror[0][col-2] == targetChar2) || (mirror[1][col-1] == targetChar2)) image[0][col-1] = targetChar2; // upper right
	if ((mirror[row-2][0] == targetChar2) || (mirror[row-1][1] == targetChar2)) image[row-1][0] = targetChar2; // lower left
	if ((mirror[row-1][col-2] == targetChar2) || (mirror[row-2][col-1] == targetChar2)) image[row-1][col-1] = targetChar2; // lower right
	// boundary pixels
	for (int j = 1; j < (col - 1); j++){
		if ((mirror[0][j-1] == targetChar2) || (mirror[0][j+1] == targetChar2)){
			image[0][j] = targetChar2;
		}
		if ((mirror[row-1][j-1] == targetChar2) || (mirror[row-1][j+1] == targetChar2)){
			image[row-1][j] = targetChar2;
		}
	}
	for (int j = 1; j < (row - 1); j++){
		if ((mirror[j-1][0] == targetChar2) || (mirror[j+1][0] == targetChar2)){
			image[j][0] = targetChar2;
		}
		if ((mirror[j-1][col-1] == targetChar2) || (mirror[j+1][col-1] == targetChar2)){
			image[j][col-1] = targetChar2;
		}
	}
	// interior pixels
	for (int i = 1; i < (row - 1); i++){
		for (int j = 1; j < (col - 1); j++){
			if ((mirror[i-1][j] == targetChar2) || (mirror[i+1][j] == targetChar2) \
				|| (mirror[i][j-1] == targetChar2) || (mirror[i][j+1] == targetChar2)){
					image[i][j] = targetChar2;
				}				
		}
	}
	return true;
}

int floodfill(vector< vector<char> > &image, int x_loc, int y_loc, char targetChar){
	int row = image.size(), col = image[0].size();
	if (image[x_loc][y_loc] != 'X' || x_loc < 0 || x_loc > row - 1 || y_loc < 0 || y_loc > col - 1){
		return 0;
	}
	else{
		image[x_loc][y_loc] = targetChar;
		int up = floodfill(image, x_loc - 1, y_loc, targetChar);
		int down = floodfill(image, x_loc + 1, y_loc, targetChar);
		int left = floodfill(image, x_loc, y_loc - 1, targetChar);
		int right = floodfill(image, x_loc, y_loc + 1, targetChar);
		return up + left + right + down + 1;
	}
}

bool opening(vector< vector<char> > &image, char targetChar1, char targetChar2){
	bool success1 = erosion(image, targetChar1, targetChar2);
	bool success2 = dilation(image, targetChar1);
	if (success1 && success2){
		return true;
	}
	else
		return false;
}

bool closing(vector< vector<char> > &image, char targetChar1, char targetChar2){
	bool success1 = dilation(image, targetChar1);
	bool success2 = erosion(image, targetChar1, targetChar2);
	if (success1 && success2){
		return true;
	}
	else
		return false;
}

bool outline(vector< vector<char> > &image, char targetChar1, char targetChar2){
	// This function is used to outline an image.
	// All the interior pixels, which are denoted by targetChar1, are replaced by targetChar2.
	int row = image.size(), col = image[0].size();
	if (row == 0 || col == 0){
		cout << "Error: Input image is not 2D!" << endl;
		return false;
	}
	// create a mirror of the input image
	vector< vector<char> > mirror;
	mirror = image;
	// corner pixels
	if ((mirror[0][1] == targetChar1) && (mirror[1][0] == targetChar1)) image[0][0] = targetChar2; // upper left
	if ((mirror[0][col-2] == targetChar1) && (mirror[1][col-1] == targetChar1)) image[0][col-1] = targetChar2; // upper right
	if ((mirror[row-2][0] == targetChar1) && (mirror[row-1][1] == targetChar1)) image[row-1][0] = targetChar2; // lower left
	if ((mirror[row-1][col-2] == targetChar1) && (mirror[row-2][col-1] == targetChar1)) image[row-1][col-1] = targetChar2; // lower right
	// boundary pixels
	for (int j = 1; j < (col - 1); j++){
		if ((mirror[0][j-1] == targetChar1) && (mirror[0][j+1] == targetChar1)){
			image[0][j] = targetChar2;
		}
		if ((mirror[row-1][j-1] == targetChar1) && (mirror[row-1][j+1] == targetChar1)){
			image[row-1][j] = targetChar2;
		}
	}
	for (int j = 1; j < (row - 1); j++){
		if ((mirror[j-1][0] == targetChar1) && (mirror[j+1][0] == targetChar1)){
			image[j][0] = targetChar2;
		}
		if ((mirror[j-1][col-1] == targetChar1) && (mirror[j+1][col-1] == targetChar1)){
			image[j][col-1] = targetChar2;
		}
	}
	// interior pixels
	for (int i = 1; i < (row - 1); i++){
		for (int j = 1; j < (col - 1); j++){
			if ((mirror[i-1][j] == targetChar1) && (mirror[i+1][j] == targetChar1) \
				&& (mirror[i][j-1] == targetChar1) && (mirror[i][j+1] == targetChar1)){
					image[i][j] = targetChar2;
				}				
		}
	}
	return true;
	
}

int main(int argc, char* argv[]){
	if (argc < 4 || argc > 6)
		cerr << "Wrong number of arguments!" << endl;
	else
		cout << "Usage: " << argv[3] << endl;
	ifstream infile(argv[1]);
	if (!infile.good()) {
		cerr << "Can not open the input file " << argv[1] << endl;
		return 1;
	}
	string line;
	vector< vector<char> > image;
	char currentChar;
	int row = 0;
	// read characters into a 2d vector and count # of rows and cols
	while (getline(infile, line)){
		stringstream temp(line);
		image.push_back(vector<char>());
		while (temp >> currentChar){
			image[row].push_back(currentChar);
		}
		row++;
	}
	int col = image[0].size();
	// print
	printImage(image);
	//execute the input commands
	string argv3 = argv[3];
	if (argv3 == "replace"){
		char oldChar = argv[4][0], newChar = argv[5][0];
		bool success = replace(image, oldChar, newChar);
		if (success) {
			cout << "Replacing succeeded!" << endl;
		}
		else
			cout << "Replacing failed!" << endl;
	}
	else if (argv3 == "dilation"){
		char targetChar = argv[4][0];
		bool success = dilation(image, targetChar);
		if (success) {
			cout << "Dilation succeeded!" << endl;
		}
		else
			cout << "Dilation failed!" << endl;
	}
	else if (argv3 == "erosion"){
		char targetChar1 = argv[4][0], targetChar2 = argv[5][0];
		bool success = erosion(image, targetChar1, targetChar2);
		if (success) {
			cout << "Erosion succeeded!" << endl;
		}
		else
			cout << "Erosion failed!" << endl;
	}
	else if (argv3 == "floodfill"){
		istringstream ss1(argv[4]), ss2(argv[5]);
		int x_loc, y_loc;
		if (!(ss1 >> x_loc))
			cerr << "Invalid row number!" << argv[4] << endl;
		if (!(ss2 >> y_loc))
			cerr << "Invalid row number!" << argv[5] << endl;
		char targetChar = argv[6][0];
		int numFilled = floodfill(image, x_loc, y_loc, targetChar);
		cout << "The number of pixels replaced: " << numFilled << endl;
	}
	else if (argv3 == "opening"){
		char targetChar1 = argv[4][0], targetChar2 = argv[5][0];
		bool success = opening(image, targetChar1, targetChar2);
		if (success) {
			cout << "Opening succeeded!" << endl;
		}
		else
			cout << "Opening failed!" << endl;
	}
	else if (argv3 == "closing"){
		char targetChar1 = argv[4][0], targetChar2 = argv[5][0];
		bool success = closing(image, targetChar1, targetChar2);
		if (success) {
			cout << "Closing succeeded!" << endl;
		}
		else
			cout << "Closing failed!" << endl;
	}
	else if (argv3 == "outline"){
		char targetChar1 = argv[4][0], targetChar2 = argv[5][0];
		bool success = outline(image, targetChar1, targetChar2);
		if (success) {
			cout << "Outline succeeded!" << endl;
		}
		else
			cout << "Outline failed!" << endl;
	}
	// print
	printImage(image);
	// write to outputfile
	ofstream outfile(argv[2]);
	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			outfile << image[i][j];
		}
		outfile << endl;	
	}
	outfile.close();

	
	return 0;
}