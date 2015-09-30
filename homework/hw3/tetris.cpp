//File name: tetris.cpp
//Purpose: Implementation of Tetris class

#include "tetris.h"
#include <iostream>

Tetris::Tetris(int aWidth) {
	//set up a new tetris
	width = aWidth;
	//create dynamic memory of data and heights
	data = new char*[width];
	heights = new int[width];
	//default height is zero
	//default data[i] length 0
	for (int i = 0; i < width; ++i) {
		heights[i] = 0;
		data[i] = new char[0];
	}
}

const int Tetris::get_max_height() const {
	//get the maximn in heights pointer..
	int max = heights[0];
	for (int i = 1; i < width; ++i) {
		if (heights[i] > max) 
			max = heights[i];
	}
	return max;
}

const int Tetris::get_min_height() const {
	//get minimun in heights pointer (used in remove_full_rows func)
	int min = heights[0];
	for (int i = 1; i < width; ++i) {
		if (heights[i] < min) 
			min = heights[i];
	}
	return min;
}

const int Tetris::count_squares() const {
	//number of piece components in the data
	int count = 0;
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < heights[i]; ++j) {
			if (data[i][j] != ' ') 
				count++;
		}
	}
	return count;
}

void Tetris::destroy() {
	//cleaning up.
	delete [] heights;
	for (int i = 0; i < width; ++i) 
		delete  [] data[i];
	delete [] data;
}

void Tetris::copy_delete(char** &data,char** &data1, int* &heights1) {
	//this function copy data to data1
	//data1 is larger 2D array which can hold the data;
	//heights1 is the heights of data1;
	//data1 is all filled with gaps primarily(because we need to worry
	//about gaps without filled in pieces.)
	//then copy all the values in data, leave those unused ' ';
	//then delete heaps of data and height
	//data points to data1; heights points to heights1; 
	//first fill in all squares with ' '
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < heights1[i];++j) 
			data1[i][j] = ' ';
	}
	//copy from old data
	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < heights[i]; ++j)
			data1[i][j] = data[i][j];
	}
	//delete from heaps
	for (int i = 0; i < width; ++i) 
		delete  [] data[i];	
	delete [] data;
	delete [] heights;
	//data equals new value
	data = data1;
	heights = heights1;
}

int Tetris::remove_full_rows(){
	//remove a row if the row is full of squares.....
	int scores = 0; 
	int i = 0;
	while (i < get_min_height()) {
		//removing can only happen in row with all filled
		//so min_height is essential
		int count = 0;
		for (int j = 0; j < width; ++j ) {
			if (data[j][i] != ' ')
				count++;
		}
		//if the count equals the width, it means no gaps, need to remove
		if  (count == width) {
			char** data1 = new char*[width];
			int* heights1 = new int[width];
			scores++;
		//if need to remove, create new data1, copy everything except 
		//that line, also deducting every heights element by 1
			for (int j = 0; j < width; ++j) {
				heights1[j] = heights[j] - 1;
				data1[j] = new char[heights1[j]];
			}
			for (int j = 0; j < width; ++j) {
				int new_row = 0;
				for (int k = 0; k < heights[j]; ++k) {
					if (k != i) {
						data1[j][new_row] = data[j][k];
						new_row++;
					}
				}
			}
		//every time finds a removing row, create new... and delete old.
			delete [] heights;
			for (int m = 0; m <width;++m)
				delete [] data[m];
			delete []data;
			data = data1;
			heights = heights1;
			}
		//if not removing, keep on.
		else {
			++i;
		}
	}
	//check if heights counts the gaps....
	//if yes, remove heights by reducing heights first
	//if no, break immediately
	for (int j = 0; j < width; ++j) {
		int count = 0;
		//check from top to bottom, find the highest square
		//and count how many gaps is above the highest square
		for (int k = heights[j]-1; k >=0; --k) {
			if (data[j][k] == ' '){
				count ++;
			}
			else 
				break;
		}
		heights[j] = heights[j] - count;
	}
	//create a new **data to store correct gaps....
	char** data1 = new char*[width];
	for (int j = 0; j < width; ++j) 
		data1[j] = new char[heights[j]];
	for (int j = 0; j < width; ++j) {
		for (int k = 0; k < heights[j]; ++k) 
			data1[j][k] = data[j][k];
	}
	//clean up
	for (int j = 0; j < width; ++j) 
		delete [] data[j];
	delete []data;
	data = data1;
	return scores;
}

