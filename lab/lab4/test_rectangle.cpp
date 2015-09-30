#include "Rectangle.h"
#include <iostream>

int main() {
	//test: create several rectangles and print them
	Point2D p1(2,4);
	Point2D p2(30,36);
	Point2D p3(20,15);
	Point2D p4(50,60);
	Rectangle r1(p1,p2);
	print_rectangle(r1);
	Rectangle r2(p3,p4);
	print_rectangle(r2);

	//test: check if the function is point within work properly
	Point2D p5(3,5); 
	Point2D p6(1,2);
	std::cout<<r1.is_point_within(p5)<<std::endl;
	std::cout<<r1.is_point_within(p6)<<std::endl;  

	
	//test: check add points
	Point2D p7(25,25);
	std::cout<<r1.add_point(p5)<<std::endl;  //in the box
	print_rectangle(r1);
	std::cout<<r1.add_point(p6)<<std::endl;  //out of the box
	print_rectangle(r1); 
	std::cout<<r1.add_point(p7)<<std::endl;  //in box r1
	print_rectangle(r1);
	std::cout<<r2.add_point(p7)<<std::endl;  //in box r2
	print_rectangle(r2);


	//test: contained within both rectangles
	std::vector<Point2D> points = points_in_both(r1,r2);
	std::cout<<points.size()<<std::endl;

	Point2D pt(1,1);
	pt.set(2,2);

	return 0;
}