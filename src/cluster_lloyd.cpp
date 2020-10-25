#include "../headers/cluster_lloyd.h"

void Lloyd_Cluster::Lloyd_Clustering()
{
    //Original array of kmeans centroisd...
    int* indexes = kmeansptr->get_centroids();
    float average_sihouette;
    
    //Store centroids with results of kmeans++ initialization...
    for(int i=0;i<kmeansptr->get_K();i++)
    {
        cout << "Index of Cluster " << i << ":" << indexes[i] << endl;
        for(int j=0;j<kmeansptr->get_dimensions();j++)
            centroids[i][j] = kmeansptr->get_Images_Array()[indexes[i]][j];
    }
    cout << endl;
    
    while(true)
    {
        cout << "Before Assignment" << endl;
        
        Lloyd_Assign();
       
        cout << "Before Silhouette" << endl << endl;
        
        average_sihouette = Silhouette(&points,kmeansptr->get_K());
        cout << average_sihouette << endl;
        if(average_sihouette > 0.1)    break;

        cout << "Before Update" << endl;

        Lloyd_Update();
    }
}

void Lloyd_Cluster::Lloyd_Assign()
{
    //For each point of dataset keep 2 nearest centroids and the appropriate distances in our map...
    for(int i=0;i<kmeansptr->get_number_of_images();i++)
    {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > distances; 
        
        //For each centroid...
        for(int j=0;j<kmeansptr->get_K();j++)
            distances.push(make_pair(ManhattanDistance(kmeansptr->get_Images_Array()[i],centroids[j],kmeansptr->get_dimensions()),j));
        
        int dist1 = distances.top().first;
        int n1 = distances.top().second;
        distances.pop();
        int dist2 = distances.top().first;
        int n2 = distances.top().second;

        // Nearest_Centroids* temp = new Nearest_Centroids(n1,dist1,n2,dist2);
        // points[i] = temp;
    }
}

void Lloyd_Cluster::Lloyd_Update()
{    
    map <int,Nearest_Centroids*>::iterator it;
    int cluster,median_index;

    //Initialize K*dimensions vectors...
    vector<item>** vectors = new vector<item>*[kmeansptr->get_K()];
    for(int i=0;i<kmeansptr->get_K();i++)   vectors[i] = new vector<int>[kmeansptr->get_dimensions()];  
    
    cout << "Before filling vectors..." << endl;

    //Fill vectors with features of each image of dataset...
    for(it=points.begin();it!=points.end();it++)    
    {
        for(int z=0;z<kmeansptr->get_dimensions();z++)
        {
            cluster = it->second->get_nearest_centroid1();
            vectors[cluster][z].push_back(kmeansptr->get_Images_Array()[it->first][z]);
        }
    }

    cout << "Before sorting..." << endl;

    //Sort each vector and choose the appropriate feature (with median index) 
    //in order to have a new one centroid.
    for(int i=0;i<kmeansptr->get_K();i++)   
    {
        for(int z=0;z<kmeansptr->get_dimensions();z++)
        {
            sort(vectors[i][z].begin(),vectors[i][z].end());
            median_index = ceil((double)vectors[i][z].size()/(double)2); 
            centroids[i][z] = vectors[i][z][median_index];
        }   
    }
    
    //Deallocate memory for vectors...
    for(int i=0;i<kmeansptr->get_K();i++)   delete [] vectors[i];
    delete [] vectors;    
}
