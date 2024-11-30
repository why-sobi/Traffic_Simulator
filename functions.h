//
// Created by AliRauf on 11/28/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "classes.hpp"
#include <fstream>

// Prototypes
void load_graph_from_file(Graph& graph,string file_name);
int dijkstra(int source, int target, int n, int adj[][10], int weight[][10]);




// Define a simple priority queue structure using a basic array
struct PriorityQueue {
    int queue[100][2]; // Stores pairs (distance, vertex)
    int size;

    PriorityQueue() : size(0) {}

    void push(int distance, int vertex) {
        queue[size][0] = distance;
        queue[size][1] = vertex;
        size++;
        sort(); // Sort the array after each push
    }

    void pop() {
        if (size > 0) {
            for (int i = 1; i < size; i++) {
                queue[i - 1][0] = queue[i][0];
                queue[i - 1][1] = queue[i][1];
            }
            size--;
        }
    }

    int topDistance() { return queue[0][0]; }
    int topVertex() { return queue[0][1]; }
    bool empty() { return size == 0; }

private:
    void sort() {
        // Simple selection sort to keep the queue sorted by distance
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (queue[i][0] > queue[j][0]) {
                    swap(queue[i], queue[j]);
                }
            }
        }
    }
};
// Dijkstra's Algorithm to find the shortest path from source to target
int dijkstra(int source, int target, Graph &graph) {
    PriorityQueue pq; // Priority queue for Dijkstra
    const int n = vertices;

    // Distance and visited arrays
    int dist[n];
    bool visited[n];
    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX; // Initialize distances to infinity
        visited[i] = false; // Initialize all vertices as unvisited
    }

    dist[source] = 0; // Distance to the source is 0
    pq.push(0, source); // Push the source into the priority queue

    while (!pq.empty()) {
        int u = pq.topVertex(); // Current vertex
        int d = pq.topDistance(); // Current distance
        pq.pop();

        // If already visited, skip
        if (visited[u])
            continue;

        // Mark as visited
        visited[u] = true;

        // If we reached the target, return the distance
        if (u == target) {
            return dist[u];
        }

        // Process all neighbors of u
        for (auto &neighbor : graph.adjacencyList[u]) {
            int v = neighbor.first;   // Neighbor vertex
            int weight_uv = neighbor.second; // Weight of edge u -> v

            // Update distance if a shorter path is found
            if (!visited[v] && dist[u] + weight_uv < dist[v]) {
                dist[v] = dist[u] + weight_uv;
                pq.push(dist[v], v); // Push the updated distance and vertex into the queue
            }
        }
    }

    // If no path is found, return -1
    return -1;
}

#endif //FUNCTIONS_H
