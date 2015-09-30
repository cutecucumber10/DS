#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0 
bool check_root(int a, int b, int c, float root) {  
  // plug the value into the formula
  float check = a * root * root + b * root + c;
  // see if the absolute value is zero (within a small tolerance)
  if (fabs(check) > 0.0001) {
    std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
    return false;
  } else {
    return true;
  }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns 
true if the roots are real, returns false if the roots are imaginary.  If the roots 
are real, they are returned through the reference parameters root_pos and root_neg. */ 
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
  // compute the quantity under the radical of the quadratic formula
  int radical = b*b - 4*a*c;
  // if the radical is negative, the roots are imaginary
  if (radical < 0) {
    std::cerr << "ERROR:  Imaginary roots" << std::endl;
    return false;
  }
  float sqrt_radical = sqrt(radical);  
  //here the variable is radical not radikal
  // compute the two roots
  root_pos = (-b + sqrt_radical) / float(2*a);
  root_neg = (-b - sqrt_radical) / float(2*a);
  //the names of the roots are different than the two set
  return true;
}

int main() {
  int b_array [5] ;
  int c_array [5] ;
  float root_1,root_2;
  int n;
  int i;
  float smaller_root [5] ;
  std::cout << "Enter 5 b values" << std::endl;
  for (i = 0; i < 5; i = i + 1)  {
    std::cin >> b_array[i];
  }
  std::cout << "Enter 5 c values" << std::endl;
  for (i = 0; i < 5; i = i + 1)  {
    std::cin >> c_array[i];
  }
  for(n = 0; n < 5; n = n + 1 ) {
  
      bool success = find_roots(1,b_array[n],c_array[n],root_1,root_2);
      if (root_1 > root_2)  {
        smaller_root[n] =root_2;
      }
      else {
        smaller_root[n] =root_1;
      }
  }
  for (i = 0; i < 5 ; i = i + 1) {
    std::cout <<"The roots are: "<<smaller_root[i]<< std::endl;
  }


  // We will loop until we are given a polynomial with real roots
  /*
  while (true) {
    std::cout << "Enter 3 integer coefficients to a quadratic function: a*x*x + b*x + c = 0" << std::endl;
    int my_a, my_b, my_c;
    std::cin >> my_a >> my_b >> my_c;
    // create a place to store the roots
    float root_1, root_2;
    bool success = find_roots(my_a,my_b,my_c, root_1,root_2);
    // If the polynomial has imaginary roots, skip the rest of this loop and start over
    if (!success) continue;
    std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
    // Check our work...
    if (check_root(my_a,my_b,my_c, root_1) && check_root(my_a,my_b,my_c, root_2)) {
      //has one less ")"
      // Verified roots, break out of the while loop
      break;
    } else {
      std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
      // if the program has an error, we choose to exit with a
      // non-zero error code
      exit(1); 
    }
  }
  */
  // by convention, main should return zero when the program finishes normally
  return 0; 
}
