#include "../headers/exhausting.h"
// #include "../headers/hypercube.h"

using namespace std;

int main(int argc, char** argv)
{
    string answer,input_file, query_file, output_file,configuration_file,complete,method;
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
                cout << endl << "Please give an input with this form: ./lsh  –d  <input file>  –q  <query file>  –k  <int>  -L  <int>  -ο  <output  file>  -Ν <number of nearest> -R <radius>\n";
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
                else if(strcmp(argv[i],"-N") == 0)
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
                cout << endl << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο <output file> -Ν <number of nearest> -R <radius>\n";
                return -1;
            }

            k=14;
            N=1;
            R=10000;
            probes=2;
            M=10;

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
                else if(strcmp(argv[i],"-M") == 0)
                    M = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-R") == 0)
                    R = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-N") == 0)
                    N = atoi(argv[i+1]);
                else
                {
                    cout << "Please give an input with this form: ./cube  –d  <input  file>  –q  <query  file>  –k  <int>  -M  <int>  -probes  <int>  -ο<output file> -Ν <number of nearest> -R <radius>\n";
                }
            }
        }
        else if(strcmp(argv[0],"./cluster") == 0)
        {
            if(argc!=11)    
            {
                cout << endl << "Please give an input with this form: ./cluster –i <input file> –c <configuration file> -o <output file> -complete <yes or no> -m <method: Classic or LSH or Hypercube>" <<  endl;
                return -1;
            }

             for(int i=1;i<argc;i+=2)
            {
                if(strcmp(argv[i],"-i") == 0)
                    input_file = (argv[i+1]);                    
                else if(strcmp(argv[i],"-c") == 0)
                    configuration_file = (argv[i+1]);
                else if(strcmp(argv[i],"-o") == 0)
                    output_file = (argv[i+1]);
                else if(strcmp(argv[i],"-complete") == 0)
                    complete = atoi(argv[i+1]);
                else if(strcmp(argv[i],"-m") == 0)
                    method = atoi(argv[i+1]);
                else
                {
                cout << endl << "Please give an input with this form: ./cluster –i <input file> –c <configuration file> -o <output file> -complete <yes or no> -m <method: Classic OR LSH or Hypercube>" <<  endl;
                }
            }
        }
    }

    while(true)
    {
        if(strcmp(argv[0],"./lsh") == 0)    LSH lsh(input_file,query_file,L,N,k,R);            
        else if(strcmp(argv[0],"./cube") == 0)    HyperCube cube(input_file,query_file,N,k,R,M,probes);            
        else if(strcmp(argv[0],"./cluster") == 0)   
        {
            if(strcmp(method.c_str(),"Classic") == 0)
            {
                
            }
            else if(strcmp(method.c_str(),"LSH") == 0)
            {

            }
            else if(strcmp(method.c_str(),"Hypercube") == 0)
            {

            }
            else
            {
                cout << endl << "Invalid method! Please try to pich one of these methods: [Classic,LSH,Hypercube]" << endl;
                return -1;
            }
        }
        
        cout << endl << "Do you want to question something else?" << endl;
        cin >> answer;

        if((answer == "no") || (answer == "No") || (answer == "NO") || (answer == "n") || (answer =="N"))
            break;
    }
    return 0; 
}