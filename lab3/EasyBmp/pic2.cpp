#include <iostream>
#include <string>
#include "EasyBMP.h"
#include "EasyBMP.cpp"
using namespace std;
//--------------------------------------CLASS---------------------------

class Node{
public:
  Node();
  Node(BMP pic);
  int red(int x, int y);
  int green(int x, int y);
  int blue(int x, int y);
  int TellHeight();
  int TellWidth();
  Node* getNext();
  void setNext(Node* p);
  void insert(BMP p);/////
  BMP GetImage();

private:
  BMP image;
  Node* next;
  Node* head;
 }; 

//----------------------------------------CLASS FUNCTIONS-------------------
Node::Node(){

}
Node::Node(BMP pic){

  next = NULL;
  
  image.SetSize(pic.TellWidth(),pic.TellHeight());

  for(int i = 0; i < pic.TellWidth(); i++)
    {
      for(int j = 0; j < pic.TellHeight(); j++)
        {
	  int red = pic(i,j)->Red;
          image(i,j)->Red = red;
	  int green = pic(i,j)->Green;
	  image(i,j)->Green = green;
	  int blue = pic(i,j)->Blue;
	  image(i,j)->Blue = blue;
	}
    }
}

int Node::red(int x, int y){
  return image(x,y)->Red;
} 

int Node::green(int x, int y){
  return image(x,y)->Green;
} 

int Node::blue(int x, int y){
  return image(x,y)->Blue;
} 


Node* Node::getNext(){
  return next;
}

void Node::setNext(Node* p){
  next = p;
}

int Node::TellHeight(){
  return image.TellHeight();
}

int Node::TellWidth(){
  return image.TellWidth();
}

BMP Node::GetImage(){

  BMP pic;
  pic.SetSize(image.TellWidth(),image.TellHeight());
    for(int i = 0; i < pic.TellWidth(); i++)
      {
	for(int j = 0; j < pic.TellHeight(); j++)
	  {
	    int red = image(i,j)->Red;
	    pic(i,j)->Red = red;
	    int green = image(i,j)->Green;
	    pic(i,j)->Green = green;
	    int blue = image(i,j)->Blue;
	    pic(i,j)->Blue = blue;
	  }
      }
  return pic;
}
void Node::insert(BMP p) {
 
  Node* tmp = new Node(p); 
  tmp->setNext(this);
  this->setNext(tmp);

}

//--------------------------------------------MAIN---------------------------
bool compareNS(BMP a, BMP b);
bool compareEW(BMP a, BMP b);

int main(int argc, char* argv []){

  int i = 2;
  BMP image1;
  BMP image2;
  BMP temp1;
  BMP temp2;

  image1.ReadFromFile(argv[1]);
 
  Node* firstNode = new Node(image1);
  
  while(argv[i]!=NULL){
    
    image2.ReadFromFile(argv[i]);

    firstNode->insert(image2); 
    i++;
  } 
 
  int counter = 0;
  while(counter<i){
 
    temp1.SetSize(firstNode->GetImage().TellHeight(),firstNode->GetImage().TellWidth());
 
    for(int i = 0; i < temp1.TellWidth(); i++)
      {
	for(int j = 0; j < temp1.TellHeight(); j++)
	  {
	    temp1(i,j)->Red = firstNode->red(i,j); 
	    temp1(i,j)->Green = firstNode->green(i,j);
	    temp1(i,j)->Blue = firstNode->blue(i,j);
	  }
      }

    Node* secondNode = firstNode->getNext();

    while(secondNode!=NULL){
      cout<<"2"<<endl;
      temp2.SetSize(secondNode->GetImage().TellHeight(),secondNode->GetImage().TellWidth());
      
      for(int i = 0; i < temp2.TellWidth(); i++)
	{
	  for(int j = 0; j < temp2.TellHeight(); j++)
	    {
	      temp2(i,j)->Red = secondNode->red(i,j);
	      temp2(i,j)->Green = secondNode->green(i,j);
	      temp2(i,j)->Blue = secondNode->blue(i,j);
	    }
	}
      cout<<"3"<<endl;
      if(compareNS(temp1,temp2)== false and compareEW(temp1,temp2)== false){
      }
      int a;
      cin>>a;
      secondNode = secondNode->getNext();
    }
    /*    Node* N = new Node();
	  N = secondNode;
	  firstNode->setNext(secondNode->getNext());//deletes 2nd node
	  N->setNext(firstNode);
	  firstNode = N;
    */ 
    counter++;
  }

  temp1.WriteToFile(argv[5]);
  return 0;
}
  //-----------------------------------NON CLASS FUNCTIONS-----------------

  bool compareNS(BMP a, BMP b){ //  a = north side, b = south side
 
  int PixelMatch = 0;
  int height = a.TellHeight();
  
  for(int i = 0; i < a.TellWidth(); i++)
    {
      if(a(i,0)->Red - b(i,height)->Red <= 50    and  a(i,0)->Red - b(i,height)->Red >= -50     and 
	 a(i,0)->Green - b(i,height)->Green <=50 and  a(i,0)->Green - b(i,height)->Green >= -50 and
	 a(i,0)->Blue - b(i,height)->Blue <=50  and  a(i,0)->Blue - b(i,height)->Blue >= -50){
	PixelMatch++;
      }
    }
  
  cout<<PixelMatch<<" pixels matched "<<endl;
  if(PixelMatch >= a.TellWidth()/2)return true;
  
  else return false;
}

  bool compareEW(BMP a, BMP b){ // a = west, b = east

  int PixelMatch = 0;
  int width = a.TellWidth();
  
  for(int i = 0; i < a.TellHeight(); i++)
    {
      if(a(0,i)->Red - b(width,i)->Red <= 50    and  a(0,i)->Red - b(width,i)->Red >= -50     and
         a(0,i)->Green - b(width,i)->Green <=50 and  a(0,i)->Green - b(width,i)->Green >= -50 and
         a(0,i)->Blue - b(width,i)->Blue <=50  and  a(0,i)->Blue - b(width,i)->Blue >= -50){
        PixelMatch++;
      }
    }
  cout<<PixelMatch<<" pixels matched "<<endl;  
  if(PixelMatch >= a.TellHeight()/2)return true;
  
  else return false;
}


