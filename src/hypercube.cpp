#include "../headers/exhausting.h"

int HyperCube::get_dimensions()
{
    return dimensions;
}

int HyperCube::get_M_boundary()
{
    return M_boundary;
}

int HyperCube::get_k()
{
    return k;
}

int HyperCube::get_M()
{
    return M;
}

int HyperCube::get_R()
{
    return R;
}

int HyperCube::get_N()
{
    return N;
}

int HyperCube::get_W()
{
    return W;
}

int HyperCube::get_HashTableSize()
{
    return HashTableSize;
}

int HyperCube::get_Num_of_Images()
{
    return Num_of_Images;
}

int HyperCube::get_Num_of_Queries()
{
    return Num_of_Queries;
}

int* HyperCube::get_modulars()
{
    return modulars;
}

int** HyperCube::get_s_i()
{
    return s_i;
}

double* HyperCube::get_tTrue()
{
    return tTrue;
}

int** HyperCube::get_True_Distances()
{
    return True_Distances;
}

map<unsigned int,unsigned int>* HyperCube::get_f_i_map()
{
    return f_i_map;
}

item** HyperCube::get_Images_Array()
{
    return Images_Array;
}

item** HyperCube::get_Queries_Array()
{
    return Queries_Array;
}

Bucket** HyperCube::get_Hash_Table()
{
    return Hash_Table;
}

int HyperCube::hammingDistance(int n1, int n2) 
{ 
    int x = n1 ^ n2; 
    int setBits = 0; 
    
    while (x > 0) { 
        setBits += x & 1; 
        x >>= 1; 
    }

    return setBits; 
} 

void HyperCube::InitHyperCube()
{
    //Declaration of variables...
    int Rows,Columns;
    
    //Read input binary file...
    Read_BF(&Images_Array,&Num_of_Images,&Columns,&Rows,input_file,1);
    
    //Read query binary file...
    Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,10);

    //Printing...
    cout << endl << "Images: " << Num_of_Images << endl << "Queries: " << Num_of_Queries << endl << "Rows: " << Rows << endl << "Columns: " << Columns << endl;

    //Initilization of dimensions of each Image,k, HashTableSize...
    dimensions = Rows*Columns;
    HashTableSize = pow(2,k);

    //Declaration of hash tables...
    Hash_Table = new Bucket*[HashTableSize];
    for(int i=0;i<HashTableSize;i++)    Hash_Table[i] = NULL;
    
    //Initialization of 2D array True_Distances...
    True_Distances = new int*[Num_of_Queries];
    for(int i=0;i<Num_of_Queries;i++)   True_Distances[i] = new int[N];

    //Initialization of m,M...
    M = pow(2,floor((double)32/(double)k));
    // m = 423255;
    m = 2;
    cout << "m: " << m << endl;
    cout << "M: " << M << endl;
    cout << "M_boundary: " << M_boundary << endl;
    cout << "Probes: " << probes << endl;

    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of tTrue,tLSH arrays...
    tHypercube = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    W = 4000;
    cout << "W: " << W << endl << endl;

    //Do exhausting search and init W...
    ExhaustingNN_HC(this);

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

    // for(int i=0;i<k;i++)
    // {
    //     for(int j=0;j<dimensions;j++)
    //         cout << s_i[i][j] << " ";
    //     cout << endl;
    // }
        
    //Fill Hash Tables...
    Insert_Images_To_Buckets_HyperCube(this);

    Approximate_Hypercube();
    
    cout << endl;
    //Print Buckets...
    int counter=0;
    for(int j=0;j<HashTableSize;j++)
        if(Hash_Table[j]!=NULL)
            counter++;                
    cout << "HashTable: " << counter << " out of " << HashTableSize << endl;


    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    //Deallocation of memory of Queries_Array...
    for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
    delete [] Queries_Array;

    //Deallocation of memory of s_i...
    for(int i=0;i<k;i++)    delete [] s_i[i];
    delete [] s_i;        

    //Deallocation of memory of Hash_Tables...
    for(int j=0;j<(HashTableSize);j++)   
        if(Hash_Table[j]!=NULL)
            delete Hash_Table[j];
    delete [] Hash_Table;

    //Deallocation of memory of True_Distances...
    for(int i=0;i<Num_of_Queries;i++)  
        delete [] True_Distances[i];
    delete [] True_Distances;
    
    //Deallocation of memory of tLSH,tTrue,modulars...
    delete [] tHypercube;
    delete [] tTrue;
    delete [] modulars;
}

