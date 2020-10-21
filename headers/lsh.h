#ifndef LSH_H
#define LSH_H

#include "../headers/exhausting.h"

using namespace std;

//Forward declaration
class Bucket;

class LSH
{
    public:
        int Num_of_Images,Num_of_Queries,k,L,R,dimensions,W,N,m,M,HashTableSize;
        int* modulars;
        double* tLSH,*tTrue;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket*** Hash_Tables;
        string input_file,query_file;

        LSH(string input_file_,string query_file_,int L_,int N_,int k_,int R_)
        :input_file(input_file_),query_file(query_file_),L(L_),N(N_),k(k_),R(R_)
        {
            InitLSH();
        }

        void Approximate_LSH();
        void Approximate_Range_Search(int*, int);
        void InitLSH();
};

#endif