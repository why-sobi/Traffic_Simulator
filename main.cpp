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
    g.displayGraph();
    Stack<char> stack;
    AStar('A','G',stack,g);
    stack.display();
    return 0;
}