#ifndef MODULDE4_HPP
#define MODULDE4_HPP

#include <iostream>
#include "classes.hpp"
#include "functions.h"

void reRouteCar(Graph& matrix, Stack<char>& carPath, char from)
{
	dijkstra(from, carPath.topNode(), matrix, false); // to get the fastest wrt to time path
}

#endif