void Tetris::add_left_column() {
	//add a column to be the first col, copy other.
	width += 1;
	//create new data and heights
	int* heights1 = new int[width];
	char** data1 = new char*[width];
	for (int i = 0; i < width; i++) {
		if (i == 0) 
			//leftest height 0
			heights1[i] = 0;
		else
			//heights1 width [1] = heights width [0] 
			heights1[i] = heights[i-1];
	}
	for (int i = 0; i < width; i++) 
		data1[i] = new char[heights1[i]];
	for (int i = 1; i < width; i++) {
		for (int j = 0; j < heights1[i]; j++) 
			data1[i][j] = data[i-1][j];
	}
	for (int i = 0; i < width-1; i++)
		delete [] data[i];
	delete [] data;
	delete [] heights;
	data = data1;
	heights = heights1;
}

void Tetris::add_right_column() {
	//add a col to be the last col, other unchanged
	width += 1;
	//create new data and heights
	int* heights1 = new int[width];
	char** data1 = new char*[width];
	for (int i = 0; i < width; i++) {
		if (i < width-1) 
			heights1[i] = heights[i];
		else
			//last height is 0
			heights1[i] = 0;
	}
	for (int i = 0; i < width; i++) 
		data1[i] = new char[heights1[i]];
	for (int i = 0; i < width-1; i++) {
		//no need to copy last col..
		for (int j = 0; j < heights1[i]; j++)
			data1[i][j] = data[i][j];
	}
	//delete dynamic data..avoid memory leak
	for (int i = 0; i < width-1; i++)
		delete [] data[i];
	delete [] data;
	delete [] heights;
	data = data1;
	heights = heights1;
}

void Tetris::remove_left_column() {
	//delete the first col
	width -= 1;
	//create new data and heights
	int* heights1 = new int[width];
	char** data1 = new char*[width];
	for (int i = 0; i < width; i++) 
		heights1[i] = heights[i+1];
	for (int i = 0; i < width; i++) 
		data1[i] = new char[heights1[i]];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heights1[i]; j++)
			//data1 col 0 = data col 1
			data1[i][j] = data[i+1][j];
	}
	//delete dynamic data..avoid memory leak
	for (int i = 0; i < width+1; i++)
		delete [] data[i];
	delete [] data;
	delete [] heights;
	data = data1;
	heights = heights1;
}

void Tetris::remove_right_column() {
	//delete the right col
	width -= 1;
	//create new data and heights
	int* heights1 = new int[width];
	char** data1 = new char*[width];
	for (int i = 0; i < width; i++) 
		heights1[i] = heights[i];
	for (int i = 0; i < width; i++) 
		data1[i] = new char[heights1[i]];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heights1[i]; j++)
			//no need to worry last col
			data1[i][j] = data[i][j];
	}
	for (int i = 0; i < width+1; i++)
		delete [] data[i];
	delete [] data;
	delete [] heights;
	data = data1;
	heights = heights1;
}

