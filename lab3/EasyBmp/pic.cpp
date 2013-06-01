//author: Cory Bekker
//Fall 2012
//CS315

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
  Node(BMP pic);
  int red(int x, int y); //gets color of bmp image in node
  int green(int x, int y);
  int blue(int x, int y);
  int TellHeight(); //gets height/width of bmp image in node
  int TellWidth();
  Node* getNext(); // gets a nodes "next" 
  void setNext(Node* p); // sets a nodes "next" to point to another node
  void insert(BMP p); // used to insert a new image into a node
  BMP GetImage();

private:
  BMP image; // nodes bmp image
  Node* next; // nodes pointer to next node
 }; 

//----------------------------------------CLASS FUNCTIONS-------------------
Node::Node(){}
Node::Node(BMP pic){ //constructor that passes a bmp object and sets it to the private member "image"

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
BMP Node::GetImage(){//returns the image that the the node is holding 

  BMP pic;
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

int Node::red(int x, int y){return image(x,y)->Red;}  //returns the RGB value of the BMP image and returns it as "int"  
int Node::green(int x, int y){return image(x,y)->Green;} 
int Node::blue(int x, int y){return image(x,y)->Blue;} 
Node* Node::getNext(){return next;}
void Node::setNext(Node* p){next = p;}
int Node::TellHeight(){return image.TellHeight();}
int Node::TellWidth(){return image.TellWidth();}

void Node::insert(BMP p) { // firstNode->next is going to be the BMP P that is passed.  inserted into 2nd spot

  Node* tmp = new Node(p); 
  tmp->setNext(this->next);
  this->setNext(tmp);
}

//--------------------------------------------MAIN---------------------------
int compareNS(BMP a, BMP b);
int compareEW(BMP a, BMP b);

int main(int argc, char* argv []){

  int ImageCount = 2; // the number of images + start command argument and writeToFile name argument
  int noMatch = 0; // used to find top left corner "not working atm"
  BMP image1; // first image entered into list
  BMP image2; // second image entered ito list, all other images added to image2->next
  BMP temp1; // used to withdraw bmp images from nodes
  BMP temp2; 
  BMP FinalPic; // the final bmp image that is pieced together 
  Node* holdNode; // used to hold the pictures at y = 0 to help change colunms when merging pics together
  Node* trav; // used to hold the current image being tiled onto the Final Pic
  vector<int> PicValues; // used to hold values of how well pixels of each pic are being matched
  vector<int> northValues;
  vector<int> westValues;
  BMP imageArray[16];
  vector<BMP> images;

  image1.ReadFromFile(argv[1]);

  FinalPic.SetSize(image1.TellHeight()*4, image1.TellWidth()*4); 

  Node* firstNode = new Node(image1); // firstNode will be used as head! 
  Node* holdSpot= new Node(image1); 

  firstNode->setNext(holdSpot);// holds the second position which the list will build off of

  BMP a;
  images.push_back(a);

  while(argv[ImageCount+1]!=NULL){ 
    
    image2.ReadFromFile(argv[ImageCount]);

    holdSpot->insert(image2); // inserts each new node into 2nd position of list
    ImageCount++;
  }

  /*  
  //---------------------------------THIS PART IS TO FIND THE TOP LEFT CORNER!!! "does not Work"
  int LoopCounter = 0;
  int test = ImageCount;

  while(LoopCounter<=ImageCount){
    
    temp1.SetSize(firstNode->getNext()->GetImage().TellHeight(),firstNode->getNext()->GetImage().TellWidth());
    
    for(int i = 0; i < temp1.TellWidth(); i++)
      {
        for(int j = 0; j < temp1.TellHeight(); j++)
          {
            temp1(i,j)->Red = firstNode->getNext()->red(i,j);
            temp1(i,j)->Green = firstNode->getNext()->green(i,j);
            temp1(i,j)->Blue = firstNode->getNext()->blue(i,j);
          }
      }
    
    Node* secondNode = firstNode->getNext()->getNext();

    while(secondNode!=NULL){
     
      temp2.SetSize(secondNode->GetImage().TellHeight(),secondNode->GetImage().TellWidth());

      for(int i = 0; i < temp2.TellWidth(); i++){
          for(int j = 0; j < temp2.TellHeight(); j++){
	    temp2(i,j)->Red = secondNode->red(i,j);
	    temp2(i,j)->Green = secondNode->green(i,j);
	    temp2(i,j)->Blue = secondNode->blue(i,j);
	  }
      }
      
      northValues.push_back(compareNS(temp1,temp2));      
      westValues.push_back(compareEW(temp1,temp2));

      secondNode = secondNode->getNext();
    }


    //------------    
    int northMax = 0;
    int nPosition=0;
    int minMatch;
    minMatch = temp2.TellWidth()/5;

    noMatch = 0;   
    for(int i = 0; i < northValues.size(); i++){//--find the least compatable picture "lowest matched pixels"
      if(northValues[i] < minMatch and westValues[i] < minMatch){
	noMatch++;
	cout<<noMatch<<endl;
      }
    }

    if(noMatch >= ImageCount-2){
      holdNode = new Node(temp1);
      RangedPixelToPixelCopy(temp1,0,temp1.TellWidth(),temp1.TellHeight(),0,FinalPic,0,0);
      FinalPic.WriteToFile(argv[ImageCount]);
      //     return 0;
    }
    //-----------
    northValues.clear();
    westValues.clear();

    LoopCounter++;
    
    Node* temp = new Node(); // saves first node
    temp = firstNode;
    firstNode = firstNode->getNext(); //deletes first node
    Node* travers = new Node(); // points to new first
    travers = firstNode;
    test = 0;
    while(travers->getNext()!=NULL){
      travers=travers->getNext();
      test++;
    }
    travers->setNext(temp); // goes to end of list and makes last node the orginal first node
    travers->getNext()->setNext(NULL);// makes sure the last node is NULL
  }
  


  cout<<"end"<<endl;
  FinalPic.WriteToFile(argv[ImageCount]);
  return 0;//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  */

  //========================THIS IS WHERE I PUT THE PIC TOGETHER=========================

  holdNode = new Node(image1); // this holds top left corner, Assuming we foound it above
  
  for(int x = 0; x < FinalPic.TellWidth(); x = x + image1.TellWidth()){ // this goes through all relative coords to Final pic 
    for(int y = 0; y < FinalPic.TellHeight(); y = y + image1.TellHeight()){ // for merging the pics together 
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
	  PicValues.push_back(compareEW(temp2,temp1)); // compares the "top picture" with pictures on its east side, adds matched to vect 
	}    
	
	else{
	  PicValues.push_back(compareNS(temp2,temp1));// compareNS(North,South), adds matched to vector
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
//at a specific location and checks whether they match. if the pixels match it returns the 
//amount that matched and is then put into a vector which will be used to find the best
//matched picture

int compareNS(BMP a, BMP b){ //  a = north side, b = south side 
  
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

int compareEW(BMP a, BMP b){ // a = west, b = east  
  
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


