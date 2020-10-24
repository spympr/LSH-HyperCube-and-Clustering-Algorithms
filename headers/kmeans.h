#ifndef KMEANS_H
#define KMEANS_H

#include "../headers/exhausting.h"

class kmeans
{
    private:
        int num_of_clusters,L,LSH_k,HC_k,HC_M,probes,dimensions,number_of_images,cols,rows;
        item** Images_Array;

    public:
        kmeans(string input_file,string conf): L(3),LSH_k(4),HC_M(10),HC_k(3),probes(2)
        {
            Read_BF(&Images_Array,&number_of_images,&cols,&rows,input_file,1);
            dimensions = cols*rows;
            info_initialization(conf);
            centroid_initialization();
        }

        ~kmeans()
        {
            //Deallocation of memory of Images_Array...
            for(int i=0;i<number_of_images;i++)    delete [] Images_Array[i];
                delete [] Images_Array;
        }

        void info_initialization(string );
        void centroid_initialization();

        int get_num_of_clusters();
        int get_L();
        int get_LSH_k();
        int get_HC_k();
        int get_HC_M();
        int get_probes();
        int get_dimensions();
        int get_number_of_images();
        item** get_Images_Array();
};
#endif