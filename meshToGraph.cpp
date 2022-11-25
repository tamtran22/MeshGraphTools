#include <iostream>
#include "mesh.h"
#include <vector>

using namespace std;

int main(){
    vector<int> vecA = {1,3,4,5};
    vector<int> vecB = {1,3,4,5, 7,8};
    vector<int> vecC = {0,2,10,4,3,5};
    std::vector<Element> elem = {Element(vecA), Element(vecB), Element(vecC)};
    quickSort<Element>(elem);
    for (int i = 0; i < elem.size(); i++){
        for (int j = 0; j < elem[i].numNode; j++){
            cout<<elem[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}