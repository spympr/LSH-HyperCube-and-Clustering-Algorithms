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

using namespace std;
using namespace std::chrono;

typedef int item;

#include "../headers/lsh.h"
#include "../headers/hypercube.h"

int ReverseInt(int);
void Read_BF(item***,int*,int*,int*,string,int a);
#endif