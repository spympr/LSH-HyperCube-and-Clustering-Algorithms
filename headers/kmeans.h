#ifndef KMEANS.H
#define KMEANS.H

#include "../headers/exhausting.h"

class kmeans
{
    private:


    public:

        kmeans(item** Images_Array_)
        {
            cluster_initialization();
        }

        void cluster_initialization();
        //get function to get structere of k clusters
};

#endif