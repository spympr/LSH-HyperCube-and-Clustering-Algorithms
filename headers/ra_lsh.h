#ifndef RA_LSH_H
#define RA_LSH_H

#include "../headers/kmeans.h"

// //Forward declaration
class kmeans;
class Nearest_Centroids;

class RA_LSH
{
    private:
        int Num_of_Images,k,L,dimensions,W,m,M,HashTableSize,K;
        int* modulars;
        int **s_i;
        item **Images_Array;
        Bucket*** Hash_Tables;
        map<int,Nearest_Centroids*>* points;
        item** centroids;
        kmeans* kmeansptr;

    public:
        RA_LSH(map<int,Nearest_Centroids*>* points_,item** centroids_,kmeans* kmeansptr_)
        :points(points_),centroids(centroids_),kmeansptr(kmeansptr_)
        {
            Initialize_Values();
        }

        ~RA_LSH()
        {
            Deallocation_of_Memory();
        }

        void Init_RA_LSH();
        void Initialize_Values();
        void Map_Init();
        void RA_LSH_Assign();
        void Exhausting_For_Non_Assign_Points();
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