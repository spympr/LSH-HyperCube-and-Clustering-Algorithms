#ifndef READ_BINARY_FILE_H
#define READ_BINARY_FILE_H

#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>   
#include <random> 
#include <queue> 
#include <chrono> 
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <map>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h> 
#include <time.h>

using namespace std;
using namespace std::chrono;

enum Clustering_Method{lloyd_method,lsh_method,hc_method};

typedef int item;

#include "../headers/lsh.h"
#include "../headers/hypercube.h"
#include "../headers/ra_lsh.h"
#include "../headers/ra_hypercube.h"

int ReverseInt(int);
void Read_BF(item***,int*,int*,int*,string,int a);
#endif