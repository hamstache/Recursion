//
//  main.cpp
//  LinkedLists
//
//  Created by Josh on 8/18/15.
//  Copyright (c) 2015 Hamstache. All rights reserved.
//

#include <iostream>
using namespace std;

//SINGLY LINKED LIST -------------------------------------------------------------
template <typename E>
class SLinkedList {
public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const E& front() const;
    void addFront(const E& e);
    void removeFront();
private:
    struct node {
        E data;
        node* next;
    };
    node* head;
};

template <typename E>
SLinkedList<E>::SLinkedList()
: head(NULL) { }

template <typename E>
bool SLinkedList<E>::empty() const
{ return head == NULL; }

template <typename E>
const E& SLinkedList<E>::front() const
{return head->data;}


template <typename E>
SLinkedList<E>::~SLinkedList<E>()
{while (!empty()) removeFront(); }

template <typename E>
void SLinkedList<E>::addFront(const E& e) {
    node* v = new node;
    v->data = e;
    v->next = head;
    head = v;
}

template <typename E>
void SLinkedList<E>::removeFront() {
    node* old = head;
    head = old->next;
    delete old;
}

//DOUBLY LINKED LIST -------------------------------------------------------------
typedef string Elem;//list element type
class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const Elem& front() const;
    const Elem& back() const;
    void addFront(const Elem& e);
    void addBack(const Elem& e);
    void removeFront();
    void removeBack();
private:
    struct NODE {
        Elem elem;
        NODE* prev;
        NODE* next;
    };
    NODE* header;
    NODE* trailer;
protected:
    void add(NODE* v, const Elem& e);
    void remove(NODE* v);
};

DLinkedList::DLinkedList() {
    header = new NODE;
    trailer = new NODE;
    header->next = trailer;
    trailer->prev = header;
}
DLinkedList::~DLinkedList() {
    while(!empty()) removeFront();
    delete header;
    delete trailer;
}
bool DLinkedList::empty() const
{return (header->next == trailer); }

const Elem& DLinkedList::front() const
{return header->next->elem; }

const Elem& DLinkedList::back() const
{return trailer->prev->elem; }

void DLinkedList::add(NODE* v, const Elem& e) {
    NODE* u = new NODE; u->elem = e;
    u->next = v; //put new node before v....x U -> v
    u->prev = v->prev;//put new node after the node that was previously behind v...x <- U v
    v->prev->next = u;//have x now point to u instead of v... x -> U v
    v->prev = u; //now have v point pack to u instead of x... x U <- v
    //now we are perfectly linked wherever :)
}
void DLinkedList::addFront(const Elem &e)
{ add(header->next, e); }
void DLinkedList::addBack(const Elem& e)
{ add(trailer, e); }

void DLinkedList::remove(NODE* v) {
    NODE* u = v->prev;
    NODE* w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}
void DLinkedList::removeFront()
{ remove(header->next); }
void DLinkedList::removeBack()
{ remove(trailer->prev); }

//CIRCULARLY LINKED LISTS------------------------------------------------------------

typedef string Element;
class CircleList {
public:
    CircleList();
    ~CircleList();
    bool empty() const;
    const Element& front() const; //element at cursor
    const Element& back() const; //element following cursor
    void advance(); //advance cursor
    void add(const Element& e); //add after cursor
    void remove(); //remove node after cursor
private:
    struct CNODE {
        Element elem;
        CNODE* next;
    };
    CNODE* cursor;
};

CircleList::CircleList()
: cursor(NULL) { }
CircleList::~CircleList()
{ while (!empty()) remove(); }

bool CircleList::empty() const
{ return cursor == NULL; }
const Element& CircleList::back() const
{ return cursor->elem; } //element at cursor
const Element& CircleList::front() const
{ return cursor->next->elem; } //element following cursor
void CircleList::advance()
{ cursor = cursor->next; }
void CircleList::add(const Element& e) {
    CNODE* v = new CNODE;
    v->elem = e;
    if (cursor == NULL){
        v->next = v;
        cursor = v;
    }
    else {
        v->next = cursor->next;
        cursor->next = v;
    }
}
void CircleList::remove() {
    CNODE* old = cursor->next;
    if (old == cursor)
        cursor = NULL;
    else
        cursor->next = old->next;
    delete old;
}

