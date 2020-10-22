#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>  
#include <map>

using namespace std;

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('c');
  if (it != mymap.end())
    mymap.erase (it);
  else 
    mymap.erase(mymap.find('a'));

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "b => " << mymap.find('b')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  // int a[4];
  // a[0] = 1;
  // a[1] = 0;
  // a[2] = 0;
  // a[3] = 1;
  // int b=0;

  // for(int i=0; i<4;i++)
  //   b += a[i] << ((4-(i+1)));

  // std::cout << b << std::endl;

  return 0;
}