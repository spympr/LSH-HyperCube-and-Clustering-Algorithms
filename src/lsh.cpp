#include "../headers/exhausting.h"

void LSH::Approximate_LSH()
{   
    for(int i=0;i<Num_of_Queries;i++)
    {
        int LSH_nns[N],LSH_Distances[N]; 
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        unsigned int gi_query_values[L];
        
        gi_values_of_query(this, gi_query_values, i);

        for(int j=0;j<L;j++)
            if(Hash_Tables[j][gi_query_values[j]] != NULL)
                for(int p=0;p<Hash_Tables[j][gi_query_values[j]]->images.size();p++)
                    distances.push(make_pair(ManhattanDistance(Queries_Array[i],Hash_Tables[j][gi_query_values[j]]->images[p], dimensions), (Hash_Tables[j][gi_query_values[j]]->images[p][dimensions])));

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
        }
        tLSH[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
        cout << "tLSH: " << tLSH[i] << "ms" << endl << "tTrue: " << tTrue[i] << "ms";

        Approximate_Range_Search(i);
    }
    cout << endl;
}

void LSH::Approximate_Range_Search(int query_index)
{   
    priority_queue<int, vector<int>, greater<int>> neighboors; 

    unsigned int gi_query_values[L];

    gi_values_of_query(this, gi_query_values, query_index);

    for(int j=0;j<L;j++)
    {
        if(Hash_Tables[j][gi_query_values[j]] != NULL)
        {
            for(int p=0; p<(Hash_Tables[j][gi_query_values[j]]->images.size());p++)
            {
                if(ManhattanDistance(Queries_Array[query_index],Hash_Tables[j][gi_query_values[j]]->images[p], dimensions) < R)
                    neighboors.push(Hash_Tables[j][gi_query_values[j]]->images[p][dimensions]);
            }
        }
    }
    
    cout << endl << "R-near neighbors:" << endl;
    // cout << neighboors.size() << endl;
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
    Read_BF(&Queries_Array,&Num_of_Queries,&Columns,&Rows,query_file,1000);

    //Printing...
    cout << "Images: " << Num_of_Images << endl << "Queries: " << Num_of_Queries << endl << "Rows: " << Rows << endl << "Columns: " << Columns << endl;
    
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
    cout << "m " << m << endl;
    cout << "M " << M << endl;
    
    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of tTrue,tLSH arrays...
    tLSH = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    //Do exhausting search and init W...
    ExhaustingNN(this);
    W = 20000;
    cout << "W: " << W << endl << endl;

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
    cout << endl;

    Approximate_LSH();
    
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