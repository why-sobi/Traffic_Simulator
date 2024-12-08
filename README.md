# Traffic_Simulator
## Introduction:
This is a basic traffic simulation and management system. This Simulator is a practical project designed to replicate real-world traffic management in a city. It optimizes urban traffic flow using data structures like graphs, heaps, and priority queues. The system focuses on real-time vehicle routing, traffic signal control, congestion management, and emergency handling without incorporating predictive features.

## Key Features:
- **City Traffic Network**:  
Models the city as a dynamic graph with intersections (nodes) and roads (edges).
- **Vehicle Routing**:  
Computes optimal routes using Dijkstra's Algorithm and adjusts dynamically.
- **Traffic Signal Management**:  
Adjusts signals based on density using priority queues, Includes emergency overrides.
- **Congestion Monitoring**:  
Tracks vehicle counts with hash tables and resolves bottlenecks using BFS/DFS.
- **Emergency Handling**:  
Provides priority routing for emergencies using A* Algorithm and overrides traffic flow.
- **Accident Simulation**:  
Dynamically blocks roads and updates vehicle routes during disruptions.
- **Simulation Dashboard**:  
Visualizes traffic flow, congestion, and system actions with manual control options.

## Structures Used  
- *Graphs*
- *Heaps*
- *Priority queues*
- *Linked lists*
- *Stacks*

## Main Functions
### 1. Dijkstra Function
**Purpose**:  
Finds the shortest or least congested path between two nodes in a graph using Dijkstra's Algorithm.

**Parameters**:
- char source: Starting intersection.  
- char target: Target intersection.  
- Stack<char>& path: Stack to store the reconstructed path.  
- Graph& graph: Graph representation of the city.  
- bool shortest: Flag to determine if the algorithm uses shortest distance (true) or fastest (false).  
Key Features:

Initializes distances to all nodes as INT_MAX, except the source, which is set to 0.
Uses a MinHeap as a priority queue for efficiency.
Tracks visited nodes to avoid revisiting.
Updates the distance and predecessor if a shorter path is found.
Reconstructs the path from target to source using the predecessor map.  
  
### 2. AStar Function  
**Purpose**:  
Calculates the fastest route between two nodes using the A* (A-Star) search algorithm.

**Parameters**:  

- char start: Starting intersection.
- char goal: Target intersection.
- Stack<char>& path: Stack to store the reconstructed path.
- Graph& graph: Graph representation of the city.
Key Features:  

Uses both g(n) (cost from start to current node) and h(n) (heuristic estimate to the goal) to calculate f(n) = g(n) + h(n).
Employs a MinHeap to prioritize nodes with the lowest f(n).
Tracks visited nodes and predecessors for path reconstruction.
Continuously updates the g(n) and f(n) values as shorter paths are found.
Stops when the goal is reached.
Reconstructs the path from goal to start using the predecessor map.
