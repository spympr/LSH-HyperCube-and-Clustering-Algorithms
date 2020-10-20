#include "../headers/read_binary_file.h"

using namespace std;

class Bucket
{
    public:
        vector<item*> images;     

        void add(item* );
};

class Info
{
    public:
        int Num_of_Images,Num_of_Queries,k,L,R,dimensions,W,N,m,M,HashTableSize;
        int* modulars;
        double* tLSH,*tTrue;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket*** Hash_Tables;

        Info(int NoI,int NoQ,int k_,int L_,int N_,int R_,int dimensions_,item** Images_Array_,item** Queries_Array_, Bucket*** Hash_Tables_,int m_,int M_,int* modulars_,int HashTableSize_,double* tLSH_,double* tTrue_)
        : Num_of_Images(NoI),Num_of_Queries(NoQ),k(k_),L(L_),N(N_),R(R_),dimensions(dimensions_),Images_Array(Images_Array_),Queries_Array(Queries_Array_),Hash_Tables(Hash_Tables_),m(m_),M(M_),modulars(modulars_),HashTableSize(HashTableSize_),tLSH(tLSH_),tTrue(tTrue_){}
};

typedef Info* infoptr;

int mod_expo(int , int ,int );
unsigned int mod(int , int );
int Calculate_hp(int* , infoptr );
void gi_values_of_train(infoptr,unsigned int**);
void Insert_Images_To_Buckets(infoptr);
void gi_values_of_query(infoptr, unsigned int* , int);