//File name: Tetris.h
//Purpose: Header file for declearation function including
     //1) add piece
     //2) remove full rows
	 //3) remove/add right/left column
     //4) destroy
	 //5) copy&delete
	 //6) get max/min heights
	 //7) count squares
	 //8) get width/count squares
	 //9) print 

#ifndef tetris_h
#define tetris_h

class Tetris {
	public:
		Tetris(int aWidth);
		
		//Accessors
		const int get_width() const {return width; }
		////get the maximn in heights pointer..
		const int get_max_height() const;
		////get the minimn in heights pointer..
		const int get_min_height() const;
		////count total number of piece components in the data
		const int count_squares() const;

		//Modifiers
		////add pieces function   const means I do not want to change the value of each of 
		////my arguments and &means I do not need a copy.....
		void add_piece(const char &piece_name, const int rotation, const int placement );
		////remove a row if the row if full
		int remove_full_rows();
		////add a col before the first col
		void add_left_column();
		////add a col behind last col
		void add_right_column();
		////delete the first col
		void remove_left_column();
		////delete the last col
		void remove_right_column();

		//Other member functions
		////clean up functions
		void destroy(); 
		////copy a data to a new data...(use in add_piece function)
		void copy_delete(char** data,char** data1, int* heights1);
		////a print function...implement in main.cpp
		void print() const;

	private:
		int width;
		////1D array
		int *heights;
		////2D array
		char **data;
};

#endif