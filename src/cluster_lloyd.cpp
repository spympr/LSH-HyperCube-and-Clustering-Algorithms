#include "../headers/cluster_lloyd.h"

void Lloyd_Cluster::Lloyd_clustering()
{
    float average_sihouette;
    
    //!!!!HAS TO BE REPLACED BY ORIGINAL LIST OF CENTROIDS//
    int indexes[kmeansptr->get_num_of_clusters()];
    
    //Store centroids with results of kmeans++ initialization...
    for(int i=0;i<kmeansptr->get_num_of_clusters();i++)
        for(int j=0;j<kmeansptr->get_dimensions();j++)
            centroids[i][j] = kmeansptr->get_Images_Array()[indexes[i]][j];

    while(true)
    {
        //For each point of dataset keep 2 nearest centroids and the appropriate distances in our map...
        for(int i=0;i<kmeansptr->get_number_of_images();i++)
        {
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > distances; 
            
            //For each centroid...
            for(int j=0;j<kmeansptr->get_num_of_clusters();j++)
                distances.push(make_pair(ManhattanDistance(kmeansptr->get_Images_Array()[i],centroids[j],kmeansptr->get_dimensions()),j));
            
            int dist1 = distances.top().first;
            int n1 = distances.top().second;
            distances.pop();
            int dist2 = distances.top().first;
            int n2 = distances.top().second;

            Nearest_Centroids* temp = new Nearest_Centroids(n1,dist1,n2,dist2);
            points[i] = temp;
        }
        
        average_sihouette = Silhouette(&points,kmeansptr->get_num_of_clusters());
        cout << average_sihouette << endl;
        if(average_sihouette>0.1)    break;
        
        ////////KMEDIANS UPDATE/////////
        
        map <int,Nearest_Centroids*>::iterator it;

        for(it=points.begin();it!=points.end();it++)    
        {
            
        }

        
    }
}