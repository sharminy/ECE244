#include "TreeDB.h"

TreeDB::TreeDB() {
    root = NULL;
    probesCount = 0;
}

TreeDB::~TreeDB() {

    if (root == NULL)
        return;
    else {
        deleteTreeRoot(root);
        root = NULL;
    }

}

//Checks for appropriate position to insert the value

bool TreeDB::insert(DBentry* newEntry) {

    if (this->root == NULL) {
        TreeNode *current = new TreeNode(newEntry);
        this->root = current;
        this->root->setLeft(NULL);
        this->root->setRight(NULL);

        return true;
    }
    // Private helper function for recursion
    return insertHelper(newEntry, root);

}

bool TreeDB::insertHelper(DBentry *temp, TreeNode *current) {
    //When the value already exists outputs an error message
    if (temp->getName() == current->getEntry()->getName()) {

        delete temp;
        return false;
    }
    //if the value of the current value is smaller than parent value goes towards left
    if (temp->getName() < current->getEntry()->getName()) {
        if (current->getLeft() == NULL) {
            TreeNode *prev = new TreeNode(temp);
            current->setLeft(prev);
            return true;
        } else {
            insertHelper(temp, current->getLeft());
        }
    }//if the value of the current value is smaller than parent value goes towards right 
    else {
        if (current->getRight() == NULL) {
            TreeNode *prev = new TreeNode(temp);
            current->setRight(prev);
            return true;
        } else {
            insertHelper(temp, current->getRight());
        }
    }
}

DBentry* TreeDB::find(string name) {

    if (root != NULL) {
        return findHelper(name, root);
    } else {
        cout << "Error: entry does not exist" << endl;
        return NULL;
    }
}

DBentry* TreeDB::findHelper(string name, TreeNode *current) {
    if (current == NULL)
        return NULL;
    //If the value in the tree and given string equal outputs the value to be printed
    if (name == current->getEntry()->getName()) {
        probesCount++;
        return current->getEntry();
    }//If value on the tree is greater than the given value the tree pointers is pointed towards left of the tree by recursively calling it 
    else if (name < current->getEntry()->getName()) {
        if (current->getLeft() == NULL) {
            cout << "Error: entry does not exist" << endl;
            return NULL;
        } else {
            probesCount++;
            return findHelper(name, current->getLeft());
        }
    }//If value on the tree is greater than the given value the tree pointers is pointed towards right of the tree by recursively calling it
    else if (name > current->getEntry()->getName()) {
        if (current->getRight() == NULL) {
            cout << "Error: entry does not exist" << endl;
            return NULL;
        } else {
            probesCount++;
            return findHelper(name, current->getRight());
        }
    }
}

bool TreeDB::remove(string name) {
    if (root == NULL) {
        return false;
    }
    //Assigns a temp root the main root value to be manipulated and
    //Allocates space for a tempRoot, used to manipulate the tree values
    TreeNode *tempRoot = new TreeNode(NULL);

    if (secondaryRemove(tempRoot, name)) {
        delete tempRoot;
        tempRoot = NULL;
        return true;
    } else {
        return false;
    }
}

bool TreeDB::secondaryRemove(TreeNode *tempRoot, string name) {
    tempRoot->setLeft(root);
    if (root->removeHelper(name, tempRoot)) {
        root = tempRoot->getLeft();
        return true;
    } else {
        return false;
    }

}

