#ifndef MODULDE5_HPP
#define MODULDE5_HPP

#include "classes.hpp"
#include "functions.h"

void Emergency_handling(Graph& matrix, Car& emergency_car)
{

    // turn on emergency state i.e. Graph.emergency = true

    Stack<char> path = emergency_car.getPath(); // returns reference of stack path
    char goal = emergency_car.getEnding(), source = emergency_car.getStarting(); // returns the starting and ending point of a car

    path.removeAll(); // empties the stack
    AStar(matrix,source, goal, path);

    // After this the path of the emergency vehicle is set now it just have to follow that, based on the priority it
    // will move through the roads

    // Once emergency vehicle reaches definition turn off the emergency state, during emergency state we can set the
    // traffic signals to give priority to emergency vans/cars, meaning we have to check this only when the
    // emergency state is on otherwise just go with the normal flow

    // turn off once the emergency state is off
}


#endif