/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#5
* List.cpp 
* C++ source code file for List ADT program
*********************************************************************************/ 

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

#define frontelement -1
#define backelement -2

List::Node::Node(ListElement x){
    data = x;
    prev = nullptr;
    next = nullptr;  
}

List::List(){
    frontDummy = new Node(frontelement);
    backDummy = new Node(backelement);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new Node(frontelement);
    backDummy = new Node(backelement);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    Node* N = L.frontDummy->next;
    while( N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
}

List::~List(){
    moveFront();
    while(num_elements > 0){
        eraseAfter();
    }
    Node* N = frontDummy;
    Node* M = backDummy;
    delete N;
    delete M;
}

int List::length() const{
    return(num_elements);
}

ListElement List::front() const{
    if(num_elements == 0){
        throw std::length_error("List: front(): empty List");
    }
    return(frontDummy->next->data);
}

ListElement List::back() const{
    if(num_elements == 0){
        throw std::length_error("List: back(): empty List");
    }
    return(backDummy->prev->data);
}

int List::position() const{
    return(pos_cursor);
}

ListElement List::peekNext() const{
    if(pos_cursor >= num_elements){
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return(afterCursor->data);
}

ListElement List::peekPrev() const{
    if(pos_cursor <= 0){
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return(beforeCursor->data);
}

void List::clear(){
    moveFront();
    while(num_elements > 0){
        eraseAfter();
    }
}

void List::moveFront(){
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

void List::moveBack(){
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}

ListElement List::moveNext(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return(beforeCursor->data);
}

ListElement List::movePrev(){
    if(pos_cursor <= 0){
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return(afterCursor->data);
}

void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    if(num_elements == 0){
        N->prev = frontDummy;
        N->next = backDummy;
        frontDummy->next = N;
        backDummy->prev = N;

        beforeCursor = frontDummy;
        afterCursor = N;
        num_elements = 1;
        pos_cursor = 0;
    }
    else{
        N->next = afterCursor;
        N->prev = beforeCursor;
        beforeCursor->next = N;
        afterCursor->prev = N;

        afterCursor = N;
        num_elements++;
    }
}

void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    if(num_elements == 0){
        N->prev = frontDummy;
        N->next = backDummy;
        frontDummy->next = N;
        backDummy->prev = N;

        beforeCursor = N;
        afterCursor = backDummy;
        num_elements = 1;
        pos_cursor = 1;
    }
    else{
        N->prev = beforeCursor;
        N->next = afterCursor;
        beforeCursor->next = N;
        afterCursor->prev = N;

        beforeCursor = N;
        num_elements++;
        pos_cursor++;
    }
}

void List::setAfter(ListElement x){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: setAfter(): cursor position at back");
    }
    afterCursor->data = x;
}

void List::setBefore(ListElement x){
    if(pos_cursor <= 0){
        throw std::range_error("List: setBefore(): at front");
    }
    beforeCursor->data = x;
}

void List::eraseAfter(){
    if(pos_cursor >= num_elements){
        throw std::range_error("List: eraseAfter(): cursor positionat back");
    }
    Node* N = afterCursor;
    afterCursor = afterCursor->next;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    delete N;
}

void List::eraseBefore(){
    if(pos_cursor <= 0){
        throw std::range_error("List: eraseBefore(): cursor at front");
    }
    Node* N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    pos_cursor--;
    delete N;
}

int List::findNext(ListElement x){
    while(afterCursor != backDummy){
        moveNext();
        if(beforeCursor->data == x){
            return pos_cursor;
        }
    }
    if(beforeCursor->data == x){
        return pos_cursor;
    }
    else{
        return -1;
    }
}

int List::findPrev(ListElement x){
    while(beforeCursor != frontDummy){
        movePrev();
        if(afterCursor->data == x){
            return pos_cursor;
        }
    }
    if(afterCursor->data == x){
        return pos_cursor;
    }
    else{
        return -1;
    }
}
void List::cleanup(){
    int position = this->pos_cursor;
    Node* before = beforeCursor;
    Node* after = afterCursor;
    List L;

    moveFront();
    while(this->pos_cursor < this->num_elements){
        int data = moveNext();
        L.moveFront();
        int dup = L.findNext(data);

        if(dup == -1){
            L.insertAfter(data);
        }
        else{
            if(this->beforeCursor == before){
                before = beforeCursor->prev;
            }
            if(this->beforeCursor == after){
                after = beforeCursor->next;
            }
            if(this->pos_cursor <= position){
                position--;
            }
            eraseBefore();
        }
    }
    this->pos_cursor = position;
    this->beforeCursor = before;
    this->afterCursor = after;
   
}

List List::concat(const List& L) const{
    List J;
    Node* N = this->frontDummy->next;
    while(N != this->backDummy){
        J.insertBefore(N->data);
        N = N->next;
    }
    Node* M = L.frontDummy->next;
    while(M != L.backDummy){
        J.insertBefore(M->data);
        M = M->next;
    }
    J.moveFront();
    return J;
}

std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "(";

    for(N = frontDummy->next; N != backDummy->prev; N = N->next){
        s += std::to_string(N->data) + ", ";
    }
    s += std::to_string(N->data) + ")";

    return s;
}

bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy;
    M = M->next;
    while(eq && N!=nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=( const List& L ){
    if(this != &L){
        List temp = L;
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}