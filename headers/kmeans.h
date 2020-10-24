#ifndef KMEANS_H
#define KMEANS_H

#include "../headers/exhausting.h"

class kmeans
{
    private:
        int num_of_clusters,L,LSH_k,HC_k,HC_M,probes;

    public:

        kmeans(item** Images_Array_,string conf)
        {
            info_initialization(conf);
            // centroid_initialization();
        }

        void info_initialization(string );
        void centroid_initialization();
        //get function to get structere of k clusters

        int get_num_of_clusters();
        int get_L();
        int get_LSH_k();
        int get_HC_k();
        int get_HC_M();
        int get_probes();
};

#endif