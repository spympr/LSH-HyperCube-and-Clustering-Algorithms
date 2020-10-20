#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include <random> 
#include "../headers/lsh.h"

using namespace std;

int main(int argc, char** argv)
{
    string answer,input_file, query_file, output_file;
    int k,L,N,R;

    if(argc ==1)
    {
        cout << "Give me the path of dataset: "; 
        cin >> input_file;

        cout << "Give me the path of queryset: "; 
        cin >> query_file;

        cout << "Give me the path of exit file: "; 
        cin >> output_file;

        k=4;
        L=5;
        N=1;
        R=1.0;
    }
    else
    {
        if(strcmp(argv[0],"./lsh") == 0)
        {
            if(argc!=15 && argc!=7)   
            {
                cout << "Please give an input with this form: ./lsh  –d  <input  file>  –q  <query  file>  –k  <int>  -L  <int>  -ο  <output  file>  -Ν<number of nearest> -R <radius>\n";
                return -1;
            }

            k=4;
            L=5;
            N=1;
            R=10000;

            for(int i=1;i<argc;i+=2)
            {
                if(strcmp(argv[i],"-d") == 0)
                    input_file = (argv[i+1]);                    
                else if(strcmp(argv[i],"-q") == 0)
                    query_file = (argv[i+1]);
                else if(strcmp(argv[i],"-o") == 0)
                    output_file = (argv[i+1]);
                else if(strcmp(argv[i],"-k") == 0)
                    k = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-L") == 0)
                    L = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-N") ==0)
                    N = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-R") == 0)
                    R = atoi(argv[i+1]);
                else
                {
                    cout << "Please give an input with this form: ./lsh  –d  <input  file>  –q  <query  file>  –k  <int>  -L  <int>  -ο  <output  file>  -Ν<number of nearest> -R <radius>\n";
                }
            }
        }
        else if(argv[0] == "./cube")
        {
            if(argc!=17 && argc!=5)    
            {
                cout << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο<output file> -Ν <number of nearest> -R <radius>\n";
                return -1;
            }

            int k=14,N=1,probes=2,M=10,R=10000;

            for(int i=1;i<=argc;i+=2)
            {
                if(argv[i] == "-d")
                    input_file = (argv[i+1]);
                else if(argv[i] == "-q")
                    query_file = (argv[i+1]);
                else if(argv[i] == "-o")
                    output_file = (argv[i+1]);
                else if(argv[i] == "-k")
                    k = atoi(argv[i+1]);
                else if(argv[i] == "-probes")
                    probes = atoi(argv[i+1]);
                else if(argv[i] == "-M")
                    M = atoi(argv[i+1]);
                else if(argv[i] == "-N")
                    N = atoi(argv[i+1]);
                else if(argv[i] == "-R")
                    R = atof(argv[i+1]);
                else
                {
                    cout << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο<output file> -Ν <number of nearest> -R <radius>\n";
                }
            }
        }
    }

    while(true)
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
        int dimensions = Columns_Of_Images*Rows_Of_Images,HashTableSize=Num_Of_Images/8;

        //Declaration of hash tables...
        Bucket** Hash_Tables[L];
        for(int i=0;i<L;i++)    
        {
            Hash_Tables[i] = new Bucket*[HashTableSize];
            for(int j=0;j<HashTableSize;j++)   Hash_Tables[i][j]=NULL;                
        }

        //Initialization of 2D array True_Distances...
        int** True_Distances = new int*[Num_Of_Queries];
        for(int i=0;i<Num_Of_Queries;i++)   True_Distances[i] = new int[N];
        
        //Initialization of m,M...
        int M = pow(2,floor((double)32/(double)k));
        int m = 423255;
        // int m = pow(2,27)+1;
        // int m = M/3;
        
        //Calculation of m^d-1modM array...
        int* modulars = new int[dimensions];
        for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);
    
        //Initialization of tTrue,tLSH arrays...
        double* tLSH = new double[Num_Of_Queries];
        double* tTrue = new double[Num_Of_Queries];

        //Initialization of pointer to object of class Info (store important variables).
        infoptr info = new Info(Num_Of_Images,Num_Of_Queries,k,L,N,R,dimensions,Images_Array,Queries_Array,Hash_Tables,m,M,modulars,HashTableSize,tLSH,tTrue);

        //Do exhausting search and init W...
        ExhaustingNN(info,True_Distances);
        int W = 50000;
        cout << "W: " << W << endl << endl;
            
        //Initialization of uniform_int_distribution class...
        default_random_engine generator;   
        uniform_int_distribution<int> distribution(0,W);
        
        //Initialization of L*k*d(imensions) random s_i integers...
        int** s_i = new int*[L*k];
        for(int i=0;i<(L*k);i++)
        {
            s_i[i] = new int[dimensions];
            for(int j=0;j<dimensions;j++)   
                s_i[i][j] = distribution(generator);
        }

        //Update info with information of s_i array,True_Distances array and W...
        info->s_i = s_i;
        info->W = W;
        info->True_Distances = True_Distances;

        //Fill Hash Tables...
        Insert_Images_To_Buckets(info);

        //Print Buckets...
        for(int i=0;i<L;i++)
        {
            int counter=0;
            for(int j=0;j<HashTableSize;j++)
                if(Hash_Tables[i][j]!=NULL)
                    counter++;                
            cout << "HashTable " << i << ": " << counter << endl;
        }
        cout << endl;
    
        Approximate_LSH(info);
        
        ////////////////////////////////////////////////////////////////////

        //Deallocation of memory of Images_Array...
        for(int i=0;i<Num_Of_Images;i++)    delete [] Images_Array[i];
        delete [] Images_Array;

        //Deallocation of memory of s_i...
        for(int i=0;i<(k*L);i++)    delete [] s_i[i];
        delete [] s_i;        

        //Deallocation of memory of Hash_Tables...
        for(int i=0;i<L;i++)    
        {
            for(int j=0;j<(Num_Of_Images/16);j++)   
                if(Hash_Tables[i][j]!=NULL)
                    delete Hash_Tables[i][j];
            delete [] Hash_Tables[i];
        }
        
        //Deallocation of memory of pointer to object of class Info...
        delete info;

        ////////////////////////////////////////////////////////////////////////////////////////////
        cout << "Do you want to question something else?\n";
        cin >> answer;

        if((answer == "no") || (answer == "No") || (answer == "NO") || (answer == "n") || (answer =="N"))
            break;
    }

    return 0; 
}