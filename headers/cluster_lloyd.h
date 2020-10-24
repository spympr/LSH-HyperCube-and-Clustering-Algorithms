#ifndef CLUSTER_LLOYD_H
#define CLUSTER_LLOYD_H

#include "../headers/kmeans.h"

class Lloyd_Cluster
{
    private:
        string complete,output_file;
        kmeans* kmeansptr;
        
    public:
        Lloyd_Cluster(string input_file,string output_file_,string conf,string comp):complete(comp),output_file(output_file_)
        {   
            kmeansptr = new kmeans(input_file,conf);
            Lloyd_clustering();
        }

        ~Lloyd_Cluster()
        {
            delete kmeansptr;
        }
        
        void Lloyd_clustering();
};

#endif