//Muhammed Saadeddin Koçak 2232346

#include <iostream>
#include <fstream>
#include <string>

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

//Implementation of Stack

template <class T>
class Stack {
    private:
        T stackList[2];
        int top;
    public:
        Stack();
        const int length = 2;
        void Push(const T& item);
        T Pop();
        T Peek() const;
        bool StackEmpty();
        bool StackFull();
};

template <class T>
Stack<T>::Stack() {
    top = -1;
}

template <class T>
void Stack<T>::Push(const T& item) {
    if(top != length-1) {
        top++;
        stackList[top] = item;
    }
    else {
        cerr << "Stack overflow!" << endl;
    }
}

template <class T>
T Stack<T>::Pop() {
    T temp;
    if(top == -1) {
        cerr << "Stack is empty!" << endl;
    }
    else {
        temp = stackList[top];
        top--;
        return temp;
    }
}

template <class T>
bool Stack<T>::StackEmpty() {
    if(top == -1)
        return true;
    else
        return false;
}

template <class T>
bool Stack<T>::StackFull() {
    if(top == length-1)
        return true;
    else
        return false;
}

template<class T>
T Stack<T>::Peek() const {
    return stackList[top];
}

//Start of Actual Code

class Process
{
public:
    Process();
    int id;
    int priority;
    int arrivaltime;
    int runtime;
    int latency;
};
Process::Process()//Default values for class are given.
{id=-1;
priority=0;
arrivaltime=0;
runtime=0;
latency=0;
}
int main(){
    int pID, priority, arrTime, runTime, numberofprocesses=0;

    ifstream infile;
    ofstream outfile;
    ofstream latency;

    infile.open("input.txt");
    outfile.open("output.txt");
    latency.open("latency.txt");

    while(!infile.eof()){
        infile >> pID >> priority >> arrTime >> runTime;
        numberofprocesses++;//First we need to see the number of processes to make a process array.
    }

    infile.close();

    Process *processarray=new Process[numberofprocesses];//Defining a process array. We need to create this array during runtime because we do not know the number of processes before runtime. Therefore we are using dynamic memory.

    infile.open("input.txt");

    int i=0;

    while(!infile.eof()){
        infile >> pID >> priority >> arrTime >> runTime;
        Process p;
        p.id=pID;
        p.priority = priority;
        p.arrivaltime = arrTime;
        p.runtime = runTime;//Assigning properties to Process objects.
        processarray[i] = p;
        i++;
    }

    infile.close();

    //Running Process

    int t=0;//Clock
    int condition=0;//Condition variable
    Process runningprocess;

    runningprocess=processarray[0];//Initializing first process which is the first element of our process array.

    outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" arrives with Priority= "<<runningprocess.priority<<" and Runtime= "<<runningprocess.runtime<<". Process "<<runningprocess.id<<" starts execution."<<endl;//???
    //The reason for separation of first process is to start first program immediately at t=0.
    Stack<Process> s1;//Process stack
    Queue<Process> q1;//Process queue for processes priority 1
    Queue<Process> q2;//Process queue for processes priority 2
    Queue<Process> q3;//Process queue for processes priority 3


    while(true){ //Using loop structure for time simulation. For loop is not satisfactory since time is unlimited.
            t++;//Increase time
            runningprocess.runtime--;//Decrease runtime of running process

    for(int i=0;i<numberofprocesses; i++){
        if(processarray[i].arrivaltime==t){//For each process check the arrival time. If any process arrives decide what to do.
            if(i!=0){
            outfile<<"At t= " <<t<<" Process "<<processarray[i].id<<" arrives with Priority= "<<processarray[i].priority<<" and Runtime= "<<processarray[i].runtime<<"."<<endl;
            }
            if(processarray[i].priority<runningprocess.priority){
                s1.Push(runningprocess);
                outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is preempted and pushed onto stack with Runtime= "<<runningprocess.runtime<<endl;
                runningprocess=processarray[i];
                outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" starts execution. "<<endl;
                break;//Higher priority process has come. So that we have pushed current process to stack and started executing higher priority process.
            }
            else {
                switch(processarray[i].priority) {//Depending on the priority of new process we push it to proper queue if stack has a higher priority process to process.
                case 1:
                    q1.insert(processarray[i]);
                    outfile<<"At t= "<<t<<" Process "<<processarray[i].id<<" is stored in Q1."<<endl;
                    break;
                case 2:
                    q2.insert(processarray[i]);
                    outfile<<"At t= "<<t<<" Process "<<processarray[i].id<<" is stored in Q2."<<endl;
                    break;
                case 3:
                    q3.insert(processarray[i]);
                    outfile<<"At t= "<<t<<" Process "<<processarray[i].id<<" is stored in Q3."<<endl;
                    break;
                }
            }
        }
        //If a process is finished following code decide what to do.

        if(runningprocess.runtime==0){//When runtime is zero it means process is finished.

            if(runningprocess.id!=-1){
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is completed."<<endl;
            runningprocess.latency=t-runningprocess.arrivaltime;//Calculating latency as described.
            latency<<"Latency for Process "<<runningprocess.id<<" is "<<runningprocess.latency<<endl;

        //Defining conditions

        if(!q1.QueueEmpty()&&!s1.StackEmpty()){condition=1;}//q1 and s1 is filled. Need to decide which to process.
        if(q1.QueueEmpty()&&!q2.QueueEmpty()&&!s1.StackEmpty()){condition=2;}//q2 and s1 is filled. Need to decide which to process.
        if(q1.QueueEmpty()&&q2.QueueEmpty()&&!q3.QueueEmpty()&&!s1.StackEmpty()){condition=3;}//q3 and s1 is filled. Does not need to decide which to process. Process stack process.
        if(q1.QueueEmpty()&&q2.QueueEmpty()&&q3.QueueEmpty()&&!s1.StackEmpty()){condition=3;}//Only s1 filled. Process it.
        if(!q1.QueueEmpty()&&s1.StackEmpty()){condition=5;}//q1 is filled and s1 is empty. Process q1 process.
        if(q1.QueueEmpty()&&!q2.QueueEmpty()&&s1.StackEmpty()){condition=6;}//q2 is filled and q1 is empty and s1 is empty. Process q2 process.
        if(q1.QueueEmpty()&&q2.QueueEmpty()&&!q3.QueueEmpty()&&s1.StackEmpty()){condition=7;}//q3 is filled. Everything else is empty. Process q3 process.
        if(q1.QueueEmpty()&&q2.QueueEmpty()&&q3.QueueEmpty()&&s1.StackEmpty()){condition=8;}//Everything is empty. Break out.

        Process p1=q1.QFront();
        Process p2=s1.Peek();
        Process p3=q2.QFront();
        Process p4=s1.Peek();

        switch(condition){
        case 0:
            break;
        case 1:

            if(p1.priority<p2.priority){
            runningprocess=q1.Delete();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is dequeued from Q1."<<endl;
            }
            else{
            runningprocess=s1.Pop();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is popped from stack."<<endl;
            }
            break;

        case 2:

            if(p3.priority<p4.priority){
            runningprocess=q2.Delete();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is dequeued from Q2."<<endl;
            }
            else{
            runningprocess=s1.Pop();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is popped from stack."<<endl;
            }
            break;

        case 3:

            runningprocess=s1.Pop();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is popped from stack."<<endl;
            break;

        case 5:

            runningprocess=q1.Delete();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is dequeued from Q1."<<endl;
            break;

        case 6:

            runningprocess=q2.Delete();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is dequeued from Q2."<<endl;
            break;

        case 7:

            runningprocess=q3.Delete();
            outfile<<"At t= "<<t<<" Process "<<runningprocess.id<<" is dequeued from Q3."<<endl;
            break;

        case 8:

            runningprocess.id=-1;
            break;

        }
        }
         }
}

    if(runningprocess.id==-1){
            break;
    }

    }

outfile.close();
latency.close();
delete[]processarray;//Return dynamic memory.
cout<<"Please check output and latency files."<<endl;
return 0;
}
