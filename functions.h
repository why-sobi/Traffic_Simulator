//
// Created by AliRauf on 11/28/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "classes.hpp"
#include <fstream>
#include <iostream>

using namespace std;
#include <chrono>
#include <thread>
#include <functional>
#include <future>

using namespace std;
using namespace chrono;

// Prototypes
void dijkstra(char source, char target, Stack<char>& path, Graph& graph, bool shortest);
void AStar(Graph& graph, char start, char goal, Stack<char>& path);
void change_signals_state();
// Dijkstra's Algorithm to find the shortest path from source to target

void change_signals_state(int count,Graph& matrix)
{
    // Set up a timer to call this function again after 5 seconds (non-blocking)

    // usage: call this function when the simulation process starts with main program thread t(change_signals_state,0, graph)

    auto future = async(launch::async, [](){
        this_thread::sleep_for(seconds(1));
    });

    // Wait for the timer to complete, then call the function again (recursive call)
    future.wait(); // Wait for 5 seconds, then continue the loop
    count += 1;
    DynamicArr<char> keys = matrix.greenTime.getKeys();
    for(int i = 0; i < keys.getSize() ; i++)
    {
        if(count % stoi(matrix.greenTime[keys[i]]) == 0)
        {
            // code to change the state of the signal
            // you can set a boolean value in graphnode and shift its value like this:
            // is_open = !is_open;
            // what im having trouble thinking is that when we want to change the state, we must iterate though all the
            // adjacency list and for every node leading to current block(intersection), we might have to change the state
            // initially everything will be green, so boolean will always be set to true
        }
    }
    change_signals_state(count,matrix);
}

void dijkstra(char source, char target, Stack<char>& path, Graph& graph, bool shortest = true)
{
    const int n = vertices;

    MinHeap<GraphNode> pq(n); // Priority queue for Dijkstra
    Set<char> visited(n);
    Map<char,int> dist(n);
    Map<char,char> predecessor(EDGES); // Map to track predecessors
    bool found = false;
    path.removeAll();

    for(char i = 'A'; i <= 'Z'; i++)
        dist.insert(i, INT_MAX);

    dist.insert(source, 0); // Distance to the source is 0
    GraphNode source_node(source, 0);
    pq.insert(source_node); // Push the source into the priority queue

    while (!pq.isEmpty())
    {
        char u = pq.peek().targetIntersection; // Current vertex
        pq.pop();

        if (visited.has(u)) continue; // If already visited, skip

        visited.insert(u); // Mark as visited

        if (u == target) {
            found = true;
            break; // If we reached the target, stop
        }

        // Process all neighbors of u using a simple for loop
        for (LinkedList<GraphNode>::Node* temp = graph.adjacencyList[u - 'A'].getHead(); temp; temp = temp->next)
        {
            {
                char v = temp->data.targetIntersection; // Neighbor vertex
                int weight_uv = temp->data.travelTime; // Weight of edge u -> v

                
                if (!shortest) {
                    std::string roadName = std::to_string(u) + v;
                    weight_uv = graph.get_Car_count(roadName); // returns the weight that is now the traffic on the road
                    if (weight_uv == -1) // -1 is the default sentinel value
                    {
                     continue; 
                        // the connection doesn't exist (although ion think this condition will ever be true unless)
                        // dynamic addition or removal of roads
                    }
                }
                // Update distance if a shorter path is found
                if (!visited.has(v) && dist[u] + weight_uv < dist[v])
                {
                    dist[v] = dist[u] + weight_uv;
                    predecessor.insert(v, u); // Set predecessor for path reconstruction
                    GraphNode temp_node(v, dist[v]);
                    pq.insert(temp_node); // Push the updated distance and vertex into the MinHeap
                }
            }
        }
    }
    if (!found) {
        return; // Exit early if no path was found
    }

    // Reconstruct the path from target to source using predecessors
    char current = target;
    while (current != source)
    {
        path.push(current); // Add to path stack
        current = predecessor[current]; // Move to the predecessor
    }
    path.push(source); // Push the source
}

void AStar(char start, char goal, Stack<char>& path, Graph& graph) {
    const int n = vertices;

    // MinHeap to store nodes based on f value (g + h)
    MinHeap<GraphNode> pq(n);

    // Maps to keep track of the distances, visited nodes, and predecessors
    Set<char> visited(n);
    Map<char, int> dist(n);          // g(n) - shortest distance from start
    Map<char, char> predecessor(n);  // To reconstruct the path

    // Initialize all nodes
    for (char i = 'A'; i <= 'Z'; i++) {
        dist.insert(i, INT_MAX);
    }

    dist.insert(start, 0);  // g(start) = 0
    GraphNode startNode(start, 0);
    startNode.heuristic_value = graph.heuristic(start, goal); // f(start) = g(start) + h(start)
    pq.insert(startNode);  // Push the start node into the priority queue

    while (!pq.isEmpty()) {
        // Pop the node with the lowest f value
        char u = pq.peek().targetIntersection;  // Current node
        pq.pop();

        if (visited.has(u)) continue;  // If already visited, skip

        visited.insert(u);  // Mark as visited

        if (u == goal) break;  // If we reach the goal, stop

        // Process all neighbors of u
        for (LinkedList<GraphNode>::Node* temp = graph.adjacencyList[u - 'A'].getHead(); temp; temp = temp->next) {
            char v = temp->data.targetIntersection;  // Neighbor node
            int weight_uv = temp->data.travelTime;  // Weight of edge u -> v

            // Calculate g(v)
            int tentativeG = dist[u] + weight_uv;

            // If the neighbor hasn't been visited and the path is shorter, update
            if (!visited.has(v) && tentativeG < dist[v]) {
                dist[v] = tentativeG;  // Update g(v)
                predecessor.insert(v, u);  // Set predecessor for path reconstruction

                // Calculate f(v) = g(v) + h(v)
                GraphNode neighborNode(v, dist[v]);
                neighborNode.heuristic_value = dist[v] + graph.heuristic(v, goal);  // f(v) = g(v) + h(v)

                pq.insert(neighborNode);  // Push the updated neighbor into MinHeap
            }
        }
    }

    // Reconstruct the path from goal to start using predecessors
    char current = goal;
    while (current != start) {
        path.push(current);  // Push to path stack
        current = predecessor[current];  // Move to predecessor
    }
    path.push(start);  // Push the start node
}



#endif //FUNCTIONS_H
