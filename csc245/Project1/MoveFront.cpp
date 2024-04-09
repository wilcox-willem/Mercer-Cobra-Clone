//Willem Wilcox, CSC 245, Dr. Digh, Mercer University, 9/21/23
#include <iostream>
#include "dlist.h"
using namespace std;

  void PrintMenu(char &sel);
  void HeadInsert(DList<int> &list);
  void TailInsert(DList<int> &list);
  void AccessItem(DList<int> &list);
  void Delete(DList<int> &list);
  void PrintList(const DList<int> &list);
  void PrintLength(const DList<int> &list);
  void FindandMove(DList<int> &list, int item);
  //Extras
  void ReverseList(DList<int> &list);
  void FrontofList(const DList<int> &list);
  void BackofList(const DList<int> &list);
  void FindandMoveSilent(DList<int> &list, int item);
  
  
int main() { 
  DList<int> list;
  char sel;
  
  
  
  do
    {
      PrintMenu (sel);
      switch (toupper(sel))
      {
        case 'H' : HeadInsert(list); break;
        case 'T' : TailInsert(list); break;
        case 'A' : AccessItem(list); break;
        case 'D' : Delete(list); break;
        case 'P' : PrintList(list); break;
        case 'F' : FrontofList(list); break;
        case 'B' : BackofList(list); break;
        case 'L' : PrintLength(list); break;
        case 'R' : ReverseList(list); break;
        case 'Q' : cout << "\tExiting Program...\n"; break;
        default : cout << "\tError. Try Again." << endl;
      }
    } while (toupper(sel) != 'Q');
  
  return 0;
}


//PrintMenu - in the style of a lavish ascii house!
void PrintMenu(char &sel) {  
  //Pre Conditions: 
  //Post Conditions: 
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "       ; % " <<endl;
  cout << "        # " << endl;
  cout << "         {      " << endl;
  cout << "        * $   <->" << endl;
  cout << "       > &   <--->" << endl;
  cout << "        _   <----->" << endl;
  cout << "       | | <------->" << endl;
  cout << "       | |<--------->" << endl;
  cout << "       | |----------->" << endl;
  cout << "       |_|------------>" << endl;
  cout << "       <--------------->" << endl;
  cout << "      <-----_______----->" << endl;
  cout << "     <-----*  Hi!  *----->" << endl;
  cout << "    <------*       *------>" << endl;
  cout << "   <-------*(v._.^)*------->" << endl;
  cout << "  <--------*_______*-------->" << endl;
  cout << " <--------------------------->" << endl;
  cout << "<----------------------------->" << endl;
  cout << "|-----------------------------|" << endl;
  cout << "|           ~Menu~            |" << endl;
  cout << "| H: Insert item at front     |" << endl;
  cout << "| T: Insert item at back      |" << endl;
  cout << "| A: Access an item in list   |" << endl;
  cout << "| D: Delete an item in list   |" << endl;
  cout << "| P: Print the list           |" << endl;
  cout << "| F: Print front of the list  |" << endl;
  cout << "| B: Print back of the list   |" << endl;
  cout << "| L: Print the list's length  |" << endl;
  cout << "| R: Reverse the list         |" << endl;
  cout << "| Q: Quit the program         |" << endl;
  cout << "|                             |" << endl;
  cout << "|-v-v-v-v-v-v-v-^-^-^-^-^-^-^-|" << endl;
  cout << "|     back <- info -> next    |" << endl;
  cout << "|-v-v-v-v-v-v-v-^-^-^-^-^-^-^-|" << endl;
  cout << "|                             |" << endl;
  cout << "|   The Doubly Linked House:  |" << endl;
  cout << "|     Home of the (linear)    |" << endl;
  cout << "|      Doubly Linked List     |" << endl;
  cout << "|                             |   %--------% v..^      / " << endl;
  cout << "|  Please enter your choice:  |   |Welcome!| /_/\\_____/" << endl;
  cout << "|       (and have fun!)       |   %--------%    /\\   /\\" << endl;
  cout << "|-----------------------------|___|________|__ /  \\ /  \\" << endl;
  cout << endl;
  
  cin >> sel;

}


