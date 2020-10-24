#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char** argv)
{
    string conf_file;
    int K,L=3,k_lsh=4,M_boundary=10,k_hc=3,probes=2;

    for(int i=1;i<argc;i+=2)
    {
        if(strcmp(argv[i],"-c") == 0)
            conf_file = (argv[i+1]);
    }

    cout << conf_file << endl;

    ifstream file(conf_file);

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
                    K = stoi(word);
                }
                else if(word == "number_of_vector_hash_tables:")
                {
                    iss >> word;
                    L = stoi(word);
                }
                else if(word == "number_of_vector_hash_functions:")
                {
                    iss >> word;
                    k_lsh = stoi(word);
                }
                else if(word == "max_number_M_hypercube:")
                {
                    iss >> word;
                    M_boundary = stoi(word);
                }
                else if(word == "number_of_hypercube_dimensions:")
                {
                    iss >> word;
                    k_hc = stoi(word);
                }
                else if(word == "number_of_probes:")
                {
                    iss >> word;
                    probes = stoi(word);
                }
            } 
        }
        
    }
    else cout << "problem\n";

    cout << "K: " << K << endl;
    cout << "L: " << L << endl;
    cout << "k_lsh: " << k_lsh << endl;
    cout << "M_boundary: " << M_boundary << endl;
    cout << "k_hc: " << k_hc << endl;
    cout << "probes: " << probes << endl;
}