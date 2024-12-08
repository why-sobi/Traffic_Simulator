//
//

#ifndef MODULE6_HPP
#define MODULE6_HPP

#include "classes.hpp"
#include "module2.hpp"

void reRouteAllCars(Graph& matrix)
{
    // now we just have to give new path to each car in the current map, we can use module 2 for that
    // for each car in the graph/map call module 2 ka function
    for (LinkedList<Car*>::Node* temp = matrix.cars.getHead(); temp; temp = temp->next)
        route_recalculation(temp->data,matrix);
}

void block_routes(Graph& matrix,string& roadName,WINDOW*& output)
{
    // This will be the node stored in the linked list ith index, meaning the road from (i to road) is going to be blocked
    // the route where there is a road closure or accident, set travel time to INT_MAX

    wclear(output);
    box(output, 0, 0);

    int x = 1, y = 1;
    char start = roadName[0];
    char end = roadName[1];
    if(matrix.get_Car_count(roadName) > 0)
    {
        mvwprintw(output, y, x, "Road %s is not empty hence cannot block it right now!", roadName.c_str());
        ++y;
        wrefresh(output);
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
            mvwprintw(output, y, x, "Rerouted all cars!");
            return;
        }
    }

    wrefresh(output);
}

void unblock_route(Graph& matrix, const string& roadName,WINDOW*& output)
{
    if(roadName.length() != 2)
        return;


    wclear(output);
    box(output, 0, 0);

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
            mvwprintw(output, 1, 1, "Unblocked all routes and Rerouted All Cars");
            cout << "Unblocked all routes and Rerouted All Cars\n";
            return;
        }
    }
    wrefresh(output);
}

#endif //MODULE6_HPP
