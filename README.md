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

## Instructions:
Open the project.sln file in your visual studio and use debugger to run code.
