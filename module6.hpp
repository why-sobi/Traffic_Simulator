//
//

#ifndef MODULE6_HPP
#define MODULE6_HPP

#include "classes.hpp"
#include "functions.h"
#include "module4.hpp"

bool is_collision(Car& car1,Car& car2)
{
    // considering that the area of the car occupied in the visualization is 10, so detecting
    // collisions accordingly

    int area = 10;
    double halfSideLength = std::sqrt(area) / 2.0;

    // Check for overlap along both x and y axes
    return (std::abs(car1.getX() - car2.getX()) <= 2 * halfSideLength) &&
           (std::abs(car1.getY() - car2.getY()) <= 2 * halfSideLength);
}

void reRouteAllCars(Graph& matrix)
{
    // now we just have to give new path to each car in the current map, we can use module 2 for that
    // for each car in the graph/map call module 2 ka function
}

void block_routes(Graph& matrix, GraphNode& road)
{

    // This will be the node stored in the linked list ith index, meaning the road from (i to road) is going to be blocked
    // the route where there is a road closure or accident, set travel time to INT_MAX
    // returns the prev_value of the car

    road.backup_value = road.travelTime;
    road.travelTime = INT_MAX;
    road.is_blocked = true;
    reRouteAllCars(matrix);
}

void unblock_route(Graph& matrix, GraphNode& road)
{
    road.travelTime = road.backup_value;
    road.backup_value = 0;
    road.is_blocked = false;
    reRouteAllCars(matrix);
}


#endif //MODULE6_HPP
