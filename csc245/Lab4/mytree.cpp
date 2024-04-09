//Willem Wilcox, CSC 245, Dr. Digh, Mercer University, 9/21/23
#include <iostream>
#include "bst.h"

using namespace std;

int main(){
	//Create int BST T with 0 to be passed as ITEM_NOT_FOUND/notFound
	BinarySearchTree<int> T(0); 

	//Fill contents of T
	T.insert(6);
	T.insert(2);
	T.insert(1);
	T.insert(4);
	T.insert(3);
	T.insert(8);



	//Extra contents for T
	T.insert(9);
  //T.insert(10000);
	//T.insert(100);
	//T.insert(1000);
 
/* 
  //Interesting set to run! 
  T.insert(11111);
	T.insert(1);
	T.insert(12);
	T.insert(123);
	T.insert(1234);
	T.insert(123456);
 	T.insert(1234567);
	T.insert(12345678);
	T.insert(123456789);
	T.insert(-1);
	T.insert(-12);
	T.insert(-123);
*/  
  	

	//Print contents of T
	cout << "-- Regular Print: Start --" << endl;
	T.printTree();
	cout << "-- Regular Print: End --" << endl << endl;

	cout << "-- Post Order Print: Start --" << endl;
	T.postOrder();
	cout << "-- Post Order Print: End --" << endl << endl;

	cout << "-- Pre Order Print: Start --" << endl;
	T.preOrder();
	cout << "-- Pre Order Print: End --" << endl << endl;

	cout << "-- Reverse Print: Start --" << endl;
	T.printTreeReverse();
	cout << "-- Reverse Print: End --" << endl << endl;

	//Print height of the tree
	if (T.isEmpty()){
		cout << "-- The Tree is empty --" << endl << endl;
	}
	else {
		int heightofT = T.height();
		cout << "-- The height of the tree is " << heightofT << " --" << endl << endl;
	}
 
  //Print the number of leaves
  if (!T.isEmpty()){
    cout << "-- The tree has " << T.numLeaves() << " leaves --" << endl << endl;
  
  }

	//Print balance status
	if (!T.isEmpty()) {
		if (T.isBalanced()) cout << "-- Tree balance status --" << endl
                             << "It's Balanced!" << endl << endl;
		else cout << "It's Not Balanced!" << endl << endl;
	}


	return 0;
}