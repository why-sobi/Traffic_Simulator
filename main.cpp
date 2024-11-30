#include "classes.hpp"
#include <iostream>
#include <string>
#include "functions.h"
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

using namespace std;

// Include the classes from the provided context here

// Function to stress test Car class
void testCar() {
    cout << "Testing Car Class..." << endl;
    Car car1("ABC123", 10, 20, 60, 1);
    Car car2("XYZ789", 15, 25, 80, 2);

    cout << "Car 1 Plate: " << car1.getPlate() << ", X: " << car1.getX() << ", Y: " << car1.getY() << ", Velocity: " << car1.getVelocity() << ", Priority: " << car1.getPriority() << endl;
    cout << "Car 2 Plate: " << car2.getPlate() << ", X: " << car2.getX() << ", Y: " << car2.getY() << ", Velocity: " << car2.getVelocity() << ", Priority: " << car2.getPriority() << endl;

    cout << "Comparing cars: " << (car1 > car2 ? "Car 1 has higher priority" : "Car 2 has higher priority") << endl;
}

// Function to stress test Map class
//void testMap() {
//    cout << "Testing Map Class..." << endl;
//    Map map;
//
//    Edge edge1("Road A", 10);
//    Edge edge2("Road B", 20);
//
//    map.insert(edge1, 100);
//    map.insert(edge2, 200);
//
//    cout << "Value for Road A: " << map[edge1] << endl;
//    cout << "Value for Road B: " << map[edge2] << endl;
//
//    map.reset(edge1);
//    cout << "Value for Road A after reset: " << map[edge1] << endl;
//}

// Function to stress test Graph class
//void testGraph() {
//    cout << "Testing Graph Class..." << endl;
//    Graph graph;
//
//    Edge road1("Highway 1", 5);
//    Edge road2("Highway 2", 10);
//
//    graph.addEdge(0, 1, road1);
//    graph.addEdge(1, 2, road2);
//    graph.addEdge(2, 0, Edge("Highway 3", 15)); // Adding another edge
//
//    cout << "Graph Adjacency Matrix:" << endl;
//    graph.displayMatrix();
//
//    graph.removeEdge(1, 2);
//    cout << "Graph Adjacency Matrix after removing edge (1, 2):" << endl;
//    graph.displayMatrix();
//}

// Function to stress test Stack class
void testStack() {
    cout << "Testing Stack Class..." << endl;
    Stack<int> stack;

    for (int i = 0; i < 10; i++) {
        stack.push(i);
        cout << "Pushed: " << i << endl;
    }

    stack.display();

    while (!stack.isEmpty()) {
        cout << "Popped: " << stack.pop() << endl;
    }
}

// Function to stress test Queue class
void testQueue() {
    cout << "Testing Queue Class..." << endl;
    Queue<int> queue;

    for (int i = 0; i < 10; i++) {
        queue.enqueue(i);
        cout << "Enqueued: " << i << endl;
    }

    queue.display();

    while (!queue.isEmpty()) {
        cout << "Dequeued: " << queue.peek() << endl;
        queue.dequeue();
    }
}

// Function to stress test MinHeap class
void testMinHeap() {
    cout << "Testing MinHeap Class..." << endl;
    MinHeap<int> minHeap;

    for (int i = 10; i >= 0; i--) {
        minHeap.insert(i);
        cout << "Inserted: " << i << endl;
    }

    cout << "MinHeap elements: ";
    minHeap.print();

    cout << "Popped Min: " << minHeap.pop() << endl;
    cout << "MinHeap after pop: ";
    minHeap.print();
}

// Function to stress test MaxHeap class
void testMaxHeap() {
    cout << "Testing MaxHeap Class..." << endl;
    MaxHeap<int> maxHeap;

    for (int i = 0; i <= 10; i++) {
        maxHeap.insert(i);
        cout << "Inserted: " << i << endl;
    }

    cout << "MaxHeap elements: ";
    maxHeap.print();

    cout << "Popped Max: " << maxHeap.pop() << endl;
    cout << " MaxHeap after pop: ";
    maxHeap.print();
}

int main() {
    Graph g;

    g.loadFromCSV("csv/road_network.csv");
    g.displayGraph();
    Stack<char> stack;
    dijkstra('A','G',stack,g);
    stack.display();
    return 0;
}