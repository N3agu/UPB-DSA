<div align="center">
  <h1>HOMEWORK 1</h1>
</div>

## Overview
The primary objective of this assignment was to utilize foundational Data Types: **Stacks, Queues, and Linked Lists** — using the custom headers provided by the course laboratory, **without the use of standard STL containers** (like `std::vector`, `std::queue`, or `std::list`). 

The project is divided into two distinct interactive console applications, accessible via an arrow-key navigable menu. To comply with assignment constraints, each data structure type (Stack, Queue, List) was used in a maximum of one exercise.

## Exercise 1: Interactive Task Flow Manager

### Story
A student team is preparing a university event.
During the preparation process, tasks arrive one by one and must be handled in the same order in which they are received.
However, mistakes can happen. If a task was processed by accident, the team wants the possibility to **undo the most recently processed task**.
Your goal is to build an **interactive console application** that simulates this workflow.

### Data Structures Used
To solve this, I used the lab-provided **Queue** and **Stack** implementations:
* **'Queue_Circular' (Waiting Tasks):** Used to maintain the strict First-In-First-Out (FIFO) order of incoming tasks. A circular implementation was chosen to allow continuous enqueue/dequeue operations without hitting a hard array limit.
* **'Source_Stack' (Processed Tasks):** Used to maintain a Last-In-First-Out (LIFO) history of processed tasks. This perfectly matches the requirement for the "Undo" feature, allowing the most recently processed task to be popped off the stack and restored.

### Features
* **Add / Process Tasks:** Add new tasks with unique IDs and priorities. Process the next task in line.
* **Undo System:** Revert the last processed task, pushing it back into the waiting system.
* **Batch Processing:** Process the next *K* tasks sequentially.
* **Search & Analytics:** Search for any task by its ID (checking both waiting and processed systems) and view live statistics (waiting count, processed count, successful undos).

## Exercise 2: Timeline Reconstruction System

### Story
In the year 2473, researchers discovered that the timeline had been affected by multiple uncontrolled interventions. Some events had been moved to the wrong time, others had been completely eliminated, and some had been artificially inserted into other periods.
To fix these anomalies, a system called the Timeline Reconstruction Engine was developed, which allows for the reconstruction of the correct chronology of events. The system maintains a coherent sequence, in which each event is linked to a preceding event and a subsequent event.
You are asked to implement a **TimelineManager** class that manages this chronology and allows for its modification.

### Data Structures Used
To solve this, I used the lab-provided **Doubly Linked List** (`LinkedList`):
* Since the timeline requires constant manipulation in the middle of the sequence (inserting events between other events, relocating events, erasing specific corrupted events), Stack and Queue structures are inefficient.

### Features
* **Record Events:** Add events to the ancient past (head of the list) or recent future (tail of the list).
* **Middle Manipulations:** Insert a newly discovered event exactly between two existing consecutive events.
* **Erase & Relocate:** Delete corrupted events entirely, or extract an event and relocate it immediately before or after another specific event.
* **Timeline Stabilization:** Reorganize the entire timeline by pushing all high-impact events (above a certain threshold) to the beginning, while strictly preserving the relative chronological order of both the high-impact and low-impact groups.

## Compilation
Compilation was done using Visual Studio 2022, the [.sln](https://github.com/N3agu/UPB-DSA/blob/main/Homework1/Homework1.sln) file is provided.

## Documentation
[Cppreference](https://en.cppreference.com/) & [cplusplus](https://cplusplus.com/) - used for syntax 
[Gemini](https://gemini.google.com/) - used for writing README.md (fix grammar mistakes and explain features), validating ideas and explaining concepts.