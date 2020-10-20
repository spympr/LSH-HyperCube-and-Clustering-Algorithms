#include "../headers/hypercube.h"

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

void HyperCube(string input_file, string query_file,int L,int N,int k,int R,int M,int probes)
{
    
}