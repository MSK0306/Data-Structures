#ifndef STACK_CLASS
#define STACK_CLASS
#include "node.h"
using namespace std;

template <class T>
class Stack
{
    private:
        // a linked list to hold the stack items
        Node<T>* stackTop; // deepmost element of the stack unless the stack is empty

    public:
    	// constructor
        Stack(void);

        // stack access methods
        void Push(const T& item);
        T Pop(void);
        T Peek(void);

        // stack test and clear methods
        int StackEmpty(void) const; // return 1 iff the stack is empty
        void ClearStack(void); //dynamically allocated memory for the nodes must be returned
        void ShowStack (void) const; // prints the content of the stack from top to bottom on the standard output (with cout)


};
// Initialize stackTop
template <class T>
Stack<T>::Stack(){
stackTop=NULL;
}
//Define Push function
template <class T>
void Stack<T>::Push(const T& item){
Node<T> *p;
p=new Node<T>(item,stackTop);
stackTop=p;
}

//Define Pop function
template <class T>
T Stack<T>::Pop(void){
Node<T> *temp;
T tempdata;
if(stackTop==NULL){
    cerr<<"Stack is already empty!"<<endl;
}
else{
    temp=stackTop;
    stackTop=temp->NextNode();
    tempdata=temp->data;
    delete temp;
    return tempdata;
}
}
//Define Peek function
template <class T>
T Stack<T>::Peek(void){
if(stackTop==NULL){
    cerr<<"Stack is empty!"<<endl;
    return 0;
}
else{
    return stackTop->data;//Data is public
}
}
//Define StackEmpty function
template<class T>
int Stack<T>::StackEmpty(void) const{
if(stackTop==NULL){
    return 1;
}
else{
    return 0;
}
}
//Define ClearStack function
template<class T>
void Stack<T>::ClearStack(void){
while(stackTop!=NULL){
    Node<T> *temp;
    temp=stackTop;
    stackTop=stackTop->NextNode();
    delete temp;
}
}
//Define ShowStack function
template<class T>
void Stack<T>::ShowStack(void) const{
    Node<T> *temp;
    temp=stackTop;
    while(temp!=NULL){
    cout<<temp->data<<endl;
    temp=temp->NextNode();
    }
    delete temp;
}

#endif  // STACK_CLASS
