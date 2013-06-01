#include <iostream>
#include <string>
#include <vector>
#include "EasyBMP.h"
#include "EasyBMP.cpp"
using namespace std;
//--------------------------------------CLASS---------------------------

class Node{
public:
  Node();
  Node(BMP pic);//=====
  int red(int x, int y);
  int green(int x, int y);
  int blue(int x, int y);
  int TellHeight();
  int TellWidth();
  Node* getNext();
  void setNext(Node* p);
  void insert(BMP p);//=======
  BMP GetImage();

private:
  BMP image;//======
  Node* next;
 }; 

//----------------------------------------CLASS FUNCTIONS-------------------
Node::Node(){}
Node::Node(BMP pic){//=====

  next = NULL;
  image.SetSize(pic.TellWidth(),pic.TellHeight());

  for(int i = 0; i < pic.TellWidth(); i++){
      for(int j = 0; j < pic.TellHeight(); j++){
	  int red = pic(i,j)->Red;
          image(i,j)->Red = red;
	  int green = pic(i,j)->Green;
	  image(i,j)->Green = green;
	  int blue = pic(i,j)->Blue;
	  image(i,j)->Blue = blue;
	}
    }
}
BMP Node::GetImage(){

  BMP pic;//=======
  pic.SetSize(image.TellWidth(),image.TellHeight());
  for(int i = 0; i < pic.TellWidth(); i++){
      for(int j = 0; j < pic.TellHeight(); j++){
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

int Node::red(int x, int y){return image(x,y)->Red;} 
int Node::green(int x, int y){return image(x,y)->Green;} 
int Node::blue(int x, int y){return image(x,y)->Blue;} 
Node* Node::getNext(){return next;}
void Node::setNext(Node* p){next = p;}
int Node::TellHeight(){return image.TellHeight();}
int Node::TellWidth(){return image.TellWidth();}

void Node::insert(BMP p) {//======= 

  Node* tmp = new Node(p); 
  tmp->setNext(this->next);
  this->setNext(tmp);
}

//--------------------------------------------MAIN---------------------------
int compareNS(BMP a, BMP b);//===========
int compareEW(BMP a, BMP b);//==========

int main(int argc, char* argv []){

  int ImageCount = 2;
  BMP image1;  //========
  BMP image2;  //=======
  BMP temp1;  //======
  BMP temp2; //=======
  BMP FinalPic; //========
  Node* holdNode;
  Node* trav;
  vector<int> PicValues;

  image1.ReadFromFile(argv[1]);

  FinalPic.SetSize(image1.TellHeight()*4, image1.TellWidth()*4); 

  Node* firstNode = new Node(image1); // firstNode will be used as head! 
  Node* holdSpot= new Node(image1); 

  firstNode->setNext(holdSpot);// holds the second position which the list will build off of
 
  while(argv[ImageCount+1]!=NULL){ 
    
    image2.ReadFromFile(argv[ImageCount]);

    holdSpot->insert(image2); // inserts each new node into 2nd position of list
    ImageCount++;
  }

  //---------------------------------
  /*  int LoopCounter = 0;

  while(LoopCounter<=ImageCount){

    int noMatch = 0; 

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
      //==============
      if(compareNS(temp1,temp2)== false and compareEW(temp1,temp2)== false){
	noMatch++;
	cout<<"loop "<<LoopCounter<<" have not matched"<<endl;
	cout<<"math count "<<noMatch<<endl;
	int ab;
	//	cin>>ab;
	if(noMatch == ImageCount-2){ //copies top left corner into final picture
	  RangedPixelToPixelCopy(temp1,0,temp1.TellWidth(),temp1.TellHeight(),0,FinalPic,0,0);
	  holdNode = new Node(temp1); // For a new list which will build off of temp1 to finish pic
	  holdSecondNode = new Node(temp1);//holds this node so that way we can refer back to it when we change colums 
	  cout<<"TopCorner"<<endl;
	  FinalPic.WriteToFile(argv[ImageCount]);//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	   return 0;
	}
      }
      else{cout<<"Matched on loop "<<LoopCounter<<endl;
	//	cin>>noMatch;
      }
      //=============
      secondNode = secondNode->getNext();
    }
  
  LoopCounter++;

  //---------------------------
  Node* temp = new Node(); // saves first node
  temp = firstNode;
  firstNode = firstNode->getNext(); //deletes first node
  Node* travers = new Node(); // points to new first
  travers = firstNode;
  while(travers->getNext()!=NULL){
    travers=travers->getNext();
  }
  travers->setNext(temp); // goes to end of list and makes last node the orginal first node
  travers->getNext()->setNext(NULL);// makes sure the last node is NULL
  }

  cout<<"ass"<<endl;
  return 0;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //========================THIS IS WHERE I PUT THE PIC TOGETHER=========================

  holdNode->setNext(firstNode); 
  firstNode = holdNode;
*/
  
  holdNode = new Node(image1); // this is for testing, holds top left corner<<<<<<<<<<<<<<<<<<<<<<<
  
  for(int x = 0; x < FinalPic.TellWidth(); x = x + image1.TellWidth()){
    for(int y = 0; y < FinalPic.TellHeight(); y = y + image1.TellHeight()){
      if(x == 0 and y == 0){
	y = y + image1.TellHeight();
      }
    
      temp1.SetSize(firstNode->getNext()->GetImage().TellHeight(),firstNode->getNext()->GetImage().TellWidth()); 
      
      for(int i = 0; i < temp1.TellWidth(); i++){ // makes a BMP object out of the node that firstNode is pointing to 
	for(int j = 0; j < temp1.TellHeight(); j++){
	  temp1(i,j)->Red = firstNode->getNext()->red(i,j);
	  temp1(i,j)->Green = firstNode->getNext()->green(i,j);
	  temp1(i,j)->Blue = firstNode->getNext()->blue(i,j);
	}
      }

      Node* secondNode = firstNode->getNext()->getNext();// grabs the second node which will be used for comparing  
      
      while(secondNode!=NULL){ // while the list !NULL it will compare temp1 with every node in the list 	  
	
	temp2.SetSize(secondNode->GetImage().TellHeight(),secondNode->GetImage().TellWidth());
	
	for(int i = 0; i < temp2.TellWidth(); i++){
	  for(int j = 0; j < temp2.TellHeight(); j++){
	    temp2(i,j)->Red = secondNode->red(i,j);
	    temp2(i,j)->Green = secondNode->green(i,j);
	    temp2(i,j)->Blue = secondNode->blue(i,j);
	  }
	}
		
	if(y == 0){//if the new picture needs to be inserted at the top go in here  
	  temp1.SetSize(holdNode->GetImage().TellHeight(),holdNode->GetImage().TellWidth());//uses "holdNode" which always holds top pictures
	  for(int i = 0; i < temp1.TellWidth(); i++){                                         
	    for(int j = 0; j < temp1.TellHeight(); j++){
	      temp1(i,j)->Red = holdNode->red(i,j);
	      temp1(i,j)->Green = holdNode->green(i,j);
	      temp1(i,j)->Blue = holdNode->blue(i,j);
	    }
	  }
	  PicValues.push_back(compareEW(temp2,temp1)); // compares the "top picture" with pictures on its east side 
	}    
	
	else{
	  PicValues.push_back(compareNS(temp2,temp1));// compareNS(North,South)
	}	
	secondNode = secondNode->getNext(); // increments the list so that way firstNode can be compared to a different node
      }
      
      int max =0;
      int position=0;
      for(int i = 0; i < PicValues.size(); i++){//--find the most compatable picture by going through the vector of "matches"
	if(max < PicValues[i]){
	  max = PicValues[i];
	  position = i;
	}
      }
      PicValues.clear();
      trav = firstNode->getNext();
      for(int i = 0; i <= position; i++){//---travers the linked list to the most compatable picture
	trav = trav->getNext();
      }
      
      temp1.SetSize(firstNode->GetImage().TellHeight(),firstNode->GetImage().TellWidth());
      
      for(int i = 0; i < temp1.TellWidth(); i++){ // makes a BMP object out of the compatable picture in the list
	for(int j = 0; j < temp1.TellHeight(); j++){
	  temp1(i,j)->Red = trav->red(i,j);
	  temp1(i,j)->Green = trav->green(i,j);
	  temp1(i,j)->Blue = trav->blue(i,j);
	}
      }
      RangedPixelToPixelCopy(temp1,0,temp1.TellWidth(),temp1.TellHeight(),0,FinalPic,x,y); //copy most compatable picture to Finalpic

      firstNode->insert(temp1); //puts the newly inserted picture from RangedPixelToPix... and puts it in the front of list 

      if(y == 0){ // if the picture was for the top, then save it for future use so we can refer back to it when we change columns
      	holdNode = trav;           
      	holdNode->setNext(NULL);
      }
    }
  }
  FinalPic.WriteToFile(argv[ImageCount]);
  return 0;
}
//-----------------------------------NON CLASS FUNCTIONS-----------------
//this function takes two BMP objects as parameters and compares each pixel of each BMP object 
//at a specific location and checks whether they match. if the do it returns true, else false. 


int compareNS(BMP a, BMP b){ //  a = north side, b = south side  //==============
  
  int PixelMatch = 0;
  int height = a.TellHeight();

  for(int i = 0; i < a.TellWidth(); i++)
    {
      if(a(i,0)->Red - b(i,height)->Red <= 10    and  a(i,0)->Red - b(i,height)->Red >= -10      and 
	 a(i,0)->Green - b(i,height)->Green <= 10 and  a(i,0)->Green - b(i,height)->Green >= -10 and
	 a(i,0)->Blue - b(i,height)->Blue <= 10  and  a(i,0)->Blue - b(i,height)->Blue >= -10){
	PixelMatch++;
      }
    }
  
  cout<<PixelMatch<<" pixels matched "<<endl;
  return PixelMatch;
}

int compareEW(BMP a, BMP b){ // a = west, b = east  //===========
  
  int PixelMatch = 0;
  int width = a.TellWidth();
  
  for(int i = 0; i < a.TellHeight(); i++)
    {
      if(a(0,i)->Red - b(width,i)->Red <= 10    and  a(0,i)->Red - b(width,i)->Red >= -10     and
         a(0,i)->Green - b(width,i)->Green <=10 and  a(0,i)->Green - b(width,i)->Green >= -10 and
         a(0,i)->Blue - b(width,i)->Blue <=10  and  a(0,i)->Blue - b(width,i)->Blue >= -10){
        PixelMatch++;
      }
    }
  cout<<PixelMatch<<" pixels matched "<<endl;  
  return PixelMatch;
  
}


