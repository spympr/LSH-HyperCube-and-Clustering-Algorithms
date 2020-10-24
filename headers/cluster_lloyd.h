#ifndef CLUSTER_LLOYD_H
#define CLUSTER_LLOYD_H

#include "../headers/kmeans.h"

class Lloyd_Cluster
{
    private:
        int dimensions,number_of_images,cols,rows;
        string input_file;
        item** Images_Array;
        kmeans* init;
        
    public:
        Lloyd_Cluster(string conf)
        {   
            Read_BF(&Images_Array,&number_of_images,&cols,&rows,input_file,1);
            dimensions = cols*rows;
            init = new kmeans(Images_Array,conf);
            // Lloyd_clustering();
        }

        ~Lloyd_Cluster()
        {
            delete init;
        }
        
        void Lloyd_clustering();
};

#endif