#include <iostream>
using namespace std;

  int fib(int n){
    int i=1;
    if(n==0)return 1;
    if(n==1){
      cout<<i<<endl;// counts how many times 'i' is called
      return 1;
    }
    else return fib(n-1) + fib(n-2);
  }

int main(){

  cout<<fib(10)<<endl;

  return 0;
}
