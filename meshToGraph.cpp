#include <iostream>
#include "mesh.h"
#include <vector>

using namespace std;

int main(){
    Mesh Th;
    Th.fromTecplot("first-396.dat");
    Th.toTecplot("output.dat");
    return 0;
}