//H : HeadInsert //replaces head with console input
void HeadInsert(DList<int> &list){
  //Pre Conditions: 
  //Post Conditions: integer from user input is added as the Head,
  //                 unless already in the list. 
  int input;
  cout << "What number would you like to insert?" << endl;
  cin >> input;
  
  if (!list.inList(input)){
    list.insertHead(input);
    cout << "Done!" << endl;
  } 
  else cout << "That item is already in the list." << endl;
  
}


//T : TailInsert // appends item to tail of list
void TailInsert(DList<int> &list){
  //Pre Conditions: 
  //Post Conditions: integer from user input is added as the Tail,
  //                 unless already in the list. 
  int input;
  cout << "What number would you like to insert?" << endl;
  cin >> input;
  
  if (!list.inList(input)){
     list.appendTail(input);
     cout << "Done!" << endl;
  } 
  else cout << "That item is already in the list." << endl;

}


//A : AccessItem //Accesses item based on console inout, then moves item to front via FindandMovd
void AccessItem(DList<int> &list){
  //Pre Conditions: 
  //Post Conditions: integer from user input is searched for, if found moved to front of list
  //                 unless already in the list. 
  if (list.lengthIs() > 0){ 
    int input;
    cout << "What number would you like to access?" << endl;
    cin >> input;
  
    if (list.inList(input)){
      FindandMove(list, input);
    } 
    else cout << "That item is not in the list." << endl;
    
  } 
  else cout << "The list is empty." << endl;
  
}

//FindandMove //AccessItem helper function
void FindandMove(DList<int> &list, int item){
  //Pre Conditions: 
  //Post Conditions: if item is in list, moves it to the head
  if (list.inList(item)){
    list.deleteItem(item);
    list.insertHead(item);
    cout << "Item found and successfully moved!" << endl;
  } 
}


//D : Delete // deletes item based on user console input
void Delete(DList<int> &list){
  if (list.lengthIs() > 0){ 
    int input;
    cout << "What number would you like to delete?" << endl;
    cin >> input;
  
    if (list.inList(input)){
      list.deleteItem(input);
      cout << "Item found and successfully removed!" << endl;
    } 
    else cout << "That item is not in the list." << endl;
    
  } 
  else cout << "The list is empty." << endl;
  
}


//P : PrintList // Prints content of the list one line per item
void PrintList(const DList<int> &list){
  if (list.lengthIs() > 0){
    cout << "Printing list..." << endl;
    list.print();
    cout << "End of List" << endl;
  } 
  else cout << "The list is empty." << endl;
}


//L : PrintLength // Prints length of the list
void PrintLength(const DList<int> &list){
  cout << "The length of the list is " << list.lengthIs() << endl;  
}

//EXTRAS WW
//R : ReverseList // Reverses the contents of the list
void ReverseList(DList<int> &list){
    if (list.lengthIs() <= 1) {
        cout << "Too short to reverse!" << endl;
    } else {
    
      //Pre Reverse    
      cout << "Current list" << endl;
      PrintList(list);
     
      
      //Reverse works by using FindandMoveSilent to move the tail to the front,
      //the number of times of the length of the list -1
      NodeType<int>* currentNode = list.getHead();
      NodeType<int>* tempNode = currentNode -> next;
       
      for (int i = 0; i < list.lengthIs()-1; i++){
      NodeType<int>* tempNode = currentNode -> next;
     
      FindandMoveSilent(list, tempNode -> info);
      }
      

      //Post Reverse
      cout << endl << "List reversed!" << endl;
      PrintList(list);
    }
}

//FindandMoveSilent//Reverse helper function
void FindandMoveSilent(DList<int> &list, int item){
  //Pre Conditions: 
  //Post Conditions: if item is in list, moves it to the head
  if (list.inList(item)){
    list.deleteItem(item);
    list.insertHead(item);
  } 
}

//F : FrontofList() // Prints head of list
void FrontofList(const DList<int> &list){
  if (list.lengthIs() > 0){
    cout << "The head is " << list.getHead() -> info << endl;
  } 
  else cout << "The list is empty." << endl;
}

//B : BackofList() // Prints tail of list
void BackofList(const DList<int> &list){
  if (list.lengthIs() > 0){
    cout << "The tail is " << list.getTail() -> info << endl;
  } 
  else cout << "The list is empty." << endl;
}