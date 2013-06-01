#include <iostream>
using namespace std;

class Node {
public:
  Node(int x) { // takes a key as parameter and sets it and creates node
    key = x;
    next = NULL;
  }
  void setNext(Node* p) {next = p;} // member functions that allows you to modify a nodes key and next
  void setKey(int k) {key = k;}
  int getKey() { return key;} // getter functions
  Node* getNext() { return next;}
private:
  int key;
  Node* next;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////
class List {
public:
  List() {
    head = 0;
  }
  //----------------------------------
  List(Node* p) {
    head = p;
  }
  //----------------------------------
  List(int x) {
    head = new Node(x);
  }
  //----------------------------------
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
  //----------------------------------
  void insert(int k) {
    // insert k as the first item of the list
    Node* tmp = new Node(k);
    tmp->setNext(head);
    head = tmp;
  }
  //----------------------------------
  List* increment() {
    if (head==0)// checks if the list "first node called (head) is pointing to null"
      return new List(1); // creates a new list, first node containg key=1
    else {
      List* temp = copy(); // copy's the list to temp
      if (head->getKey() < 99999) {
	temp->head->setKey(temp->head->getKey()+1);
	return temp;
      }
      else {
	temp->head->setKey(0); 
	List* rest = new List(head->getNext());
	temp->head->setNext(rest->increment()->head);//????
	return temp;
      }
    }
  }
  //----------------------------------
  List* add(List* in, int carry) {

    if(head==NULL){
      if(in->head==NULL){
	if(carry==0)return new List();// how does in have a carry when its pointing to null?
	else return new List(1);  
      }
      else{
	List* result = in->copy();
	if(carry==0)return result;
	else return result->increment(); // increments by 1 because carry can be only 1 or 0
      }
    }  
    else{
      //recursion
      int temp =(in->head->getKey() + head->getKey() + carry);
      List* result = new List(temp%100000);
      List* L1 = new List(in->head->getNext());
      List* L2 = new List(head->getNext());
      L1 = L2->add(L2, temp/100000); // either 0 or 1 only for carry
      result->head->setNext(L1->head);
      return result;
    }
  }
 //----------------------------------
  List* multiply(int x, int carry) {

    List* Mult = new List(1); 
    Mult->head->setKey(Mult->head->getKey * x + carry);
 
    if(Mult->head->getKey > 100000)
      {
      carry = Mult->head->getKey%100000;
      Mult->head->setNext(multiply(x,carry)); 
      return Mult;
      }
  }
  //----------------------------------
  List* fact(int n) {

    List* result = new List(1);
    
    for(int j=2; j<n+1; j++)
      {
	result= result-> multiply(j,0);          
      }
    //   head= result->head;
    return result;
  }
  //----------------------------------
  List* exp(int x, int n) {



  }
  //----------------------------------
  void print() {

  }
  //----------------------------------
private:
  Node* head;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
  // create a user interface to solve the two problems
  // first get a number n, computer n! and display. Then ask for two numbers n and m and
  // compute 2^n + 3^m and display the result.

  return 0;
}
