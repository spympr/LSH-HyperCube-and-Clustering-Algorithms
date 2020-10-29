#ifndef LSH_H
#define LSH_H

#include "../headers/exhausting.h" 

//Forward declaration
class Bucket;

class LSH
{
    private:
        int Num_of_Images,Num_of_Queries,k,L,R,dimensions,W,N,m,M,HashTableSize;
        int* modulars;
        double *tLSH,*tTrue,dist_AF,time_error;;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket*** Hash_Tables;
        string input_file,query_file,output_file;
        fstream file;

    public:
        LSH(string input_file_,string query_file_,string output_file_,int L_,int N_,int k_,int R_)
        :input_file(input_file_),query_file(query_file_),output_file(output_file_),L(L_),N(N_),k(k_),R(R_),dist_AF(0.0),time_error(0.0)
        {}

        ~LSH()
        {
            //Deallocation of memory of Images_Array...
            for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
            delete [] Images_Array;

            //Deallocation of memory of Queries_Array...
            for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
            delete [] Queries_Array;

            //Deallocation of memory of s_i...
            for(int i=0;i<(k*L);i++)    delete [] s_i[i];
            delete [] s_i;        

            //Deallocation of memory of Hash_Tables...
            for(int i=0;i<L;i++)    
            {
                for(int j=0;j<(HashTableSize);j++)   
                    if(Hash_Tables[i][j]!=NULL)
                        delete Hash_Tables[i][j];
                delete [] Hash_Tables[i];
            }
            delete [] Hash_Tables;

            //Deallocation of memory of True_Distances...
            for(int i=0;i<Num_of_Queries;i++)  
                delete [] True_Distances[i];
            delete [] True_Distances;
            
            //Deallocation of memory of tLSH,tTrue,modulars...
            delete [] tLSH;
            delete [] tTrue;
            delete [] modulars;
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
        fstream get_file();
};

#endif