//REVERSING A LINKED LIST -- COPYING FIRST ELEMENT AND PUT INTO FRONT OF ANOTHER LIST THEN COPY BACK (actually copy to front....the book fucked up) BUT TO THE BACK OF THE LIST
void listReverse(DLinkedList& L) {
    DLinkedList T;
    while (!L.empty()) {
        string s = L.front();
        L.removeFront();
        T.addFront(s);
    }
    while(!T.empty()) {
        string s = T.front();
        T.removeFront();
        L.addFront(s);
    }
}

//FACTORIAL RECURSION---------------------------------------------------------------

int recursiveFactorial(int n) {
    if (n == 0) return 1;
    else return n * recursiveFactorial(n-1);
}

//DRAWING A RULER RECURSION (this makes no sense rn)-------------------------------

void drawOneTick(int tickLength, int tickLabel = -1) {
    for (int i = 0; i<tickLength; i++)
        cout<<"-";
    if (tickLabel >= 0) cout << " " << tickLabel;
    cout<<endl;
}
void drawTicks(int tickLength) {
    if (tickLength > 0 ) {
        drawTicks(tickLength-1);
        drawOneTick(tickLength);
        drawTicks(tickLength-1);
    }
}
void drawRuler(int nInches, int majorLength) {
    drawOneTick(majorLength, 0);
    for (int i = 1;i<=nInches;i++) {
        drawTicks(majorLength-1);
        drawOneTick(majorLength, i);
    }
}

//LINEAR RECURSION

int linearRecursion(int A[], int n) {
    if (n == 1) {
        return A[0];
    }
    else {
        return linearRecursion(A, n-1) + A[n-1];
    }
}

void reverseArray(int A[], int i, int j) {
    if (i<j) {
        swap(A[i], A[j]);
        reverseArray(A, i+1, j-1);
    }
    return;
}
//Tail recursion = an algorithm that uses linear recursion and the algorithm makes a recursive call as the very last operation before it returns.

void IterativeReverseArray(int A[], int i, int j){
    while(i<j){
        swap(A[i], A[j]);
        i++;
        j--;
    }
}

//Binary Recusion = when an algorithm makes TWO recursive calls



int main() {
    SLinkedList<string> a;
    a.addFront("MSP");
    cout << a.front()<<endl;
    
    SLinkedList<int> b;
    b.addFront(666);
    cout << b.front() << endl;
    
    a.removeFront();
    b.removeFront();
    
    DLinkedList aa;
    Elem info = "demo";
    aa.addFront(info);
    DLinkedList bb;
    Elem info2 = "dashie";
    bb.addFront(info2);
    cout<<"The elements in the list: " <<endl;
    
    cout << aa.front() << " " << bb.front() << endl;
    aa.addFront("milk");
    aa.addFront("cookies");
    aa.addFront("soda");
    aa.addFront("chips");
    
    listReverse(aa);
    cout<<aa.front() << endl;
    
    CircleList playList;
    playList.add("Stayin Alive");
    playList.add("Le Freak");
    playList.add("Jive Talkin");
    
    playList.advance();
    playList.advance();
    playList.remove();
    playList.add("Disco Inferno");
    
    int n = 6;
    cout<< recursiveFactorial(n) <<" "<< recursiveFactorial(0) << endl;
    
    cout<<endl;
    drawRuler(2, 4);
    
    int A[] = {4,3,6,2,5};
    cout<< linearRecursion(A,5)<<endl;
    
    reverseArray(A, 0, 4);
    for (int i = 0;i<5;i++){
        cout<<A[i];
    }
    cout<<endl;
    IterativeReverseArray(A, 0, 4);
    for (int i = 0;i<5;i++){
        cout<<A[i];
    }
    
    return 0;
}
