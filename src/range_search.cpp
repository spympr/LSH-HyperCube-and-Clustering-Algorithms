// #include <iostream>
// #include <string.h>
// #include <vector>
// #include <math.h>   
// #include <queue> 
// #include "../headers/exhausting.h"

// int ManhattanDistance(item* x,item* y,int dimensions)
// {
//     int sum=0;
//     for(int i=0;i<dimensions;i++)   sum+=abs(x[i]-y[i]);    
    
//     return sum;
// }

// void Approximate_LSH(infoptr info,item** Images_Range_Search)
// {   
//     for(int i=0;i<info->Num_of_Queries;i++)
//     {
//         item* temp_query = info->Queries_Array[i];
//         priority_queue<int, vector<int>, greater<int>> images; 

//         unsigned int gi_query_values[info->L];

//         gi_values_of_query(info, gi_query_values, i);

//         // for(int o=0;o<info->L;o++)  cout << gi_query_values[o] << " ";
//         // cout <<endl;

//         for(int j=0;j<info->L;j++)
//         {
//             if(info->Hash_Tables[j][gi_query_values[j]] != NULL)
//             {
//                 int images_in_bucket = info->Hash_Tables[j][gi_query_values[j]]->images.size();
//                 // cout << images_in_bucket << endl;
                
//                 for(int p=0; p<images_in_bucket;p++)
//                 {
//                     item* temp_image = info->Hash_Tables[j][gi_query_values[j]]->images[p];
//                     if(ManhattanDistance(temp_query,temp_image, info->dimensions) < info->R)
//                     // cout << " hh " << info->Hash_Tables[j][gi_query_values[j]]->images[p] << endl;
//                     images.push((ManhattanDistance(temp_query,temp_image, info->dimensions), (temp_image-info->Images_Array[0])/(info->dimensions*sizeof(item))+1));
//                 }
//             }
//         }

//         for(int k=0;k<info->N;k++)
//         {
//             Images_Range_Search[i][k] = images.top();

//             images.pop();
//         }
//     }

// }