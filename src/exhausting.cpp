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