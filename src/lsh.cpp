#include <iostream>
#include <queue> 
#include <chrono> 
#include "../headers/lsh.h"

using namespace std;
using namespace std::chrono;

void Approximate_LSH(infoptr info)
{   
    int** LSH_nns = new int*[info->Num_of_Queries];
    for(int i=0;i<info->Num_of_Queries;i++)   LSH_nns[i] = new int[info->N];
        
    int** LSH_Distances = new int*[info->Num_of_Queries];
    for(int i=0;i<info->Num_of_Queries;i++)   LSH_Distances[i] = new int[info->N];

    for(int i=0;i<info->Num_of_Queries;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        unsigned int gi_query_values[info->L];
        
        gi_values_of_query(info, gi_query_values, i);

        for(int j=0;j<info->L;j++)
        {
            if(info->Hash_Tables[j][gi_query_values[j]] != NULL)
            {                
                for(int p=0;p<info->Hash_Tables[j][gi_query_values[j]]->images.size();p++)
                {
                    // item* temp_image = info->Hash_Tables[j][gi_query_values[j]]->images[p];
                    // cout << " hh " << info->Hash_Tables[j][gi_query_values[j]]->images[p] << endl;
                    distances.push(make_pair(ManhattanDistance(info->Queries_Array[i],info->Hash_Tables[j][gi_query_values[j]]->images[p], info->dimensions), (info->Hash_Tables[j][gi_query_values[j]]->images[p]-info->Images_Array[0])/(info->dimensions*sizeof(item))+1));
                }
            }
        }

        for(int k=0;k<info->N;k++)
        {
            LSH_Distances[i][k] = distances.top().first;
            LSH_nns[i][k] = distances.top().second;
            distances.pop();
        }
        auto end = chrono::high_resolution_clock::now(); 
        info->tLSH[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
    }

    for(int i=0;i<info->Num_of_Queries;i++)
    {
        cout << endl << "--------------------------------------------" << endl;
        cout << "Query: " << i+1 << endl;
        for(int j=0;j<info->N;j++)
        {
            cout << "Nearest neighbor-" << j+1 << ": " << LSH_nns[i][j] << endl;
            cout << "distanceLSH: " << LSH_Distances[i][j] << endl;
            cout << "distanceTrue: " << info->True_Distances[i][j] << endl << endl;
        }
        cout << "tLSH: " << info->tLSH[i] << "ms" << endl << "tTrue: " << info->tTrue[i] << "ms";
    }
    cout << endl << "--------------------------------------------" << endl;

    for(int i=0;i<info->Num_of_Queries;i++)   
    {
        delete [] LSH_Distances[i];
        delete [] LSH_nns[i];
    }
    delete [] LSH_Distances;
    delete [] LSH_nns;
}

void Approximate_Range_Search(infoptr info)
{   
    for(int i=0;i<info->Num_of_Queries;i++)
    {
        item* temp_query = info->Queries_Array[i];
        priority_queue<int, vector<int>, greater<int>> images; 

        unsigned int gi_query_values[info->L];

        gi_values_of_query(info, gi_query_values, i);

        // for(int o=0;o<info->L;o++)  cout << gi_query_values[o] << " ";
        // cout <<endl;

        for(int j=0;j<info->L;j++)
        {
            if(info->Hash_Tables[j][gi_query_values[j]] != NULL)
            {
                int images_in_bucket = info->Hash_Tables[j][gi_query_values[j]]->images.size();
                // cout << images_in_bucket << endl;
                
                for(int p=0; p<images_in_bucket;p++)
                {
                    item* temp_image = info->Hash_Tables[j][gi_query_values[j]]->images[p];
                    if(ManhattanDistance(temp_query,temp_image, info->dimensions) < info->R)
                    // cout << " hh " << info->Hash_Tables[j][gi_query_values[j]]->images[p] << endl;
                    images.push((ManhattanDistance(temp_query,temp_image, info->dimensions), (temp_image-info->Images_Array[0])/(info->dimensions*sizeof(item))+1));
                }
            }
        }

        for(int k=0;k<info->N;k++)
        {
            Images_Range_Search[i][k] = images.top();

            images.pop();
        }
    }

}