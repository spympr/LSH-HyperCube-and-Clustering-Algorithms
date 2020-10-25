#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>  
#include <map>
#include <random> 

using namespace std;

int hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
    
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    }

    return setBits; 
} 

int main ()
{
  // std::map<char,int> mymap;
  // std::map<char,int>::iterator it;

  // mymap['a']=50;
  // mymap['b']=100;
  // mymap['c']=150;
  // mymap['d']=200;

  // it = mymap.find('c');
  // if (it != mymap.end())
  //   mymap.erase (it);
  // else 
  //   mymap.erase(mymap.find('a'));

  // // print content:
  // std::cout << "elements in mymap:" << '\n';
  // std::cout << "a => " << mymap.find('a')->second << '\n';
  // std::cout << "b => " << mymap.find('b')->second << '\n';
  // std::cout << "c => " << mymap.find('c')->second << '\n';
  // std::cout << "d => " << mymap.find('d')->second << '\n';

  // int a[4];
  // a[0] = 1;
  // a[1] = 0;
  // a[2] = 0;
  // a[3] = 1;
  // int b=0;

  // for(int i=0; i<4;i++)
  //   b += a[i] << ((4-(i+1)));

  // std::cout << b << std::endl;
  // int k=6812,l=6868;
  // cout << hammingDistance(k,l) << endl;


  // std::map<int,int> points;
  // std::map<int,int>::iterator it;

  // points[1]=1;
  // points[2]=2;
  // points[3]=3;
  // points[4]=4;
  // points[5]=5;
  // for(it=points.begin();it!=points.end();it++)    
  //   cout << it->first << " " << it->second << endl;
  // cout << "----------------------------------" << endl;
  // points[1]=2;
  // for(it=points.begin();it!=points.end();it++)    
  //   cout << it->first << " " << it->second << endl;
for(int i=0;i<4;i++)
{
    default_random_engine generator;   
    uniform_real_distribution<float> distribution(float(0.0),17000);
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl;
    cout << distribution(generator) << endl << endl;
}
  return 0;
}


  // for(int i;i<Num_of_Images;i++)
  // {
  //   for(int z=0;z<dimensions;z++)
  //   {
  //     cout << Images_Array[i][z] << " "; 
  //   }
  //   cout << endl;
  // }
  // for(int i;i<Num_of_Queries;i++)
  //     cout << Queries_Array[i][Columns*Rows] << " "; 
  // cout << endl << endl;

    // for(int i=0;i<Num_of_Images;i++)
    // {
    //     for(int r=0;r<=Rows*Columns;r++)
    //     {
    //         if(i<4)  cout << Images_Array[i][r] << " ";
    //     }
    //     if(i<4) cout << endl;
    // }
    // cout << endl;

    // map<unsigned int,unsigned int>::iterator it;
    // for(int i=0;i<k;i++)
    // {
    //     cout << "Map " << i << endl;
    //     for(auto it = f_i_map[i].cbegin(); it != f_i_map[i].cend(); ++it)        
    //     {
    //         cout << it->first << " " << it->second << endl;
    //     }
    //     cout << "=======================================" << endl;
    // }