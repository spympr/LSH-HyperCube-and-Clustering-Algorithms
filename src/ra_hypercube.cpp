#include "../headers/kmeans.h"

int RA_HyperCube::get_dimensions()
{
    return dimensions;
}

int RA_HyperCube::get_M_boundary()
{
    return M_boundary;
}

int RA_HyperCube::get_k()
{
    return k;
}

int RA_HyperCube::get_M()
{
    return M;
}

int RA_HyperCube::get_W()
{
    return W;
}

int RA_HyperCube::get_HashTableSize()
{
    return HashTableSize;
}

int RA_HyperCube::get_Num_of_Images()
{
    return Num_of_Images;
}

int* RA_HyperCube::get_modulars()
{
    return modulars;
}

int** RA_HyperCube::get_s_i()
{
    return s_i;
}

map<unsigned int,unsigned int>* RA_HyperCube::get_f_i_map()
{
    return f_i_map;
}

item** RA_HyperCube::get_Images_Array()
{
    return Images_Array;
}

Bucket** RA_HyperCube::get_Hash_Table()
{
    return Hash_Table;
}

int RA_HyperCube::hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
    
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    }

    return setBits; 
} 

void RA_HyperCube::Initialize_Values()
{
    K = kmeansptr->get_K();
    dimensions = kmeansptr->get_dimensions();
    k = kmeansptr->get_HC_k();
    M_boundary = kmeansptr->get_HC_M();
    probes = kmeansptr->get_probes();
    Num_of_Images = kmeansptr->get_number_of_images();
    Images_Array = kmeansptr->get_Images_Array();
    HashTableSize = pow(2,k);
}

void RA_HyperCube::Deallocation_of_Memory()
{
    delete [] f_i_map;

    //Deallocation of memory of s_i...
    for(int i=0;i<k;i++)    delete [] s_i[i];
    delete [] s_i;        

    //Deallocation of memory of Hash_Tables...
    for(int j=0;j<(HashTableSize);j++)   
        if(Hash_Table[j]!=NULL)
            delete Hash_Table[j];
    delete [] Hash_Table;

    //Deallocation of memory of modulars...
    delete [] modulars;
}

void RA_HyperCube::Init_RA_HyperCube()
{
    f_i_map = new map<unsigned int, unsigned int>[k];

    //Declaration of hash tables...
    Hash_Table = new Bucket*[HashTableSize];
    for(int i=0;i<HashTableSize;i++)    Hash_Table[i] = NULL;

    //Initialization of m,M...
    M = pow(2,floor((double)32/(double)k));
    m = 423255;
    W = 40000;

    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of uniform_int_distribution class...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,W);
    
    //Initialization of k*d(imensions) random s_i integers...
    s_i = new int*[k];
    for(int i=0;i<k;i++)
    {
        s_i[i] = new int[dimensions];
        for(int j=0;j<dimensions;j++)   
            s_i[i][j] = distribution(generator);        
    }
        
    //Fill Hash Table...
    Insert_Images_To_Buckets_RA_HyperCube(this);
}

void RA_HyperCube::Map_Init()
{
    map <int,Nearest_Centroids*>::iterator it;

    for(it=(*points).begin();it!=(*points).end();it++) 
        it->second->set_nearest_centroid1(-1);
}

