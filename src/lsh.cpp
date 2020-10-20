#include "../headers/lsh.h"

void Approximate_LSH(infoptr info)
{   
    for(int i=0;i<info->Num_of_Queries;i++)
    {
        int N_NN_Range_Search[info->N];

        int LSH_nns[info->N],LSH_Distances[info->N]; 
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        unsigned int gi_query_values[info->L];
        
        gi_values_of_query(info, gi_query_values, i);

        for(int j=0;j<info->L;j++)
            if(info->Hash_Tables[j][gi_query_values[j]] != NULL)
                for(int p=0;p<info->Hash_Tables[j][gi_query_values[j]]->images.size();p++)
                    distances.push(make_pair(ManhattanDistance(info->Queries_Array[i],info->Hash_Tables[j][gi_query_values[j]]->images[p], info->dimensions), (info->Hash_Tables[j][gi_query_values[j]]->images[p][info->dimensions])));

        auto end = chrono::high_resolution_clock::now(); 
        
        cout << endl << "--------------------------------------------" << endl;
        cout << "Query: " << info->Queries_Array[i][info->dimensions] << endl;
        
        for(int k=0;k<info->N;k++)
        {
            LSH_Distances[k] = distances.top().first;
            LSH_nns[k] = distances.top().second;
            distances.pop();
            cout << "Nearest neighbor-" << k+1 << ": " << LSH_nns[k] << endl;
            cout << "distanceLSH: " << LSH_Distances[k] << endl;
            cout << "distanceTrue: " << info->True_Distances[i][k] << endl << endl;
        }
        info->tLSH[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
        cout << "tLSH: " << info->tLSH[i] << "ms" << endl << "tTrue: " << info->tTrue[i] << "ms";

        Approximate_Range_Search(info,N_NN_Range_Search, i);

        cout << endl;
        cout << "R-near neighbors:" << endl;

        for(int n=0;n<info->N;n++)
        { 
            if(N_NN_Range_Search[n] != -1) cout << N_NN_Range_Search[n] << endl;
            else cout << "None\n";
        }

    }
    cout << endl;
}

void Approximate_Range_Search(infoptr info,int* N_NN_Range_Search, int query_index)
{   
    priority_queue<int, vector<int>, greater<int>> neighboors; 

    unsigned int gi_query_values[info->L];

    gi_values_of_query(info, gi_query_values, query_index);

    for(int j=0;j<info->L;j++)
    {
        if(info->Hash_Tables[j][gi_query_values[j]] != NULL)
        {
            int images_in_bucket = info->Hash_Tables[j][gi_query_values[j]]->images.size();
            
            for(int p=0; p<images_in_bucket;p++)
            {
                if(ManhattanDistance(info->Queries_Array[query_index],info->Hash_Tables[j][gi_query_values[j]]->images[p], info->dimensions) < info->R)
                    neighboors.push(info->Hash_Tables[j][gi_query_values[j]]->images[p][info->dimensions]);
            }
        }
    }

    for(int k=0;k<info->N;k++)
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

void LSH(string input_file,string query_file,int L,int N,int k,int R)
{
    //Declaration of variables...
    int Num_Of_Images,Columns_Of_Images,Rows_Of_Images,Num_Of_Queries,Columns_Of_Queries,Rows_Of_Queries;
    item **Images_Array,**Queries_Array;

    //Read input binary file...
    Read_BF(&Images_Array,&Num_Of_Images,&Columns_Of_Images,&Rows_Of_Images,input_file,1);
    
    //Read query binary file...
    Read_BF(&Queries_Array,&Num_Of_Queries,&Columns_Of_Queries,&Rows_Of_Queries,query_file,1000);

    //Printing...
    cout << "Images: " << Num_Of_Images << endl << "Queries: " << Num_Of_Queries << endl << "Rows: " << Rows_Of_Images << endl << "Columns: " << Columns_Of_Images << endl;

    //Initilization of W(grid), dimensions of each Image...
    int dimensions = Columns_Of_Images*Rows_Of_Images,HashTableSize=Num_Of_Images/8;

    //Declaration of hash tables...
    Bucket** Hash_Tables[L];
    for(int i=0;i<L;i++)    
    {
        Hash_Tables[i] = new Bucket*[HashTableSize];
        for(int j=0;j<HashTableSize;j++)   Hash_Tables[i][j]=NULL;                
    }

    //Initialization of 2D array True_Distances...
    int** True_Distances = new int*[Num_Of_Queries];
    for(int i=0;i<Num_Of_Queries;i++)   True_Distances[i] = new int[N];
    
    //Initialization of m,M...
    int M = pow(2,floor((double)32/(double)k));
    int m = 423255;
    // int m = pow(2,27)+1;
    // int m = M/3;
    
    //Calculation of m^d-1modM array...
    int* modulars = new int[dimensions];
    for(int i=0;i<dimensions;i++)   modulars[i]=mod_expo(m,i,M);

    //Initialization of tTrue,tLSH arrays...
    double* tLSH = new double[Num_Of_Queries];
    double* tTrue = new double[Num_Of_Queries];

    //Initialization of pointer to object of class Info (store important variables).
    infoptr info = new Info(Num_Of_Images,Num_Of_Queries,k,L,N,R,dimensions,Images_Array,Queries_Array,Hash_Tables,m,M,modulars,HashTableSize,tLSH,tTrue);

    //Do exhausting search and init W...
    ExhaustingNN(info,True_Distances);
    int W = 50000;
    cout << "W: " << W << endl << endl;
        
    //Initialization of uniform_int_distribution class...
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,W);
    
    //Initialization of L*k*d(imensions) random s_i integers...
    int** s_i = new int*[L*k];
    for(int i=0;i<(L*k);i++)
    {
        s_i[i] = new int[dimensions];
        for(int j=0;j<dimensions;j++)   
            s_i[i][j] = distribution(generator);
    }

    //Update info with information of s_i array,True_Distances array and W...
    info->s_i = s_i;
    info->W = W;
    info->True_Distances = True_Distances;

    //Fill Hash Tables...
    Insert_Images_To_Buckets(info);

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

    Approximate_LSH(info);
    
    ////////////////////////////////////////////////////////////////////

    //Deallocation of memory of Images_Array...
    for(int i=0;i<Num_Of_Images;i++)    delete [] Images_Array[i];
    delete [] Images_Array;

    //Deallocation of memory of Queries_Array...
    for(int i=0;i<Num_Of_Queries;i++)    delete [] Queries_Array[i];
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
    for(int i=0;i<Num_Of_Queries;i++)  
        delete [] True_Distances[i];
    delete [] True_Distances;
    
    //Deallocation of memory of tLSH,tTrue,modulars...
    delete [] tLSH;
    delete [] tTrue;
    delete [] modulars;

    //Deallocation of memory of pointer to object of class Info...
    delete info;
}