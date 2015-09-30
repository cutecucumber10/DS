#include "time.h"
#include <iostream>
#include <vector>
#include <algorithm>


int main() {
	
	Time t1(5,14,9);
	std::cout << "Now it's ";
	t1.PrintAmPm();
	std::cout << std::endl;

	Time t2(5,5,1);
	std::cout << "Now it's ";
	t2.PrintAmPm();
	std::cout << std::endl;

	Time t3(14,5,4);
	std::cout << "Now it's ";
	t3.PrintAmPm();
	std::cout << std::endl;

	Time t4 (12,0,0);
	std::cout << "Now it's ";
	t4.PrintAmPm();
	std::cout << std::endl;
	
	std::vector<Time> times;

	times.push_back(t1);
	times.push_back(t2);
	times.push_back(t3);
	times.push_back(t4);

	sort(times.begin(),times.end(), IsEarlierThan);

	for (unsigned int i=0 ; i < times.size(); ++i) {
		times[i].PrintAmPm();
		std::cout << std::endl;
	}
}



