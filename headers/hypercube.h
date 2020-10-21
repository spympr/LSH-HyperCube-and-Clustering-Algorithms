#include "../headers/exhausting.h"
#include <map> 

class HyperCube
{
    public:
        int Num_of_Images,Num_of_Queries,k,M,N,probes,R,dimensions,W,HashTableSize;
        int* modulars;
        double* tHypercube,*tTrue;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket*** Hash_Tables;
        string input_file,query_file;
        map<int, int> f_i;

        HyperCube(string input_file_,string query_file_,int N_,int k_,int R_,int M_,int probes_)
        : k(k_),M(M_),probes(probes_),R(R_),input_file(input_file_),query_file(query_file_),N(N_)
        {
            InitHyperCube();
        }

        int hammingDistance(int , int );
        void InitHyperCube();
        void Approximate_Hypercube();
};