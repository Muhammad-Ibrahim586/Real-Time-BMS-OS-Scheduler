#include "Task.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <string>

using namespace std;

pthread_mutex_t taskMutex;

void* simulateTask(void* arg){
    Task* myTask = (Task*)arg;
    
    pthread_mutex_lock(&taskMutex);
    cout << " Thread" << myTask->getName() << "is initialized!" << endl;
    sleep(1);
    pthread_mutex_unlock(&taskMutex);
    
    pthread_exit(NULL);
}

int main() {
    Task bmsTasks[5] = {
        Task(" 'Voltage Monitor' ", 100, 20, 1),
        Task(" 'Temperature Sensor' ", 200, 20, 2),
        Task(" 'SoC Calculator' ", 500, 50, 3),
        Task(" 'Cell Balancer' ", 1000, 100, 4),
        Task(" 'Logger' ", 2000, 100, 5)
    };

    pthread_t threads[5];
    pthread_mutex_init(&taskMutex, NULL);

    int globalTime = 0;
    int simulationDuration = 2000;
    int tick = 10;

    int totalTicks = 0;
    int idleTicks = 0;
    int deadlineMisses = 0;

    // Strings to dynamically build each row of our Gantt chart
    string rowTask0 = "Voltage Monitor    | ";
    string rowTask1 = "Temperature Sensor | ";
    string rowTask2 = "SoC Calculator     | ";
    string rowTask3 = "Cell Balancer      | ";
    string rowTask4 = "Logger             | ";
    string rowIdle  = "CPU Idle           | ";
    string timeline = "Time Axis (x10ms)  | ";

    for(int i = 0; i < 5; i++){
        pthread_create(&threads[i], NULL, simulateTask, (void*)&bmsTasks[i]);
    }

    cout << " Starting RMS Scheduler Simulation..." << endl;

    while(globalTime < simulationDuration){
        int highestPrioIdx = -1;
        int highestPrioVal = 999; 

        pthread_mutex_lock(&taskMutex);

        for(int i = 0; i < 5; i++){
            if(globalTime % bmsTasks[i].getPeriod() == 0){
                if(globalTime > 0 && bmsTasks[i].getRemainingTime() > 0){
                    cout << " [!!!] DEADLINE MISSED: " << bmsTasks[i].getName() << endl;
                    deadlineMisses++;
                }
                bmsTasks[i].setRemainingTime(bmsTasks[i].getExecTime());
                bmsTasks[i].setNextDeadline(globalTime + bmsTasks[i].getPeriod());
            }

            if(bmsTasks[i].getRemainingTime() > 0){
                if(bmsTasks[i].getPriority() < highestPrioVal){
                    highestPrioVal = bmsTasks[i].getPriority();
                    highestPrioIdx = i;
                }
            }
        }

        if(highestPrioIdx != -1){
            cout << " [Time: " << globalTime << "ms] Running:" << bmsTasks[highestPrioIdx].getName() << "(Remaining: " << bmsTasks[highestPrioIdx].getRemainingTime() << "ms)" << endl;
            bmsTasks[highestPrioIdx].setRemainingTime(bmsTasks[highestPrioIdx].getRemainingTime() - tick);
        }else{
            cout << " [Time: " << globalTime << "ms] CPU Idle" << endl;
            idleTicks++;
        }

        // --- GANTT CHART DATA GENERATION ---
        // Append execution characters to corresponding string rows based on current state
        rowTask0 += (highestPrioIdx == 0) ? "█" : " ";
        rowTask1 += (highestPrioIdx == 1) ? "█" : " ";
        rowTask2 += (highestPrioIdx == 2) ? "█" : " ";
        rowTask3 += (highestPrioIdx == 3) ? "█" : " ";
        rowTask4 += (highestPrioIdx == 4) ? "█" : " ";
        rowIdle  += (highestPrioIdx == -1) ? "░" : " ";
        
        // Put a tick mark on the timeline axis every 100ms (10 ticks)
        if ((globalTime / tick) % 10 == 0) {
            timeline += "|";
        } else {
            timeline += "-";
        }

        pthread_mutex_unlock(&taskMutex);

        totalTicks++;
        globalTime += tick;
        usleep(50000);
    }

    for(int i = 0; i < 5; i++){
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&taskMutex);

    cout << " Simulation Finished..." << endl;

    // --- DISPLAY GENERATED GANTT CHART ---
    cout << "\n(RMS SCHEDULER GANTT CHART)" << endl;
    cout << "" << endl;
    cout << rowTask0 << endl;
    cout << rowTask1 << endl;
    cout << rowTask2 << endl;
    cout << rowTask3 << endl;
    cout << rowTask4 << endl;
    cout << rowIdle  << endl;
    cout << timeline << endl;
    cout << "\n" << endl;

    double utilization = (1.0 - ((double)idleTicks / totalTicks)) * 100.0;
    cout << "\n (RMS PERFORMANCE METRICS)" << endl;
    cout << " Total Execution Ticks: " << totalTicks << endl;
    cout << " Idle Ticks Recorded:   " << idleTicks << endl;
    cout << " Total Deadline Misses: " << deadlineMisses << endl;
    cout << " Overall CPU Utilization: " << utilization << "% \n" << endl;

    return 0;
}
