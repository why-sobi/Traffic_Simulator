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
    Stack<char> stack;
    dijkstra('A','G',stack,g);
    stack.display();
    return 0;
}