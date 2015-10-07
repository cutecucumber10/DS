#include <vector>
#include <iostream>

void reverse_vector(std::vector<int>& vec) {
	int temp;
	int front;
	int back;
	if (vec.size() == 1 || vec.size() == 0) {

	}
	else {
		//odd number of elements....
		if ( vec.size()%2 != 0 ) {
			front = (vec.size() / 2) - 1;
			back = (vec.size() / 2) + 1;
		}
		//even number of elements.....
		else if (vec.size()%2 == 0 ) {
			front = (vec.size() / 2) - 1;
			back = (vec.size() / 2); 
		}
		//swap values.....
		while (front >= 0 && back < vec.size()) {
			temp = vec[front];
			vec[front] = vec[back];
			vec[back] = temp;
			front--;
			back++;
		}
	}
}

void print_vector (const std::vector<int>& vec) {
	std::cout << "The size of the vector is: " << vec.size() << std::endl;
	std::cout << "The contents of the vecotr: ";
	for (int i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << "  ";
	}
	std::cout << std::endl;
}

int main() {
	std::vector<int> odd;
	for (int i = 0; i < 15; ++i) {
		odd.push_back(i);
	}

	std::vector<int> even;
	for (int i = 0; i < 20; ++i) {
		even.push_back(i);
	}

	std::vector<int> zero;

	std::vector<int> one(1,1);

	std::vector<int> two;
	two.push_back(1);
	two.push_back(2);



	std::cout<<"The vector with odd number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_vector(odd);
	reverse_vector(odd);
	std::cout<<"The reverse one: "<<std::endl;
	print_vector(odd);

	std::cout<<std::endl;

	std::cout<<"The vector with even number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_vector(even);
	reverse_vector(even);
	std::cout<<"The reverse one: "<<std::endl;
	print_vector(even);

	std::cout<<std::endl;

	std::cout<<"The vector with zero number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_vector(zero);
	reverse_vector(zero);
	std::cout<<"The reverse one: "<<std::endl;
	print_vector(zero);

	std::cout<<std::endl;

	std::cout<<"The vector with one number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_vector(one);
	reverse_vector(one);
	std::cout<<"The reverse one: "<<std::endl;
	print_vector(one);

	std::cout<<std::endl;

	std::cout<<"The vector with two number of elements:"<<std::endl;
	std::cout<<"The original one: "<<std::endl;
	print_vector(two);
	reverse_vector(two);
	std::cout<<"The reverse one: "<<std::endl;
	print_vector(two);


	return 0;
} 