#include <vector>
#include "math.h"



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

bool Point::operator==(Point otherPoint){
    float eps = 1e-15;
    if (abs(this->operator-(otherPoint)) < eps){
        return true;
    } else {
        return false;
    }
}

float abs(Point a){
    float squareSum = 0;
    for(int i=0; i<a.dim; i++){
        squareSum += pow(a[i], 2);
    }
    return sqrt(squareSum);
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
};

Element::Element(std::vector<int> nodeID){
    this->nodeID = nodeID;
    this->numNode = nodeID.size();
}

Element::~Element(){
}

template<typename T>
std::vector<T> quickSort(std::vector<T> arr){
    
}

