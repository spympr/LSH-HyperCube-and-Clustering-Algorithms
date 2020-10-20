#include "../headers/hypercube.h"
#include <math>

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
    //Declaration of variables...
    int Num_Of_Images,Columns_Of_Images,Rows_Of_Images,Num_Of_Queries,Columns_Of_Queries,Rows_Of_Queries;
    item **Images_Array,**Queries_Array;

    //Read input binary file...
    Read_BF(&Images_Array,&Num_Of_Images,&Columns_Of_Images,&Rows_Of_Images,input_file,1);
    
    //Read query binary file...
    Read_BF(&Queries_Array,&Num_Of_Queries,&Columns_Of_Queries,&Rows_Of_Queries,query_file,1000);

    //Printing...
    cout << "Images: " << Num_Of_Images << endl << "Queries: " << Num_Of_Queries << endl << "Rows: " << Rows_Of_Images << endl << "Columns: " << Columns_Of_Images << endl;

    //Initilization of W(grid), dimensions of each Image...
    int dimensions = (int)(floor(double(log2(Num_Of_Images) - (rand() % 3 +1)));
    int HashTableSize = pow(2,dimensions);

    //Declaration of hash tables...
    Bucket* Hash_Table = new Bucket[HashTableSize];

    
    
}