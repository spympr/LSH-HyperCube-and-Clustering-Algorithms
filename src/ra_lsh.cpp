#include "../headers/kmeans.h"

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
        
        Reverse_Assignment_LSH_Centroid_in_Bucket(this,gi_values,centroids[i]);

        //For each Hash Table
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

                    //In case there isn't first centroid yet
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
                        
                        //Change the old centroid with the new one
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
}

// void LSH::Approximate_LSH()
// {   
//     for(int i=0;i<Num_of_Queries;i++)
//     {
//         // file.open(output_file,ios::out);

//         int LSH_nns[N],LSH_Distances[N]; 
//         auto start = chrono::high_resolution_clock::now(); 
//         priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 
//         unordered_set<int> indexes_of_images;

//         unsigned int gi_query_values[L];
        
//         gi_values_of_query(this, gi_query_values, i);

//         for(int j=0;j<L;j++)
//         {
//             Bucket* temp = Hash_Tables[j][gi_query_values[j]];

//             if(temp != NULL)
//             {
//                 vector<pair<item*,unsigned int>>::iterator it;
                
//                 for(it=temp->images.begin();it!=temp->images.end();it++)    
//                 {
//                     if(it->second==gi_query_values[j])
//                     {
//                         if(indexes_of_images.find((it->first[dimensions]))==indexes_of_images.end())
//                         {
//                             indexes_of_images.insert(it->first[dimensions]);
//                             distances.push(make_pair(ManhattanDistance(Queries_Array[i],it->first, dimensions), it->first[dimensions]));
//                         }
//                     }
//                 }
//             }
//         }

//         auto end = chrono::high_resolution_clock::now(); 
        
//         file << endl << "--------------------------------------------" << endl;
//         file << "Query: " << Queries_Array[i][dimensions] << endl;
        
//         for(int k=0;k<N;k++)
//         {
//             LSH_Distances[k] = distances.top().first;
//             LSH_nns[k] = distances.top().second;
//             distances.pop();
//             file << "Nearest neighbor-" << k+1 << ": " << LSH_nns[k] << endl;
//             file << "distanceLSH: " << LSH_Distances[k] << endl;
//             file << "distanceTrue: " << True_Distances[i][k] << endl << endl;
//             dist_AF += (double)(LSH_Distances[k])/(double)True_Distances[i][k];
//         }
//         tLSH[i] = chrono::duration_cast<chrono::microseconds>(end - start).count();  
//         file << "tLSH: " << tLSH[i] << "μs" << endl << "tTrue: " << tTrue[i] << "μs";
//         time_error += tLSH[i]/tTrue[i];

//         Approximate_Range_Search(i);
//     }

//     file << endl << "LSH Mean Distance Error: " << dist_AF/(double)(Num_of_Queries*N) << endl;
//     file << endl << "tLSH/tTrue: " << time_error/(double)(Num_of_Queries) << endl;
    
//     file << endl;
//     //Print Buckets...
//     for(int i=0;i<L;i++)
//     {
//         int counter=0;
//         int sum=0;
//         for(int j=0;j<HashTableSize;j++)
//         {
//             if(Hash_Tables[i][j]!=NULL)
//             {
//                 counter++;
//                 sum+=Hash_Tables[i][j]->images.size();
//             }                
//         }
//         file << "HashTable " << i << ": " << counter << ", " << sum << endl;
//     }
// }

// void LSH::Approximate_Range_Search(int query_index)
// {   
//     priority_queue<int, vector<int>, greater<int>> neighboors; 
//     unordered_set<int> indexes_of_images;

//     unsigned int gi_query_values[L];

//     gi_values_of_query(this, gi_query_values, query_index);

//     for(int j=0;j<L;j++)
//     {
//         Bucket* temp = Hash_Tables[j][gi_query_values[j]];

//         if(temp != NULL)
//         {
//             vector<pair<item*,unsigned int>>::iterator it;

//             for(it=temp->images.begin();it!=temp->images.end();it++)    
//             {
//                 if(ManhattanDistance(Queries_Array[query_index],it->first, dimensions) < R)
//                 {
//                     if(it->second==gi_query_values[j])
//                     {
//                         if(indexes_of_images.find((it->first[dimensions])) == indexes_of_images.end())
//                         {
//                                 indexes_of_images.insert((it->first[dimensions]));
//                             neighboors.push(it->first[dimensions]);
//                         }
//                     }
//                 }
//             }
//         }
//     }
    
//     file << endl << "R-near neighbors:" << endl;
//     if(neighboors.empty())  file << "None" << endl;
//     else
//     {
//         for(int k=0;k<neighboors.size();k++)
//         { 
//             file << neighboors.top() << endl;
//             neighboors.pop();
//         }    
//     }   

// }

void RA_LSH::InitLSH()
{
    //Declaration of variables...
    int Rows=0,Columns=0;

    //Read input binary file...
    Read_BF(&Images_Array,&Num_of_Images,&Columns,&Rows,input_file,1);
    
    // //Read query binary file...
    // Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,100);
   
    file.open(output_file,ios::out);

    if(file)
    {
        file << "Images:" << Num_of_Images << endl << "Dimensions:" << Rows << "x" << Columns << endl;
    }
    else cout << "Problem\n";

    //Initilization of W(grid), dimensions of each Image...
    dimensions = Columns*Rows;
    HashTableSize = Num_of_Images/8;

    //Declaration of hash tables...
    Hash_Tables = new Bucket**[L];
    for(int i=0;i<L;i++)    
    {
        Hash_Tables[i] = new Bucket*[HashTableSize];
        for(int j=0;j<HashTableSize;j++)   Hash_Tables[i][j]=NULL;                
    }

    // //Initialization of 2D array True_Distances...
    // True_Distances = new int*[Num_of_Queries];
    // for(int i=0;i<Num_of_Queries;i++)   True_Distances[i] = new  int[N];
    
    //Initialization of m,M...
    M = pow(2,floor((double)32/(double)k));
    m = 423255;
    file << "m:" << m << endl;
    file << "M:" << M << endl;
    
    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    // //Initialization of tTrue,tLSH arrays...
    // tLSH = new double[Num_of_Queries];
    // tTrue = new double[Num_of_Queries];

    W = 4000;
    file << "W:" << W << endl << endl;

    // //Do exhausting search and init W...
    // ExhaustingNN(this);

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
    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    // //Deallocation of memory of Queries_Array...
    // for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
    // delete [] Queries_Array;

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

    // //Deallocation of memory of True_Distances...
    // for(int i=0;i<Num_of_Queries;i++)  
    //     delete [] True_Distances[i];
    // delete [] True_Distances;
    
    // //Deallocation of memory of tLSH,tTrue,modulars...
    // delete [] tLSH;
    // delete [] tTrue;
    delete [] modulars;
}