void HyperCube::Approximate_Hypercube()
{
    unsigned int fi_query_values[Num_of_Queries];
    for(int i=0;i<Num_of_Queries;i++)  fi_query_values[i] = 0;
    
    fi_values_of_query(this, fi_query_values);

    for(int i=0;i<Num_of_Queries;i++)
    {
        auto start = chrono::high_resolution_clock::now();
        int HyperCube_nns[N],HyperCube_Distances[N], count_hamming=1,count_images=0, count_probes=0; 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        Bucket* temp = Hash_Table[fi_query_values[i]];

        if(temp != NULL)
        {
            vector<pair<item*,unsigned int>>::iterator it;

            for(it=temp->images.begin();it!=temp->images.end();it++)    
            {
                distances.push(make_pair(ManhattanDistance(Queries_Array[i],it->first,dimensions), (it->first[dimensions])));
                count_images++;
                // cout << count_images << " ";
                if(count_images == M_boundary)  break;
            }
            // cout << endl;
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
                        int hamming_distance = hammingDistance(fi_query_values[i],j);
                        if(hamming_distance == count_hamming)
                        {
                            // cout << endl << "query_bucket= " << fi_query_values[i]  << " bucket=" << j << " hamming=" << count_hamming << " " << count_images << "<" << M_boundary << " " << count_probes << "<" << probes << endl;
                            vector<pair<item*,unsigned int>>::iterator it;

                            for(it=hash_cell->images.begin();it!=hash_cell->images.end();it++)    
                            {
                                distances.push(make_pair(ManhattanDistance(Queries_Array[i],it->first, dimensions), (it->first[dimensions])));
                                count_images++;
                                if(count_images == M_boundary)  break;
                            }
                            count_probes++;
                        }
                    }
                    if(count_images == M_boundary)  break;
                }
                count_hamming++;
            }
        }

        auto end = chrono::high_resolution_clock::now(); 

        cout << endl << "--------------------------------------------" << endl;
        cout << "Query: " << Queries_Array[i][dimensions] << endl;

        for(int k=0;k<N;k++)
        {
            HyperCube_Distances[k] = distances.top().first;
            HyperCube_nns[k] = distances.top().second;
            distances.pop();
            cout << "Nearest neighbor-" << k+1 << ": " << HyperCube_nns[k] << endl;
            cout << "distanceHyperCube: " << HyperCube_Distances[k] << endl;
            cout << "distanceTrue: " << True_Distances[i][k] << endl << endl;
            dist_AF += (double)(HyperCube_Distances[k])/(double)True_Distances[i][k];
        }

        tHypercube[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
        cout << "tHypercube: " << tHypercube[i] << "ms" << endl << "tTrue: " << tTrue[i] << "ms";
        time_error += tHypercube[i]/tTrue[i];

        Approximate_Range_Search(i,fi_query_values[i]);
    }

    cout << endl << "HyperCube's Mean Distance Error: " << dist_AF/(double)(Num_of_Queries*N) << endl;
    cout << endl << "tHyperCube/tTrue: " << time_error/(double)(Num_of_Queries) << endl;
}

void HyperCube::Approximate_Range_Search(int query_index,unsigned int fi_query_value)
{
    auto start = chrono::high_resolution_clock::now();
    int HyperCube_nns[N], count_hamming=1,count_images=0, count_probes=0; 
    priority_queue<int, vector<int>, greater<int>> neighboors;

    Bucket* temp = Hash_Table[fi_query_value];

    if(temp != NULL)
    {
        vector<pair<item*,unsigned int>>::iterator it;

        for(it=temp->images.begin();it!=temp->images.end();it++)
        {
            if(ManhattanDistance(Queries_Array[query_index],it->first, dimensions) < R)
                neighboors.push(it->first[dimensions]);
            count_images++;
            // cout << count_images << " ";
            if(count_images == M_boundary)  break;
        }
        // cout << endl;
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
                    int hamming_distance = hammingDistance(fi_query_value,j);
                    if(hamming_distance == count_hamming)
                    {
                        vector<pair<item*,unsigned int>>::iterator it;

                        // cout << endl << "bucket=" << j << " hamming=" << count_hamming << " " << count_images << "<" << M_boundary << " " << count_probes << "<" << probes << endl;
                        for(it=hash_cell->images.begin();it!=hash_cell->images.end();it++)   
                        {
                            if(ManhattanDistance(Queries_Array[query_index],it->first, dimensions) < R)
                                neighboors.push(it->first[dimensions]);
                            
                            count_images++;
                            if(count_images == M_boundary)  break;
                        }
                        count_probes++;
                    }
                }
                if(count_images == M_boundary)  break;
            }
            count_hamming++;
        }
    }

    auto end = chrono::high_resolution_clock::now(); 

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