#include <iostream>
using namespace std;

int fib(int n);


int main(){

  cout<<fib(50)<<endl;

  return 0;
}


int fib(int n){

  static long long prev;

  if(n==0){
    prev = 1;
    return 0;
  }
  else if(n==1){
    prev=0;
    return 1;
  }
  else{
    long long temp = fib(n-1);
    long long temp1= temp + prev;
    prev=temp;
    return temp1;
  }
}
