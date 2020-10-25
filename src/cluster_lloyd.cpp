#include "../headers/cluster_lloyd.h"

void Lloyd_Cluster::Lloyd_Clustering()
{
    //Threshold epsilon...
    float epsilon=0.001;

    //Original array of kmeans centroisd...
    int* indexes = kmeansptr->get_centroids();
 
    //Store previous and current average_silhouette in this array..
    float average_sihouettes[2];
    average_sihouettes[0]=2;

    //Allocate memory for array with silhouette values...
    float* silhouette_array = new float[kmeansptr->get_K()+1];    

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
        Lloyd_Assign();

        average_sihouettes[1] = Silhouette(&points,kmeansptr->get_K(),&silhouette_array);
        cout << average_sihouettes[1] << "-" << average_sihouettes[0] << "<" << epsilon << endl;
        if(abs(average_sihouettes[1]-average_sihouettes[0])<epsilon) break;
        average_sihouettes[0] = average_sihouettes[1];

        Lloyd_Update();
    }
    Lloyd_Print(silhouette_array);

    delete [] silhouette_array;
}

void Lloyd_Cluster::Lloyd_Assign()
{
    //For each point of dataset keep 2 nearest centroids and the appropriate distances in our map...
    for(int i=0;i<kmeansptr->get_number_of_images();i++)
    {
        //Store pairs of distance to each centroid from a point of dataset and index of this centroid...
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > distances; 
        
        for(int j=0;j<kmeansptr->get_K();j++)
            distances.push(make_pair(ManhattanDistance(kmeansptr->get_Images_Array()[i],centroids[j],kmeansptr->get_dimensions()),j));
        
        //Store distance and index of first nearest centroid...
        int dist1 = distances.top().first;
        int n1 = distances.top().second;
        
        //Pop up first pair...
        distances.pop();
        
        //Store distance and index of second nearest centroid...
        int dist2 = distances.top().first;
        int n2 = distances.top().second;

        //Pass these values to class Nearest_Centroids of each point of dataset...
        points[i]->set_dist1(dist1);
        points[i]->set_nearest_centroid1(n1);
        points[i]->set_dist2(dist2);
        points[i]->set_nearest_centroid2(n2);
    }
}

void Lloyd_Cluster::Lloyd_Update()
{    
    map <int,Nearest_Centroids*>::iterator it;
    int cluster,median_index;

    //Initialize K*dimensions vectors...
    vector<item>** vectors = new vector<item>*[kmeansptr->get_K()];
    for(int i=0;i<kmeansptr->get_K();i++)   vectors[i] = new vector<int>[kmeansptr->get_dimensions()];  
    
    //Fill vectors with features of each image of dataset...
    for(it=points.begin();it!=points.end();it++)    
    {
        for(int z=0;z<kmeansptr->get_dimensions();z++)
        {
            cluster = it->second->get_nearest_centroid1();
            vectors[cluster][z].push_back(kmeansptr->get_Images_Array()[it->first][z]);
        }
    }

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

void Lloyd_Cluster::Lloyd_Print(float* silhouette_array)
{
    //Declaration of important structures,variables...
    int cluster,K = kmeansptr->get_K();
    map <int,Nearest_Centroids*>::iterator it;
    int images_in_cluster[K];
    for(int i=0;i<kmeansptr->get_K();i++)   images_in_cluster[i]=0;

    //Iterate whole map so as to calculate silhouette for points of each cluster...
    for(it=points.begin();it!=points.end();it++)    
    {
        cluster = it->second->get_nearest_centroid1();
        images_in_cluster[cluster]++;
    }

    for(int i=0;i<K;i++)   
    {
        cout << "CLUSTER-" << i+1 << "{" << images_in_cluster[i] << ", [ ";
        for(int z=0;z<kmeansptr->get_dimensions();z++)  cout << centroids[i][z] << " "; 
        cout << endl;
    }
    
    cout << "clustering_time: " << "TIME" << endl << "Silhouette: [ ";

    for(int i=0;i<=K;i++)   
    {
        cout << silhouette_array[i] << ", ";
    }
    cout << endl;

    // if(complete=="yes")
    // {
    //     for(int i=0;i<K;i++)   
    //     {
    //     cout << "CLUSTER-" << i+1 << "{" <<  << ",  ";
    //     for(int z=0;z<kmeansptr->get_dimensions();z++)  cout << centroids[i][z] << " "; 
    //     cout << endl;
    //     }
    // }
}