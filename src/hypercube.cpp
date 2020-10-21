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
    Bucket** Hash_Table = new Bucket*[HashTableSize];
    for(int i=0;i<HashTableSize;i++)
    {
        Hash_Table[i] = NULL;
    }

    //Initialization of 2D array True_Distances...
    True_Distances = new int*[Num_of_Queries];
    for(int i=0;i<Num_of_Queries;i++)   True_Distances[i] = new int[N];

    //Initialization of m,M...
    int M_boundary = pow(2,floor((double)32/(double)k));
    int m = 423255;
    // int m = pow(2,27)+1;
    // int m = M/3;
    cout << "M " << M << endl;

    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M_boundary);

    //Initialization of tTrue,tLSH arrays...
    tHypercube = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    //Do exhausting search and init W...
    ExhaustingNN(this,True_Distances);
    int W = 50000;
    cout << "W: " << W << endl << endl;

    //Initialization of uniform_int_distribution class...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,W);
    
    //Initialization of L*k*d(imensions) random s_i integers...
    s_i = new int*[k];
    for(int i=0;i<(k);i++)
    {
        s_i[i] = new int[dimensions];
        for(int j=0;j<dimensions;j++)   
            s_i[i][j] = distribution(generator);
    }

    //Fill Hash Tables...
    Insert_Images_To_Buckets_HyperCube(this);

    //Print Buckets...
    // for(int i=0;i<L;i++)
    // {
    int counter=0;
    for(int j=0;j<HashTableSize;j++)
        if(Hash_Tables[j]!=NULL)
            counter++;                
    cout << "HashTable " << j << ": " << counter << endl;
    // }
    cout << endl;

    Approximate_Hypercube();

    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    //Deallocation of memory of Queries_Array...
    for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
    delete [] Queries_Array;

    //Deallocation of memory of s_i...
    for(int i=0;i<(k);i++)    delete [] s_i[i];
    delete [] s_i;        

    //Deallocation of memory of Hash_Tables...
    // for(int i=0;i<L;i++)    
    // {
    for(int j=0;j<(HashTableSize);j++)   
        if(Hash_Tables[j]!=NULL)
            delete Hash_Tables[j];
        // delete [] Hash_Tables[i];
    // }

    //Deallocation of memory of True_Distances...
    for(int i=0;i<Num_of_Queries;i++)  
        delete [] True_Distances[i];
    delete [] True_Distances;
    
    //Deallocation of memory of tLSH,tTrue,modulars...
    delete [] tHypercube;
    delete [] tTrue;
    delete [] modulars;
}

void HyperCube::Approximate_Hypercube()
{

}