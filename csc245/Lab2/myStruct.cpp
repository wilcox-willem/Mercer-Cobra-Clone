//Willem E Wilcox, Mercer Uni, CSC245, Dr. Digh, September 1st 2023

#include <iostream>
#include <string> 
using namespace std;

const int SIZE = 100;

struct DateType
{
	string month;
	int day;
	int year;
};


// Insert EventType definition HERE
struct EventType
{
  string place;
  DateType date;
};


void PrintStruct (DateType Holiday);
void AssignMonth (EventType Dates[]);

int main()
{

  //Declare Holiday with date 9/4/23
	DateType Holiday;
  Holiday.month = "September";
  Holiday.day = 4;
  Holiday.year = 2023;
  
  //Declare Dates array
  EventType Dates {SIZE};
  
   
 




	PrintStruct (Holiday);
	AssignMonth (Dates);
	return 0;
}

void PrintStruct (DateType Holiday)
{
	// pre  : Holiday is intialized with three field values
	// post : Function prints date of Holiday in form mm dd, yy
 
  cout << Holiday.month << " " << Holiday.day << ", " << Holiday.year << endl;
 



}

void AssignMonth (EventType Dates[])
{
	// pre  : none 
	// post : The month field of every date record in array is assigned a month 
 
  for (int i = 0; i < SIZE; i++){
    Dates[i].month = "September";
  }


}
