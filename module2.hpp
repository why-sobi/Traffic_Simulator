#ifndef MODULE2_HPP
#define MODULE2_HPP

#include <iostream>
#include "classes.hpp"
#include "functions.h"

void route_recalculation(Car*& car, Graph& graph)
{
	// for least priority call dijkstra to recalculate route else A*
	if (car->getPriority() == 0)
		dijkstra(car->getPath().topNode(), car->getEnding(), car->getPath(), graph);
	else
		AStar(car->getPath().topNode(), car->getEnding(), car->getPath(), graph);
}


#endif