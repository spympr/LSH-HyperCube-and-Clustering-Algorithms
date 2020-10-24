#include "../headers/kmeans.h"

// void Nearest_Centroids::set_nearest_centroid1(int a)
// {
//     nearest_centroid1=a;
// }

// void Nearest_Centroids::set_dist1(int a)
// {
//     dist1=a;
// }

// void Nearest_Centroids::set_nearest_centroid2(int a)
// {
//     nearest_centroid2=a;
// }

// void Nearest_Centroids::set_dist2(int a)
// {
//     dist2=a;
// }

int Nearest_Centroids::get_nearest_centroid1()
{
    return nearest_centroid1;
}

int Nearest_Centroids::get_dist1()
{
    return dist1;
}

int Nearest_Centroids::get_nearest_centroid2()
{
    return nearest_centroid2;
}

int Nearest_Centroids::get_dist2()
{
    return dist2;
}

item** kmeans::get_Images_Array()
{
    return Images_Array;
}

int kmeans::get_num_of_clusters()
{
    return num_of_clusters;
}

int kmeans::get_L()
{
    return L;
}

int kmeans::get_LSH_k()
{
    return LSH_k;
}

int kmeans::get_HC_k()
{
    return HC_k;
}

int kmeans::get_HC_M()
{
    return HC_M;
}

int kmeans::get_probes()
{
    return probes;
}

int kmeans::get_dimensions()
{
    return dimensions;
}

int kmeans::get_number_of_images()
{
    return number_of_images;
}

void kmeans::info_initialization(string configuration_file)
{
    ifstream file(configuration_file);

    if(file.is_open())
    {
        string line, word;
        while(getline(file, line))
        {
            istringstream iss(line);

            while (iss >> word) 
            { 
                if(word == "number_of_clusters:")
                {
                    iss >> word;
                    num_of_clusters = stoi(word);
                }
                else if(word == "number_of_vector_hash_tables:")
                {
                    iss >> word;
                    L = stoi(word);
                }
                else if(word == "number_of_vector_hash_functions:")
                {
                    iss >> word;
                    LSH_k = stoi(word);
                }
                else if(word == "max_number_M_hypercube:")
                {
                    iss >> word;
                    HC_M = stoi(word);
                }
                else if(word == "number_of_hypercube_dimensions:")
                {
                    iss >> word;
                    HC_k = stoi(word);
                }
                else if(word == "number_of_probes:")
                {
                    iss >> word;
                    probes = stoi(word);
                }
            } 
        }
        
    }
    else cout << "Problem" << endl;
}

void kmeans::centroid_initialization()
{
    
}