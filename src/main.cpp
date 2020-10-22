#include "../headers/exhausting.h"
#include "../headers/hypercube.h"

using namespace std;

int main(int argc, char** argv)
{
    string answer,input_file, query_file, output_file;
    int k,L,N,R,M,probes;

    if(argc==1)
    {
        cout << "Give me the path of dataset: "; 
        cin >> input_file;

        cout << "Give me the path of queryset: "; 
        cin >> query_file;

        cout << "Give me the path of exit file: "; 
        cin >> output_file;

        k=4;
        L=5;
        N=1;
        R=1.0;
    }
    else
    {
        if(strcmp(argv[0],"./lsh") == 0)
        {
            if(argc!=15 && argc!=7)   
            {
                cout << "Please give an input with this form: ./lsh  –d  <input  file>  –q  <query  file>  –k  <int>  -L  <int>  -ο  <output  file>  -Ν<number of nearest> -R <radius>\n";
                return -1;
            }

            k=4;
            L=5;
            N=1;
            R=10000;

            for(int i=1;i<argc;i+=2)
            {
                if(strcmp(argv[i],"-d") == 0)
                    input_file = (argv[i+1]);                    
                else if(strcmp(argv[i],"-q") == 0)
                    query_file = (argv[i+1]);
                else if(strcmp(argv[i],"-o") == 0)
                    output_file = (argv[i+1]);
                else if(strcmp(argv[i],"-k") == 0)
                    k = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-L") == 0)
                    L = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-N") ==0)
                    N = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-R") == 0)
                    R = atoi(argv[i+1]);
                else
                {
                    cout << "Please give an input with this form: ./lsh  –d  <input  file>  –q  <query  file>  –k  <int>  -L  <int>  -ο  <output  file>  -Ν<number of nearest> -R <radius>\n";
                }
            }
        }
        else if(strcmp(argv[0],"./cube") == 0)
        {
            if(argc!=17 && argc!=7)    
            {
                cout << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο <output file> -Ν <number of nearest> -R <radius>\n";
                return -1;
            }

            k=14;
            N=1;
            R=10000;
            // probes=2;
            // M=10;
            probes=10;
            M=200;

            for(int i=1;i<argc;i+=2)
            {
                if(strcmp(argv[i],"-d") == 0)
                    input_file = (argv[i+1]);                    
                else if(strcmp(argv[i],"-q") == 0)
                    query_file = (argv[i+1]);
                else if(strcmp(argv[i],"-o") == 0)
                    output_file = (argv[i+1]);
                else if(strcmp(argv[i],"-k") == 0)
                    k = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-probes") == 0)
                    probes = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-M") ==0)
                    M = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-R") == 0)
                    R = atoi(argv[i+1]);
                else
                {
                    cout << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο<output file> -Ν <number of nearest> -R <radius>\n";
                }
            }
        }
    }

    while(true)
    {
        if(strcmp(argv[0],"./lsh") == 0)    LSH lsh(input_file,query_file,L,N,k,R);            
        else if(strcmp(argv[0],"./cube") == 0)    HyperCube cube(input_file,query_file,N,k,R,M,probes);            
        else if(strcmp(argv[0],"./cluster") == 0)   cout << "under construction..." << endl;
        
        cout << endl << "Do you want to question something else?\n";
        cin >> answer;

        if((answer == "no") || (answer == "No") || (answer == "NO") || (answer == "n") || (answer =="N"))
            break;
    }

    return 0; 
}