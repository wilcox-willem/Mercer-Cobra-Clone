//Willem Wilcox, CSC 245, Dr. Digh, Mercer University, 9/21/23
#include <cstddef> 
#include <iostream>


using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};



// Class constructor
template <class ItemType>		
DList<ItemType>::DList()
{
    length = 0;
    head = NULL;
}


// Class deconstructor
template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.
  makeEmpty();
}


// makeEmpty //empties list
template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
  
 while (head != NULL){
   deleteLocation(last());
 }

}


// deleteItem //deletes item from parameter
template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 

  if (inList(item)){
    deleteLocation(location(item));
  }  

}






// inList // returns bool of if parameter is in list
template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found 
 bool isHere = false;
 
 if (!isEmpty()){
   NodeType<int>* currentNode = head;
    
   while (currentNode != NULL){ //check each node, stops at tail
     if (currentNode -> info == item){
      isHere = true;
     }
    currentNode = currentNode -> next;   
   }
 }
   
   return isHere;
}






// isEmpty // returns bool of empty status
template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{

  return (head == NULL);
	// Post : function returns true if list is empty, false otherwise
	
}






// print // prints list contents
template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen
 
  int iterator = 1;
 
  if(!isEmpty()){
    NodeType<int>* currentNode = head;
   
    while (currentNode != NULL) {
      cout << iterator << ". " << currentNode -> info << endl;
      currentNode = currentNode -> next;   
      iterator++;
   }
  }
  else cout << "The list is empty." << endl;
   
   
}
	

 
 
 
 
 
// insertHead // inserts parameter as new head 
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 
        
 NodeType<int>* newNode = new NodeType<int>;
 newNode -> info = item;
 newNode -> back = NULL;
 
 if (head != NULL){
   head -> back = newNode; //Link old 1st item to new 1st item
   newNode -> next = head; //Link new 1st item to old 1st item 
 } 
 else {
   newNode -> next = NULL; 
 }
   
 head = newNode;
 length++; //update length of list
}







// appendTail // inserts parameter to tail position
template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link   
 
 
 NodeType<int>* newNode = new NodeType<int>;
 newNode -> info = item;
 newNode -> next = NULL;
 
 if (!isEmpty()){
  newNode -> back = last();
  last() -> next = newNode;
 } 
 else {
   newNode -> back = NULL;
   head = newNode;
 }
 
 length++; //update length of list
}







// lengthIs // returns length of list
template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list  
  return length;
}


// location // returns pointer for parameter
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned 
 
 if (!isEmpty()){
   NodeType<int>* currentNode = head;
   while (currentNode != NULL) {  
     if (currentNode -> info == item){
         return currentNode;    
     } 
     else currentNode = currentNode -> next;
   } 
 }
 
 return NULL;	
}


// last // returns last item in list
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list
  
  //check if empty
   if (!isEmpty()){
     NodeType<ItemType>* currentNode = head;
   
     while (currentNode -> next != NULL){  
      currentNode = currentNode -> next;   
     }
   
   return currentNode;
   }
   return NULL;   
}


// deleteLocation // deletes paramter location
template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
  
  NodeType<int>* spareNextNode = delPtr;
  NodeType<int>* spareBackNode = delPtr;


  if (!isEmpty()){
    //If delPtr is head and not only item
    if ((delPtr == head)){
       if (delPtr -> next != NULL){
        head = delPtr -> next;
        head -> back = NULL;
        }
        else head = NULL;
    }
  
    //if delPtr is tail
    else if (delPtr -> next == NULL){
      spareBackNode = spareBackNode -> back;
      spareBackNode -> next = NULL;
 
      //if delPtr is neither head/tail
    }else {
      //stich delPtr's back & next ptrs
      spareNextNode = delPtr -> next;
      spareBackNode = delPtr -> back;
    
      spareNextNode -> back = spareBackNode;
      spareBackNode -> next = spareNextNode;
    }
    delete delPtr;
    delPtr = NULL;
    length--;
  } 
  
  //Be sure to deallocate or it will point to null and lead to seg fault
  //Special cases
    //Deleting head,new heads back must be null
    //Deleting tail, new tail next must be null
    //Deleting only item in list
}

//EXTRAS WW
// getHead // returns head item in list
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::getHead() const	
{
	// Post : Function returns location of current head item in list
  
   if (!isEmpty()){
     NodeType<ItemType>* currentNode = head;
  
   return currentNode;
   }
   return NULL;   
}

// getTail // returns last item in list // essentially just a public version of last()
template <class ItemType>
NodeType<ItemType>* DList<ItemType>::getTail() const	
{
	// Post : Function returns location of current tail item in list
  
   if (!isEmpty()){
     NodeType<ItemType>* currentNode = head;
   
     while (currentNode -> next != NULL){  
      currentNode = currentNode -> next;   
     }
   
   return currentNode;
   }
   return NULL; 
}

