#include "DBentry.h"

DBentry::DBentry() {
    
}

DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active) {
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}

// the destructor
DBentry::~DBentry() 
{
    
}
// sets the domain name, which we will use as a key.
void DBentry::setName(string _name) {
    name = _name;
}

// sets the IPaddress data.
void DBentry::setIPaddress(unsigned int _IPaddress) {
    IPaddress = _IPaddress;
}

// sets whether or not this entry is active.
void DBentry::setActive(bool _active) {
    active = _active;
}

// returns the name.
string DBentry::getName() const {
    return name;
}

// returns the IPaddress data
unsigned int DBentry::getIPaddress() const {
    return IPaddress;
}

// returns whether or not this entry is active
bool DBentry::getActive() const {
    return active;
}


//prints out a node from the tree
void DBentry::print() {
    if (this != NULL) {
        if (this->active) {
            cout << name << " : " << IPaddress << " : " << "active" << endl;
        } else {
            cout << name << " : " << IPaddress << " : " << "inactive" << endl;
        }
    }
}

//prints out all the values of the tree in ascending order
ostream& operator<<(ostream& out, DBentry *rhs) {
    if (rhs != NULL) {
        if (rhs->getActive()) {
            return out << rhs->getName() << " : " << rhs->getIPaddress() << " : " << "active" << endl;
        } else {
            return out << rhs->getName() << " : " << rhs->getIPaddress() << " : " << "inactive" << endl;
        }
    }
}