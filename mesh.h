#include <vector>
#include <string>
#include <fstream>
#include "math.h"

//---------------------------------------------------------------------
//-------------------------- quicksort vector -------------------------
template<typename T>
void swap(std::vector<T>& arr, int i, int j){
    T temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

template<typename T>
int partition(std::vector<T>& arr, int start, int end){
    T pivot = arr[start];
    int count = 0;
    for (int i = start + 1; i<=end; i++){
        if (arr[i] <= pivot){
            count++;
        }
    }
    int pivotIndex = start + count;
    swap<T>(arr, pivotIndex, start);
    int i = start;
    int j = end;
    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;
        }
        while (pivot <= arr[j]) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap<T>(arr, i++, j--);
        }
    }
    return pivotIndex;
}

template<typename T>
void quickSort(std::vector<T>& arr, int start, int end){
    if (start < end) {
        int pi = partition<T>(arr, start, end);
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}

template<typename T>
void quickSort(std::vector<T>& arr){
    quickSort<T>(arr, 0, arr.size() - 1);
}

//---------------------------------------------------------------------
//-------------------------- Point class ------------------------------
class Point{
public:
    int dim;
    std::vector<float> var;
    Point(std::vector<float> var);
    ~Point();
    float operator[](int index);
    Point operator+(Point otherPoint);
    Point operator-(Point otherPoint);
    Point operator*(float otherScala);
    Point operator/(float otherScala);
    bool operator==(Point otherPoint);
    void operator=(std::vector<float> otherVar);
};

Point::Point(std::vector<float> var){
    this->dim = var.size();
    this->var = var;
}

Point::~Point(){}

float Point::operator[](int index){
    return this->var[index];
}

Point Point::operator+(Point otherPoint){
    std::vector<float> outPoint(this->dim);
    for(int i=0; i<this->dim; i++){
        outPoint[i] = this->var[i] + otherPoint[i];
    }
    return Point(outPoint);
}

Point Point::operator-(Point otherPoint){
    std::vector<float> outPoint(this->dim);
    for(int i=0; i<this->dim; i++){
        outPoint[i] = this->var[i] - otherPoint[i];
    }
    return Point(outPoint);
}

Point Point::operator*(float otherScala){
    std::vector<float> outPoint(this->dim);
    for(int i=0; i<this->dim; i++){
        outPoint[i] = this->var[i] * otherScala;
    }
    return Point(outPoint);
}

Point Point::operator/(float otherScala){
    std::vector<float> outPoint(this->dim);
    for(int i=0; i<this->dim; i++){
        outPoint[i] = this->var[i] / otherScala;
    }
    return Point(outPoint);
}

void Point::operator=(std::vector<float> otherVar){
    this->var = otherVar;
}

float abs(Point a){
    float squareSum = 0;
    for(int i=0; i<a.dim; i++){
        squareSum += pow(a[i], 2);
    }
    return sqrt(squareSum);
}

bool Point::operator==(Point otherPoint){
    float eps = 1e-15;
    Point thisPoint = Point(this->var);
    if (abs(thisPoint-otherPoint) < eps){
        return true;
    } else {
        return false;
    }
}

float d(Point a, Point b){
    return abs(a - b);
}


//---------------------------------------------------------------------
//-------------------------- Element class ----------------------------
class Element{
private:
    /* data */
public:
    int numNode;
    std::vector<int> nodeID;
    Element(std::vector<int> nodeID);
    ~Element();
    int operator[](int index);
    bool operator<=(Element otherElement);
    bool operator==(Element otherElement);
};

Element::Element(std::vector<int> nodeID){
    quickSort(nodeID);
    this->nodeID = nodeID;
    this->numNode = nodeID.size();
}

Element::~Element(){
}

int Element::operator[](int index){
    return this->nodeID[index];
}

bool Element::operator<=(Element otherElement){
    // Comparison follows lexicography law on the minimum length
    int minLength = fmin(this->numNode, otherElement.numNode);
    bool equal = true;
    for (int i = 0; i < minLength; i++){
        if (this->nodeID[i] > otherElement[i]) {
            return false;
        } else if (this->nodeID[i] < otherElement[i]) {
            equal = false;
        }
    }
    if (equal) {
        return (this->numNode <= otherElement.numNode);
    } else {
        return true;
    }
}

bool Element::operator==(Element otherElement){
    if (this->numNode != otherElement.numNode) {
        return false;
    } else {
        for (int i = 0; i < this->numNode; i++){
            if (this->nodeID[i] != otherElement[i]) {
                return false;
            }
        }
    }
    return true;
}

//---------------------------------------------------------------------
//-------------------------- Mesh class -------------------------------
class Mesh{
private:
    /* data */
    void sortElement();
public:
    std::vector<Point> node;
    std::vector<Element> elem;
    int numNode, numElem, numVar, numElemNode;
    Mesh(/* args */);
    ~Mesh();
    void addNode(Point node);
    void addElement(Element elem);
    void fromTecplot(std::string fileName);
    void toTecplot(std::string fileName);
};

Mesh::Mesh(/* args */){}

Mesh::~Mesh(){}

void Mesh::sortElement(){
    quickSort<Element>(this->elem);
}

void Mesh::addNode(Point node){
    this->node.push_back(node);
}

void Mesh::addElement(Element elem){
    this->elem.push_back(elem);
}

bool matchPrefix(std::string str, std::string pattern){
    for (int i = 0; i < pattern.length(); i++) {
        if (str[i] != pattern[i]) {
            return false;
        }
    }
    return true;
}

std::string cleanStr(std::string str){
    while (str.front() != '=') {
        str.erase(str.begin());
    }
    str.erase(str.begin());
    while (str.back() != ',') {
        str.pop_back();
    }
    str.pop_back();
    return str;
}

void Mesh::fromTecplot(std::string fileName){
    std::ifstream tecFile(fileName);
    std::string s;
    this->numVar = 4;
    this->numElemNode = 2;
    do { // Read numver of nodes.
        tecFile >> s;
    } while (! matchPrefix( s, "Nodes"));
    this->numNode = std::stoi(cleanStr(s));

    do { // Read numver of elems.
        tecFile >> s;
    } while (! matchPrefix( s, "Faces"));
    this->numElem = std::stoi(cleanStr(s));

    do { // Move pointer to data part.
        tecFile >> s;
    } while (! matchPrefix( s, "SINGLE"));
    std::getline(tecFile, s);

    // Read node data.
    std::vector<float> tempPoint(this->numVar, 0);
    this->node.assign(this->numNode, Point(tempPoint));
    for (int j = 0; j < this->numVar; j++){
        for (int i = 0; i < this->numNode; i++){
            tecFile >> s;
            this->node[i].var[j] = std::stof(s);
        }
    }

    std::getline(tecFile, s);
    std::getline(tecFile, s);
    // Read elem data.
    std::vector<int> tempElem(this->numElemNode, 0);
    this->elem.assign(this->numElem, Element(tempElem));
    for (int i = 0; i < this->numElem; i++){
        for (int j = 0; j < this->numElemNode; j++){
            tecFile >> s;
            this->elem[i].nodeID[j] = std::stoi(s);
        }
    }

    tecFile.close();

    this->sortElement();
}

void Mesh::toTecplot(std::string fileName){
    std::ofstream tecFile(fileName);
    tecFile << "TITLE     = \"Tecplot Export\""<<std::endl;
    tecFile << "VARIABLES =";
    for (int i = 0; i < this->numVar; i++){
        tecFile << "\"var-" << i << "\"" << std::endl;
    }
    tecFile << "ZONE T=\"age of air\"" << std::endl;
    tecFile << "N=" << this->numNode << ", E="<<this->numElem<<" ,F=FEPoint ,ET=LINESEG" <<std::endl;
    // tecFile << "DATAPACKING=BLOCK" << std::endl;
    // tecFile << "DT=(SINGLE SINGLE SINGLE SINGLE )" << std::endl;

    // int countPerLine = 0, maxPerLine = 5;
    // for (int j = 0; j < this->numVar; j++){
    //     for (int i = 0; i < this->numNode; i++){
    //         tecFile << std::scientific << " " << this->node[i][j];
    //         countPerLine++;
    //         if (countPerLine == maxPerLine) {
    //             tecFile << std::endl;
    //             countPerLine = 0;
    //         }
    //     }
    //     if (countPerLine != 0) {
    //         countPerLine = 0;
    //         tecFile << std::endl;
    //     }
    // }

    for (int i = 0; i < this->numNode; i++){
        for (int j = 0; j < this->numVar; j++){
            tecFile <<" "<< this->node[i][j];
        }
        tecFile << std::endl;
    }

    for (int i = 0; i < this->numElem; i++){
        for (int j = 0; j < this->numElemNode; j++){
            tecFile <<" "<< this->elem[i][j];
        }
        tecFile << std::endl;
    }
    tecFile.close();
}