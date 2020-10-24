#ifndef CLUSTER_LLOYD.H
#define CLUSTER_LLOYD.H

#include "../headers/exhausting.h"
#include "../headers/kmeans.h"

class LLoyd_Cluster
{
    private:
        int dimensions,number_of_images,cols,rows;
        string input_file;
        item** Images_Array;
        kmeans* init;
        
    public:
        LLoyd_Cluster()
        {   
            Read_BF(&Images_Array,&number_of_images,&cols,&rows,input_file,1);
            dimensions = cols*rows;
            init = new kmeans(Images_Array);
            Lloyd_clustering();
        }

        ~LLoyd_Cluster()
        {
            delete init;
        }
        
        void Lloyd_clustering();
};

#endif