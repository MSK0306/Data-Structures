#ifndef PQUEUE_CLASS
#define PQUEUE_CLASS
#include "node.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Element.h"
using namespace std;

template <class T>
class PQueue
{
    private:
    	// a linked list to hold the queue items
        Node<T>* queueFront;//pointer to the head of the list
        int count;//number of elements in the the queue

    public:
    	// constructor
        PQueue(void);

        // queue access methods
        void PQInsert(const T& item);//inserts the item in the correct position.
        T PQDelete(void);//Deletes the highest priority element at the queue front

        // queue access returns the highest priority element that is in the queue in O(1) time
        T PQFront(void);

        // queue test methods
        int PQLength(void) const;
        int PQEmpty(void) const;// return 1 iff the queue is empty
        void PQClear(void);//dynamically allocated memory for the nodes must be returned
        void ShowPQ (void) const; // prints the content of the priority queue from front to rear on the standard output (with cout)

};
//Initializing PQueue
template<class T>
PQueue<T>::PQueue(){
    queueFront=NULL;
    count=0;
}
//Defining PQInsert function
template<class T>
void PQueue<T>::PQInsert(const T& item){
if(count==0){
    Node<T> *temp;
    temp=new Node<T>(item,queueFront);
    queueFront=temp;
    count++;
}
else{
    if(!(item<queueFront->data)){
        Node<T> *temp;
        temp=new Node<T>(item,queueFront);
        queueFront=temp;
        count++;
    }
    else{
         Node<T> *temp;
         temp=new Node<T>(item);
         Node<T> *curr;
         Node<T> *prev;
         curr=queueFront;
         prev=NULL;
         while(curr->NextNode()!=NULL && item<curr->data){
            prev=curr;
            curr=prev->NextNode();
         }
         if(!(item<curr->data)){
            prev->InsertAfter(temp);
            count++;
         }
         else{
            curr->InsertAfter(temp);
            count++;
         }
    }
}
}
//Defining PQDelete function
template<class T>
T PQueue<T>::PQDelete(void){
if(PQLength()==0){
    cerr<<"Queue is empty!"<<endl;
    exit(1);
}
else
{

    //Node<T> *temp;
    T tempdata=queueFront->data;
    if(queueFront->NextNode()==NULL){
        delete queueFront;
        queueFront=NULL;
    }
    else{
        //temp=queueFront;
        queueFront=queueFront->NextNode();
        //delete temp;
    }
    count--;
    return tempdata;
}
}
//Defining PQFront
template<class T>
T PQueue<T>::PQFront(void){
    if(queueFront==NULL){
        cerr<<"Queue is empty!"<<endl;
        exit(1);
    }
    else{
        return queueFront->data;
    }
}
//Defining PQLength function
template<class T>
int PQueue<T>::PQLength(void) const{
return count;
}
//Defining PQEmpty
template<class T>
int PQueue<T>::PQEmpty(void) const{
if(count=0){
    return 1;
}
else{
    return 0;
}
}
//Defining PQClear
template<class T>
void PQueue<T>::PQClear(void){
    Node<T> *temp;
    temp=queueFront;
    while(queueFront!=NULL){
        queueFront=queueFront->NextNode();
        delete temp;
    }
    count=0;
}
//Defining ShowPQ
template<class T>
void PQueue<T>::ShowPQ(void) const{
    Node<T> *temp;
    temp=queueFront;
    while(temp!=NULL){
        cout<<temp->data.ShowData()<<endl;
        temp=temp->NextNode();
    }
}
#endif  // PQUEUE_CLASS
