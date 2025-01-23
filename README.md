# Maze-Builder-in-C
 This repository contains a C program that dynamically solves a maze using **Breadth-First Search (BFS)** and highlights the path from the start (`S`) to the end (`E`). The project demonstrates core concepts of **C programming**, **data structures**, and **graph algorithms**.

-
##  Features
- **Maze Input**: Accepts maze configurations with walls (`W`) and open paths (` `).
- **Pathfinding**: Implements BFS to find the shortest path from `S` (start) to `E` (end).
- **Dynamic Visualization**: Displays the maze with the solution path highlighted.
- **Efficient Memory Management**: Uses adjacency lists for optimal space utilization.

## 🛠️ Technologies
- **Language**: C Programming
- **Data Structures**: Adjacency Lists
- **Algorithm**: Breadth-First Search (BFS)

### **Example Maze Input**
```
S W   W  
  W    
 W W   
       
W  W  E
```

### **Highlighted Path Output**
```
{ '1', 'W', '0', 'W', '0' },
{ '1', '1', 'W', '0', '0' },
{ '0', 'W', '0', 'W', '0' },
{ '0', '0', '1', '1', '1' },
{ 'W', '0', 'W', '0', '1' }


##  How It Works
1. **Adjacency List Creation**: The maze is represented as a graph where cells are nodes and edges represent valid paths.
2. **Breadth-First Search (BFS)**: BFS traverses the maze from the start (`S`) to the end (`E`), marking the shortest path.
3. **Visualization**: The path is highlighted as `1` in the maze output

##  Key Takeaways
- Learned to use BFS for solving graph problems.
- Mastered adjacency list representation for efficient memory usage.
- Demonstrated proficiency in C programming and algorithm design.
