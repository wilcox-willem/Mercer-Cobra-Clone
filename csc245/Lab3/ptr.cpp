//Willem Wilcox, CSC 245, Dr. Digh, Sep 6th 2023
#include <iostream>
#include <cstring>

using namespace std;

//5. declare struct RecType
struct RecType
{
  int age;
  float weight;
  char gender;
};



int main()
{
  //1. Declare int num equal to 5
  int num = 5;
  
  //2. Declare int ptr equal to NULL
  int *intPtr = NULL;
  
  //3. Set pointer location to num address
//17. comment out --->  intPtr = &num;
  
  //4. Multiply and print
  *intPtr *= 10;
  
  cout << "intPtr points to: " << *intPtr << endl;
  
  //6, 7, 8. allocate dynamic memory for recPtr,
  //         adjust values pointed to by recPtr using member select'->'
  //         print out each field
  RecType *recPtr = new RecType;
  recPtr->age = 25; cout << "recPtr points to: " << endl;
  recPtr->weight = 190; cout << "Weight: " << recPtr->weight << endl;
  recPtr->gender = 'M'; cout << "Gender: " << recPtr->gender << endl;
  
  recPtr->age += 5; cout << "Age: " << recPtr->age << endl;
  
  
  //9. deallocate the memory pointed to by recPtr
  delete recPtr;
  
  //10. point recPtr to nowhere
  recPtr = NULL;
  
  //11. declare strPtr to a single char,
  //    then initialize it to point to a new created dynamic array of 50 char
  char *strPtr = new char[50];
  
  //12. make strPtr point to string "Operating Systems" and print
  strcpy(strPtr, "Operating Systems");
  cout << "strPtr points to: " <<  strPtr << endl;
  
  //13. construct a for loop to count lower case chars pointed to by strPtr
  //    DO NOT USE BRACKETS, use pointers. Print num of lower case chars
  int numLowerCase = 0;
  int stringLength = strlen(strPtr);
  
  for (int i = 0; i < stringLength; i++) {
    
    if (islower(*strPtr))
      numLowerCase++;
    
    strPtr++;
      
  } 
  
  strPtr = strPtr - stringLength;
  
  cout << "Number of lowercase letter pointed to by strPtr: " << numLowerCase << endl;
  
  //14. add 10 to the base address of strPtr and print
  strPtr += 10;
  cout << "strPtr after adding 10: " << strPtr << endl;
  
  //15. subtract 10 from base address, then deallocate
  strPtr -= 10; 
  delete strPtr;
  
  
  
  return 0;

}