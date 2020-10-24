#include "../headers/kmeans.h"

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
    default_random_engine generator;   
    uniform_int_distribution<int> distribution(0,number_of_images);

    int first_centroid = distribution(generator);
    int clusters = 1;
    
    while(clusters != num_of_clusters)
    {
        int min_distance=-1;
        int D_i[number_of_images];
        priority_queue<int> distances;

        for(int i=0;i<number_of_images;i++)
        {
            min_distance=-1;
            for(int j=0;j<clusters;j++)
            {
                int distance = ManhattanDistance(Images_Array[i], Images_Array[first_centroid],dimensions);
                if(distance < min_distance)  min_distance = distance;
            }
            D_i[i] = min_distance;
            distances.push(min_distance);
        }
        int max_Di = distances.top();
        distances.pop();

        float sum=0.0;
        for(int z=0;z<number_of_images;z++)
            sum += pow((D_i[z]/min_distance),2);
        
        clusters++;
        P_r[clusters] = sum;

        default_random_engine generator;   
        uniform_int_distribution<float> distribution(0,P_r[number_of_images-clusters]);
    }
}