void Tetris::add_piece(const char &piece_name, const int rotation, const int placement ) {
	///all the if statements are under same structure (not so much change....)
	///(except details in setting heights and data and replace piecename.... )
	///get a new_height variable to construct new *height pointer
	///and create a new **data pointer which has the element of new *height
	///then use copy and delete to copy values from old data 
	///then delete all the memory leaks (the function include copy and delete)
	///in the function the new data is firstly filled with ' ' in all possible 
	///squares, then exsiting squares in the old data are copied from old data
	///finally the function deleted [] data* and []heightand point data to
	///data1 and height to height1.
	///Then the function finishes
	///in the final part of the if statements, replace ' ' with piece_name in 
	///appropriate place.
	if (piece_name == 'O') {
		///no matter the rotation is....
		//////////////The piece look like                          ///////////
		//////////////   new_height->     O O                      ///////////
		//////////////                    O O                      ///////////
		//Find the higher height within the piece range
		int new_height;
		if (heights[placement] > heights[placement+1])
			new_height = heights[placement];
		else
			new_height = heights[placement+1];
		new_height += 2;
		//create data1 to store new piece and old piece
		int *heights1 = new int[width];
		//creae a new height to store new heights
		char **data1 = new char*[width];
		//set up heights and data
		for (int i = 0; i < width; ++i) {
			if (i==placement || i ==(placement+1) ) {
				data1[i] = new char[new_height];
				heights1[i] = new_height;
			}
			else {
				data1[i] = new char[heights[i]];
				heights1[i] = heights[i];
			}
		}
		copy_delete(data,data1,heights1);
		//change the gap into piecename
		data[placement][new_height-1] = piece_name;
		data[placement+1][new_height-1] = piece_name;
		data[placement][new_height-2] = piece_name;
		data[placement+1][new_height-2] = piece_name;
	}

	else if (piece_name == 'I') {
		if (rotation == 0 || rotation == 180) {
			/////////////The piece looks like     ///////////////////////////
			/////////////  new_height ->    I     ///////////////////////////
			/////////////                   I     ///////////////////////////
			/////////////                   I     ///////////////////////////
			/////////////                   I     ///////////////////////////
			// find the height of the placement position....
			int new_height;
			new_height = heights[placement]+4;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			for (int i = 0; i < width; ++i) {
				if (i==placement){
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height-2] = piece_name;
			data[placement][new_height-3] = piece_name;
			data[placement][new_height-4] = piece_name;
		}
		else {
			/////////////The piece looks like     ///////////////////////////
			/////////////  new_height ->    I I I I    //////////////////////
			//Find the new height within the piece range
			int new_height = heights[placement];
			for (int i = placement; i < placement+4; ++i) {
				if (heights[i] > new_height)
					new_height = heights[i];
			}
			new_height += 1;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i==placement+1 || i==placement +2 || i==placement +3) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
			data[placement+3][new_height-1] = piece_name;
		}
	}
	else if (piece_name == 'T') {
		int new_height;
		if (rotation == 0) {
			/////////////The piece looks like     ///////////////////////////
			///////////// new_height ->     T T T    ////////////////////////
			////////////                      T      ////////////////////////
			//Find the new height within the piece range
			if ((heights[placement+1] >= heights[placement]) && \
				(heights[placement+1] >= heights[placement+2]) )
				new_height = heights[placement+1]+2;
			else {
				if (heights[placement] > heights[placement+2])
					new_height = heights[placement]+1;
				else 
					new_height = heights[placement+2]+1;
			}
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i==placement+1 || i==placement+2 ) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height-2] = piece_name;
			data[placement+2][new_height-1] = piece_name;

		}
		else if (rotation == 90) {
			/////////////The piece looks like     ///////////////////////////
			/////////////                    T     //////////////////////////
			/////// new_height ->          T T      /////////////////////////
			/////////////                    T     //////////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1] )
				new_height = heights[placement]+1;
			else
				new_height = heights[placement+1]+2;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement+1){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}

				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height-2] = piece_name;

		}
		else if (rotation == 180) {
			/////////////The piece looks like     ///////////////////////////
			/////////////                     T      ////////////////////////
			////////// new_height ->        T T T    ////////////////////////
			//Find the new height within the piece range
			new_height = heights[placement];
			for (int i = placement; i < placement+3; ++i) {
				if (heights[i] > new_height)
					new_height = heights[i];
			}
			new_height +=1;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i == placement || i == placement+2) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement+1){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}

				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
		}
		else if (rotation == 270) {
			/////////////The piece looks like     ///////////////////////////
			/////////////                     T      ////////////////////////
			////////// new_height ->          T T    ////////////////////////
			/////////////                     T      ////////////////////////
			//Find the new height within the piece range
			if (heights[placement] >= heights[placement+1] )
				new_height = heights[placement]+2;
			else
				new_height = heights[placement+1]+1;
			//create data1 to store new piece and old piece	
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement) {
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else if (i==placement+1){
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}

				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height-2] = piece_name;
			data[placement][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
		} 
	}
	else if (piece_name == 'Z') {
		int new_height;
		if (rotation == 0 || rotation == 180) {
			/////////////The piece looks like            ////////////////////
			////////// new_height ->          Z Z        ////////////////////
			/////////////                       Z Z      ////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1] && \
			    heights[placement] > heights[placement+2])
			    new_height = heights[placement]+1;
			else{
				if (heights[placement+1] > heights[placement+2] )
					new_height = heights[placement+1] +2;
				else
					new_height = heights[placement+2] +2;
			}
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i==placement+1) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement+2){
					data1[i] = new char[new_height-1];
					heights1[i] = new_height-1;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height-2] = piece_name;
			data[placement+2][new_height-2] = piece_name;
		}
		else if (rotation == 90 || rotation == 270) {
			/////////////The piece looks like            ////////////////////
			//////////                          Z        ////////////////////
			///////////  new_height ->        Z Z        ////////////////////
			/////////////                     Z          ////////////////////
			//Find the new height within the piece range
			if (heights[placement] >= heights[placement+1])	
				new_height = heights[placement]+2;
			else 
				new_height = heights[placement+1]+1;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement+1){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height-2] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height] = piece_name;
		}
	}
	else if (piece_name == 'S') {
		int new_height;
		if (rotation == 0 || rotation == 180) {
			/////////////The piece looks like            ///////////////////
			//////////                        S S        ///////////////////
			///////////new_height ->        S S         ////////////////////
			//Find the new height within the piece range
			if (heights[placement+2] > heights[placement+1] && \
			    heights[placement+2] > heights[placement])
			    new_height = heights[placement+2];
			else{
				if (heights[placement+1] > heights[placement] )
					new_height = heights[placement+1] +1;
				else
					new_height = heights[placement] +1;
			}
			//create data1 to store new piece and old piece			
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement+2 || i==placement+1) {
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else if (i==placement){
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height] = piece_name;
			data[placement+2][new_height] = piece_name;
		}
		else if (rotation == 90 || rotation == 270) {
			/////////////The piece looks like            ////////////////////
			//////////                        S          ////////////////////
			///////////  new_height ->        S S        ////////////////////	
			/////////////                       S        ////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1])
				new_height = heights[placement]+1;
			else 
				new_height = heights[placement+1]+2;
			//create data1 to store new piece and old piece		
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement+1) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height-2] = piece_name;
		}
	}
	else if (piece_name == 'L') {
		int new_height;
		if (rotation == 0) {
			/////////////The piece looks like            ////////////////////
			//////////                        L          ////////////////////
			///////////                       L          ////////////////////	
			///////////// new_height ->       L L        ////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1])
				new_height = heights[placement] +1;
			else 
				new_height = heights[placement+1] +1; 	
			//create data1 to store new piece and old piece	
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement) {
					data1[i] = new char[new_height+2];
					heights1[i] = new_height+2;
				}
				else if (i==placement+1){
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height] = piece_name;
			data[placement][new_height+1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
		}
		else if (rotation == 90) {
			/////////////The piece looks like            ////////////////////
			//////////    new_height ->        L l l     ////////////////////	
			/////////////                      L         ////////////////////
			//Find the new height within the piece range
			if (heights[placement] >= heights[placement+1] && \
				heights[placement] >= heights[placement+2])
				new_height = heights[placement]+2;
			else {
				if (heights[placement+1] > heights[placement+2])
					new_height = heights[placement+1]+1;
				else
					new_height = heights[placement+2]+1;
			}		
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i == placement+1 || i == placement+2) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height-2] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
		}
		else if (rotation == 180) {
			/////////////The piece looks like            ////////////////////
			//////////    new_height ->     l L         ////////////////////
			///////////                       L          ////////////////////	
			/////////////                     L          ////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1]+1 ) 
				new_height = heights[placement]+1;
			else 
				new_height = heights[placement+1]+3;
			//create data1 to store new piece and old piece			
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i == placement+1) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+1][new_height-2] = piece_name;
			data[placement+1][new_height-3] = piece_name;
		}
		else if (rotation == 270) {
			/////////////The piece looks like            ////////////////////	
			/////////////                          L     ////////////////////
			//////////    new_height ->        L l l     ////////////////////
			//Find the new height within the piece range
			new_height = heights[placement];
			for (int i = placement; i < placement+3; ++i) {
				if (heights[i] > new_height)
					new_height = heights[i];
			}
			new_height +=1;			
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i == placement || i == placement+1) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement+2){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+2][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
		}
	}
	else if (piece_name == 'J') {
		int new_height;
		if (rotation == 0) {
			/////////////The piece looks like            ////////////////////
			//////////                        J          ////////////////////
			///////////                       J          ////////////////////	
			///////////// new_height ->     J J          ////////////////////
			//Find the new height within the piece range
			if (heights[placement] > heights[placement+1])
				new_height = heights[placement] +1;
			else 
				new_height = heights[placement+1] +1;
			//create data1 to store new piece and old piece 		
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement+1) {
					data1[i] = new char[new_height+2];
					heights1[i] = new_height+2;
				}
				else if (i==placement){
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+1][new_height] = piece_name;
			data[placement+1][new_height+1] = piece_name;
			data[placement+1][new_height-1] = piece_name;
		}
		else if (rotation == 90) {
			/////////////The piece looks like            ////////////////////	
			/////////////                      J         ////////////////////
			//////////    new_height ->        J J J     ////////////////////
			/////almost same as T....copy.............../////////////////////
			//Find the new height within the piece range
			new_height = heights[placement];
			for (int i = placement; i < placement+3; ++i) {
				if (heights[i] > new_height)
					new_height = heights[i];
			}
			new_height +=1;
			//create data1 to store new piece and old piece			
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i == placement+1 || i == placement+2) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else if (i==placement){
					data1[i] = new char[new_height+1];
					heights1[i] = new_height+1;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
		}
		else if (rotation == 180) {
			/////////////The piece looks like            ////////////////////
			//////////    new_height ->       J J        ////////////////////
			///////////                       J          ////////////////////	
			/////////////                     J          ////////////////////
			//Find the new height within the piece range
			if (heights[placement+1] > heights[placement]+1 ) 
				new_height = heights[placement+1]+1;
			else 
				new_height = heights[placement]+3;
			//create data1 to store new piece and old piece
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i == placement+1) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement][new_height-2] = piece_name;
			data[placement][new_height-3] = piece_name;
			data[placement+1][new_height-1] = piece_name;
		}
		else if (rotation == 270) {
			/////////////The piece looks like            ////////////////////
			//////////    new_height ->        J J J     ////////////////////	
			/////////////                          J     ////////////////////
			//Find the new height within the piece range
			if (heights[placement+2] >= heights[placement+1] && \
				heights[placement+2] >= heights[placement])
				new_height = heights[placement+2]+2;
			else {
				if (heights[placement] > heights[placement+1])
					new_height = heights[placement]+1;
				else
					new_height = heights[placement+1]+1;
			}	
			//create data1 to store new piece and old piece	
			char **data1 = new char*[width];
			int *heights1 = new int[width];
			//set up heights and data
			for (int i = 0; i < width; ++i) {
				if (i==placement || i == placement+1 || i == placement+2) {
					data1[i] = new char[new_height];
					heights1[i] = new_height;
				}
				else {
					data1[i] = new char[heights[i]];
					heights1[i] = heights[i];
				}
			}
			copy_delete(data,data1,heights1);
			//change the gap into piecename
			data[placement][new_height-1] = piece_name;
			data[placement+2][new_height-2] = piece_name;
			data[placement+1][new_height-1] = piece_name;
			data[placement+2][new_height-1] = piece_name;
		}
	}
}