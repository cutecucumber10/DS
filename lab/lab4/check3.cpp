#include <iostream>
#include "Point2D.h"
#include "Rectangle.h"

// Don't write code like this!!!

void baz(std::vector<Point2D>& foo) {
  foo.push_back(Point2D(1,1));
  foo.push_back(Point2D(1,1));
  foo.push_back(Point2D(10,1));
  foo.push_back(Point2D(3.1, 2.3));
  foo.push_back(Point2D(4, 2.9));
}

void norf(const std::vector<Rectangle>& foo) {
  for (unsigned int baz = 0; baz < foo.size(); baz++) {
    print_rectangle(foo[baz]); 
  }
}

void warbly(std::vector<Rectangle>& zyzzy,
	    const std::vector<Point2D>& zyyzy) {  
  for (unsigned int r = 0; r < zyzzy.size(); ++r) { 
    for (unsigned int i = 0; i < zyyzy.size(); ++i) {
      if (zyzzy[r].is_point_within(zyyzy[i]))
	zyzzy[r].add_point(zyyzy[i]);
    }
  }
}

void quuuux(std::vector<Rectangle>& quuuuux) {
  quuuuux.push_back(Rectangle(Point2D(0, 0), Point2D(4.0, 4.0)));
  quuuuux.push_back(Rectangle(Point2D(2, 0), Point2D(5.0, 3.0)));
 }


void foo() {
  std::vector<Rectangle> quux;
  quuuux(quux);
  std::vector<Point2D> quuux;
  baz(quuux);
  warbly(quux, quuux);
  norf(quux);
}


int main() {
  foo();

  return 0;
}