#include "../headers/cluster.h"

int main(int argc, char** argv)
{
    string answer,input_file, query_file, output_file,configuration_file,complete,method;
    int k,L,N,R,M,probes;

    if(argc==1)
    {
        if(strcmp(argv[0],"./lsh") == 0)
        {
            cout << "Give me the path of input dataset: "; 
            cin >> input_file;

            cout << "Give me the path of queryset: "; 
            cin >> query_file;

            cout << "Give me the path of output file: "; 
            cin >> output_file;

            cout << "Give me k: "; 
            cin >> k;

            cout << "Give me L: "; 
            cin >> L;

            cout << "Give me N: "; 
            cin >> N;

            cout << "Give me R: "; 
            cin >> R;
        }
        else if(strcmp(argv[0],"./cube") == 0)
        {
            cout << "Give me the path of input dataset: "; 
            cin >> input_file;

            cout << "Give me the path of queryset: "; 
            cin >> query_file;

            cout << "Give me the path of output file: "; 
            cin >> output_file;

            cout << "Give me k: "; 
            cin >> k;

            cout << "Give me M: "; 
            cin >> M;

            cout << "Give me probes: "; 
            cin >> probes;

            cout << "Give me N: "; 
            cin >> N;

            cout << "Give me R: "; 
            cin >> R;   
        }
        else if(strcmp(argv[0],"./cluster") == 0)
        {
            cout << "Give me the path of input dataset: "; 
            cin >> input_file;

            cout << "Give me the path of configuration file: "; 
            cin >> configuration_file;

            cout << "Give me the path of output file: "; 
            cin >> output_file;

            cout << "Give me complete (yes or no): " << endl;
            cin >> complete;

            cout << "Give me method of assignment ('Classic','LSH','Hypercube'): " << endl;
            cin >> method;
        }
        else
        {
            cout << "Executable isn't valid! Try ./lsh or ./cube or ./cluster !" << endl;
            return -1;
        }
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
                    return -1;
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
                    complete = argv[i+1];
                else if(strcmp(argv[i],"-m") == 0)
                    method = argv[i+1];
                else
                {
                    cout << endl << "Please give an input with this form: ./cluster –i <input file> –c <configuration file> -o <output file> -complete <yes or no> -m <method: Classic OR LSH or Hypercube>" <<  endl;
                    return -1;
                }
            }

            if((strcmp(method.c_str(),"LSH") == 0))
            {
                k=4;
                L=5;
                N=1;
                R=10000;
            }
            else if(strcmp(method.c_str(),"Hypercube") == 0)
            {
                k=14;
                N=1;
                R=10000;
                probes=2;
                M=10; 
            }
        }
        else
        {
            cout << "Executable isn't valid! Try ./lsh or ./cube or ./cluster !" << endl;
            return -1;
        }   
    }
    
    while(true)
    {
        LSH* lsh = NULL;
        HyperCube* cube = NULL;
        Cluster* Lloyd = NULL;
        Cluster* RA_LSH = NULL;
        Cluster* RA_HC = NULL;

        if(strcmp(argv[0],"./lsh") == 0)    
        {
            lsh = new LSH(input_file,query_file,output_file,L,N,k,R);    
            lsh->InitLSH();
            lsh->Approximate_LSH();
        }        
        else if(strcmp(argv[0],"./cube") == 0)    
        {
            cube = new HyperCube(input_file,query_file,output_file,N,k,R,M,probes);  
            cube->InitHyperCube();
            cube->Approximate_Hypercube();
        }          
        else if(strcmp(argv[0],"./cluster") == 0)   
        {
            if(strcmp(method.c_str(),"Classic") == 0)   
            {
                Lloyd = new Cluster(input_file,output_file,configuration_file,complete,lloyd_method);
                Lloyd->Clustering();
            }
            else if(strcmp(method.c_str(),"LSH") == 0)  
            {
                RA_LSH = new Cluster(input_file,output_file,configuration_file,complete,lsh_method);
                RA_LSH->Clustering();
            }
            else if(strcmp(method.c_str(),"Hypercube") == 0)
            {
                RA_HC = new Cluster(input_file,output_file,configuration_file,complete,hc_method);
                RA_HC->Clustering();
            }
            else
            {
                cout << endl << "Invalid method! Please try to pich one of these methods: [Classic,LSH,Hypercube]" << endl;
                return -1;
            }
        }
        string answer; 

        cout << endl << "Do you want to question something else? (y/n)" << endl;
        cin >> answer;

        if(strcmp(argv[0],"./lsh") == 0)    delete lsh;       
        else if(strcmp(argv[0],"./cube") == 0)  delete cube;      
        else if(strcmp(argv[0],"./cluster") == 0)   
        {
            if(strcmp(method.c_str(),"Classic") == 0)   delete Lloyd;
            else if(strcmp(method.c_str(),"LSH") == 0)  delete RA_LSH;
            else if(strcmp(method.c_str(),"Hypercube") == 0)    delete RA_HC;
        }
        
        if((answer == "no") || (answer == "No") || (answer == "NO") || (answer == "n") || (answer =="N"))
        {
            fstream file;
            file.open(output_file, std::ofstream::out | std::ofstream::trunc);
            file.close();
            break;
        }
        else
        {
            fstream file;
            file.open(output_file, std::ofstream::out | std::ofstream::trunc);
            file.close();

            cout << "Please give a new query file:\n";
            cin >> query_file;
        } 

    }
    return 0; 
}