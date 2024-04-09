//Willem E Wilcox, Mercer Uni, CSC245, Dr. Digh, September 1st 2023

#include <string>
#include <iostream>
using namespace std;

void BreakDown (string name, string& first, string& last, string& mi);
int main()
{
	string name, first, last, mi;

	cout << "Name? <Last, First MI.> ";
	getline (cin, name);
		
	BreakDown (name, first, mi, last);

	cout << "First Name Entered :  " << first << endl;
	cout << "Last Name Entered :  " << last << endl;
	cout << "Middle Initial Entered :  " << mi << endl;
	return 0;
}

void BreakDown (string name, string& first, string& mi, string& last)
{
	// pre  : name is initialized with a full name
	// post : first, mi, and last contain the individual components
  //        of that name
  
  //initial attempt at making function
  //int length = name.length();
  //int position = name.find(", ");
  //first = name.substr(0, position)
  //position = name.find(".");
  
  
  //Second attempt at making BreakDown function
  //Format -> Last, First M.
  
  //Find the position of the first name
  int position = name.length() - name.find(",");
  
  mi = name.substr(name.find(".") -1, 1);
  last = name.substr(0, name.find(","));
  first = name.substr(name.find(",") + 2, position -5);


} 
