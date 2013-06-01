#include <iostream>
using namespace std;

long long  exp (long long int x, int n) {

  static int counter;
  
  if (n == 0) return 1; 

  else if (n % 2 == 0){
    counter++;
    cout<<counter<<endl;   
    return exp(x * x, n/2);
  }
  else{
    counter++;
    cout<<counter<<endl;
    return exp(x * x, (n - 1)/2) * x;
  }
}


int main(){

  int a = 2;
  int b = b;
  cout<<"type in n\n";
  cin>>b;

  cout<<exp(a,b)<<endl;

  return 0;
}
