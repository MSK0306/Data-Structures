//Muhammed Saadeddin Koçak 2232346
#include <iostream>

using namespace std;

//Implementation of Queue
template <class T>
class Queue
{
    private:
        int front;
        int rear;
        int count;
        T queueList[1000];
    public:
        Queue();
        const int length = 1000;
        void insert(const T& item);
        T Delete();
        T QFront() const;
        int QueueLength();
        bool QueueEmpty();
        bool QueueFull();
};

template <class T>
Queue<T>::Queue(): front(0),rear(0),count(0) {};

template <class T>
void Queue<T>::insert(const T& item) {
    if(count == length) {
        cerr << "Queue is full!" << endl;
    }
    else {
        count++;// Counting number of objects in array. In this way we are always aware of Queue limits.
        queueList[rear] = item;
        rear = (rear+1)%length;// % symbol is used to be able to use array in circular manner.
    }
}

template <class T>
T Queue<T>::Delete() {
    T temp;
    if(count == 0) {
        cerr << "Queue is empty!" << endl;
    }
    else {
        count--;
        temp = queueList[front];
        front = (front+1)%length;// % symbol is used to be able to use array in circular manner.
        return temp;
    }

}

template <class T>
int Queue<T>::QueueLength() {
    return length;
}

template <class T>
bool Queue<T>::QueueEmpty() {
    if(count == 0)
        return true;
    else
        return false;
}

template <class T>
bool Queue<T>::QueueFull() {
    if(count == length)
        return true;
    else
        return false;
}

template <class T>
T Queue<T>::QFront() const {
    return queueList[front];
}

//Student Class Implementation
class Student
{public:
int studentID;
bool record_valid;
int index;
Student (int ID=0, bool valid=false, int i=-1){
studentID=ID;
record_valid=valid;
index=i;
};//constructor
};


class StudentRecord
{public:
bool valid;
int studentID;
char studentName [100];
int studentGrades[3];/*array element i stores the grade of course id i (course ids are selected from 0 to 2).*/
StudentRecord (bool v=false, int ID=0, char* name="", int grade1=0, int grade2=0, int grade3=0){
valid=v;
studentID=ID;
int i;
    while(name[i]!=NULL){
        studentName[i]=name[i];
        i++;
    }
studentGrades[0]=grade1;
studentGrades[1]=grade2;
studentGrades[2]=grade3;
}//constructor};
};

template <class T>
class BTreeNode
{
public:
BTreeNode<T> * Children[3];
T data[2];
// constructor initializes all children pointers to null, inserts the items in the data field of the BTreeNode in the correct order
BTreeNode (T* items, BTreeNode<T> ** C){//First initialize Children
    Children[0]=C[0];
    Children[1]=C[1];
    Children[2]=C[2];
    if(items[0].studentID==0){//If first item is empty insert second item to first data
        data[0]=items[1];
        data[1]=items[0];
    }
    else if(items[1].studentID==0){//If second item is empty insert first item to first data
        data[0]=items[0];
        data[1]=items[1];
    }
    else if(items[1].studentID<items[0].studentID){//If items order is reverse insert in reverse order
        data[0]=items[1];
        data[1]=items[0];
    }
    else{//If items are ordered insert them to data in order
        data[0]=items[0];
        data[1]=items[1];
    }
}
};

//searchStudent Function Implementation
Student& searchStudent (int ID, BTreeNode<Student>* Tree, bool& valid){
    while(Tree!=NULL){//We may use since we do not take it by reference
        if(Tree->data[0].studentID==ID){//If first data is the key then return first data
            valid=Tree->data[0].record_valid;//Updating valid information to be used later in other functions
            return Tree->data[0];
        }
        else if(Tree->data[1].studentID==ID){//If second data is the key then return second data
            valid=Tree->data[1].record_valid;//Updating valid information to be used later in other functions
            return Tree->data[1];
        }
        else if(ID<Tree->data[0].studentID){
            Tree=Tree->Children[0];//Search for left branch if key is smaller than left data
            }
        else if(ID>Tree->data[1].studentID){//Search for right branch if key bigger than right data
            Tree=Tree->Children[2];
        }
        else{//Search for middle branch if key is in between two data
            Tree=Tree->Children[1];
        }
    }
    if(Tree==NULL){
        cerr<<"Student is not found!!"<<endl;
        valid=false;//Update valid information
        Student nonexistantstudent;//If key is not found return nonexistant student object which is initialized with default constructor
        return nonexistantstudent;//Note that default constructor has index -1 for nonexistant student
    }
}
//PrintStudent Function Implementation
void PrintStudent (int ID, StudentRecord* Database, BTreeNode<Student>* Tree){
    bool validation;//Temporary validation is defined
    Student existance=searchStudent(ID,Tree,validation);//Obtaining validation information with searchStudent function
    if(validation==false){
        cerr<<"Student is not found!!"<<endl;
    }
    else{//If student exists print student name and grades
        cout<<Database[existance.index].studentName<<endl;
        cout<<Database[existance.index].studentGrades[0]<<endl<<Database[existance.index].studentGrades[1]<<endl<<Database[existance.index].studentGrades[2]<<endl;
    }
}
//UpdateStudentGrades Function Implementation
UpdateStudentGrades (int ID, int * grades, StudentRecord* Database, BTreeNode<Student>* Tree){
    bool validation;//Temporary validation is defined
    Student existance=searchStudent(ID,Tree,validation);//Obtaining validation information with searchStudent function
    if(validation==false){
        cerr<<"Student is not found!!"<<endl;
    }
    else{//If student exists update Database grades
        Database[existance.index].studentGrades[0]=grades[0];
        Database[existance.index].studentGrades[1]=grades[1];
        Database[existance.index].studentGrades[2]=grades[2];
    }
}

