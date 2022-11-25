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
    Mesh(/* args */);
    ~Mesh();
    void addNode(Point node);
    void addElement(Element elem);
    void fromTecplot(std::string fileName);
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

// Auxiliary function for reading Tecplot data.
std::string findPattern(std::ifstream& file, std::string pattern){
    std::string temp;
    while (file >> temp) {
        if (temp.find(pattern, 0) == 0) {
            break;
        }
    }
    return temp;
}

std::string cleanPrefix(std::string str) {
    while (str.length() > 0) {
        if (str.front() != '=') {
            str.erase(str.begin());
        } else {
            str.erase(str.begin());
            break;
        }
    }
    if (str.back() == ',') {
        str.pop_back();
    }
    return str;
}

int countVariable(std::ifstream& file){
    std::string s;
    int count = 0;
    findPattern(file, "VARIABLES");
    file >> s;
    while (true) {
        file >> s;
        if (s == "ZONE") {
            break;
        }
        count++;
    }
    return count;
}
void print(std::vector<float> arr){
    for (int i = 0; i < arr.size(); i++){
        std::cout<<arr[i]<<" ";
    }
    std::cout<<std::endl;
}
void Mesh::fromTecplot(std::string fileName){
    std::cout<<"Read file "<<fileName<<std::endl;
    std::ifstream tecFile(fileName);
    std::string dataPacking, s;
    int numVar, numNode, numElem;
    numVar = countVariable(tecFile);
    numNode = std::stoi( cleanPrefix( findPattern(tecFile, "Nodes") ) );
    numElem = std::stoi( cleanPrefix( findPattern(tecFile, "Elements") ) );
    dataPacking = cleanPrefix( findPattern(tecFile, "DATAPACKING") ); 
    findPattern(tecFile, "SINGLE");
    std::getline(tecFile, s); // Last header line.
    // Read data
    std::vector<float> row(numVar);
    std::vector<std::vector<float>> nodeData(numNode, row);
    if (dataPacking == "BLOCK") {
        for (int j = 0; j < numVar; j++){
            for (int i = 0; i <numNode; i++){
                tecFile >> nodeData[i][j];
            }
        }
    }
    for (int i = 0; i < numNode; i++) {
        this->addNode(Point(nodeData[i]));
    }
    // std::getline(tecFile, s); // 
    std::cout<<s<<std::endl;
    tecFile.close();
    this->sortElement();
}

