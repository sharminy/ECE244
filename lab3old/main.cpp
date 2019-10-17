//

//  main.cpp skeleton

//  lab3

//

//  Created by Tarek Abdelrahman on 2018-08-25.

//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.

//


#include <iostream>

#include <sstream>

#include <string>


using namespace std;


#include "globals.h"

#include "shape.h"


// This is the shape array, to be dynamically allocated

shape** shapesArray;


// The number of shapes in the database, to be incremented

// everytime a shape is successfully created

int shapeCount = 0;


// The value of the argument to the maxShapes command

int max_shapes;


// ECE244 Student: you may want to add the prototype of

// helper functions you write here

bool commandCheck(string command);

bool invalidArg(stringstream &lineStream);




void maxVal(stringstream &lineStream);

void create(stringstream &lineStream);

void moveFunc(stringstream &lineStream);

void rotate(stringstream &lineStream);

void drawShape(stringstream &lineStream);

void deleteShape(stringstream &lineStream);


int main() {

    

    string line;

    string command;

    

    cout << "> ";         // Prompt for input

    getline(cin, line);   // Get a line from standard input

    

    while (!cin.eof()) {

        // Put the line in a lineStream for parsing

        // Making a new sstream for each line so the flags are cleared

        stringstream lineStream (line);

        

        // Read from string stream into the command

        // The only way this can fail is if the eof is encountered

        lineStream >> command;


        if (commandCheck(command))

        {

            if(command=="maxShapes")

            {

                maxVal(lineStream);

            }

            else if(command=="create")

            {

                create(lineStream);

            }

            else if(command=="move")

            {

                moveFunc(lineStream);

            }

            else if(command=="draw")

            {

                drawShape(lineStream);

            }

            else if(command=="delete")

            {

                deleteShape(lineStream);

            }

            else if(command=="rotate")

            {

                rotate(lineStream);

            }

        }

        else

        {

            cout<<"Error: invalid command\n";

        }

        // Check for the command and act accordingly

        // ECE244 Student: Insert your code here

        

        

        

        

        // Once the command has been processed, prompt for the

        // next command

        cout << "> ";          // Prompt for input

        getline(cin, line);   // Get the command line

        

    }  // End input loop until EOF.

    

    return 0;

}


bool commandCheck(string command)

{

    for(int i=0;i<7;i++)
    {
        if (command == keyWordsList[i])
        {
            return true;
        }
    }
    

    

    return false;

}


bool invalidArg(stringstream &lineStream )

{

    

    

    // Testing if the input type is wrong

    if (lineStream.fail()  ) {

        

        lineStream.clear();

        lineStream.ignore(190000000, '\n');

        cout << "Error: invalid argument"<< endl;

        

        return true;

    }

    // Testing if there is any invalid input right next to the correct input

    else if (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != -1) {

        

        lineStream.clear();

        lineStream.ignore(190000000, '\n');

        cout << "Error: invalid argument"<< endl;

        

        return true;

        

        

    }

    return false;

}

bool fewArg(stringstream &lineStream)

{

    

    // lineStream.peek gives a value '-1' if no character is read.

    if (lineStream.peek() == -1)

    {

        lineStream.clear(); // getting "-1" from "peek()" method might turn 'lineStream' into 'fail' mode

        cout << "Error: too few arguments" << endl;

        return true;

    }

    return false;

}

bool manyArg(stringstream & lineStream)

{

    // lineStream.peek gives a value '-1' if no character is read.

    if (lineStream.peek() != -1 && lineStream.peek() != '\n' && lineStream.peek() != '\t' && lineStream.peek() != ' ') {

        cout << "Error: too many arguments" << endl;

        return true;

    }

    return false;

}


void maxVal(stringstream &lineStream)

{

    int tempMaxShapes;

    

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>tempMaxShapes;

    

    if (invalidArg(lineStream))

    {

        return;

    }

    

    if (manyArg (lineStream))

    {

        return;

    }

    

    max_shapes=tempMaxShapes;

    if(shapesArray!=0)

    {

        for (int i=0; i<max_shapes; i++)

        {

            delete shapesArray[i];

        }

    }

    delete [] shapesArray;

    shapeCount=0;

    shapesArray=new shape* [max_shapes];

    

    cout<<"New database: max shapes is "<<max_shapes<<"\n";

    

}


/*these functions exclusive for create*/

bool nameExists(string tempName)

{

    for(int i=0;i<shapeCount;i++)

    {

        if(tempName==shapesArray[i]->getName())

        {

            cout << "Error: shape name exists" << endl;

            return true;

        }

    }

    return false;

}

bool nameCheck(string tempName)

