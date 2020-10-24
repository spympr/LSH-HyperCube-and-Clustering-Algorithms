#ifndef KMEANS_H
#define KMEANS_H

#include "../headers/exhausting.h"

class kmeans
{
    private:
        int num_of_clusters,L,LSH_k,HC_k,HC_M,probes;
        unsigned int* P;

    public:

        kmeans(item** Images_Array,string conf): L(3),LSH_k(4),HC_M(10),HC_k(3),probes(2)
        {
            info_initialization(conf);
            centroid_initialization(Images_Array);

            P = new int [];
        }

        void info_initialization(string );
        void centroid_initialization(item** );

        int get_num_of_clusters();
        int get_L();
        int get_LSH_k();
        int get_HC_k();
        int get_HC_M();
        int get_probes();
};
#endif