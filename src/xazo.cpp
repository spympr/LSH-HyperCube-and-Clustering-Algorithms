#include <iostream>
#include <map>
using namespace std;
int main()
{
    // for(int i=0;i<=0;i++)
    // {
    //     cout<< "geia\n";
    // }
    map <int,int> points;
    points.insert(make_pair(1,1));
    points[1] = 1;

    cout << points.at(1) << endl;
    points[1] = 2;
    cout << points.at(1) << endl;
}