//
//  main.cpp skeleton
//  lab3.
//
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
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
bool invalidArg(stringstream & lineStream );
bool fewArg(stringstream &lineStream);
bool manyArg(stringstream & lineStream);
bool nameExists(string tempName);
bool nameCheck(string tempName);
bool typeCheck(string tempType);
bool maxCountCheck(int tempMaxCount, int tempShapeCount);
int getNameIndex(string name);
bool valCheck(int tempAngle);
bool numCheck(int tempNum);

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
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        
        lineStream >> command; //LineStream extracts the word and assigns it to command
        
        //Checks for the command viability by sending the command word to comandCheck Function
        if (commandCheck(command))
        {
            //Sends the rest of the lineStream to the appropritate functions based upon their command trigger
            // Once the command has been processed, prompt for the
            // next command
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
        
        cout << "> ";          // Prompt for input
        getline(cin, line);   // Get the command line
    }  // End input loop until EOF.
    return 0;
}
/*commandCheck Function checks throughout the list of commands whether the
input command mathches its list if it fails to do so, a flag is raised and
the program outputs an Error message as instructed in the lab manual */
bool commandCheck(string command)
{
    for (int i = 0; i < 7; i++)
    {
        if(command=="all")
        {
             return false;
        }
        else if (command == keyWordsList[i])
        {
            return true;
        }
    }
    return false;
}
/*invalidArg Function checks throughout lineStream for a invalid input, such
 as a string input for the place of a integer when an error is noticied due
 to the hehirarchy of the error arguments provided in the lab manual code
 further checks if the line ends beofre raising a flag. Furthermore, code
 checks for extra spaces and handles them with ease */
bool invalidArg(stringstream & lineStream )
{
    // Testing if the input type is wrong
    if (lineStream.fail() )
    {
        if(!lineStream.eof()) //Only outputs error if its the end of line as instructed in the lab manual
        {
            cout << "Error: invalid argument"<< endl;;
            return true;
        }
    }
    // Testing if there is any invalid input right next to the correct input
    else if (lineStream.peek() != ' ' && lineStream.peek() != '\n' && lineStream.peek() != -1)
    {
        cout << "Error: invalid argument"<< endl;
        return true;
    }
    return false;
}
/*fewArg function checks if there are less than the necessary amount of
 arguments required for the certain command and immedatiely raisese a flag */
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
/*manyArg function checks if there are more than the necessary amount of
 arguments required for the certain command and immedatiely raisese a flag */
bool manyArg(stringstream & lineStream)
{
    // lineStream.peek gives a value '-1' if no character is read.
    if (lineStream.peek() != -1 )
    {
        cout << "Error: too many arguments" << endl;
        return true;
    }
    return false;
}
/*nameExists function checks for the name given by the user and matches with
the database to see if the name already exists or not and raises a flag*/
bool nameExists(string tempName)
{
    //loop around all the values of shape array to get the name at each value and compare with user entered value
    for (int i = 0; i < shapeCount; i++)
    {
        if (tempName == shapesArray[i]->getName())//Flags when a match is found
        {
            cout << "Error: shape "<<tempName<<" exists" << endl;
            return true;
        }
    }
    return false;
}
/*nameCheck function checks for the name given by the user and matches with
 the command word database to see if the name is appropriate or not and raises
 a flag*/