{

    for(int i=0;i<7;i++)
    {
        if (tempName == keyWordsList[i])
        {
             cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    for(int j=0;j<3;j++)
    {
        if (tempName == shapeTypesList[j])
        {
             cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    
    return false;

}

bool typeCheck(string tempType)

{

    for(int j=0;j<3;j++)
    {
        if (tempType == shapeTypesList[j])
        {
             
            return false;
        }
    }

    cout << "Error: invalid shape type" << endl;

    return true;

}

bool maxCountCheck(int tempMaxCount,int tempShapeCount)

{

    if(tempShapeCount<tempMaxCount)

    {

        return false;

    }

    cout<< "Error: shape array is full"<<endl;

    

    return true;

}

void create(stringstream &lineStream)

{

    

    string nameFunc;

    string typeName;

    int x_loc_stream;

    int y_loc_stream;

    int x_siz_stream;

    int y_siz_stream;

    

    if(fewArg(lineStream))

    {

        return;

    }

    if(maxCountCheck(max_shapes, shapeCount))

    {

        return;

    }

    lineStream>>nameFunc;

    

    if(nameCheck(nameFunc))

    {

        return;

    }

    if(nameExists(nameFunc))

    {

        return;

    }

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>typeName;

    if(typeCheck(typeName))

    {

        return;

    }

    if(fewArg (lineStream))

    {

        return;

    }

    

    lineStream>> x_loc_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(fewArg (lineStream))

    {

        return;

    }

    

    lineStream>>y_loc_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(fewArg (lineStream))

    {

        return;

    }

    

    lineStream>>x_siz_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(fewArg (lineStream))

    {

        return;

    }

    

    lineStream>>y_siz_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if (manyArg (lineStream))

    {

        return;

    }

    shapesArray[shapeCount]= new shape(nameFunc,typeName,x_loc_stream,y_loc_stream,x_siz_stream,y_siz_stream);

    cout<<"Created "<<nameFunc<<": "<<typeName<<" "<<x_loc_stream<<" "<<y_loc_stream<<" "<<x_siz_stream<<" "<<y_siz_stream<<endl;

    shapeCount++;

}


int getNameIndex(string name) {

    for (int i=0; i< shapeCount; i++) {

        //comparing the name within the shapesArray

        string tempName = (*(shapesArray[i])).getName();

        if (tempName == name)

            return i;

        

    }

    cout << "Error: shape " << name << " not found" << endl;

    return -1; // if the shape doesn't exist

    

}

void moveFunc(stringstream &lineStream)

{

    string name;

    int x_loc_stream;

    int y_loc_stream;

    int moveIndex;

    

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>name;

    if(nameCheck(name))

    {

        return;

    }

    moveIndex=getNameIndex(name);

    if (moveIndex==-1)

    {

        return;

    }

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>> x_loc_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>y_loc_stream;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(manyArg(lineStream))

    {

        return;

    }

    

    (*shapesArray[moveIndex]).setXlocation(x_loc_stream);

    (*shapesArray[moveIndex]).setYlocation(y_loc_stream);

    

    cout<<"Moved "<<shapesArray[moveIndex]->getName()<<" to "<<shapesArray[moveIndex]->getXlocation()<<" "<<shapesArray[moveIndex]->getYlocation()<< endl;

}


bool valCheck(int tempAngle)

{

    if(tempAngle<0 || tempAngle>360)

    {

        cout << "Error: invalid value"<< endl;

        return true;

    }

    

    return false;

}

void rotate(stringstream &lineStream)

{

    string name;

    int angle;

    int rotateIndex;

    

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>name;

    if(nameCheck(name))

    {

        return;

    }

    rotateIndex=getNameIndex(name);

    if (rotateIndex==-1)

    {

        return;

    }

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>angle;

    if (invalidArg(lineStream))

    {

        return;

    }

    if(valCheck(angle))

    {

        return;

    }

    if(manyArg(lineStream))

    {

        return;

    }

    

    

    (*shapesArray[rotateIndex]).setRotate(angle);

    

    cout<<"Rotated "<<shapesArray[rotateIndex]->getName()<<" to "<<angle<<" degrees"<< endl;

}


void drawShape(stringstream &lineStream)

{

    string name;

    int drawIndex;

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>name;

    if(name!="all")

    {

        if(nameCheck(name))

        {

            return;

        }

        drawIndex=getNameIndex(name);

        if (drawIndex==-1)

        {

            return;

        }

        if(manyArg(lineStream))

        {

            return;

        }

        cout<<"Drew "<<shapesArray[drawIndex]->getName()<<endl;

        

        cout<<shapesArray[drawIndex]->getName()<<":"<<shapesArray[drawIndex]->getType()<<" "<<shapesArray[drawIndex]->getXlocation()<<" "<<shapesArray[drawIndex]->getYlocation()<<" "<<shapesArray[drawIndex]->getXsize()<<" "<<shapesArray[drawIndex]->getYsize()<< endl;

    }

    else if(name=="all")

    {

        if(manyArg(lineStream))

        {

            return;

        }

        cout<<"Drew all shapes"<<endl;

        for (int i=0; i<shapeCount; i++)

        {

            drawIndex=i;

            if(shapesArray[drawIndex]->getName()!="")

            {

            cout<<shapesArray[drawIndex]->getName()<<":"<<shapesArray[drawIndex]->getType()<<" "<<shapesArray[drawIndex]->getXlocation()<<" "<<shapesArray[drawIndex]->getYlocation()<<" "<<shapesArray[drawIndex]->getXsize()<<" "<<shapesArray[drawIndex]->getYsize()<< endl;

            }

        }

    }

    

}

void deleteShape(stringstream &lineStream)

{

    string name;

    int deleteIndex;

    if(fewArg(lineStream))

    {

        return;

    }

    

    lineStream>>name;

    if(name!="all")

    {

        if(nameCheck(name))

        {

            return;

        }

        deleteIndex=getNameIndex(name);

        if (deleteIndex==-1)

        {

            return;

        }

        if(manyArg(lineStream))

        {

            return;

        }

        cout<<"Deleted shape "<<shapesArray[deleteIndex]->getName()<<endl;

        shapesArray[deleteIndex]->setName("");

        delete shapesArray[deleteIndex];

    }

    else if(name=="all")

    {

        if(manyArg(lineStream))

        {

            return;

        }

        cout<<"Deleted: all shapes"<<endl;

        

        /*for (int i=0; i<shapeCount; i++)

        {

            deleteIndex=i;

            delete shapesArray[deleteIndex];

        }*/

        delete [] shapesArray;

        max_shapes=0;

        shapesArray=new shape* [max_shapes];

        shapeCount=0;

    }

    

}