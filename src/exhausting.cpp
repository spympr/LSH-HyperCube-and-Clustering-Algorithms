#include "../headers/exhausting.h"

void ExhaustingNN(LSH* info)
{   
    for(int i=0;i<info->get_Num_of_Queries();i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<int, vector<int>, greater<int>> pq;

        for(int j=0;j<info->get_Num_of_Images();j++)
            pq.push(ManhattanDistance(info->get_Queries_Array()[i],info->get_Images_Array()[j],info->get_dimensions()));
        
        auto end = chrono::high_resolution_clock::now(); 
        for(int k=0;k<info->get_N();k++)
        {
            info->get_True_Distances()[i][k] = pq.top();
            pq.pop();
        }
        info->get_tTrue()[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
    }
}

void ExhaustingNN_HC(HyperCube* info)
{   
    for(int i=0;i<info->Num_of_Queries;i++)
    {
        auto start = chrono::high_resolution_clock::now(); 
        priority_queue<int, vector<int>, greater<int>> pq;

        for(int j=0;j<info->Num_of_Images;j++)
            pq.push(ManhattanDistance(info->Queries_Array[i],info->Images_Array[j],info->dimensions));
        
        auto end = chrono::high_resolution_clock::now(); 
        for(int k=0;k<info->N;k++)
        {
            info->True_Distances[i][k] = pq.top();
            pq.pop();
        }
        info->tTrue[i] = chrono::duration_cast<chrono::milliseconds>(end - start).count();  
    }
}

item ManhattanDistance(item* x,item* y,int dimensions)
{
    item sum=0;
    for(int i=0;i<dimensions;i++)   sum+=abs(x[i]-y[i]);    
    
    return sum;
}