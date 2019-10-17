#include <galaxy-explorer/AsteroidList.hpp>

AsteroidListItem::AsteroidListItem() {
    this->next = nullptr;
    this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
    this->next = nullptr;
    //Update asteroid data
    this->data = new Asteroid(a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity());
}

AsteroidListItem::~AsteroidListItem() {
    //Delete the head
    delete &(this->getData());
}

AsteroidList::AsteroidList() {

}

AsteroidList::AsteroidList(const AsteroidList& src) {
    
    this->operator=(src);
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the destructor (because you should put all your constructors together).
}

AsteroidList::~AsteroidList() {
    this->clear();
    // The functions in this class are listed in a suggested order of implementation,
    // except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {
    //Create a new asteroid list item e
    //Add the item after head
    AsteroidListItem *itemE = new AsteroidListItem(e);
    itemE->setNext(head.getNext());
    head.setNext(itemE);
}

Asteroid& AsteroidList::front() {
    //Return the first item of the list
    return (head.getNext())->getData();
}

const Asteroid& AsteroidList::front() const {
    //Return the first item of the list
    return (head.getNext())->getData();
}

bool AsteroidList::isEmpty() const {
    //Check if the item after the head is NULL return true
    if (head.getNext() == NULL) {
        return true;
    }
    return false;
}

int AsteroidList::size() const {
    //Create a temp object and point it to head
    const AsteroidListItem *temp = &head;
    int counter = 0;
    //goes across the linked list to until it reaches nullptr
    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
        counter++;//increments every time goes through the loop
    }
    return counter;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    //Returns head
    if (head.getNext() == nullptr) {
        return beforeEnd();
    }
    return &head;
    
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
    //Returns head
    if (head.getNext() == nullptr) {
        return beforeEnd();
    }
    
    return &head;
    
}

AsteroidListItem* AsteroidList::begin() {
    //Returns first item after head
    if (head.getNext() != nullptr) {
        return head.getNext();
    }
    //If list if empty returns nullptr
    return nullptr;
    
}

const AsteroidListItem* AsteroidList::begin() const {
    //Returns first item after head
    if (head.getNext() != nullptr) {
        return head.getNext();
    }
    //If list if empty returns nullptr
    return nullptr;
    
}

AsteroidListItem* AsteroidList::beforeEnd() {
    //Creates a temp list and loops through all the items and returns last item of the list
    AsteroidListItem *temp =  &head;
    //Returns head if the list if empty
    if (head.getNext() == nullptr) {
        return &head;
    }
    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
    }
    return temp;
    

}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    //Creates a temp list and loops through all the items and returns last item of the list
    const AsteroidListItem *temp =  &head;
    //Returns head if the list if empty
    if (head.getNext() == nullptr) {
        return &head;
    }
    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
    }
    return temp;
    
}

AsteroidListItem* AsteroidList::end() {
    //Creates a temp item and loops through the list to return the position after the last item
    AsteroidListItem *temp = &head;
    temp = &head;
    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
    }
    return temp->getNext();


}

const AsteroidListItem* AsteroidList::end() const {
    //Creates a temp item and loops through the list to return the position after the last item
    const AsteroidListItem *temp = &head;
    temp = &head;
    while (temp->getNext() != nullptr) {
        temp = temp->getNext();
    }
    return temp->getNext();
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    //Insert item e after prev
    AsteroidListItem *itemE = new AsteroidListItem(e);
    itemE->setNext(prev->getNext());
    prev->setNext(itemE);
    return itemE;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    //Get data from others and add them to prev
    const AsteroidListItem* temp = others.begin();

    //loops until others ends
    while (temp != nullptr) {
        this->insertAfter(prev, temp->getData());//Calls insertAfter function to add information from others to prev
        temp = temp->getNext();
        prev = prev->getNext();
    }
    return prev;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    //Points head to temp and manipulates temp to erase a particular item after prev from the 'this' list
    AsteroidListItem *temp = &head;
    AsteroidListItem *pptr = NULL;
    //if the list is empty just returns end
    if (head.getNext() != NULL) {
        while (temp != NULL) {
        //if the loop matches with item after prev it breaks
        if (temp == prev->getNext()) {
            break;
        }
        pptr = temp;
        temp = temp->getNext();
    }
    //skips the required value and continues the list
    pptr->setNext(temp->getNext());
    //deletes the value
    delete temp;
    temp = NULL;
    }
    else
    {
        return end();
    }
}

void AsteroidList::clear() {

    AsteroidListItem *temp = &head;
    AsteroidListItem *pptr = nullptr;
    //Goes through all the items of the list to delete them individually
    while (temp->getNext() != nullptr) {
        pptr = temp;
        temp = temp->getNext();
        if (pptr != &head) {
            delete pptr;
        }
        pptr = nullptr;
    }
    //Finally deletes temp
    if (temp != &head) 
    {
        delete temp;
        head.setNext(nullptr);
    }

}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {

    //If both lists are same it just returns the current list
    if (this == &src) {
        return (*this);
    }
    this->clear();
    this->insertAfter(&head, src);//Uses insert function to add src to the current list
    return (*this);//and returns the current list after adding src to the current list
}