#include "../headers/cluster_lloyd.h"

void Lloyd_Cluster::Lloyd_clustering()
{
    //!!!!HAS TO BE REPLACED BY ORIGINAL LIST OF CENTROIDS//
    int indexes[kmeansptr->get_num_of_clusters()];

    //Fill centroids with results of kmeans++ initialization...
    for(int i=0;i<kmeansptr->get_num_of_clusters();i++)
        for(int j=0;j<kmeansptr->get_dimensions();j++)
            centroids[i][j] = kmeansptr->get_Images_Array()[indexes[i]][j];

    //For each point of dataset...
    for(int i=0;i<kmeansptr->get_number_of_images();i++)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > distances; 
        
        //For each centroid...
        for(int j=0;j<kmeansptr->get_num_of_clusters();j++)
            distances.push(make_pair(ManhattanDistance(kmeansptr->get_Images_Array()[i],centroids[j],kmeansptr->get_dimensions()),j));
        
        distances.top().first;
        distances.top().second;
        distances.pop();
        distances.top().first;
        distances.top().second;
        
    }
}