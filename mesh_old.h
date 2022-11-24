#include <vector>
#include <initializer_list>
#include <iostream>
#include "math.h"



//---------------------------------------------------------------------
//-------------------------- Point class ------------------------------
class Point{
public:
    int dim;
    float x, y, z;
    Point(float x, float y, float z);
    Point(float x, float y);
    ~Point();
    Point operator+(Point other);
    Point operator-(Point other);
    Point operator*(float other);
    Point operator/(float other);
};

Point::Point(float x, float y, float z){
    this->dim = 3;
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(float x, float y){
    this->dim = 2;
    this->x = x;
    this->y = y;
    this->z = 0;
}

Point::~Point(){}

Point Point::operator+(Point other){
    if (this->dim == 2) {
        return Point(this->x + other.x, this->y + other.y);
    } else {
        return Point(this->x + other.x, this->y + other.y,
                            this->z + other.z);
    }
}

Point Point::operator-(Point other){
    if (this->dim == 2) {
        return Point(this->x - other.x, this->y - other.y);
    } else {
        return Point(this->x - other.x, this->y - other.y,
                            this->z - other.z);
    }
}

Point Point::operator*(float other){
    if (this->dim == 2) {
        return Point(this->x * other, this->y * other);
    } else {
        return Point(this->x * other, this->y * other,
                            this->z * other);
    }
}

Point Point::operator/(float other){
    if (this->dim == 2) {
        return Point(this->x / other, this->y / other);
    } else {
        return Point(this->x / other, this->y / other,
                            this->z / other);
    }
}

float abs(Point a){
    return sqrt(a.x**2 + a.y**2 + a.z**2);
}

float d(Point a, Point b){
    return abs(a - b);
}

void print(Point a){
    if (a.dim == 2) {
        std::cout<<a.x<<" "<<a.y<<std::endl;
    } else {
        std::cout<<a.x<<" "<<a.y<<" "<<a.z<<std::endl;
    }
}


//---------------------------------------------------------------------
//-------------------------- Element class ----------------------------
class Element{
private:
    /* data */
public:
    Element(/* args */);
    ~Element();
};

Element::Element(/* args */){
}

Element::~Element(){
}

