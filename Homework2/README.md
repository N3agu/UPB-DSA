## Overview
The primary objective of this assignment was to utilize foundational Data Types: **Graphs and Binary Trees**, using the custom implementations provided by the lab, **without the use of standard STL containers** (like `std::set`, `std::map` or `std::list`) for the core logical data structures. 

The project is divided into two distinct console applications, which read from input files for automated testing. To comply with assignment constraints, each data structure type (Graph, Binary Tree) was used in a maximum of one exercise.

## Exercise 1: Autonomous Intervention in a Damaged Urban Network

### Story
After a natural disaster, a rescue team deploys several autonomous robots in a partially damaged city. The city infrastructure is heavily compromised, and the robots must navigate to critical zones or charging stations to fulfill their missions. Each road has specific travel times, risk levels, and energy consumptions. Each robot has limited battery autonomy and a strict maximum risk tolerance. Your goal is to map the city, identify vulnerabilities, and calculate the absolute optimal routes for these rescue robots.

### Image
![graphviz](https://raw.githubusercontent.com/N3agu/UPB-DSA/refs/heads/main/Images/graphviz.png)

### Data Structures Used
To solve this, I used the lab-provided **Graph**, **Queue**, and **Double Linked List** implementations:
* **[Graph](graph.h) (The Urban Network):** Used to model the city as a weighted, directed graph. The nodes represent important areas (intersections, hospitals, depots), while the directed edges represent the one-way roads. Custom structs were used for edge weights to simultaneously track travel time, risk, and energy consumption.
* **[Queue](queue.h) & [Linked List](linked_list.h):** The `LinkedList` serves as the underlying adjacency list for the `Graph`, while the custom `Queue` is utilized to perform Breadth-First Search (BFS) operations when calculating regional accessibility.

### Features
* **Visual Mapping (Extra Feature):** Generates a network map, and outputs the file `network_graph.dot` that can be rendered into a 2D image using [Graphviz](https://dreampuf.github.io/GraphvizOnline/).
* **Vulnerability Analytics:** Determines the most exposed areas (highest in-degree) and globally validates the network by checking for isolated connected components (ignoring road direction).
* **Dead-End Detection:** Identifies "blocked" areas that robots can enter but cannot leave (in-degree > 0, out-degree == 0).
* **Reachability Testing:** Performs a BFS to display all areas that are completely inaccessible from a given starting base.
* **Optimal Pathfinding:** Utilizes a custom Depth-First Search (DFS) to find the optimal path to critical zones that prioritizes minimum travel time, and then lowest energy consumption, while strictly adhering to the robot's autonomy and risk thresholds.
* **Fallback Charging System:** If a direct path is mathematically impossible due to battery constraints, the system automatically routes the robot to the most efficient charging station to fully restore autonomy before proceeding to a critical zone.

### Input
```text
9 13
Base North East South West Hospital Depot School Center
Base North 4 2 3
North East 3 1 2
East Hospital 5 3 4
Base South 6 2 5
South West 2 1 2
West Depot 4 2 3
Depot Hospital 3 2 2
North School 2 1 1
School Depot 6 3 5
Hospital Base 7 4 6
East Center 2 2 2
Center Hospital 2 1 1
South Center 4 3 3
3
Hospital Depot School
2
Hospital Center
3
Base 8 2
South 6 1
West 4 2
Base
```

## Exercise 2: The Royal Chronicle of POLITEHNICA

### Story
The Kingdom of POLITEHNICA has waged a century of wars, and the Royal Archive now overflows with unordered scrolls. The King's Council commands the Royal Scribe to organize the Registry of Knights, a record of all knights who have sworn fealty to the crown. The registry must be perfectly ordered by each knight's "Bravery Score," a unique integer granted by the King for deeds in battle.

### Data Structures Used
To solve this, I used the lab-provided **Binary Tree** implementation:
* **[Binary Tree](binary_tree.h) (The Registry):** Used as a Binary Search Tree (BST) to maintain a highly efficient, automatically ordered registry. The `Knight` struct was created with overloaded comparison operators (`<`, `>`, `==`) so the generic tree could automatically sort and retrieve knights entirely based on their unique bravery scores.

### Features
* **Ceremonial Traversals:** Announces knights in three ceremonial orders using In-order (Tournament Ranking), Pre-order (Royal Proclamation), and Post-order (Tribute Collection) traversals.
* **House Summons & Extremes:** Filters and displays all knights sworn to a specific Noble House in ascending order of bravery. Instantly identifies the "Newest Recruit" (minimum value / left-most node) and the "Champion of the Realm" (maximum value / right-most node).
* **Structural Archive Report:** Recursively analyzes the BST to calculate the tree's height, count the exact number of leaf nodes, and verify if the archive is height-balanced.
* **Range Queries:** Summons all knights whose bravery falls within a specified `[L, R]` range and calculates the total number of battles won by that specific group.
* **Political Queries:** Determines the K-th most valorous knight using a reverse in-order traversal (Right-Root-Left) and calculates the Lowest Common Ancestor (LCA) between any two specific knights in the hierarchy.
* **Banishment System:** Erases a disgraced knight from the historical registry, replacing them with a leaf node to maintain perfect tree stability, followed by a live reprint of the updated registry.

### Input
```text
10
Arthur 50 Pendragon 30
Lancelot 30 Lionel 45
Gawain 70 Pendragon 22
Percival 20 Fisher 15
Tristan 40 Cornwall 28
Galahad 60 Lionel 38
Bedivere 80 Pendragon 19
Bors 25 Lionel 12
Gareth 55 Pendragon 17
Lamorak 35 Cornwall 33
Pendragon
25 60
3
Bors Lamorak
Tristan
```

## Compilation
Compilation was done using Visual Studio 2022, the .sln file is provided.

## Documentation
- [Cppreference](https://en.cppreference.com/) & [cplusplus](https://cplusplus.com/) - used for syntax
- [Gemini](https://gemini.google.com/) - used for writing README.md (fix grammar mistakes and explain features), validating ideas and explaining concepts.
