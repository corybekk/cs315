#include <iostream>
#include <cstdlib>
using namespace std;


int main(){

  int count=0;
  int n=0;
  int A[10000];
  int temp;

  cout<<"type in n\n";
  cin>>n;

  for(int p=0; p<10000; p++){
    for(int i=0; i<n; i++){
      A[i]=rand();
    }
  }
  for(int j=1; j<n; ++j){
    temp = A[j];
    
    for (int k = j-1; k >= 0 && A[k] > temp; --k){
      A[k+1] = A[k];
      count++;
    }
    A[j+1] = temp;
  }
  cout<<count/10000<<endl;
  
  return 0;
}
