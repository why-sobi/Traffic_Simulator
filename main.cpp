#include "classes.hpp"
#include <iostream>
#include <string>
#include "functions.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;


int main() {
    Graph g;

    g.loadFromCSV("csv/road_network.csv");
    // g.displayGraph();
    // Stack<char> stack;
    // g.BFSpathFinding('A','M',stack);
    // stack.display();
    // dijkstra('A','M',stack,g);
    // stack.display();
    g.set_coordinates_of_intersection();
    return 0;
}