#include "../headers/hypercube.h"

int HyperCube::hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
  
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    } 
  
    return setBits; 
} 

void HyperCube::InitHyperCube()
{
    //Declaration of variables...
    int Rows,Columns;

    //Read input binary file...
    Read_BF(&Images_Array,&Num_of_Images,&Columns,&Rows,input_file,1);
    
    //Read query binary file...
    Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,1000);

    //Printing...
    cout << "Images: " << Num_of_Images << endl << "Queries: " << Num_of_Queries << endl << "Rows: " << Rows << endl << "Columns: " << Columns << endl;

    //Initilization of W(grid), dimensions of each Image...
    dimensions = (int)(floor(double(log2(Num_of_Images) - (rand() % 3 +1))));
    HashTableSize = pow(2,dimensions);

    //Declaration of hash tables...
    Bucket* Hash_Table = new Bucket[HashTableSize];
}