//
// Created by AliRauf on 11/28/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "classes.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Prototypes
int dijkstra(int source, int target, Graph &graph, bool = true);

// Dijkstra's Algorithm to find the shortest path from source to target

void dijkstra(char source, char target, Stack<char>& path, Graph &graph, bool = true)
{
    MinHeap<GraphNode> pq;  // Priority queue for Dijkstra
    const int n = vertices;
    bool visited[n];
    Map dist(n, INT_MAX);
    Char_Map predecessor;  // Map to track predecessors
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;  // Initialize all vertices as unvisited
    }

    dist.insert(to_string(source),0);  // Distance to the source is 0
    GraphNode source_node(source, 0);
    pq.insert(source_node);  // Push the source into the priority queue

    while (!pq.isEmpty()) {
        char u = pq.peek().targetIntersection;  // Current vertex
        int d = pq.peek().travelTime;  // Current distance
        pq.pop();

        if (visited[u-'A']) continue;  // If already visited, skip

        visited[u-'A'] = true;  // Mark as visited

        if (u == target) break;  // If we reached the target, stop

        // Process all neighbors of u using a simple for loop
        for (int i = 0; i < graph.adjacencyList[u-'A'].getSize(); ++i) {
            LinkedList<GraphNode>::Node* temp = graph.adjacencyList[u-'A'].getNode(i);
            while (temp != nullptr)
            {
                char v = temp->data.targetIntersection;  // Neighbor vertex
                int weight_uv = temp->data.travelTime;  // Weight of edge u -> v

                // Update distance if a shorter path is found
                if (!visited[v-'A'] && dist[to_string(u)] + weight_uv < dist[to_string(v)]) {
                    dist[to_string(v)] = dist[to_string(u)] + weight_uv;
                    predecessor.insert(v, u);  // Set predecessor for path reconstruction
                    GraphNode temp_node(v, dist[to_string(v)]);
                    pq.insert(temp_node);  // Push the updated distance and vertex into the MinHeap
                }
                temp = temp->next;
            }
        }
    }
    // Reconstruct the path from target to source using predecessors
    char current = target;
    while (current != source)
    {
        path.push(current);  // Add to path stack
        current = predecessor[current];  // Move to the predecessor
    }
    path.push(source);  // Push the source
}



#endif //FUNCTIONS_H
