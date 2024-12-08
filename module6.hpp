//
//

#ifndef MODULE6_HPP
#define MODULE6_HPP

#include "classes.hpp"
#include "functions.h"
#include "module2.hpp"


void reRouteAllCars(Graph& matrix)
{
    // now we just have to give new path to each car in the current map, we can use module 2 for that
    // for each car in the graph/map call module 2 ka function
    for (LinkedList<Car>::Node* temp = matrix.cars.getHead(); temp; temp = temp->next)
        route_recalculation(temp->data,matrix);
}

void block_routes(Graph& matrix,string& roadName)
{
    // This will be the node stored in the linked list ith index, meaning the road from (i to road) is going to be blocked
    // the route where there is a road closure or accident, set travel time to INT_MAX
    if(roadName.length() != 2)
        return;

    char start = roadName[0];
    char end = roadName[1];
    if(matrix.get_Car_count(roadName) > 0)
    {
        cout << "Car " << roadName << " is not empty" << endl;
        cout << "Cant block this route!\n";
        return;
    }
    for (LinkedList<GraphNode>::Node* temp = matrix.adjacencyList[start - 'A'].getHead(); temp; temp = temp->next)
    {
        if(temp->data.targetIntersection == end)
        {
            temp->data.backup_value = temp->data.travelTime;
            temp->data.travelTime = INT_MAX;
            temp->data.status = "Blocked";
            reRouteAllCars(matrix);
            cout << "Rerouted All Cars\n";
            return;
        }
    }
}

void unblock_route(Graph& matrix, const string& roadName)
{
    if(roadName.length() != 2)
        return;

    char start = roadName[0];
    char end = roadName[1];
    for (LinkedList<GraphNode>::Node* temp = matrix.adjacencyList[start - 'A'].getHead(); temp; temp = temp->next)
    {
        if(temp->data.targetIntersection == end && temp->data.status == "Blocked")
        {
            temp->data.travelTime = temp->data.backup_value;
            temp->data.backup_value = 0;
            temp->data.status = "Clear";
            reRouteAllCars(matrix);
            cout << "Unblocked all routes and Rerouted All Cars\n";
            return;
        }
    }
}

#endif //MODULE6_HPP
