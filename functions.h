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
int dijkstra(int source, int target, Graph& graph, bool shortest = true);

// Dijkstra's Algorithm to find the shortest path from source to target

void dijkstra(char source, char target, Stack<char>& path, Graph& graph, bool shortest = true)
{
    MinHeap<GraphNode> pq; // Priority queue for Dijkstra
    const int n = vertices;
    bool visited[n];
    Map<char,int> dist(n);
    Map<char,char> predecessor(EDGES); // Map to track predecessors

    for (int i = 0; i < n; i++)
    {
        visited[i] = false; // Initialize all vertices as unvisited
    }

    dist.insert(source, 0); // Distance to the source is 0
    GraphNode source_node(source, 0);
    pq.insert(source_node); // Push the source into the priority queue

    while (!pq.isEmpty())
    {
        char u = pq.peek().targetIntersection; // Current vertex
        int d = pq.peek().travelTime; // Current distance
        pq.pop();

        if (visited[u - 'A']) continue; // If already visited, skip

        visited[u - 'A'] = true; // Mark as visited

        if (u == target) break; // If we reached the target, stop

        // Process all neighbors of u using a simple for loop
        // for (LinkedList<GraphNode> Node* curr = adjacencyList[childrenListIndex].getHead();  curr; curr = curr->next)
        for (LinkedList<GraphNode>::Node* temp = graph.adjacencyList[u - 'A'].getHead(); temp; temp = temp->next)
        {
            {
                char v = temp->data.targetIntersection; // Neighbor vertex
                int weight_uv = temp->data.travelTime; // Weight of edge u -> v

                /*
                if (!shortest) {
                    std::string roadName = std::to_string(u) + v;
                    weight_uv = graph.getRoadCarCount(roadName); // returns the weight that is now the traffic on the road
                    if (weight_uv == -1) // -1 is the default sentinel value
                    {
                        continue; 
                        // the connection doesn't exist (although ion think this condition will ever be true unless
                        // dynamic addition or removal of roads
                    }
                }
                */
                // Update distance if a shorter path is found
                if (!visited[v - 'A'] && dist[u] + weight_uv < dist[v])
                {
                    dist[v] = dist[u] + weight_uv;
                    predecessor.insert(v, u); // Set predecessor for path reconstruction
                    GraphNode temp_node(v, dist[v]);
                    pq.insert(temp_node); // Push the updated distance and vertex into the MinHeap
                }
            }
        }
    }
    // Reconstruct the path from target to source using predecessors

    char current = target;
    if (predecessor[current] == '\0')
        return;
    while (current != source)
    {
        path.push(current); // Add to path stack
        current = predecessor[current]; // Move to the predecessor
    }
    path.push(source); // Push the source
}


#endif //FUNCTIONS_H
