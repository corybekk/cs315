#include <iostream>
#include <string>
using namespace std;
//------------------------------------------------------------
class Node {
public:
  Node(int x) {
    key = x;
    next = NULL;
  }
  void setNext(Node* p) {next = p;}
  void setKey(int k) {key = k;}
  int getKey() { return key;}
  Node* getNext() { return next;}

private:
  int key;
  Node* next;
};
//------------------------------------------------------------
class List {
public:
  List() {
    head = 0;
  }

  List(Node* p) {
    head = p;
  }

  List(int x) {
    head = new Node(x);
  }

  List* copy() {
    if (head == NULL)
      return new List();
    else {
      List* temp = new List(head->getKey());
      List* rest = new List(head->getNext());
      temp->head->setNext(rest->copy()->head);
      return temp;
    }
  }

  void insert(int k) {
    // insert k as the first item of the list
    Node* tmp = new Node(k);
    tmp->setKey(k);
    tmp->setNext(head);
    head = tmp;
  }

  List* increment() {
    if (head==0)
      return new List(1);
    else {
      List* temp = copy();
      if (head->getKey() < 99999) {
        temp->head->setKey(temp->head->getKey()+1);
        return temp;
      }
      else {
        temp->head->setKey(0); List* rest = new List(head->getNext());
        temp->head->setNext(rest->increment()->head);
        return temp;
      }
    }
  }
  List* add(List* in, int carry) {
    if (head == NULL && in->head == NULL) { // checks if both lists are empty 
      if (carry == 0) return new List();
      else return new List(1);
    }
    else if (head==NULL) { // check if one list is empty 
      List* result = in->copy();
      if (carry == 0) return result;
      else return result->increment();
    }
    else if (in->head==NULL) { // check if the other list is empty, but the first isnt
      List* result = copy();
      if (carry == 0) return result;
      else return result->increment();
    }
    else {
      int temp = (in->head->getKey() + head->getKey() + carry); // if both lists aren't empty 
      List* result = new List(temp%100000);
      List* L1 = new List(in->head->getNext());// grabs the next nodes so it can add them together
      List* L2 = new List(head->getNext());
      List* temp1 = L1->add(L2, temp/100000); // add L1+L2+Carry
      result->head->setNext(temp1->head); // makes the list 
      return result;
    }
  }

  List* multiply(int x, int carry) {

    if(head == NULL) {
      if(carry == 0) return new List(); // if its 0 then it won't add 0 in the front of the list 
      else{
	return new List(carry); //
      }
    }
    else{
      List* L1 = copy();
      int y = L1->head->getKey() * x + carry; // does the multiply algorithm
      L1->head = L1->head->getNext();// shortens the list
      int FirstKey = y % 100000; // the actual key number for the new node
      int newCarry = y / 100000; // checks for carry. only 0 or 1
      List* L2 = L1->multiply(x, newCarry); // gets next node and multiplies it by "x" and adds newcary
      List* L3 = new List(FirstKey);
      L3->head->setNext(L2->head);// fills the list from the recursive calls
      return L3;
    }
  }

  List* fact(int n) { // goes through each number of the factorial and calls multiply function

    List* result = new List(1);

    for(int j=2; j<n+1; j++){
      result= result-> multiply(j,0);
    }
    return result;
  }

  List* exp(int x, int y){

    List* L1 = new List(1);
    List* L2 = new List(1);

    for(int j=0; j<x; j++){
      L1= L1-> multiply(2,0); // multiplies 2 to the x power
    }
    for(int j=0; j<y; j++){
      L2= L2-> multiply(3,0); // multiplies 3 to the y power
    }
    L2 = L1->add(L2,0); // adds both lists together

    return L2;
  }
  void print() {

    if(head==NULL)return;
    if(head->getNext()==NULL){ // goes through the list, stops at base case
      cout<<head->getKey(); // prints out nodes
      return;
    }
    List* a = new List(head);
    List* b = new List(head-> getNext());
    b->print(); // recursive call 
    int c = a->head->getKey();
    if(c > 999 && c < 9999) cout<< '0'; // prints out zeros at the end of the list 
    if(c > 99 && c < 999) cout <<"00";
    if(c > 9 && c < 99) cout<< "000";
    if(c < 10 ) cout << "0000";
    cout<<c;
  }
 
private:
  Node* head;
}; 

int main() {

  int input1;
  int input2;

  List* number = new List();
  List* power = new List();

  cout<<"Problem 1, compute n!: Enter an int n, 1 <= n <= 999"<<endl;
  cin>>input1;
  cout<<"factorial of "<<input1<<" is...."<<endl;
  number = number->fact(input1);
  number->print();
  cout<<endl;
  cout<<"Problem 2: Enter two ints p and q, 1 <= p, q <=999 "<<endl;
  cout<<"Enter P : ";
  cin>>input1;
  cout<<"Enter Q : ";
  cin>>input2;
  power = power->exp(input1,input2);
  cout<<"2^p + 2^q is :";
  power->print();

  cin>>input1;
  return 0;

};



