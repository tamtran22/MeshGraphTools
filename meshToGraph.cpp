#include <iostream>
#include "mesh.h"
#include <vector>

using namespace std;

int main(){
    Mesh Th;
    Th.fromTecplot("first-396.dat");
    return 0;
}