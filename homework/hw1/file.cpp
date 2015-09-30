#include <iostream>
#include <fstream>
//#include <ofstream> //
//#include <ifstream> //
#include <string> 
using namespace std; //


int main() {
    std::string lines;
    int line_array[100];
    int i;
    i = 0;
    ifstream  inputs ("input4.txt");
    if(file_.is_open()) {
        while(getline(inputs,lines)) {
            std::cout<<lines<<'\n';
            line_array[i] = lines;
            lines = "";
            i = i + 1;
        }
        file_.close();
    }
    else
        std::cout<<"file is not open"<<'\n';
    std::cin.get();
    for (i=0, i<100, i=i+1) {
        std::cout<< line_array[i]<<std::endl;
    }
    }