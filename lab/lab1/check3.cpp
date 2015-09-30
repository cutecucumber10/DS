#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function

int main() {
	int a;   //how many numbers
	float numbers[100];
	int i;
	float total;
	float ave;
	total = 0;
	std::cout << "Number of numbers" << std::endl;
	std::cin >> a;
	std::cout << "Enter your numbers" << std::endl;
	for (i = 0; i < a; i = i + 1)  {
    	std::cin >> numbers[i];
  	}
  	for (i = 0; i < a; i = i + 1) {
  		total = total + numbers[i];
  	}
  	ave = total / a;
  	std::cout << ave << std::endl;
  	for (i = 0; i < a; i = i + 1) {
  		if (numbers[i] < ave) {
  			std::cout << numbers[i] << std::endl;
  		}
  	}

 
}