#ifndef BUCKET_H
#define BUCKET_H

#include "../headers/read_binary_file.h"

class Bucket
{
    public:
        vector<pair<item*,unsigned int>> images;     

        void add(item*,unsigned int);
};

int mod_expo(int , int ,int );
unsigned int mod(int , int );
int Calculate_hp_LSH(int* , LSH* );
int Calculate_hp_RA_LSH(int*, RA_LSH*);
int Calculate_hp_HyperCube(int* , HyperCube* );
void gi_values_of_train(LSH*,unsigned int**);
void gi_values_of_train_RA_LSH(RA_LSH*,unsigned int**);
void fi_values_of_train(HyperCube*, unsigned int*);
void fi_values_of_query(HyperCube*, unsigned int*);
void Insert_Images_To_Buckets_LSH(LSH*);
void Insert_Images_To_Buckets_HyperCube(HyperCube*);
void Insert_Images_To_Buckets_RA_LSH(RA_LSH*);
void Insert_Images_To_Buckets_RA_HyperCube(RA_HyperCube*);
void fi_values_of_train_RA_HyperCube(RA_HyperCube*,unsigned int*);
int Calculate_hp_RA_HyperCube(int*, HyperCube*);
void gi_values_of_query(LSH*, unsigned int* , int);
void Reverse_Assignment_LSH_Centroid_in_Bucket(RA_LSH*, unsigned int*, item*);
unsigned int Reverse_Assignment_HyperCube_Centroid_in_Bucket(RA_HyperCube*, item*);

#endif