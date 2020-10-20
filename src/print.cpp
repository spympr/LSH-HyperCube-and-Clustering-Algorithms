#include <iostream>
#include <vector>

using namespace std;


int main()
{
    // vector<int> images;
    // int size=-1;

    // size=images.size();

    // cout << size << endl;

    // char* t = new char[3];
    // t[0] = 1;
    // t[1] = 3;
    // t[2] = 4;
    // cout << t[0] << endl;

    // unsigned int k=0;
    // int p;
    // for(int i=0;i<4;i++)
    // {
    //     p = 1;
    //     k |= (p << ((4-(i+1))*8));                
    // }
    // cout << k << endl;
    int a=-1,m=2;

     if (a % m < 0) 
        cout <<  a % m + m << endl;
    else
        cout << (unsigned int) a % m << endl;
}

// // Printing...
    // for(int i=0;i<100;i++)
    // {
    //     for(int j=0;j<info->L;j++)
    //     {
    //         cout << g_i[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // //Print Buckets
        // for(int i=0;i<L;i++)
        // {
        //     int counter=0;
        //     for(int j=0;j<(Num_Of_Images/16);j++)
        //     {
        //         Bucket* temp = Hash_Tables[i][j];
        //         if(temp!=NULL)
        //         {
        //             counter++;
        //             // int counter=0;
        //             // for(int k=0;k<temp->images.size();k++)  counter++;
        //             // cout << "BUCKET " << j << " HAS " << counter << endl; 
        //         }
        //     }
        //     cout << "HashTable " << i << ": " << counter << endl;
        // }

        // int temp=0;
        // for(int i=0;i<L;i++)
        // {
        //     for(int j=0;j<(Num_Of_Images/16);j++)
        //     {
        //         if(info->Hash_Tables[i][j] != NULL)
        //         {
        //             for(int p=0; p<info->Hash_Tables[i][j]->images.size();p++)
        //                 cout << "k " <<  info->Hash_Tables[i][j]->images[p];
                    
        //             cout <<endl;
        //             temp=1;
        //             break;
        //         }
        //     }
        //     if(temp==1) break;
        // }
        
        // for(int i=0;i<10;i++)
        // {
        //     for(int j=0;j<10;j++)
        //     {
        //         cout << Images_Array[i][j] << " ";
        //     }
        //     cout << endl;
        // }