bool nameCheck(string tempName)
{
    //loop around all the values of command and type database to get the name at each value and compare with user entered value
    for (int i = 0; i < 7; i++) {
        if (tempName == keyWordsList[i]) {//Flags when a match is found
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    for (int j = 0; j < 3; j++) {
        if (tempName == shapeTypesList[j]) {//Flags when a match is found
            cout << "Error: invalid shape name" << endl;
            return true;
        }
    }
    return false;
}
/*typeCheck function checks for the type given by the user and matches with
 the type  database to see if the name is appropriate or not and raises
 a flag*/
bool typeCheck(string tempType)
{
    //loop around all the values of type database to get the name at each value and compare with user entered value
    //Flags when a match is not found
    for (int j = 0; j < 3; j++) {
        if (tempType == shapeTypesList[j])
        {
            return false;
        }
    }
    cout << "Error: invalid shape type" << endl;
    return true;
}
/*maxCountCheck function constantly checks whether the creation of shapes
 have reached the limit of maximum shapes enetered by the user*/
bool maxCountCheck(int tempMaxCount, int tempShapeCount)
{
    //Flags when a match is not found
    if (tempShapeCount < tempMaxCount)
    {
        return false;
    }
    cout << "Error: shape array is full" << endl;
    return true;
}
/* getNameIndex fuctions serves the task of getting the position in the
 shape array where a certain shape name is found and returns the vlaue
 to called upon function*/
int getNameIndex(string name)
{
    //Loops acrross all the vlaues of the shape array
    for (int i=0; i< shapeCount; i++) {
        //comparing the name within the shapesArray
        string tempName = (*(shapesArray[i])).getName();
        if (tempName == name)
        {
            return i;
        }
    }
    cout << "Error: shape " << name << " not found" << endl;
    return -1; // if the shape doesn't exist (flag)
}
/*valCheck functions checks if the integer value entered for rotation of
 the shape is within the bounds of >0 and <360*/
bool valCheck(int tempAngle)
{
    if(tempAngle<0 || tempAngle>360)//A flag is is rasised if the conditions are not met
    {
        cout << "Error: invalid value"<< endl;
        return true;
    }
    return false;
}
/*numCheck functions checks if the integer value entered is greater than 0*/
bool numCheck(int tempNum)
{
    if(tempNum<0)//A flag is is rasised if the conditions are not met
    {
        cout << "Error: invalid value"<< endl;
        return true;
    }
    return false;
}


/*maxVal functions gets the maximum number of shapes that user enters
 and assigns to the shape array*/
void maxVal(stringstream &lineStream)
{
    int tempMaxShapes;
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    lineStream>>tempMaxShapes;//Value Assigning
    //Error Checking
    if (invalidArg(lineStream))
    {
        return;
    }
    if (manyArg (lineStream))
    {
        return;
    }
    //Clears the array of all the previous values before assiging new value
    max_shapes=tempMaxShapes;
    if(shapesArray!=0)
    {
        for (int i=0; i<max_shapes; i++)
        {
            delete shapesArray[i];
        }
    }
    delete [] shapesArray;
    //Assigns new value and starts shapeCount counter
    shapeCount=0;
    shapesArray=new shape* [max_shapes];
    //Output message as indicated in the lab manual
    cout<<"New database: max shapes is "<<max_shapes<<"\n";
}
/*create function takes inputs from the user and constantly checks for
 any errors and if no flags are reaised the code creates shape based
 upon the requirements given by the user*/
void create(stringstream & lineStream)
{
    //Variable Declaration
    string nameFunc;
    string typeName;
    int x_loc_stream;
    int y_loc_stream;
    int x_siz_stream;
    int y_siz_stream;
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    if(maxCountCheck(max_shapes, shapeCount))
    {
        return;
    }
    lineStream>>nameFunc;//Value Assigning
    //Error Checking
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
    
    lineStream>>typeName;//Value Assigning
    //Error Checking
    if(typeCheck(typeName))
    {
        return;
    }
    if(fewArg (lineStream))
    {
        return;
    }
    
    lineStream>> x_loc_stream;//Value Assigning
    //Error Checking
    if (invalidArg(lineStream)==true)
    {
        return;
    }
    if(numCheck(x_loc_stream))
    {
        return;
    }
    if(fewArg (lineStream))
    {
        return;
    }
    
    lineStream>>y_loc_stream;//Value Assigning
    //Error Checking
    if (invalidArg(lineStream))
    {
        return;
    }
    if(numCheck(y_loc_stream))
    {
        return;
    }
    if(fewArg (lineStream))
    {
        return;
    }
    
    lineStream>>x_siz_stream;//Value Assigning
    //Error Checking
    if (invalidArg(lineStream))
    {
        return;
    }
    if(numCheck(x_siz_stream))
    {
        return;
    }
    if(fewArg (lineStream))
    {
        return;
    }
    
    lineStream>>y_siz_stream;//Value Assigning
    //Error Checking
    if ( invalidArg(lineStream))
    {
        return;
    }
    if(numCheck(y_siz_stream))
    {
        return;
    }
    if (manyArg (lineStream))
    {
        return;
    }
    //If all the error cases fail the code excutes the creation by sending the values to the shape array of the class shape.cpp
    shapesArray[shapeCount]= new shape(nameFunc,typeName,x_loc_stream,y_loc_stream,x_siz_stream,y_siz_stream);
    //Outputs a message indicating the creation of the shape
    cout<<"Created "<<nameFunc<<": "<<typeName<<" "<<x_loc_stream<<" "<<y_loc_stream<<" "<<x_siz_stream<<" "<<y_siz_stream<<endl;
    //increments the number of shapes that have been created
    shapeCount++;
}
/*moveFunc function checks for the validy of the user input
 and excutes the move if no flags are raised*/
void moveFunc(stringstream &lineStream)
{
    //Variable Declaration
    string name;
    int x_loc_stream;
    int y_loc_stream;
    int moveIndex;
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    
    lineStream>>name;//Value Assigning
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
    
    lineStream>> x_loc_stream;//Value Assigning
    //Error Checking
    if ( invalidArg(lineStream))
    {
        return;
    }
    if(numCheck(x_loc_stream))
    {
        return;
    }
    if(fewArg(lineStream))
    {
        return;
    }
    
    lineStream>>y_loc_stream;//Value Assigning
    //Error Checking
    if (invalidArg(lineStream))
    {
        return;
    }
    if(numCheck(y_loc_stream))
    {
        return;
    }
    if(manyArg(lineStream))
    {
        return;
    }
    //if all the error  flags fail the code changes the locations of the shape
    (*shapesArray[moveIndex]).setXlocation(x_loc_stream);
    (*shapesArray[moveIndex]).setYlocation(y_loc_stream);
    //Outputs a message indicating the creation of the shape
    cout<<"Moved "<<shapesArray[moveIndex]->getName()<<" to "<<shapesArray[moveIndex]->getXlocation()<<" "<<shapesArray[moveIndex]->getYlocation()<< endl;
}

void rotate(stringstream &lineStream)
{
    //Variable Declaration
    string name;
    int angle;
    int rotateIndex;
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    
    lineStream>>name;//Value Assigning
    //Error Checking
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
    
    lineStream>>angle;//Value Assigning
    //Error Checking
    if ( invalidArg(lineStream))
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
    //if all the error flags fail the code changes the rotation of the shape
    (*shapesArray[rotateIndex]).setRotate(angle);
    //Outputs a message indicating the creation of the shape
    cout<<"Rotated "<<shapesArray[rotateIndex]->getName()<<" to "<<angle<<" degrees"<< endl;
}
/*drawShape function draws out the shape based on users command of all or a certain shape*/
void drawShape(stringstream &lineStream)
{
    //Variable Declaration
    string name;
    int drawIndex;
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    
    lineStream>>name;//Value Assigning
    if(name!="all") //Checks if its all
    {
        //if not all reads the name and draws that particular shape
        //Error Checking
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
        //Outputs the drawing of the shape
        cout<<"Drew "<<shapesArray[drawIndex]->getName()<<endl;
        cout<<shapesArray[drawIndex]->getName()<<": "<<shapesArray[drawIndex]->getType()<<" "<<shapesArray[drawIndex]->getXlocation()<<" "<<shapesArray[drawIndex]->getYlocation()<<" "<<shapesArray[drawIndex]->getXsize()<<" "<<shapesArray[drawIndex]->getYsize()<< endl;
    }
    else if(name=="all")//if the command is all
    {
        //Error Checking
        if(manyArg(lineStream))
        {
            return;
        }
        //Outputs the drawing of all the if the shape array space name is not epmty (deleted ones)
        cout<<"Drew all shapes"<<endl;
        for (int i=0; i<shapeCount; i++) //Loops around the shape array
        {
            drawIndex=i;
            if(shapesArray[drawIndex]->getName()!="") //Outputs the drawing of the shape
            {
                cout<<shapesArray[drawIndex]->getName()<<": "<<shapesArray[drawIndex]->getType()<<" "<<shapesArray[drawIndex]->getXlocation()<<" "<<shapesArray[drawIndex]->getYlocation()<<" "<<shapesArray[drawIndex]->getXsize()<<" "<<shapesArray[drawIndex]->getYsize()<< endl;
            }
        }
    }
}
/*deleteShape function deletes out the shape based on users command of all or a certain shape*/
void deleteShape(stringstream &lineStream)
{
    //Variable Declaration
    string name;
    int deleteIndex;
    
    //Error Checking
    if(fewArg(lineStream))
    {
        return;
    }
    
    lineStream>>name;//Value Assigning
    //Error Checking
    if(name!="all")//Checks if its all
    {
        //if not all reads the name and deletes that particular shape
        //Error Checking
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
        //Outputs the message for the deleted shape
        cout<<"Deleted shape "<<shapesArray[deleteIndex]->getName()<<endl;
        shapesArray[deleteIndex]->setName("");
        delete shapesArray[deleteIndex];
    }
    else if(name=="all")//if the command is all
    {
        //Error checking
        if(manyArg(lineStream))
        {
            return;
        }
        //Outputs the message for the deleted shapes
        cout<<"Deleted: all shapes"<<endl;
        //Deletes the values of the array and resets all the counters to 0
        delete [] shapesArray;
        max_shapes=0;
        shapesArray=new shape* [max_shapes];
        shapeCount=0;
    }
}
