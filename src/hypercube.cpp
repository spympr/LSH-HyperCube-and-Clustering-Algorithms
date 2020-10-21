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
    cout << "Images: " << Num_of_Images << endl << "Queries: " << Num_of_Queries << endl << "Rows: " << Rows << endl << "Columns: " << Columns << endl;

    //Initilization of W(grid), dimensions of each Image...
    dimensions = (int)(floor(double(log2(Num_of_Images) - (rand() % 3 +1))));
    HashTableSize = pow(2,dimensions);

    //Declaration of hash tables...
    Bucket** Hash_Table = new Bucket*[HashTableSize];
    for(int i=0;i<HashTableSize;i++)
    {
        Hash_Table[i] = NULL;
    }

    //Initialization of 2D array True_Distances...
    True_Distances = new int*[Num_of_Queries];
    for(int i=0;i<Num_of_Queries;i++)   True_Distances[i] = new int[N];

    //Initialization of m,M...
    int M_boundary = pow(2,floor((double)32/(double)k));
    int m = 423255;
    // int m = pow(2,27)+1;
    // int m = M/3;
    cout << "M " << M << endl;

    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M_boundary);

    //Initialization of tTrue,tLSH arrays...
    tHypercube = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    //Do exhausting search and init W...
    ExhaustingNN_HC(this);
    int W = 50000;
    cout << "W: " << W << endl << endl;

    //Initialization of uniform_int_distribution class...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,W);
    
    //Initialization of L*k*d(imensions) random s_i integers...
    s_i = new int*[k];
    for(int i=0;i<(k);i++)
    {
        s_i[i] = new int[dimensions];
        for(int j=0;j<dimensions;j++)   
            s_i[i][j] = distribution(generator);
    }

    //Fill Hash Tables...
    Insert_Images_To_Buckets_HyperCube(this);

    //Print Buckets...
    // for(int i=0;i<L;i++)
    // {
    // int counter=0;
    // for(int j=0;j<HashTableSize;j++)
    //     if(Hash_Table[j]!=NULL)
    //         counter++;                
    // cout << "HashTable " << j << ": " << counter << endl;
    // }
    // cout << endl;

    Approximate_Hypercube();

    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    //Deallocation of memory of Queries_Array...
    for(int i=0;i<Num_of_Queries;i++)    delete [] Queries_Array[i];
    delete [] Queries_Array;

    //Deallocation of memory of s_i...
    for(int i=0;i<(k);i++)    delete [] s_i[i];
    delete [] s_i;        

    //Deallocation of memory of Hash_Tables...
    // for(int i=0;i<L;i++)    
    // {
    for(int j=0;j<(HashTableSize);j++)   
        if(Hash_Table[j]!=NULL)
            delete Hash_Table[j];
        // delete [] Hash_Tables[i];
    // }

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

    int count_images=0, count_probes=0;
    
    fi_values_of_query(this, fi_query_values);

    for(int i=0;i<Num_of_Queries;i++)
    {
        auto start = chrono::high_resolution_clock::now();
        int HyperCube_nns[N],HyperCube_Distances[N], count_hamming=1; 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        if(Hash_Table[fi_query_values[i]] != NULL)
        {
            for(int p=0;p<Hash_Table[fi_query_values[i]]->images.size();p++)
            {
                distances.push(make_pair(ManhattanDistance(Queries_Array[i],Hash_Table[fi_query_values[i]]->images[p], dimensions), (Hash_Table[fi_query_values[i]]->images[p][dimensions])));
                count_images++;
                if(count_images == M)  break;
            }
        }
        if((Hash_Table[fi_query_values[i]] == NULL) || (count_images < M))
        {
            while((count_probes < probes) && (count_images < M))
            {
                for(int j=0;j<HashTableSize;j++)
                {
                    if(Hash_Table[j] != NULL)
                    {
                        int hamming_distance = hammingDistance(fi_query_values[i],j);
                        if(hamming_distance == count_hamming)
                        {
                            for(int p=0;p<Hash_Table[j]->images.size();p++)
                            {
                                distances.push(make_pair(ManhattanDistance(Queries_Array[i],Hash_Table[j]->images[p], dimensions), (Hash_Table[j]->images[p][dimensions])));
                                count_images++;
                                if(count_images == M)  break;
                            }
                            count_probes++;
                        }
                    }
                    if(count_images == M)  break;
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
            cout << "distanceLSH: " << HyperCube_Distances[k] << endl;
            cout << "distanceTrue: " << True_Distances[i][k] << endl << endl;
        }

        tHypercube[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
        cout << "tHypercube: " << tHypercube[i] << "ms" << endl << "tTrue: " << tTrue[i] << "ms";
    }
}