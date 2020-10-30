#ifndef RA_HYPERCUBE_H
#define RA_HYPERCUBE_H

#include "../headers/kmeans.h"

// //Forward declaration
class kmeans;
class Nearest_Centroids;

class RA_HyperCube
{
    private:
        int Num_of_Images,k,m,M,M_boundary,probes,dimensions,W,HashTableSize,K;
        int* modulars, *f_i;
        int **s_i;
        item **Images_Array;
        Bucket** Hash_Table;
        map<unsigned int,unsigned int>* f_i_map;
        map<int,Nearest_Centroids*>* points;
        item** centroids;
        kmeans* kmeansptr;

    public:
        RA_HyperCube(map<int,Nearest_Centroids*>* points_,item** centroids_,kmeans* kmeansptr_)
        : points(points_),centroids(centroids_),kmeansptr(kmeansptr_)
        {      
            Initialize_Values();   
        }

        ~RA_HyperCube()
        {
            Deallocation_of_Memory();
        }

        int hammingDistance(int , int );
        void Init_RA_HyperCube();
        void Approximate_Hypercube();
        void Approximate_Range_Search(int ,unsigned int );
        void Deallocation_of_Memory();
        void Initialize_Values();

        int get_dimensions();
        int get_M_boundary();
        int get_M();
        int get_k();
        int get_W();
        int get_HashTableSize();
        int get_Num_of_Images();
        int* get_modulars();
        int** get_s_i();
        map<unsigned int,unsigned int>* get_f_i_map();
        item** get_Images_Array();
        Bucket** get_Hash_Table();
};

#endif