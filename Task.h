#define TASK_H

#include <string>
#include <pthread.h>
using namespace std;

class Task{
    private:
        string name;
		int period;
		int execution_time;
		int priority;
		
		int remaining_time;
		int next_deadline;

    public:
	    Task(string n, int p, int e, int prio);
		
		string getName();
		int getPeriod();
		int getExecTime();
		int getPriority();
    
        int getRemainingTime();
		void setRemainingTime(int r);
    
        int getNextDeadline();
		void setNextDeadline(int d);
};

Task :: Task(string n, int p, int e, int prio){
    name = n;
    period = p;
    execution_time = e;
    priority = prio;
    
    remaining_time = e;
    next_deadline = p;
}

string Task :: getName(){
	return name;
}
		
int Task :: getPeriod(){
    return period;
}
		
int Task :: getExecTime(){
	return execution_time;
}
		
int Task :: getPriority(){
	return priority;
}
    
int Task :: getRemainingTime(){
	return remaining_time;
}
        
void Task :: setRemainingTime(int r){
	remaining_time = r;
}
    
int Task :: getNextDeadline(){ 
	return next_deadline;
}
        
void Task :: setNextDeadline(int d){
	next_deadline = d;
}

