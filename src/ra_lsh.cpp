#include "../headers/kmeans.h"
// #include "../headers/exhausting.h"

int RA_LSH::get_dimensions()
{
    return dimensions;
}

int RA_LSH::get_M()
{
    return M;
}

int RA_LSH::get_k()
{
    return k;
}

int RA_LSH::get_L()
{
    return L;
}

int RA_LSH::get_W()
{
    return W;
}

int RA_LSH::get_HashTableSize()
{
    return HashTableSize;
}

int RA_LSH::get_Num_of_Images()
{
    return Num_of_Images;
}

int* RA_LSH::get_modulars()
{
    return modulars;
}

int** RA_LSH::get_s_i()
{
    return s_i;
}

item** RA_LSH::get_Images_Array()
{
    return Images_Array;
}

Bucket*** RA_LSH::get_Hash_Tables()
{
    return Hash_Tables;
}

void RA_LSH::Map_Init()
{
    map <int,Nearest_Centroids*>::iterator it;

    for(it=(*points).begin();it!=(*points).end();it++) 
        it->second->set_nearest_centroid1(-1);
}

void RA_LSH::RA_LSH_Assign()
{
    int image_index = 0, nearest_centroid1=0, nearest_centroid2=0;

    for(int i=0;i<K;i++)
    {
        unsigned int gi_values[L];
        cout << "edw1 " << endl;
        Reverse_Assignment_LSH_Centroid_in_Bucket(this,gi_values,centroids[i]);
        cout << "edw2 " << endl;

        //For each Hash Table...
        for(int j=0;j<L;j++)
        {
            Bucket* temp = Hash_Tables[j][gi_values[j]];

            if(temp!=NULL)
            {
                vector<pair<item*,unsigned int>>::iterator it;
                
                //For each image in Bucket...
                for(it=temp->images.begin();it!=temp->images.end();it++)    
                {
                    image_index = it->first[dimensions];
                    nearest_centroid1 = (*points)[image_index]->get_nearest_centroid1();

                    //In case there isn't first centroid yet...
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
                    //In case we have already assign a centroid, we have to check if we found a new centroid much closer than the previous one
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
                }
            }
        }
    }

    Exhausting_For_Non_Assign_Points();
}

void RA_LSH::Exhausting_For_Non_Assign_Points()
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

void RA_LSH::Init_RA_LSH()
{
    //Declaration of hash tables...
    Hash_Tables = new Bucket**[L];
    for(int i=0;i<L;i++)    
    {
        Hash_Tables[i] = new Bucket*[HashTableSize];
        for(int j=0;j<HashTableSize;j++)   Hash_Tables[i][j]=NULL;                
    }

    //Initialization of m,M...
    M = pow(2,floor((double)32/(double)k));
    m = 423255;
    W = 4000;
    
    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of uniform_int_distribution class...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,W);
    
    //Initialization of L*k*d(imensions) random s_i integers...
    s_i = new int*[L*k];
    for(int i=0;i<(L*k);i++)
    {
        s_i[i] = new int[dimensions];
        for(int j=0;j<dimensions;j++)   
            s_i[i][j] = distribution(generator);
    }

    //Fill Hash Tables...
    Insert_Images_To_Buckets_RA_LSH(this);
}

void RA_LSH::Deallocation_of_Memory()
{
    //Deallocation of memory of s_i...
    for(int i=0;i<(k*L);i++)    delete [] s_i[i];
    delete [] s_i;        

    //Deallocation of memory of Hash_Tables...
    for(int i=0;i<L;i++)    
    {
        for(int j=0;j<(HashTableSize);j++)   
            if(Hash_Tables[i][j]!=NULL)
                delete Hash_Tables[i][j];
        delete [] Hash_Tables[i];
    }
    delete [] Hash_Tables;
    delete [] modulars;
}