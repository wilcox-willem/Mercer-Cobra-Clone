//Willem Wilcox, CSC 245, Dr. Digh, 
#include <iostream>

using namespace std;



//Function to check if pointers point to equal value
bool matchingValues(double* ptr1, double* ptr2)
{
  
  if (*ptr1 == *ptr2) return true;
  else return false;
  
}

//function to check if pointers point to same address
bool matchingPtrs(double* ptr1, double* ptr2)
{
  
  if (ptr1 == ptr2) return true;
  else return false;
  
}


int main()
{

  //Create 2 new pointers with different assigned values
  double *num1ptr = new double(5.9);
  double *num2ptr = new double(8.9);
  
  //Test and print functions
  cout << "Test with different values and addresses" << endl;
  cout << matchingValues(num1ptr, num2ptr) << endl;
  cout << matchingPtrs(num1ptr, num2ptr) << endl;
  
  *num1ptr = *num2ptr;
  cout << "Test with equal values and different addresses" << endl;
  cout << matchingValues(num1ptr, num2ptr) << endl;
  cout << matchingPtrs(num1ptr, num2ptr) << endl;
  
  num1ptr = num2ptr;
  cout << "Test with matching values and addresses" << endl;
  cout << matchingValues(num1ptr, num2ptr) << endl;
  cout << matchingPtrs(num1ptr, num2ptr) << endl;

  return 0;
}
