# BMS Real-Time OS Scheduler (RMS)

This project simulates a real-time Battery Management System (BMS) using C++ and POSIX threads. It runs multiple battery subsystems concurrently and applies Rate Monotonic Scheduling (RMS) to ensure that high-priority safety tasks execute before lower-priority tasks. The system also tracks execution statistics including CPU utilization, idle time, and deadline misses.

## Overview

1) Simulates a real-time BMS using POSIX threads (pthreads) in C++.
2) Implements Rate Monotonic Scheduling for deterministic task execution.
3) Manages 5 concurrent battery subsystem tasks.
4) Uses mutex locks to ensure thread-safe scheduling behavior.
5) Executes a fixed-time simulation loop to model real-time CPU activity.

## Features

1) 5 concurrent battery management tasks
2) Rate Monotonic Scheduling (static priority assignment)
3) Preemptive task switching based on priority rules
4) Mutex-based synchronization for shared resources
5) Automated performance tracking (ticks, idle time, utilization)
6) Deadline monitoring and miss detection

## Applications

1) Real-time operating system simulation
2) Embedded systems and automotive BMS design concepts
3) CPU scheduling algorithm demonstration (RMS)
4) Multithreading and concurrency learning in C++
5) POSIX-based system programming practice

## Files Included

1) Source – C++ source code (main.cpp, Task.h)
2) Output – Execution log file (Project_Output.txt)
3) Slides – PowerPoint presentation (ppt)
4) Report – Project documentation (PDF)

## Instructions

1) Open the project folder in a Linux terminal.
2) Compile the program using:
       g++ -o bms_sim main.cpp -lpthread
3) Run the simulation:
       ./bms_sim
4) To save execution output:
       ./bms_sim > Project_Output.txt

## Acknowledgements

Developed by Team CE (Muhammad Ibrahim and Mohammad Ahtesam).

## License

This project is licensed under the MIT License - see the LICENSE file for details.
