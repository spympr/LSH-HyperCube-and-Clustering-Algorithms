#ifndef RA_LSH_H
#define RA_LSH_H

#include "../headers/kmeans.h"
//Forward declaration
class Bucket;

class RA_LSH
{
    private:
        int Num_of_Images,k,L,dimensions,W,m,M,HashTableSize;
        int* modulars;
        int **s_i;
        item **Images_Array;
        Bucket*** Hash_Tables;
        string input_file,output_file;
        fstream file;
        map <int,Nearest_Centroids*>* points;
        item** centroids;

    public:
        RA_LSH(string input_file_,string output_file_,int L_,int k_, map <int,Nearest_Centroids*>* points_, item** centroids_)
        :input_file(input_file_),output_file(output_file_),L(L_),k(k_),points(points_),centroids(centroids_)
        {}

        ~RA_LSH()
        {
            Deallocation_of_Memory();
        }

        void Approximate_LSH();
        void RA_LSH_Assign();
        void Approximate_Range_Search(int);
        void InitLSH();
        void Deallocation_of_Memory();
        
        int get_dimensions();
        int get_M();
        int get_k();
        int get_L();
        int get_W();
        int get_HashTableSize();
        int get_Num_of_Images();
        int* get_modulars();
        int** get_s_i();
        item** get_Images_Array();
        Bucket*** get_Hash_Tables();
};

#endif