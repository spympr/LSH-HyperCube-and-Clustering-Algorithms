#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include "../headers/bucket.h"

void Bucket::add(item* image)
{
    images.push_back(image);
}

int mod_expo(int base, int exponent,int modulus) 
{
    if(modulus==1)  return 0;
    int c=1;
    for(int i=0;i<exponent;i++) c = (c*base)%modulus;
    return c;
    
    // int result = 1;
  
    // base = base % exponent; 
    // if(base == 0) return 0;
    // while(exponent > 0)  
    // {  
    //     if (exponent & 1)  
    //         result = (result*base) % exponent;  
  
    //     exponent = exponent>>1;
    //     base = (base*base) % exponent;  
    // }  
    // return result;   
}

int Calculate_hp(int* a_i, infoptr info)
{
    int sum = 0,first_term,second_term,temp_term;
    

    for(int i=1; i<=info->dimensions;i++)
    {
        first_term = a_i[info->dimensions-i] % info->M;
        second_term = info->modulars[i-1];
        temp_term = first_term*second_term;        
        sum += (temp_term % info->M);
    }

    return(sum % info->M);
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
                    a_i[z] = floor((info->Images_Array[image][z] - info->s_i[i*info->k+j][z])/info->W);
                }
                h_p[j] = Calculate_hp(a_i,info);

                g_i[image][i] |= (h_p[j] << (j*8));                
            }
                g_i[image][i] = g_i[image][i]%(info->Num_of_Images/16);
        }
    }
}

void gi_values_of_query(infoptr info, unsigned int* gi_query_values, int query)
{
    for(int i=0;i<info->L;i++)
    {
        int h_p[info->k];
        for(int j=0;j<info->k;j++)
        {
            int a_i[info->dimensions];

            for(int z=0;z<info->dimensions;z++)
            {
                a_i[z] = floor((info->Queries_Array[query][z] - info->s_i[i*info->k+j][z])/info->W);
            }
            h_p[j] = Calculate_hp(a_i,info);

            gi_query_values[i] |= (h_p[j] << (j*8));                
        }
            gi_query_values[i] = gi_query_values[i]%(info->Num_of_Images/16);
    }
}

void Insert_Images_To_Buckets(infoptr info)
{
    //Allocate memory so as to store temporarily g_i values...
    unsigned int** g_i = new unsigned int*[info->Num_of_Images];
    for(int i=0;i<info->Num_of_Images;i++)  
        g_i[i] = new unsigned int[info->L];
    
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