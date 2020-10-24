#include "../headers/kmeans.h"

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

    cout << "K: " << num_of_clusters << endl;
    cout << "L: " << L << endl;
    cout << "k_lsh: " << LSH_k << endl;
    cout << "M_boundary: " << HC_M << endl;
    cout << "k_hc: " << HC_k << endl;
    cout << "probes: " << probes << endl;
}