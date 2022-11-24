#include <iostream>
#include "mesh.h"
#include <vector>

using namespace std;

int main(){
    vector<float> vecA = {1,5,6,3,6,2};
    // Point a = Point(vecA);
    // Point b = Point(vecA);
    // if (a==b){
    //     cout<<"bang nhau ne"<<endl;
    // }
    quickSort<float>(vecA);
    for (int i = 0; i < vecA.size(); i++){
        cout<<vecA[i]<<endl;
    }
    return 0;
}