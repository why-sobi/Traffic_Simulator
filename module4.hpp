#ifndef MODULDE4_HPP
#define MODULDE4_HPP

#include <iostream>
#include "classes.hpp"
#include "functions.h"

void reRouteCar(Graph& matrix, Car& car)
{
	Stack<char> path = car.getPath(); // returns reference of stack path
	char goal = car.getEnding(), source = car.getStarting(); // returns the starting and ending point of a car

	path.removeAll(); // empties the stack
	matrix.BFSpathFinding(source, goal, path); 
}

#endif