#ifndef CLUSTER_LLOYD_H
#define CLUSTER_LLOYD_H

#include "../headers/kmeans.h"

class Lloyd_Cluster
{
    private:
        string complete,output_file;
        kmeans* kmeansptr;
        item** centroids;
        map <int,Nearest_Centroids*> points;
        
    public:
        Lloyd_Cluster(string input_file,string output_file_,string conf,string comp):complete(comp),output_file(output_file_)
        {   
            kmeansptr = new kmeans(input_file,conf);
            centroids = new item*[kmeansptr->get_num_of_clusters()];
            for(int i=0;i<kmeansptr->get_num_of_clusters();i++) centroids[i] = new item[kmeansptr->get_dimensions()];
            
            Lloyd_Clustering();
        }

        ~Lloyd_Cluster()
        {
            for(int i=0;i<kmeansptr->get_num_of_clusters();i++) delete [] centroids[i];
            delete [] centroids;
            delete kmeansptr;

            map <int,Nearest_Centroids*>::iterator it;  
            for(it=points.begin();it!=points.end();it++)    delete it->second;
        }
        
        void Lloyd_Clustering();
        void Lloyd_Assign();
        void Lloyd_Update();
};

#endif