#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<vector<int> > v;
    vector<int> x;
    //for(int i=0;i<5;i++)
    //    v.push_back(x);
    cout<<v.size()<<endl;
    for(int i=0;i<5;i++)
        v[i].push_back(i);
    cout<<v.size()<<endl;
    for(int i=0;i<5;i++)
        cout<<v[i].size()<<endl;

    return 0;
}