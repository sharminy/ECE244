//
//  shape.cpp skeleton
//  lab3

#include <iostream>
#include <string>
using namespace std;

#include "shape.h"

// ECE244 Student:
// Write the implementation (and only the implementation) of the shape
// class below

shape::shape(string n, string t, int x_loc, int y_loc, int x_sz, int y_sz)
{
    name=n;                   // The name of the shape
    type=t;                   // The type of the shape (see globals.h)
    x_location=x_loc;                // The location of the shape on the x-axis
    y_location=y_loc;                // The location of the shape on the y-axis
    x_size=x_sz;                    // The size of the shape in the x-dimension
    y_size=y_sz;                    // The size of the shape in the y-dimension
    rotation = 0;
}
//from functions prototypes in shape.h create proper functions for mutators and accessors

//Accessor for type
string shape::getType()
{
    return type;
}
//Accessor for Name
string shape::getName()
{
    return name;
}
//Accessor for X Location
int shape::getXlocation()
{
    return x_location;
}
//Accessor for Y Location
int shape::getYlocation()
{
    return y_location;
}
//Accessor for X Size
int shape::getXsize()
{
    return x_size;
}
//Accessor for Y Size
int shape::getYsize()
{
    return y_size;
}

//Mutator for Name
void shape::setName(string n)
{
    name=n;
}
//Mutator for Type
void shape::setType(string t)
{
    type=t;
}
//Mutator for X Location
void shape::setXlocation(int x_loc)
{
    x_location=x_loc;
}
//Mutator for Y Location
void shape::setYlocation(int y_loc)
{
    y_location=y_loc;
}
//Mutator for X Size
void shape::setXsize(int x_sz)
{
    x_size=x_sz;
}
//Mutator for Y Size
void shape::setYsize(int y_sz)
{
    y_size=y_sz;
}
//Mutator for Rotation Angle
void shape::setRotate(int angle)
{
    rotation=0;
}

//Mutator for draw
void shape::draw()
{
    
}






