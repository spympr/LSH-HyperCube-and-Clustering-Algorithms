#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include "../headers/bucket.h"

void Bucket::add(item* image)
{
    images.push_back(image);
}

unsigned int mod(int k, int M) 
{   
    //M is 2^(32/k) so...
    // unsigned int temp = k << int(32-log2(M));
    // temp = temp << int(32-log2(M));
    // return temp;    

    if ((k % M) < 0) 
        return (unsigned int ) (k % M + M);
    else
        return (unsigned int) (k % M);
}

int mod_expo(int base, int exponent,int modulus) 
{
    if(modulus==1)  return 0;
    int c=1;
    for(int i=0;i<exponent;i++) c = (c*base)%modulus;
    return c;
}

int Calculate_hp(int* a_i, infoptr info)
{
    unsigned int sum = 0,first_term,second_term,temp_term;

    for(int i=1; i<=info->dimensions;i++)
    {
        first_term = mod(a_i[info->dimensions-i],info->M);
        second_term = info->modulars[i-1];
        temp_term = first_term*second_term;
        sum += mod(temp_term,info->M);
    }
    // cout << "temp = " << sum << endl;        
    return mod(sum,info->M);
}

void gi_values_of_train(infoptr info,unsigned int** g_i)
{
    for(int image=0;image<info->Num_of_Images;image++)
    {
        for(int i=0;i<info->L;i++)
        {
            int h_p[info->k];
            for(int j=0;j<info->k;j++)
            {
                int a_i[info->dimensions];

                for(int z=0;z<info->dimensions;z++)
                {
                    a_i[z] = floor((double)((info->Images_Array[image][z] - info->s_i[(i*info->k)+j][z]))/(double)(info->W));
                    // cout << a_i[z] << " " ;
                }
                // cout << endl;
                h_p[j] = Calculate_hp(a_i,info);
                // if(image<10)    cout << "f " << h_p[j] << endl;
            }
            for(int j=0;j<info->k;j++)
            {
                g_i[image][i] += (h_p[j] << ((info->k-(j+1))*8));                
            }
            g_i[image][i] = g_i[image][i]%(info->HashTableSize);
        }
    }
}

void gi_values_of_query(infoptr info, unsigned int* gi_query_values, int query)
{
    for(int i=0;i<info->L;i++)
    {
        gi_query_values[i] = 0;

        int h_p[info->k];
        for(int j=0;j<info->k;j++)
        {
            int a_i[info->dimensions];

            for(int z=0;z<info->dimensions;z++)
            {
                a_i[z] = floor((double)((info->Queries_Array[query][z] - info->s_i[i*info->k+j][z]))/(double)(info->W));
            }
            h_p[j] = Calculate_hp(a_i,info);
        }
        
        for(int j=0;j<info->k;j++)
        {
            gi_query_values[i] += (h_p[j] << ((info->k-(j+1))*8));                
        }
        gi_query_values[i] = gi_query_values[i]%(info->HashTableSize);
    }
}

void Insert_Images_To_Buckets(infoptr info)
{
    //Allocate memory so as to store temporarily g_i values...
    unsigned int** g_i = new unsigned int*[info->Num_of_Images];
    for(int i=0;i<info->Num_of_Images;i++)  
    {
        g_i[i] = new unsigned int[info->L];
        for(int j=0;j<info->L;j++)  g_i[i][j]=0;
    }

    //Call function so as to compute all g_i values...
    gi_values_of_train(info,g_i);
    
    //Fill buckets of L Hash_Tables...
    for(int i=0;i<info->Num_of_Images;i++)
    {
        for(int j=0;j<info->L;j++)
        {
            if(info->Hash_Tables[j][g_i[i][j]]==NULL)  info->Hash_Tables[j][g_i[i][j]] = new Bucket();
            info->Hash_Tables[j][g_i[i][j]]->add(info->Images_Array[i]);    
        }
    }

    //Deallocation of memory...
    for(int i=0;i<info->Num_of_Images;i++)  
        delete [] g_i[i];
    delete [] g_i;
}