//File name: Tetris.h
//Purpose: Header file for declearation function including
     //1) add piece
     //2) remove full rows
	 //3) remove right column
     //4) destroy

#ifndef tetris_h
#define tetris_h

#include <string>

class Tetris {
	public:
		Tetris(int aWidth);
		
		//Accessors
		const int get_width() const {return width; }
		const int get_max_height() const;
		const int get_min_height() const;
		const int count_squares() const;

		//Modifiers
		void add_piece(const char &piece_name, int rotation, int placement );
		int remove_full_rows();
		void remove_right_column(int new_width);
		void add_left_column();
		void add_right_column();
		void remove_left_column();
		void remove_right_column();

		//Other member functions
		void destroy(); 
		void copy_delete(char** &data,char** &data1, int* heights1);
		void print() const;

	private:
		int width;
		int *heights;
		char **data;
};

#endif