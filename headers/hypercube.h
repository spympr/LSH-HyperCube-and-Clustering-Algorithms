#ifndef HYPERCUBE_H
#define HYPERCUBE_H

#include "../headers/exhausting.h"

class HyperCube
{
    private:
        int Num_of_Images,Num_of_Queries,k,m,M,M_boundary,N,probes,R,dimensions,W,HashTableSize;
        int* modulars, *f_i;
        double* tHypercube,*tTrue,time_error,dist_AF;
        int **s_i,**True_Distances;
        item **Images_Array,**Queries_Array;
        Bucket** Hash_Table;
        string input_file,query_file,output_file;
        map<unsigned int,unsigned int>* f_i_map;
        fstream file;

    public:

        HyperCube(string input_file_,string query_file_,string output_file_,int N_,int k_,int R_,int M_boundary_,int probes_)
        : k(k_),M_boundary(M_boundary_),probes(probes_),R(R_),input_file(input_file_),query_file(query_file_),output_file(output_file_),N(N_),dist_AF(0.0),time_error(0.0)
        {         
            f_i_map = new map<unsigned int, unsigned int>[k];
        }

        ~HyperCube()
        {
            delete [] f_i_map;

            //Deallocation of memory of Images_Array...
            for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
            delete [] Images_Array;

            //Deallocation of memory of Queries_Array...
            for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
            delete [] Queries_Array;

            //Deallocation of memory of s_i...
            for(int i=0;i<k;i++)    delete [] s_i[i];
            delete [] s_i;        

            //Deallocation of memory of Hash_Tables...
            for(int j=0;j<(HashTableSize);j++)   
                if(Hash_Table[j]!=NULL)
                    delete Hash_Table[j];
            delete [] Hash_Table;

            //Deallocation of memory of True_Distances...
            for(int i=0;i<Num_of_Queries;i++)  
                delete [] True_Distances[i];
            delete [] True_Distances;
            
            //Deallocation of memory of tLSH,tTrue,modulars...
            delete [] tHypercube;
            delete [] tTrue;
            delete [] modulars;
        }

        int hammingDistance(int , int );
        void InitHyperCube();
        void Approximate_Hypercube();
        void Approximate_Range_Search(int ,unsigned int );

        int get_dimensions();
        int get_M_boundary();
        int get_M();
        int get_k();
        int get_R();
        int get_N();
        int get_W();
        int get_HashTableSize();
        int get_Num_of_Images();
        int get_Num_of_Queries();
        int* get_modulars();
        int** get_s_i();
        double* get_tTrue();
        int** get_True_Distances();
        map<unsigned int,unsigned int>* get_f_i_map();
        item** get_Images_Array();
        item** get_Queries_Array();
        Bucket** get_Hash_Table();
};
#endif