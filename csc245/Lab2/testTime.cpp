//Willem E Wilcox, Mercer Uni, CSC245, Dr. Digh, September 1st 2023


#include <iostream>
using namespace std;
#include "time.h"

int main(){
  
  //Declare time object at time 9:30
  Time myTime(9,30,0);
  
  //Print time
  myTime.Write();
  myTime.WriteAmPm();
  
  //Set time to 8AM, test Mealtime
  myTime.Set(8,0,0);
  myTime.WriteAmPm();
  myTime.Mealtime();
  
  
  //Declare 10 time objects
  Time myTime1;
  Time myTime2;
  Time myTime3;
  Time myTime4;
  Time myTime5;
  Time myTime6;
  Time myTime7;
  Time myTime8;
  Time myTime9;
  Time myTime10;
  
  //Declare Time array Schedules, set time of each to 11, then print AmPm
  Time Schedules[10] = {
    myTime1, myTime2, myTime3, 
    myTime4, myTime5, myTime6, 
    myTime7, myTime8, myTime9, myTime10
    };
  
  for (int i = 0; i < 10; i++) {
    Schedules[i].Set(11,0,0);
    Schedules[i].WriteAmPm();
  }
  
  return 0;
}