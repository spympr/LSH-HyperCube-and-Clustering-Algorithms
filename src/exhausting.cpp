#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include <queue> 
#include <cstdlib>
#include "../headers/exhausting.h"

int ExhaustingNN(infoptr info,int** True_Distances)
{   
    int W=0;

    for(int i=0;i<info->Num_of_Queries;i++)
    {
        priority_queue<int, vector<int>, greater<int>> pq;

        for(int j=0;j<info->Num_of_Images;j++)
            pq.push(ManhattanDistance(info->Queries_Array[i],info->Images_Array[j],info->dimensions));
        
        for(int k=0;k<info->N;k++)
        {
            True_Distances[i][k] = pq.top();
            pq.pop();
            
            W += True_Distances[i][k];
            // cout << True_Distances[i][k] << " ";
        }
        // cout << endl;
    }

    W = W/(info->Num_of_Queries*info->N);
    return W;
}

item ManhattanDistance(item* x,item* y,int dimensions)
{
    item sum=0;
    for(int i=0;i<dimensions;i++)   sum+=abs(x[i]-y[i]);    
    
    return sum;
}

void Approximate_LSH(infoptr info,int** LSH_Distances, int** LSH_nns)
{   
    for(int i=0;i<info->Num_of_Queries;i++)
    {
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
    }
}