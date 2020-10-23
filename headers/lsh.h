#ifndef LSH_H
#define LSH_H

#include "../headers/exhausting.h" 

using namespace std;

//Forward declaration
class Bucket;

class LSH
{
    private:
        int Num_of_Images,Num_of_Queries,k,L,R,dimensions,W,N,m,M,HashTableSize;
        int* modulars;
        double *tLSH,*tTrue,dist_error,time_error;;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket*** Hash_Tables;
        string input_file,query_file;

    public:
        LSH(string input_file_,string query_file_,int L_,int N_,int k_,int R_)
        :input_file(input_file_),query_file(query_file_),L(L_),N(N_),k(k_),R(R_),dist_error(0.0),time_error(0.0)
        {
            InitLSH();
        }

        void Approximate_LSH();
        void Approximate_Range_Search(int);
        void InitLSH();
        int get_dimensions();
        int get_M();
        int get_k();
        int get_L();
        int get_N();
        int get_W();
        int get_HashTableSize();
        int get_Num_of_Images();
        int get_Num_of_Queries();
        int* get_modulars();
        int** get_s_i();
        double* get_tTrue();
        int** get_True_Distances();
        item** get_Images_Array();
        item** get_Queries_Array();
        Bucket*** get_Hash_Tables();
};

#endif