bool TreeNode::removeHelper(string name, TreeNode* main) {
    //Checks for empty trees
    if (this == NULL) {
        return false;
    }
    //Depending upon the value of the string the function recursively reaches to the specific value in the tree and gets deallocated
    if ((name != entryPtr->getName())) {
        if (name > entryPtr->getName()) {
            return right->removeHelper(name, this);
        } else if (name < entryPtr->getName()) {
            return left->removeHelper(name, this);
        }
    }
    else if (name == entryPtr->getName()) {
        //Case1-if both values of last node's left and right is NULL, code dealloacates the node
        if (left == NULL && right == NULL) {
            delete this;
            this == NULL;
            if (main->getLeft() == this) {
                main->setLeft(NULL);
            }
            if (main->getRight() == this) {
                main->setRight(this);
            }
        }//Case2: If only the left value of the required node is NULL
        else if (left == NULL) {
            if (main->getLeft() == this) {
                main->setLeft(right);
            }
            if (main->getRight() == this) {
                main->setRight(right);
            }
            delete this;
            this == NULL;
        }//Case3: If only the right value of the required node is NULL
        else if (right == NULL) {
            if (main->getLeft() == this) {
                main->setLeft(left);
            }
            if (main->getRight() == this) {
                main->setRight(left);
            }
            delete this;
            this == NULL;
        }//Case4- If both end values of the required value arent NULL and the deleted value is replaced by the smallest value between the left and right side of the required node
            //Deallocation and assigning the positions for the nodes with both side values 
        else if (left != NULL && right != NULL) {
            removeHelperSecondary();
        }
        return true;
    }
}

void TreeNode::removeHelperSecondary() {
    TreeNode *leftmax = left->findMax();
    entryPtr->setActive(leftmax->getEntry()->getActive());
    entryPtr->setIPaddress(leftmax->getEntry()->getIPaddress());
    entryPtr->setName(leftmax->getEntry()->getName());
    left->removeHelper(leftmax->getEntry()->getName(), this);
}
//Returns the max value in the given this tree

TreeNode* TreeNode::findMax() {
    if (right != NULL) {
        return right->findMax();
    } else {
        return this;
    }
}
//Clears the tree, and deallocates the tree to null, to avoid memory leaks

void TreeDB::clear() {
    if (root == NULL)
        return;
    else {
        deleteTreeRoot(root);
        root = NULL;
    }
}

void TreeDB::deleteTreeRoot(TreeNode *root) {
    if (root == NULL) {
        return;
    }//Deallocates memory in ascending order
    else {
        deleteTreeRoot(root->getLeft());
        root->setLeft(NULL);
        deleteTreeRoot(root->getRight());
        root->setRight(NULL);
        delete root;
    }
}
//Prints out all the values in the tree by going to each and every value and using the print function declared in DBentry
void TreeDB::printAllVals() {
    if (root == NULL)
        return;
        //Calls print helper function to print
    else {
        printVals(root);
    }
}

void TreeDB::printVals(TreeNode *current) {
    //Goes to the lowest value of the tree and starts printing 
    if (current->getLeft() != NULL) {
        printVals(current->getLeft());
    }
    current->getEntry()->print();
    //Finally goes to the largest value
    if (current->getRight() != NULL) {
        printVals(current->getRight());
    }
}


//Checks if the tree is empty, if its not, it will send the the name, root value and the probe count to probe helper for recusion function
void TreeDB::printProbes(string name) {
    probesCount = 0;
    if (root != NULL) {
        if (find(name)) {
            cout << probesCount << endl;
            return;
        }

    } else {
        cout << "Error: entry does not exist" << endl;
    }
}


//Checks through the tree to find all the values with active status
void TreeDB::countActive() const {
    //Pointer value count carries the increment in count 
    int count = 0;
    int answer = 0;
    //If root is not empty  a recursive function sizeCount counts all the active positions by going the tree
    if (root != NULL) {
        answer = sizeCount(root, count);
    }
    cout << answer << endl;

}
//countActive helper function
int TreeDB::sizeCount(TreeNode *temp, int& count) const {
    if (temp != NULL)//if we are not at a leaf
    {
        if (temp->getEntry()->getActive()) {
            //Increments when the node is active
            count++;
        }

        sizeCount(temp->getLeft(), count); //recurisvly call the function and increment the count
        sizeCount(temp->getRight(), count);
    }

    return count; //return the count
}
//Uses the previously created find function to the find the value and assigns it to a temp pointed entry for changes to made   
void TreeDB::updatestatus(string name, string status) {
    DBentry *temp = find(name);
    bool active = false;
    if (status == "active") active = true;
    if (temp != NULL) {
        temp->setActive(active);
        cout << "Success" << endl;
    }
}
