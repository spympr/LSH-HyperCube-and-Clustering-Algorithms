#include "../headers/exhausting.h"

int LSH::get_dimensions()
{
    return dimensions;
}

int LSH::get_M()
{
    return M;
}

int LSH::get_N()
{
    return N;
}

int LSH::get_k()
{
    return k;
}

int LSH::get_L()
{
    return L;
}

int LSH::get_W()
{
    return W;
}

int LSH::get_HashTableSize()
{
    return HashTableSize;
}

int LSH::get_Num_of_Images()
{
    return Num_of_Images;
}

int LSH::get_Num_of_Queries()
{
    return Num_of_Queries;
}

int* LSH::get_modulars()
{
    return modulars;
}

int** LSH::get_s_i()
{
    return s_i;
}

double* LSH::get_tTrue()
{
    return tTrue;
}

int** LSH::get_True_Distances()
{
    return True_Distances;
}

item** LSH::get_Images_Array()
{
    return Images_Array;
}

item** LSH::get_Queries_Array()
{
    return Queries_Array;
}

Bucket*** LSH::get_Hash_Tables()
{
    return Hash_Tables;
}

void LSH::Approximate_LSH()
{   
    for(int i=0;i<Num_of_Queries;i++)
    {
        int LSH_nns[N],LSH_Distances[N]; 
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 
        unordered_set<int> indexes_of_images;

        unsigned int gi_query_values[L];
        
        gi_values_of_query(this, gi_query_values, i);

        for(int j=0;j<L;j++)
        {
            Bucket* temp = Hash_Tables[j][gi_query_values[j]];

            if(temp != NULL)
            {
                vector<pair<item*,unsigned int>>::iterator it;
                
                for(it=temp->images.begin();it!=temp->images.end();it++)    
                {
                    if(it->second==gi_query_values[j])
                    {
                        if(indexes_of_images.find((it->first[dimensions]))==indexes_of_images.end())
                        {
                            indexes_of_images.insert(it->first[dimensions]);
                            distances.push(make_pair(ManhattanDistance(Queries_Array[i],it->first, dimensions), it->first[dimensions]));
                        }
                    }
                }
            }
        }

        auto end = chrono::high_resolution_clock::now(); 
        
        cout << endl << "--------------------------------------------" << endl;
        cout << "Query: " << Queries_Array[i][dimensions] << endl;
        
        for(int k=0;k<N;k++)
        {
            LSH_Distances[k] = distances.top().first;
            LSH_nns[k] = distances.top().second;
            distances.pop();
            cout << "Nearest neighbor-" << k+1 << ": " << LSH_nns[k] << endl;
            cout << "distanceLSH: " << LSH_Distances[k] << endl;
            cout << "distanceTrue: " << True_Distances[i][k] << endl << endl;
            dist_AF += (double)(LSH_Distances[k])/(double)True_Distances[i][k];
        }
        tLSH[i] = chrono::duration_cast<chrono::microseconds>(end - start).count();  
        cout << "tLSH: " << tLSH[i] << "μs" << endl << "tTrue: " << tTrue[i] << "ms";
        time_error += tLSH[i]/tTrue[i];

        Approximate_Range_Search(i);
    }

    cout << endl << "LSH Mean Distance Error: " << dist_AF/(double)(Num_of_Queries*N) << endl;
    cout << endl << "tLSH/tTrue: " << time_error/(double)(Num_of_Queries) << endl;
}

void LSH::Approximate_Range_Search(int query_index)
{   
    priority_queue<int, vector<int>, greater<int>> neighboors; 
    unordered_set<int> indexes_of_images;

    unsigned int gi_query_values[L];

    gi_values_of_query(this, gi_query_values, query_index);

    for(int j=0;j<L;j++)
    {
        Bucket* temp = Hash_Tables[j][gi_query_values[j]];

        if(temp != NULL)
        {
            vector<pair<item*,unsigned int>>::iterator it;

            for(it=temp->images.begin();it!=temp->images.end();it++)    
            {
                if(ManhattanDistance(Queries_Array[query_index],it->first, dimensions) < R)
                {
                    if(it->second==gi_query_values[j])
                    {
                        if(indexes_of_images.find((it->first[dimensions])) == indexes_of_images.end())
                        {
                                indexes_of_images.insert((it->first[dimensions]));
                            neighboors.push(it->first[dimensions]);
                        }
                    }
                }
            }
        }
    }
    
    cout << endl << "R-near neighbors:" << endl;
    if(neighboors.empty())  cout << "None" << endl;
    else
    {
        for(int k=0;k<neighboors.size();k++)
        { 
            cout << neighboors.top() << endl;
            neighboors.pop();
        }    
    }    
}

void LSH::InitLSH()
{
    //Declaration of variables...
    int Rows,Columns;

    //Read input binary file...
    Read_BF(&Images_Array,&Num_of_Images,&Columns,&Rows,input_file,1);
    
    //Read query binary file...
    Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,10);

    //Printing...
    cout << endl << "Images: " << Num_of_Images << endl << "Queries: " << Num_of_Queries << endl << "Rows: " << Rows << endl << "Columns: " << Columns << endl;
    
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

    //Initialization of 2D array True_Distances...
    True_Distances = new int*[Num_of_Queries];
    for(int i=0;i<Num_of_Queries;i++)   True_Distances[i] = new int[N];
    
    //Initialization of m,M...
    M = pow(2,floor((double)32/(double)k));
    m = 423255;
    // m = M/2+1;
    cout << "m: " << m << endl;
    cout << "M: " << M << endl;
    
    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of tTrue,tLSH arrays...
    tLSH = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    W = 40000;
    cout << "W: " << W << endl << endl;

    //Do exhausting search and init W...
    ExhaustingNN(this);

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
    Insert_Images_To_Buckets_LSH(this);

    Approximate_LSH();

    cout << endl;
    //Print Buckets...
    for(int i=0;i<L;i++)
    {
        int counter=0;
        int sum=0;
        for(int j=0;j<HashTableSize;j++)
        {
            if(Hash_Tables[i][j]!=NULL)
            {
                counter++;
                sum+=Hash_Tables[i][j]->images.size();
            }                
        }
        cout << "HashTable " << i << ": " << counter << ", " << sum << endl;
    }

    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    //Deallocation of memory of Queries_Array...
    for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
    delete [] Queries_Array;

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

    //Deallocation of memory of True_Distances...
    for(int i=0;i<Num_of_Queries;i++)  
        delete [] True_Distances[i];
    delete [] True_Distances;
    
    //Deallocation of memory of tLSH,tTrue,modulars...
    delete [] tLSH;
    delete [] tTrue;
    delete [] modulars;
}