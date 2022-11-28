#include <iostream>
#include "mesh.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
    string fileName;
    if (argc == 0) {
        fileName = "default.dat";
    } else {
        fileName = argv[0];
    }
    cout<<fileName<<endl;
    // Mesh Th;
    // Th.fromTecplot("first-396.dat");
    // Th.toTecplot("output.dat");
    return 0;
}