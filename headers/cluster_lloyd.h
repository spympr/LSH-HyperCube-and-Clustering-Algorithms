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
        fstream file;
        
    public:

        Lloyd_Cluster(string input_file,string output_file_,string conf,string comp):complete(comp),output_file(output_file_)
        {   
            file.open(output_file,ios::out);
            
            //Allocate memory for kmeans pointer (helpful class kmeans).
            kmeansptr = new kmeans(input_file,conf);
            file << endl << "Images:" << kmeansptr->get_number_of_images() << endl << "Dimensions:" << sqrt(kmeansptr->get_dimensions()) << "x" << sqrt(kmeansptr->get_dimensions()) << endl <<  "Κ:" << kmeansptr->get_K() << endl;

            //Allocate memory for centroids of each cluster (centroids_dimensions=K*image_dimensions).
            centroids = new item*[kmeansptr->get_K()];
            for(int i=0;i<kmeansptr->get_K();i++) centroids[i] = new item[kmeansptr->get_dimensions()];
            for(int i=0;i<kmeansptr->get_K();i++) 
                for(int z=0;z<kmeansptr->get_dimensions();z++) 
                    centroids[i][z]=0;
            
            //Allocate memory for each class Nearest_Centroids (each image has one pointer to an object of Nearest_Centroids).
            for(int i=0;i<kmeansptr->get_number_of_images();i++)
            {
                Nearest_Centroids* temp = new Nearest_Centroids();
                points[i] = temp;
            }

            //Begin Clustering...
            Lloyd_Clustering();
        }

        ~Lloyd_Cluster()
        {
            //Deallocate memory for each pointer to class Nearest_Centroids.
            for(int i=0;i<kmeansptr->get_number_of_images();i++)    delete points[i];
            
            //Deallocate memory for centroids array.
            for(int i=0;i<kmeansptr->get_K();i++) delete [] centroids[i];
            delete [] centroids;

            //Deallocate memory for kmeans pointer.
            delete kmeansptr;
        }
        
        void Lloyd_Clustering();
        void Lloyd_Assign();
        void Lloyd_Update();
        void Lloyd_Print(float* ,int);
        float Lloyd_Objective();
};

#endif