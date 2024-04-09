//Willem Wilcox, CSC 245, Dr. Digh, 9/8/23

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std; 

//3.
void Initialize(vector<int> &v)
{
  int temp;
  cout << "Please enter 5 integers: " << endl;
  for (int i = 0; i < 5 ; i++) {
    cin >> temp;
    v.push_back(temp);
  }

}

//4.
void Print(vector<int> v)
{

  for (int i : v){
  cout << i << " ";
  }
  
  cout << endl;
}

//5. 
void Reverse(vector<int>& v)
{

  reverse(v.begin(), v.end());

}

//6.
void Sort(vector<int>& v)
{

  sort(v.begin(), v.end());

}

//1.
int main()
{

stack<string> s1, s2;

s1.push("Hi There");
s1.push("Example");
s2.push("Something");

//cout << "s1 is "<< s1 << "\\ s2 is " << s2 << endl;
cout << "Is s1 == s2? " << (s1 == s2) << endl;
cout << "Is s1 < s2? " << (s1 < s2) << endl;
cout << "Is s1 > s2? " << (s1 > s2) << endl;

//2.
vector<int> v;

Initialize(v);
Print(v);

Reverse(v);
Print(v);

Sort(v);
Print(v);

return 0;
}