//magicfunc Implemenation
void magicfunc(BTreeNode<Student>* Tree,Student& newstudent){
    BTreeNode<Student>* temp;
    temp=Tree;
    while(0==0){//Traverse until we find appropriate leaf. Note that following code is very similar to search function
        if(temp->data[0].studentID>newstudent.studentID&&temp->data[0].index!=-1)
            temp=temp->Children[0];
        else if(temp->data[1].studentID<newstudent.studentID&&temp->data[0].index!=-1)
            temp=temp->Children[2];
        else
            temp=temp->Children[1];
        if(temp->Children[0]==NULL)
            if(temp->Children[1]==NULL)
                if(temp->Children[0]==NULL)
                    break;//If we find the leaf node break from while loop
    }
    if(temp->data[0].index==-1&&newstudent.studentID<temp->data[1].studentID){
        temp->data[0]=newstudent;//New student is inserted assuming that leaf node has an empty position
        }
    else if (temp->data[0].studentID<newstudent.studentID&&temp->data[1].index==-1){
        temp->data[1]=newstudent;//New student is inserted assuming that leaf node has an empty position
    }
}
//It is very important to note that insertion function is not satisfactory since it ignores the cases where all B-Tree is full,
//there is no free place in the traversed leaf node, and leaf node has data values in incorrect position. For full B-Tree we need
//to add new layer to B-Tree. For no free place in traversed leaf case the algorithm described in lectures should be implemented.
//By incorrect position what I mean is assuming 23 is to be inserted and we have 24 and null data in leaf node. In this node 24 should be moved
//to right node and 23 should be inserted to left data place.


//InsertStudent Function Implementation
void InsertStudent (int ID, char* Name, int* grades, StudentRecord* Database, BTreeNode<Student>* Tree){
    int t=0;
    bool existance;
    int temp_index=-1;
    Student* temp_student=&searchStudent(ID,Tree,existance);
    //Inserting new student to Database array
    if(existance==true){
        cerr<<"Student already exists in Database!!"<<endl;
        return;
    }
    while(t>100){//Find an empty place for insertion
        if(Database[t].valid==false)
            temp_index=t;
        t++;
    }
    if(temp_index==-1)
        cerr<<"There is not an empty place in Database!!"<<endl;
        bool validation=true;
    StudentRecord newstudentrecord(validation,ID,Name,grades[0],grades[1],grades[2]);//Creating new student record object for database
    Database[temp_index]=newstudentrecord;//Insert new student record object to found index place
    //Inserting new student to B-Tree
    if(temp_student->index==-1){
        Student newstudent(ID,validation,temp_index);//Create new student object to be inserted in B-Tree as a node by magicfunc
        magicfunc(Tree,newstudent);
    }
    else{//If new student was already existant on B-Tree before and it was deleted only change record valid an update index information
        temp_student->record_valid=true;
        temp_student->index=temp_index;
    }
}

//DeleteStudent Function Implementation
DeleteStudent (int ID, StudentRecord* Database, BTreeNode<Student>* Tree){
    bool validation;//Temporary validation is made
    Student* existance=&searchStudent(ID,Tree,validation);//Updating validation information with searchStudent function
    if(validation==false){
        cerr<<"Student is not found!!"<<endl;
    }
    else{
        Database[existance->index].valid=false;//Updating Database valid
        existance->record_valid=false;//Updating tree record_valid
    }
}
//List Function Implementation
//In this function iterative solution is utilized.  Inorder LNR traversal is utilized to have ordered list.
void List (BTreeNode<Student>* Tree){
    if(Tree!=NULL){
        List(Tree->Children[0]);//First traverse left branch
        if(Tree->data[0].record_valid==true){
            cout<<Tree->data[0].studentID<<endl;
        }
        List(Tree->Children[1]);//Second list middle branch
        if(Tree->data[1].record_valid==true){
            cout<<Tree->data[1].studentID<<endl;
        }
        List(Tree->Children[2]);//Third traverse right branch
    }
}

//PrintTree Function Implementation
void PrintTree (BTreeNode<Student>* Tree){
    Queue<BTreeNode<Student>*> Q;//Queue stores all elements of a layer and allow us to print them according to Breadth First Algorithm ie layer by layer
    Q.insert(Tree);//Insert first layer of Tree to Queue
    BTreeNode<Student>* temp;//temp allows us to keep track of tree
    while(!Q.QueueEmpty()){
        temp=Q.Delete();
        if(temp->data[0].index!=0){
            cout<<"ID is "<<temp->data[0].studentID<<"Validation is "<<temp->data[0].record_valid<<endl;
        if(temp->data[0].record_valid==true){
            cout<<"Index is "<<temp->data[0].index<<endl;
        }
        }
        if(temp->data[1].index!=0){
            cout<<"ID is "<<temp->data[1].studentID<<"Validation is "<<temp->data[1].record_valid<<endl;
        if(temp->data[1].record_valid==true){
            cout<<"Index is "<<temp->data[1].index<<endl;
        }
        }
        //Inserting all children of current node
        if(temp->Children[0]!=NULL){
            Q.insert(temp->Children[0]);
        }
        if(temp->Children[1]!=NULL){
            Q.insert(temp->Children[1]);
        }
        if(temp->Children[2]!=NULL){
            Q.insert(temp->Children[2]);
        }
}
}
