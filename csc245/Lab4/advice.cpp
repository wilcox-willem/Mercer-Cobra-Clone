//Willem Wilcox, M.U., Dr. Digh, CSC 245, 10/18/23
#include <fstream>
#include <cctype>
#include <iostream>
using namespace std;

#include <string>
#include "stack.h" 

struct AdviceNode
{
  string QorA;      // a question or an answer
  AdviceNode * yes;   // yes branch
  AdviceNode * no;    // no branch

  AdviceNode(const string & s);  // constructor
};

AdviceNode::AdviceNode(const string & s)
: QorA(s),
  yes(NULL),
  no(NULL)
{}

void ReadTree(istream & in, AdviceNode * & T);

bool IsQuestionNode(AdviceNode * T);
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false

void GiveAdvice(AdviceNode * T);
// precondition: T is not NULL

bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack);
// precondition:  T is not NULL

void ShowPath(const Stack<string> & pathStack);

int main()
{
  string fname;
  cout << "\nEnter filename of advice knowledge base: ";
  cin  >> fname; cin.ignore();

  ifstream treeIn(fname.c_str());

  AdviceNode * T;
  ReadTree(treeIn, T);

  GiveAdvice(T);

  string movie;
  Stack<string> path;


  while(movie != "q"){
    cout << "\nEnter the name of a movie from tree to see path (q to quit): ";
    getline(cin, movie);
    if(movie != "q"){
      path.makeEmpty();
      TracePath(T, movie, path);
      ShowPath(path);
    }
  }


  return 0;
}

void ReadTree(istream & in, AdviceNode * & T)
{
  string QA;

  getline(in, QA);
  T = new AdviceNode(QA);
  if(QA[QA.length()-1] != '?'){
    T->yes = NULL;
    T->no  = NULL;
  }
  else{
    ReadTree(in, T->yes);
    ReadTree(in, T->no);
  }
}

bool IsQuestionNode(AdviceNode * T)
// precondition:  T is not NULL
// postcondition: returns true f T points to a question node;
//                otherwise returns false
{
  return (T->QorA[(T->QorA).length()-1] == '?');
}

void GiveAdvice(AdviceNode * T)
{
// 1)  Check to see if T is a Question Node.
// 2)  If it is, print T -> QorA and Input a 'Y' or 'N' (in any case).
//     If 'Y', recursively go left (T -> yes).  Otherwise, recursively go right.
// 3)  If the node is not a Question Node, it is a leaf and answer node.  So, just print T -> QorA.
  string userInput;
  if (IsQuestionNode(T)){
    cout << T->QorA << " ";
    cin >> userInput;
    char userChar = userInput[0];
    userChar = toupper(userChar);

    if (userChar == 'Y'){
      GiveAdvice(T->yes);
    }
    else if (userChar == 'N'){
      GiveAdvice(T->no);
    }
  } else {
    cout << T->QorA << endl;
  }
}


bool TracePath(AdviceNode * T, const string & movie,
               Stack<string> & pathStack)
{
  string tempString;
  if (T->QorA == movie){
    tempString = T->QorA;
    pathStack.push(tempString);
    return true;
  }
  else if (IsQuestionNode(T)) {
    if(TracePath(T->yes, movie, pathStack)){
      tempString = T->QorA;
      tempString += " yes";
      pathStack.push(tempString);
      return true;
    } 
    else if (TracePath(T->no, movie, pathStack)){
      tempString = T->QorA;
      tempString += " no";
      pathStack.push(tempString);
      return true;
    } 
  }
  return false;
}


void ShowPath(const Stack<string> & pathStack)
{
  Stack<string> path(pathStack);

  while(!path.isEmpty()){
    cout << path.top() << endl;
    path.pop();
  }
}
