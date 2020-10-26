#ifndef BUCKET_H
#define BUCKET_H

#include "../headers/read_binary_file.h"

class Bucket
{
    public:
        vector< pair<item*,unsigned int> > images;     

        void add(item*,unsigned int);
};

int mod_expo(int , int ,int );
unsigned int mod(int , int );
int Calculate_hp_LSH(int* , LSH* );
int Calculate_hp_HyperCube(int* , HyperCube* );
void gi_values_of_train(LSH*,unsigned int**);
void fi_values_of_train(HyperCube*, unsigned int*);
void fi_values_of_query(HyperCube*, unsigned int*);
void Insert_Images_To_Buckets_LSH(LSH*);
void Insert_Images_To_Buckets_HyperCube(HyperCube* info);
void gi_values_of_query(LSH*, unsigned int* , int);

#endif