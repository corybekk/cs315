//CoryBekker
// Cs315 lab 3

#include "EasyBMP.h"
#include "EasyBMP.cpp"
#include <iostream>
using namespace std;

void scale_down(BMP& I, BMP& O);
void tile(BMP& I, BMP& O, BMP& K);//======

int main(int argc, char* argv[]){

  BMP image;// used for scale_down
  BMP output;// used for scale_down
  BMP Final;// The final picture 
  BMP forth; //=======

  image.ReadFromFile(argv[1]);
  Final.ReadFromFile(argv[1]);

  if(image.TellWidth() * image.TellHeight()%2 == 1)
    {
      cout<<"picture is in wrong format, needs to be a square"<<endl;
      return 0;
    }
   
  scale_down(image,output);
  forth.SetSize(image.TellWidth(),image.TellHeight());//===== 

  RangedPixelToPixelCopy(image, 0, image.TellWidth(), image.TellHeight(), 0,Final, 0, Final.TellHeight()/2);
 
  tile(image,output,forth);//=========

  RangedPixelToPixelCopy(forth, 0, forth.TellWidth(), forth.TellHeight(), 0,Final, Final.TellWidth()/2, 0);
  RangedPixelToPixelCopy(forth, 0, forth.TellWidth()/2, forth.TellHeight(), 0,Final, Final.TellWidth()/4, 0);
  RangedPixelToPixelCopy(forth, 0, forth.TellWidth()/2, forth.TellHeight(), 0,Final, 0, 0);
  RangedPixelToPixelCopy(forth, 0, forth.TellWidth(), forth.TellHeight(),forth.TellHeight()/2,Final, Final.TellWidth()/2, Final.TellHeight()/2);
  RangedPixelToPixelCopy(forth, 0, forth.TellWidth(), forth.TellHeight(),forth.TellHeight()/2,Final, Final.TellWidth()/2, 3*Final.TellHeight()/4);
  
  Final.WriteToFile(argv[2]);
  
  return 0;
}
//=-------------------------------------------------------------------------------------------------------------------
void scale_down(BMP& I, BMP& O){

  O.SetSize(I.TellWidth()/2, I.TellHeight()/2);
  
  for(int i = 0; i < I.TellWidth()/2; i++)
    {
      for(int j = 0; j < I.TellHeight()/2; j++)
	{
	  int redavg=((I(2*i,2*j)->Red) +(I(2*i, 2*j + 1)->Red)+(I(2*i+1,2*j)->Red) +(I(2*i+1,2*j+1)->Red))/4;
	  O(i,j)->Red = redavg;
	  int gravg=((I(2*i,2*j)->Green) +(I(2*i, 2*j + 1)->Green)+(I(2*i+1,2*j)->Green) +(I(2*i+1,2*j+1)->Green))/4;
	  O(i,j)->Green = gravg;
	  int blavg=((I(2*i,2*j)->Blue) +(I(2*i, 2*j + 1)->Blue)+(I(2*i+1,2*j)->Blue) +(I(2*i+1,2*j+1)->Blue))/4;
	  O(i,j)->Blue =blavg;
	}
    }

  I.SetSize(I.TellWidth()/2, I.TellHeight()/2); // this changes the original to the same as output so that way
                                                // it can be scaled down again   
  for(int i = 0; i < I.TellWidth(); i++)
    {
      for(int j = 0; j < I.TellHeight(); j++)
        {
	  I(i,j)->Red = O(i,j)->Red;
	  I(i,j)->Green = O(i,j)->Green;
	  I(i,j)->Blue =O(i,j)->Blue;
        }
    }
}
//=-------------------------------------------------------------------------------------------------------------------
void tile(BMP& I, BMP& O,BMP& K){
  
  if(I.TellWidth()>5)
    {
      scale_down(I,O);

      for(int i = 0; i < K.TellWidth()-O.TellWidth()*2; i = i+O.TellWidth())
	{
	  RangedPixelToPixelCopy(O, 0, O.TellWidth(), O.TellHeight(), 0, K, i, O.TellHeight());
	}

      for(int i = K.TellHeight()-O.TellHeight(); i > O.TellHeight(); i = i-O.TellHeight())
        {
          RangedPixelToPixelCopy(O, 0, O.TellWidth(), O.TellHeight(), 0, K, K.TellWidth()- O.TellWidth()*2, i);
        }

      tile(I,O,K);//========= 
    }
}