void RA_HyperCube::RA_HyperCube_Assign()
{
    int image_index = 0, nearest_centroid1=0, nearest_centroid2=0;

    Map_Init();
    
    for(int i=0;i<K;i++)
    {
        int count_hamming=1,count_images=0, count_probes=0;
        unsigned int f_i = Reverse_Assignment_HyperCube_Centroid_in_Bucket(this,centroids[i]);     

        Bucket* temp = Hash_Table[f_i];

        if(temp != NULL)
        {
            vector<pair<item*,unsigned int>>::iterator it;

            for(it=temp->images.begin();it!=temp->images.end();it++)    
            {
                image_index = it->first[dimensions];
                nearest_centroid1 = (*points)[image_index]->get_nearest_centroid1();

                if(nearest_centroid1 == -1)
                {
                    (*points)[image_index]->set_nearest_centroid1(i);
                    (*points)[image_index]->set_dist1(ManhattanDistance(it->first, centroids[i], dimensions));

                    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances2; 
                    
                    for(int z=0;z<K;z++)
                        if(z!=i)
                            distances2.push(make_pair((ManhattanDistance(centroids[z],it->first,dimensions)),z));

                    (*points)[image_index]->set_nearest_centroid2(distances2.top().second);
                    (*points)[image_index]->set_dist2(distances2.top().first);   
                }
                else
                {
                    item new_distance1 = ManhattanDistance(it->first,centroids[i],dimensions);
                    item old_distance1 = ManhattanDistance(it->first,centroids[nearest_centroid1],dimensions);
                    
                    //Change the old centroid with the new one...
                    if(new_distance1 < old_distance1)
                    {
                        (*points)[image_index]->set_nearest_centroid1(i);
                        (*points)[image_index]->set_dist1(new_distance1);

                        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances2; 
                    
                        for(int z=0;z<K;z++)
                            if(z!=i)
                                distances2.push(make_pair((ManhattanDistance(centroids[z],it->first,dimensions)),z));
                        
                        (*points)[image_index]->set_nearest_centroid2(distances2.top().second);
                        (*points)[image_index]->set_dist2(distances2.top().first);
                    }
                }

                count_images++;
                if(count_images == M_boundary)  break;
            }
        }
        if((temp == NULL) || (count_images < M_boundary))
        {
            while((count_probes < probes) && (count_images < M_boundary))
            {
                for(int j=0;j<HashTableSize;j++)
                {
                    Bucket* hash_cell = Hash_Table[j];

                    if(hash_cell != NULL)
                    {
                        int hamming_distance = hammingDistance(f_i,j);
                        if(hamming_distance == count_hamming)
                        {
                            vector<pair<item*,unsigned int>>::iterator it;

                            for(it=hash_cell->images.begin();it!=hash_cell->images.end();it++)    
                            {
                                image_index = it->first[dimensions];
                                nearest_centroid1 = (*points)[image_index]->get_nearest_centroid1();

                                if(nearest_centroid1 == -1)
                                {
                                    (*points)[image_index]->set_nearest_centroid1(i);
                                    (*points)[image_index]->set_dist1(ManhattanDistance(it->first, centroids[i], dimensions));

                                    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances2; 
                                    
                                    for(int z=0;z<K;z++)
                                        if(z!=i)
                                            distances2.push(make_pair((ManhattanDistance(centroids[z],it->first,dimensions)),z));

                                    (*points)[image_index]->set_nearest_centroid2(distances2.top().second);
                                    (*points)[image_index]->set_dist2(distances2.top().first);   
                                }
                                else
                                {
                                    item new_distance1 = ManhattanDistance(it->first,centroids[i],dimensions);
                                    item old_distance1 = ManhattanDistance(it->first,centroids[nearest_centroid1],dimensions);
                                    
                                    //Change the old centroid with the new one...
                                    if(new_distance1 < old_distance1)
                                    {
                                        (*points)[image_index]->set_nearest_centroid1(i);
                                        (*points)[image_index]->set_dist1(new_distance1);

                                        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances2; 
                                    
                                        for(int z=0;z<K;z++)
                                            if(z!=i)
                                                distances2.push(make_pair((ManhattanDistance(centroids[z],it->first,dimensions)),z));
                                        
                                        (*points)[image_index]->set_nearest_centroid2(distances2.top().second);
                                        (*points)[image_index]->set_dist2(distances2.top().first);
                                    }
                                }
                                count_images++;
                                if(count_images == M_boundary)  break;
                            }
                            count_probes++;
                        }
                    }
                    if((count_images == M_boundary) || (count_probes == probes))  break;
                }
                count_hamming++;
            }
        }
    }
    Exhausting_For_Non_Assign_Points();
}

void RA_HyperCube::Exhausting_For_Non_Assign_Points()
{
    map <int,Nearest_Centroids*>::iterator it;

    for(it=(*points).begin();it!=(*points).end();it++) 
    {
        if(it->second->get_nearest_centroid1() ==-1)
        {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances1;

            for(int i=0;i<K;i++)
                distances1.push(make_pair((ManhattanDistance(centroids[i],Images_Array[it->first],dimensions)),i));
            
            it->second->set_nearest_centroid1(distances1.top().second);
            it->second->set_dist1(distances1.top().first);
            
            distances1.pop();

            it->second->set_nearest_centroid2(distances1.top().second);
            it->second->set_dist2(distances1.top().first);
        }
    }
}