#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include <queue> 
#include "../headers/exhausting.h"

using namespace std;

void Approximate_LSH(infoptr info,int** LSH_Distances, int** LSH_nns)
{   
    int W=0;

    for(int i=0;i<info->Num_of_Queries;i++)
    {
        item* temp_query = info->Queries_Array[i];
        priority_queue<int, vector<int>, greater<int> > distances;

        for(int j=0;j<info->L;j++)
        {
            
        }

        for(int j=0;j<info->Num_of_Images;j++)
        {
            item* temp_image = info->Images_Array[j];
            pq.push(ManhattanDistance(temp_query,temp_image,info->dimensions));
        }
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

int ManhattanDistance(item* x,item* y,int dimensions)
{
    int sum=0;
    for(int i=0;i<dimensions;i++)   sum+=abs(x[i]-y[i]);    
    
    return sum;
}

