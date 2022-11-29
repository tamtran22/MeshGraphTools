#include <iostream>
#include "mesh.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    string fileInName, fileOutName;
    switch (argc){
    case 2:
        fileInName = argv[1];
        fileOutName = "output.dat";
        break;
    case 3:
        fileInName = argv[1];
        fileOutName = argv[2];
        break;
    default:
        fileInName = "input.dat";
        fileOutName = "output.dat";
        break;
    }
    cout<<"Reading datafile "<<fileInName<<", writing into "<<fileOutName<<endl;
    Mesh Th;
    Th.fromTecplot(fileInName);
    Th.toTecplot(fileOutName);
    return 0;
}