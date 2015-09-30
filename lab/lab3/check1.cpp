/*Write a function compute_squares that takes 3 arguments: two C-style arrays (not STL vectors), a and b, 
of unsigned integers, and an unsigned integer, n, representing the size of each of the arrays.

The function should square each element in the first array, a, and write each result into the corresponding slot in the second array, b. 

You may not use the subscripting operator ( a[i] ) in writing this function; instead, practice using pointer arithmetic. 

Also, write a main function and a couple of test cases with output to the screen to verify that your function is working correctly.*/

#include <iostream>
#include <cmath>


void compute_squares(unsigned int *a, unsigned int *b, unsigned int n) {
    
    for (unsigned int i=0; i < n; ++i) {
        *(b+i) = *(a+i) * *(a+i) ;
        std::cout<<*(b+i)<<" ";
    }
}


int main() {
    unsigned int size = 10;
    unsigned int a[size] = {1,2,3,4,5,6,7,8,9,10};
    unsigned int b[size];
    compute_squares(a, b, size);
}