#ifndef RA_LSH_H
#define RA_LSH_H

#include "../headers/kmeans.h"

//Forward declaration
class Nearest_Centroids;

class RA_LSH
{
    private:
        int Num_of_Images,k,L,dimensions,W,m,M,HashTableSize,K;
        int* modulars;
        int **s_i;
        item **Images_Array;
        Bucket*** Hash_Tables;
        string output_file;
        fstream file;
        map<int,Nearest_Centroids*>* points;
        item** centroids;

    public:
        RA_LSH(string output_file_,map<int,Nearest_Centroids*>* points_,item** centroids_,kmeans* kmeansptr)
        :output_file(output_file_),points(points_),centroids(centroids_),K(kmeansptr->get_K()),dimensions(kmeansptr->get_dimensions()),L(kmeansptr->get_L()),k(kmeansptr->get_LSH_k())
        {
            Num_of_Images = kmeansptr->get_number_of_images();
            Images_Array = kmeansptr->get_Images_Array();
            HashTableSize = Num_of_Images/8;
        }

        ~RA_LSH()
        {
            Deallocation_of_Memory();
        }

        void RA_LSH_Assign();
        void Init_RA_LSH();
        void Deallocation_of_Memory();
        void Map_Init();
        void Exhausting_For_Non_Assign_Points();
        
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