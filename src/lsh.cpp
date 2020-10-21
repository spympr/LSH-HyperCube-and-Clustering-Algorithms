#include "../headers/lsh.h"

void LSH::Approximate_LSH()
{   
    for(int i=0;i<Num_of_Queries;i++)
    {
        int N_NN_Range_Search[N];

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

        Approximate_Range_Search(N_NN_Range_Search, i);

        cout << endl;
        cout << "R-near neighbors:" << endl;

        for(int n=0;n<N;n++)
        { 
            if(N_NN_Range_Search[n] != -1) cout << N_NN_Range_Search[n] << endl;
            else cout << "None\n";
        }
    }
    cout << endl;
}

void LSH::Approximate_Range_Search(int* N_NN_Range_Search, int query_index)
{   
    priority_queue<int, vector<int>, greater<int>> neighboors; 

    unsigned int gi_query_values[L];

    gi_values_of_query(this, gi_query_values, query_index);

    for(int j=0;j<L;j++)
    {
        if(Hash_Tables[j][gi_query_values[j]] != NULL)
        {
            int images_in_bucket = Hash_Tables[j][gi_query_values[j]]->images.size();
            
            for(int p=0; p<images_in_bucket;p++)
            {
                if(ManhattanDistance(Queries_Array[query_index],Hash_Tables[j][gi_query_values[j]]->images[p], dimensions) < R)
                    neighboors.push(Hash_Tables[j][gi_query_values[j]]->images[p][dimensions]);
            }
        }
    }

    for(int k=0;k<N;k++)
    {
        if(!neighboors.empty())
        {
            N_NN_Range_Search[k] = neighboors.top();
            neighboors.pop();
        }
        else
        {
            N_NN_Range_Search[k] = -1;
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
    HashTableSize= Num_of_Images/8;

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
    int M = pow(2,floor((double)32/(double)k));
    int m = 423255;
    // int m = pow(2,27)+1;
    // int m = M/3;
    
    //Calculation of m^d-1modM array...
    modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of tTrue,tLSH arrays...
    tLSH = new double[Num_of_Queries];
    tTrue = new double[Num_of_Queries];

    //Do exhausting search and init W...
    ExhaustingNN(this,True_Distances);
    int W = 50000;
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
    Insert_Images_To_Buckets(this);

    //Print Buckets...
    for(int i=0;i<L;i++)
    {
        int counter=0;
        for(int j=0;j<HashTableSize;j++)
            if(Hash_Tables[i][j]!=NULL)
                counter++;                
        cout << "HashTable " << i << ": " << counter << endl;
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