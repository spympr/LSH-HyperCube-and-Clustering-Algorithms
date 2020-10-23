#include "../headers/exhausting.h"

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
    Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,1000);

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
    m = 423255;
    // m = M/2;
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

    //Do exhausting search and init W...
    ExhaustingNN_HC(this);
    W = 50000;
    cout << "W: " << W << endl << endl;

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
        
    //Fill Hash Tables...
    Insert_Images_To_Buckets_HyperCube(this);

    //Print Buckets...
    int counter=0;
    for(int j=0;j<HashTableSize;j++)
        if(Hash_Table[j]!=NULL)
            counter++;                
    cout << "HashTable: " << counter << " out of " << HashTableSize << endl;

    Approximate_Hypercube();

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

        if(Hash_Table[fi_query_values[i]] != NULL)
        {
            for(int p=0;p<Hash_Table[fi_query_values[i]]->images.size();p++)
            {
                distances.push(make_pair(ManhattanDistance(Queries_Array[i],Hash_Table[fi_query_values[i]]->images[p], dimensions), (Hash_Table[fi_query_values[i]]->images[p][dimensions])));
                count_images++;
                // cout << count_images << " ";
                if(count_images == M_boundary)  break;
            }
            // cout << endl;
        }
        if((Hash_Table[fi_query_values[i]] == NULL) || (count_images < M_boundary))
        {
            while((count_probes < probes) && (count_images < M_boundary))
            {
                for(int j=0;j<HashTableSize;j++)
                {
                    if(Hash_Table[j] != NULL)
                    {
                        int hamming_distance = hammingDistance(fi_query_values[i],j);
                        if(hamming_distance == count_hamming)
                        {
                            // cout << endl << "bucket=" << j << " hamming=" << count_hamming << " " << count_images << "<" << M_boundary << " " << count_probes << "<" << probes << endl;
                            for(int p=0;p<Hash_Table[j]->images.size();p++)
                            {
                                distances.push(make_pair(ManhattanDistance(Queries_Array[i],Hash_Table[j]->images[p], dimensions), (Hash_Table[j]->images[p][dimensions])));
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
            dist_error += (double)(HyperCube_Distances[k]-True_Distances[i][k])/(double)True_Distances[i][k];
        }

        tHypercube[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
        cout << "tHypercube: " << tHypercube[i] << "ms" << endl << "tTrue: " << tTrue[i] << "ms";
        time_error += tHypercube[i]/tTrue[i];

        Approximate_Range_Search(i,fi_query_values[i]);
    }

    cout << endl << "HyperCube's Mean Distance Error: " << dist_error/(double)(Num_of_Queries*N) << endl;
    cout << endl << "tHyperCube/tTrue: " << time_error/(double)(Num_of_Queries) << endl;
}

void HyperCube::Approximate_Range_Search(int query_index,unsigned int fi_query_value)
{
    auto start = chrono::high_resolution_clock::now();
    int HyperCube_nns[N], count_hamming=1,count_images=0, count_probes=0; 
    priority_queue<int, vector<int>, greater<int>> neighboors;

    if(Hash_Table[fi_query_value] != NULL)
    {
        for(int p=0;p<Hash_Table[fi_query_value]->images.size();p++)
        {
            if(ManhattanDistance(Queries_Array[query_index],Hash_Table[fi_query_value]->images[p], dimensions) < R)
                neighboors.push((Hash_Table[fi_query_value]->images[p][dimensions]));
            count_images++;
            // cout << count_images << " ";
            if(count_images == M_boundary)  break;
        }
        // cout << endl;
    }
    if((Hash_Table[fi_query_value] == NULL) || (count_images < M_boundary))
    {
        while((count_probes < probes) && (count_images < M_boundary))
        {
            for(int j=0;j<HashTableSize;j++)
            {
                if(Hash_Table[j] != NULL)
                {
                    int hamming_distance = hammingDistance(fi_query_value,j);
                    if(hamming_distance == count_hamming)
                    {
                        // cout << endl << "bucket=" << j << " hamming=" << count_hamming << " " << count_images << "<" << M_boundary << " " << count_probes << "<" << probes << endl;
                        for(int p=0;p<Hash_Table[j]->images.size();p++)
                        {
                            if(ManhattanDistance(Queries_Array[query_index],Hash_Table[j]->images[p], dimensions) < R)
                            {
                                neighboors.push((Hash_Table[j]->images[p][dimensions]));
                            }
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