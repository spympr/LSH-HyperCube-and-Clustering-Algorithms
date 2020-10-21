#include "../headers/exhausting.h"

void Bucket::add(item* image)
{
    images.push_back(image);
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

int Calculate_hp_HyperCube(int* a_i, HyperCube* info)
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

void gi_values_of_train(LSH* info,unsigned int** g_i)
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
                h_p[j] = Calculate_hp_LSH(a_i,info);
            }
            for(int j=0;j<info->k;j++)
            {
                g_i[image][i] += (h_p[j] << ((info->k-(j+1))*8));                
            }
            g_i[image][i] = g_i[image][i]%(info->HashTableSize);
        }
    }
}

void fi_values_of_train(HyperCube* info,unsigned int* f_i)
{
    map<unsigned int,unsigned int>::iterator it;
    
    for(int image=0;image<info->Num_of_Images;image++)
    {
        int h_p[info->k];
        int f_i_values[info->k];
        for(int j=0;j<info->k;j++)
        {
            int a_i[info->dimensions];

            for(int z=0;z<info->dimensions;z++)
            {
                a_i[z] = floor((double)((info->Images_Array[image][z] - info->s_i[(info->k)+j][z]))/(double)(info->W));
                // cout << a_i[z] << " " ;
            }
            // cout << endl;
            h_p[j] = Calculate_hp_HyperCube(a_i,info);
            
            it = info->f_i_map[j].find(h_p[j]);

            if (it == info->f_i_map[j].end())
                info->f_i_map[j][h_p[j]] = rand() % 2;

            f_i_values[j] = info->f_i_map[j][h_p[j]];
        }

        for(int j=0;j<info->k;j++)
        {
            f_i[image] += (f_i_values[j] << ((info->k-(j+1))));                
        }
    }
}

void fi_values_of_query(HyperCube* info,unsigned int* f_i)
{
    map<unsigned int,unsigned int>::iterator it;
    
    for(int image=0;image<info->Num_of_Queries;image++)
    {
        int h_p[info->k];
        int f_i_values[info->k];
        for(int j=0;j<info->k;j++)
        {
            int a_i[info->dimensions];

            for(int z=0;z<info->dimensions;z++)
            {
                a_i[z] = floor((double)((info->Images_Array[image][z] - info->s_i[(info->k)+j][z]))/(double)(info->W));
                // cout << a_i[z] << " " ;
            }
            // cout << endl;
            h_p[j] = Calculate_hp_HyperCube(a_i,info);
            
            it = info->f_i_map[j].find(h_p[j]);

            if (it == info->f_i_map[j].end())
                info->f_i_map[j][h_p[j]] = rand() % 2;

            f_i_values[j] = info->f_i_map[j][h_p[j]];
        }

        for(int j=0;j<info->k;j++)
        {
            f_i[image] += (f_i_values[j] << ((info->k-(j+1))));                
        }
        // f_i[image] %= (info->HashTableSize);
    }
}

void gi_values_of_query(LSH* info, unsigned int* gi_query_values, int query)
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
            h_p[j] = Calculate_hp_LSH(a_i,info);
        }
        
        for(int j=0;j<info->k;j++)
        {
            gi_query_values[i] += (h_p[j] << ((info->k-(j+1))*8));                
        }
        gi_query_values[i] = gi_query_values[i]%(info->HashTableSize);
    }
}

void Insert_Images_To_Buckets_LSH(LSH* info)
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

void Insert_Images_To_Buckets_HyperCube(HyperCube* info)
{
    //Allocate memory so as to store temporarily g_i values...
    unsigned int* f_i = new unsigned int[info->Num_of_Images];
    info->f_i_map = new map<unsigned int, unsigned int>[info->k];

    for(int i=0;i<info->Num_of_Images;i++)  f_i[i] = 0;

    //Call function so as to compute all g_i values...
    fi_values_of_train(info,f_i);
    
    //Fill buckets of L Hash_Tables...
    for(int i=0;i<info->Num_of_Images;i++)
    {
        if(info->Hash_Table[f_i[i]]==NULL)  info->Hash_Table[f_i[i]] = new Bucket();
        info->Hash_Table[f_i[i]]->add(info->Images_Array[i]);    
    }

    //Deallocation of memory...
    delete [] f_i;
}