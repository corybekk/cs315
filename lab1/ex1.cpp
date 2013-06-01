#include <iostream>
using namespace std;

int f(int n);


int main(){
  cout<<f(0)<<endl;
  cout<<f(1)<<endl;
  //  cout<<f(2)<<endl;
  cout<<f(3)<<endl;
  cout<<f(4)<<endl;
  cout<<f(5)<<endl;
  cout<<f(6)<<endl;
  cout<<f(7)<<endl;
  cout<<f(8)<<endl;
  cout<<f(9)<<endl;
  cout<<f(10)<<endl;
  cout<<f(11)<<endl;
  cout<<f(12)<<endl;
  cout<<f(13)<<endl;
   
 return 0;
}


int f(int n) {
  if (n % 2 == 1) return 1; else
    if (n == 0) return 2;
  return f(n - 3) + n;
}
