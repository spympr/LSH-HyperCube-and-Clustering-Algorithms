#ifndef CLUSTER_LLOYD_H
#define CLUSTER_LLOYD_H

#include "../headers/kmeans.h"

class Lloyd_Cluster
{
    private:
        int dimensions,number_of_images,cols,rows;
        string complete,output_file;
        item** Images_Array;
        kmeans* init;
        
    public:
        Lloyd_Cluster(string input_file,string output_file_,string conf,string comp):complete(comp),output_file(output_file_)
        {   
            Read_BF(&Images_Array,&number_of_images,&cols,&rows,input_file,1);
            dimensions = cols*rows;
            init = new kmeans(Images_Array,conf);
            Lloyd_clustering();
        }

        ~Lloyd_Cluster()
        {
            delete init;
            //Deallocation of memory of Images_Array...
            for(int i=0;i<number_of_images;i++)    delete [] Images_Array[i];
                delete [] Images_Array;
        }
        
        void Lloyd_clustering();
};

#endif