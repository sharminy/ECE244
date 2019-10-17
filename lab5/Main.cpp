
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include "TreeDB.h"

using namespace std;

//function prototypes
void insert(stringstream &lineStream, TreeDB *tree);
void find(stringstream &lineStream, TreeDB *tree);
void remove(stringstream &lineStream, TreeDB *tree);
void printprobes(stringstream &lineStream, TreeDB *tree);
void updatestatus(stringstream &lineStream, TreeDB *tree);

int main(int argc, char** argv) {
    TreeDB *treeDB = new TreeDB();
    string line, command;
    cout << " > ";
    getline(cin, line);

    //takes input from command line and processes it until eof has been reached
    while (!cin.eof()) {

        stringstream lineStream(line);
        lineStream >> command;

        if (command == "insert") {
            insert(lineStream, treeDB);
        } else if (command == "find") {
            find(lineStream, treeDB);
        } else if (command == "remove") {
            remove(lineStream, treeDB);
        } else if (command == "printall") {
            treeDB->printAllVals();
        } else if (command == "printprobes") {
            printprobes(lineStream, treeDB);
        } else if (command == "removeall") {
            treeDB->clear();
            cout << "Success" << endl;
        } else if (command == "countactive") {
            treeDB->countActive();
        } else if (command == "updatestatus") {
            updatestatus(lineStream, treeDB);
        } else
            ;


        cout << "> ";
        getline(cin, line);
    }
    //deallocating memory
    delete treeDB;
    treeDB = NULL;

}

//gets input from command line and creates a new dB entry item - inputs it into tree
void insert(stringstream &lineStream, TreeDB *treeDB) {
    string name, status;
    unsigned int IPaddress;
    bool active = false;
    lineStream >> name;
    lineStream >> IPaddress;
    lineStream >> status;

    if (status == "active") active = true;
    DBentry *newEntry = new DBentry(name, IPaddress, active);

    if (treeDB->insert(newEntry)) {
        cout << "Success" << endl;
    } else {
        cout << "Error: entry already exists" << endl;
    }

}

//finds item in tree

void find(stringstream &lineStream, TreeDB *treeDB) {
    string name;
    lineStream >> name;
    cout << (treeDB->find(name));
}

//removes item in tree

void remove(stringstream &lineStream, TreeDB *treeDB) {
    string name;
    lineStream >> name;
    if(treeDB->remove(name))
    {
        cout << "Success" << endl;
    } else {
        cout << "Error: entry does not exist" << endl;
    }
}

//prints number of probes the code passed through before reaching the given element in the tree

void printprobes(stringstream &lineStream, TreeDB *treeDB) {
    string name;
    lineStream >> name;
    treeDB->printProbes(name);
}

//updates the status of a particular domain

void updatestatus(stringstream &lineStream, TreeDB *treeDB) {
    string name, status;
    lineStream >> name;
    lineStream >> status;

    
    treeDB->updatestatus(name, status);
}
