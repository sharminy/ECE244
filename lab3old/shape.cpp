//

//  shape.cpp skeleton

//  lab3

//

//  Created by Tarek Abdelrahman on 2018-08-25.

//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.

//


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


string shape::getType()

{

    return type;

}

string shape::getName()

{

    return name;

}


int shape::getXlocation()

{

    return x_location;

}

int shape::getYlocation()

{

    return y_location;

}

int shape::getXsize()

{

    return x_size;

}

int shape::getYsize()

{

    return y_size;

}


void shape::setName(string n)

{

    name=n;

}

void shape::setType(string t)

{

    type=t;

}

void shape::setXlocation(int x_loc)

{

    x_location=x_loc;

}

void shape::setYlocation(int y_loc)

{

    y_location=y_loc;

}

void shape::setXsize(int x_sz)

{

    x_size=x_sz;

}

void shape::setYsize(int y_sz)

{

    y_size=y_sz;

}

void shape::setRotate(int angle)

{

    rotation=0;

}



void shape::draw()

{

    

}


