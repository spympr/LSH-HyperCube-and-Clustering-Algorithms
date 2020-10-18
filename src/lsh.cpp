#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>   
#include <queue> 
#include "../headers/lsh.h"

using namespace std;

void Approximate_LSH(infoptr info,int** LSH_Distances, int** LSH_nns)
{   
    for(int i=0;i<info->Num_of_Queries;i++)
    {
        item* temp_query = info->Queries_Array[i];
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > distances; 

        unsigned int gi_query_values[info->L];

        gi_values_of_query(info, gi_query_values, i);

        for(int j=0;j<info->L;j++)
        {
            int images_in_bucket = info->Hash_Tables[j][gi_query_values[j]]->images.size();
            
            for(int p=0; p<images_in_bucket;p++)
            {
                item* temp_image = info->Hash_Tables[j][gi_query_values[j]]->images.at(p);
                distances.push(make_pair(ManhattanDistance(temp_query,temp_image, info->dimensions), (temp_image-info->Images_Array[0])/(info->dimensions*sizeof(item))+1));
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

int ManhattanDistance(item* x,item* y,int dimensions)
{
    int sum=0;
    for(int i=0;i<dimensions;i++)   sum+=abs(x[i]-y[i]);    
    
    return sum;
}

