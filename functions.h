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




// Dijkstra's Algorithm to find the shortest path from source to target
int dijkstra(int source, int target, int n, int adj[][10], int weight[][10])
{
    // Create a priority queue to store (distance, vertex) pairs
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Initialize distances with infinity and distance to source is 0
    int dist[n];
    memset(dist, INT_MAX, sizeof(dist));  // Initialize all distances to INT_MAX
    dist[source] = 0;

    // Push the source vertex with distance 0 into the priority queue
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;  // Current vertex
        int d = pq.top().first;   // Current distance
        pq.pop();

        // If the current vertex's distance is already greater than the known shortest, skip it
        if (d > dist[u]) {
            continue;
        }

        // If we've reached the target, return the distance
        if (u == target) {
            return dist[u];
        }

        // Process all neighbors of u
        for (int v = 0; v < n; ++v) {
            if (adj[u][v] != -1) {  // If there's an edge between u and v
                int weight_uv = adj[u][v]; // Edge weight between u and v

                // If a shorter path to v is found, update its distance and push it to the queue
                if (dist[u] + weight_uv < dist[v]) {
                    dist[v] = dist[u] + weight_uv;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // If no path is found, return -1
    return -1;
}



void load_graph_from_file(Graph& graph,string file_name = "")
{
    if(file_name == "")
        file_name = "csv/road_network.csv";
    ifstream outfile(file_name);
    if (!outfile)
    {
        std::cerr << "Error: Unable to open file " << file_name << std::endl;
        return;
    }
    string line;
    bool head = true;
    while(getline(outfile,line))
    {
        if(head)        // Skipping head of the CSV file
            head = false;
        int vertex_1 = line[0]-65;          // A,B,14
        int vertex_2 = line[2]-65;
        int weight = stoi(line.substr(4));
        string name = line.substr(0, 1) + line.substr(2, 1);
        Edge temp(name,weight);
        graph.addEdge(vertex_1,vertex_2,temp);
    }
}
#endif //FUNCTIONS_H
