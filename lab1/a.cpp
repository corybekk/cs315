#include <iostream>
#include <vector>
using namespace std;


int MAX(vector<int>A, int k){

  int temp;

  if(k==0){
    temp = A[k];
    return temp;
  }

  else if(temp < MAX(k-1,k)){
      temp = MAX(k-1,k);
  } 

  return temp;
    
}



int main(){

  vector<int>B;
 
  cout<<"enter in K\n";
  cin>>input;

  for(int i =0; i<50; i++;){
    B.push_back[i];
  }

  cout<<MAX(B,input)<<endl;

  return 0;
}
