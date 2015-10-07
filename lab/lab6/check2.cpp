#include <list>
#include <iostream>

void reverse_list(std::list<int>& lst) {
	int temp;
	if (lst.size() == 1 || lst.size() == 0) {
	}
	else {
		//odd number of elements....
		int temp;
		if ( lst.size()%2 != 0 ) {
			int count = 0;
			std::list<int>::iterator front = lst.begin();
			std::list<int>::reverse_iterator back = lst.rbegin();
			while ( count <= lst.size() / 2) {
				temp = *front;
				*front = *back;
				(*back) = temp;
				front++;
				back++;
				count++;	
			}
		}
		else {
			int count = 0;
			std::list<int>::iterator front = lst.begin();
			std::list<int>::reverse_iterator back = lst.rbegin();
			while ( count < lst.size() / 2) {
				temp = (*front);
				(*front) = (*back);
				(*back) = temp;
				front++;
				back++;
				count++;
			}
		}
	}
}

void print_list (std::list<int>& lst) {
	std::cout << "The size of the list is: " << lst.size() << std::endl;
	std::cout << "The contents of the lstotr: ";
	for (std::list<int>::iterator q = lst.begin(); q != lst.end(); ++q) {
		std::cout << (*q) << "  ";
	}
	std::cout << std::endl;
}


int main() {
	std::list<int> odd;
	for (int i = 0; i < 15; ++i) {
		odd.push_back(i);
	}

	std::list<int> even;
	for (int i = 0; i < 20; ++i) {
		even.push_back(i);
	}

	std::list<int> zero;

	std::list<int> one(1,1);

	std::list<int> two;
	two.push_back(1);
	two.push_back(2);

	std::cout<<"The list with odd number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_list(odd);
	reverse_list(odd);
	std::cout<<"The reverse one: "<<std::endl;
	print_list(odd);

	std::cout<<std::endl;

	std::cout<<"The list with even number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_list(even);
	reverse_list(even);
	std::cout<<"The reverse one: "<<std::endl;
	print_list(even);

	std::cout<<std::endl;

	std::cout<<"The list with zero number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_list(zero);
	reverse_list(zero);
	std::cout<<"The reverse one: "<<std::endl;
	print_list(zero);

	std::cout<<std::endl;

	std::cout<<"The list with one number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_list(one);
	reverse_list(one);
	std::cout<<"The reverse one: "<<std::endl;
	print_list(one);

	std::cout<<std::endl;

	std::cout<<"The list with two number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_list(two);
	reverse_list(two);
	std::cout<<"The reverse one: "<<std::endl;
	print_list(two);


	return 0;

}