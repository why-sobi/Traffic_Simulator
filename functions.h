//
// Created by AliRauf on 11/28/2024.
//

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "classes.hpp"
#include <fstream>

// Prototypes
void load_graph_from_file(Graph& graph,string file_name);




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
    while(getline(outfile,line))
    {
        int vertex_1 = line[0]-65;
        int vertex_2 = line[2]-65;
        int weight = stoi(line.substr(4));
        string name = line.substr(0, 1) + line.substr(2, 1);
        Edge temp(name,weight);
        graph.addEdge(vertex_1,vertex_2,temp);
    }
}
#endif //FUNCTIONS_H
