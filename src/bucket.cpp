#include "../headers/exhausting.h"

void Bucket::add(item* image,unsigned int g_i)
{
    images.push_back(make_pair(image,g_i));
}

unsigned int mod(int k, int M) 
{   
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

int Calculate_hp_LSH(int* a_i, LSH* info)
{
    unsigned int sum = 0,first_term,second_term,temp_term;

    for(int i=1; i<=info->get_dimensions();i++)
    {
        first_term = mod(a_i[info->get_dimensions()-i],info->get_M());
        second_term = info->get_modulars()[i-1];
        temp_term = first_term*second_term;
        sum += mod(temp_term,info->get_M());
    }
    return mod(sum,info->get_M());
}

int Calculate_hp_RA_LSH(int* a_i, RA_LSH* info)
{
    unsigned int sum = 0,first_term,second_term,temp_term;

    for(int i=1; i<=info->get_dimensions();i++)
    {
        first_term = mod(a_i[info->get_dimensions()-i],info->get_M());
        second_term = info->get_modulars()[i-1];
        temp_term = first_term*second_term;
        sum += mod(temp_term,info->get_M());
    }
    return mod(sum,info->get_M());
}

int Calculate_hp_HyperCube(int* a_i, HyperCube* info)
{
    unsigned int sum = 0,first_term,second_term,temp_term;

    for(int i=1; i<=info->get_dimensions();i++)
    {
        first_term = mod(a_i[info->get_dimensions()-i],info->get_M());
        second_term = info->get_modulars()[i-1];
        temp_term = first_term*second_term;
        sum += mod(temp_term,info->get_M());
    }
    return mod(sum,info->get_M());
}

int Calculate_hp_RA_HyperCube(int* a_i, RA_HyperCube* info)
{
    unsigned int sum = 0,first_term,second_term,temp_term;

    for(int i=1; i<=info->get_dimensions();i++)
    {
        first_term = mod(a_i[info->get_dimensions()-i],info->get_M());
        second_term = info->get_modulars()[i-1];
        temp_term = first_term*second_term;
        sum += mod(temp_term,info->get_M());
    }
    return mod(sum,info->get_M());
}

void gi_values_of_train(LSH* info,unsigned int** g_i)
{
    for(int image=0;image<info->get_Num_of_Images();image++)
    {
        for(int i=0;i<info->get_L();i++)
        {
            int h_p[info->get_k()];
            for(int j=0;j<info->get_k();j++)
            {
                int a_i[info->get_dimensions()];

                for(int z=0;z<info->get_dimensions();z++)
                    a_i[z] = floor((double)((info->get_Images_Array()[image][z] - info->get_s_i()[(i*info->get_k())+j][z]))/(double)(info->get_W()));

                h_p[j] = Calculate_hp_LSH(a_i,info);
            }
            for(int j=0;j<info->get_k();j++)
            {
                g_i[image][i] += (h_p[j] << ((info->get_k()-(j+1))*8));                
            }
            g_i[image][i] = g_i[image][i]%(info->get_HashTableSize());
        }
    }
}

void gi_values_of_train_RA_LSH(RA_LSH* info,unsigned int** g_i)
{
    for(int image=0;image<info->get_Num_of_Images();image++)
    {
        for(int i=0;i<info->get_L();i++)
        {
            int h_p[info->get_k()];
            for(int j=0;j<info->get_k();j++)
            {
                int a_i[info->get_dimensions()];

                for(int z=0;z<info->get_dimensions();z++)
                    a_i[z] = floor((double)((info->get_Images_Array()[image][z] - info->get_s_i()[(i*info->get_k())+j][z]))/(double)(info->get_W()));

                h_p[j] = Calculate_hp_RA_LSH(a_i,info);
            }
            for(int j=0;j<info->get_k();j++)
            {
                g_i[image][i] += (h_p[j] << ((info->get_k()-(j+1))*8));                
            }
            g_i[image][i] = g_i[image][i]%(info->get_HashTableSize());
        }
    }
}

void fi_values_of_train_RA_HyperCube(RA_HyperCube* info,unsigned int* f_i)
{
    for(int image=0;image<info->get_Num_of_Images();image++)
    {
        int h_p[info->get_k()];
        int f_i_values[info->get_k()];
        for(int j=0;j<info->get_k();j++)
        {
            int a_i[info->get_dimensions()];

            for(int z=0;z<info->get_dimensions();z++)
                a_i[z] = floor((double)((info->get_Images_Array()[image][z] - info->get_s_i()[j][z]))/(double)(info->get_W()));

            h_p[j] = Calculate_hp_RA_HyperCube(a_i,info);
            
            f_i_values[j] = info->get_f_i_map()[j][h_p[j]];
        }

        for(int j=0;j<info->get_k();j++)  f_i[image] += (f_i_values[j] << ((info->get_k()-(j+1))));
    }
}

void fi_values_of_query(HyperCube* info,unsigned int* f_i)
{    
    for(int image=0;image<info->get_Num_of_Queries();image++)
    {
        int h_p[info->get_k()];
        int f_i_values[info->get_k()];
        for(int j=0;j<info->get_k();j++)
        {
            int a_i[info->get_dimensions()];

            for(int z=0;z<info->get_dimensions();z++)
                a_i[z] = floor((double)(info->get_Images_Array()[image][z] - info->get_s_i()[j][z])/(double)(info->get_W()));

            h_p[j] = Calculate_hp_HyperCube(a_i,info);
           
            f_i_values[j] = info->get_f_i_map()[j][h_p[j]];
        }
        for(int j=0;j<info->get_k();j++)  f_i[image] += (f_i_values[j] << ((info->get_k()-(j+1))));     
    }
}

void gi_values_of_query(LSH* info, unsigned int* gi_query_values, int query)
{
    for(int i=0;i<info->get_L();i++)
    {
        gi_query_values[i] = 0;

        int h_p[info->get_k()];
        for(int j=0;j<info->get_k();j++)
        {
            int a_i[info->get_dimensions()];

            for(int z=0;z<info->get_dimensions();z++)
            {
                a_i[z] = floor((double)(info->get_Queries_Array()[query][z] - info->get_s_i()[i*info->get_k()+j][z])/(double)(info->get_W()));
            }
            h_p[j] = Calculate_hp_LSH(a_i,info);
        }
        
        for(int j=0;j<info->get_k();j++)
        {
            gi_query_values[i] += (h_p[j] << ((info->get_k()-(j+1))*8));                
        }
        gi_query_values[i] = gi_query_values[i]%(info->get_HashTableSize());
    }
}

void Reverse_Assignment_LSH_Centroid_in_Bucket(RA_LSH* info, unsigned int* gi_query_values, item* centroid)
{
    for(int i=0;i<info->get_L();i++)
    {
        gi_query_values[i] = 0;

        int h_p[info->get_k()];
        for(int j=0;j<info->get_k();j++)
        {
            int a_i[info->get_dimensions()];

            for(int z=0;z<info->get_dimensions();z++)
            {
                a_i[z] = floor((double)(centroid[z] - info->get_s_i()[i*info->get_k()+j][z])/(double)(info->get_W()));
            }
            h_p[j] = Calculate_hp_RA_LSH(a_i,info);
        }
        
        for(int j=0;j<info->get_k();j++)
        {
            gi_query_values[i] += (h_p[j] << ((info->get_k()-(j+1))*8));                
        }
        gi_query_values[i] = gi_query_values[i]%(info->get_HashTableSize());
    }
}

unsigned int Reverse_Assignment_HyperCube_Centroid_in_Bucket(RA_HyperCube* info, item* centroid)
{    
    unsigned int f_i;
    int h_p[info->get_k()];
    int f_i_values[info->get_k()];
    for(int j=0;j<info->get_k();j++)
    {
        int a_i[info->get_dimensions()];

        for(int z=0;z<info->get_dimensions();z++)
            a_i[z] = floor((double)(centroid[z] - info->get_s_i()[j][z])/(double)(info->get_W()));

        h_p[j] = Calculate_hp_RA_HyperCube(a_i,info);
        
        f_i_values[j] = info->get_f_i_map()[j][h_p[j]];
    }
    for(int j=0;j<info->get_k();j++)  f_i += (f_i_values[j] << ((info->get_k()-(j+1))));   
    return f_i;  
}

void Insert_Images_To_Buckets_LSH(LSH* info)
{
    //Allocate memory so as to store temporarily g_i values...
    unsigned int** g_i = new unsigned int*[info->get_Num_of_Images()];
    for(int i=0;i<info->get_Num_of_Images();i++)  
    {
        g_i[i] = new unsigned int[info->get_L()];
        for(int j=0;j<info->get_L();j++)  g_i[i][j]=0;
    }

    //Call function so as to compute all g_i values...
    gi_values_of_train(info,g_i);
    
    //Fill buckets of Hash_Table...
    for(int i=0;i<info->get_Num_of_Images();i++)
    {
        for(int j=0;j<info->get_L();j++)
        {
            if(info->get_Hash_Tables()[j][g_i[i][j]]==NULL)  info->get_Hash_Tables()[j][g_i[i][j]] = new Bucket();
            info->get_Hash_Tables()[j][g_i[i][j]]->add(info->get_Images_Array()[i],g_i[i][j]);    
        }
    }

    //Deallocation of memory...
    for(int i=0;i<info->get_Num_of_Images();i++)  
        delete [] g_i[i];
    delete [] g_i;
}

void Insert_Images_To_Buckets_HyperCube(HyperCube* info)
{
    //Allocate memory so as to store temporarily f_i values...
    unsigned int* f_i = new unsigned int[info->get_Num_of_Images()];
    for(int i=0;i<info->get_Num_of_Images();i++)  f_i[i] = 0;

    //Initialization of map...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,1);
    
    for(int i=0;i<info->get_k();i++)
        for(int j=0;j<info->get_M();j++)    
            info->get_f_i_map()[i][j] = distribution(generator);

    //Call function so as to compute all f_i values...
    fi_values_of_train(info,f_i);
    
    //Fill buckets of L Hash_Tables...
    for(int i=0;i<info->get_Num_of_Images();i++)
    {   
        if(info->get_Hash_Table()[f_i[i]]==NULL)  info->get_Hash_Table()[f_i[i]] = new Bucket();
        info->get_Hash_Table()[f_i[i]]->add(info->get_Images_Array()[i],f_i[i]);    
    }

    //Deallocation of memory...
    delete [] f_i;
}

void Insert_Images_To_Buckets_RA_LSH(RA_LSH* info)
{
    //Allocate memory so as to store temporarily g_i values...
    unsigned int** g_i = new unsigned int*[info->get_Num_of_Images()];
    for(int i=0;i<info->get_Num_of_Images();i++)  
    {
        g_i[i] = new unsigned int[info->get_L()];
        for(int j=0;j<info->get_L();j++)  g_i[i][j]=0;
    }

    //Call function so as to compute all g_i values...
    gi_values_of_train_RA_LSH(info,g_i);
    
    //Fill buckets of Hash_Table...
    for(int i=0;i<info->get_Num_of_Images();i++)
    {
        for(int j=0;j<info->get_L();j++)
        {
            if(info->get_Hash_Tables()[j][g_i[i][j]]==NULL)  info->get_Hash_Tables()[j][g_i[i][j]] = new Bucket();
            info->get_Hash_Tables()[j][g_i[i][j]]->add(info->get_Images_Array()[i],g_i[i][j]);    
        }
    }

    //Deallocation of memory...
    for(int i=0;i<info->get_Num_of_Images();i++)  
        delete [] g_i[i];
    delete [] g_i;
}

void Insert_Images_To_Buckets_RA_HyperCube(RA_HyperCube* info)
{
    //Allocate memory so as to store temporarily f_i values...
    unsigned int* f_i = new unsigned int[info->get_Num_of_Images()];
    for(int i=0;i<info->get_Num_of_Images();i++)  f_i[i] = 0;

    //Initialization of map...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,1);
    
    for(int i=0;i<info->get_k();i++)
        for(int j=0;j<info->get_M();j++)    
            info->get_f_i_map()[i][j] = distribution(generator);

    //Call function so as to compute all f_i values...
    fi_values_of_train_RA_HyperCube(info,f_i);
    
    //Fill buckets of L Hash_Tables...
    for(int i=0;i<info->get_Num_of_Images();i++)
    {   
        if(info->get_Hash_Table()[f_i[i]]==NULL)  info->get_Hash_Table()[f_i[i]] = new Bucket();
        info->get_Hash_Table()[f_i[i]]->add(info->get_Images_Array()[i],f_i[i]);    
    }

    //Deallocation of memory...
    delete [] f_i;
}