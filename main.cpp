#include <iostream>
#include <string>
#include <chrono>
#include "classes.hpp"
#include "functions.h"
#include "module2.hpp"
#include "module4.hpp"
#include "module5.hpp"
#include "module6.hpp"


void readAndAddCars(Graph& graph, const string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) { exit(1); }
    std::getline(file, line); // skipping the first line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, start, end, priority;

        // Split the line by commas
        std::getline(ss, name, ',');
        std::getline(ss, start, ',');
        std::getline(ss, end, ',');
        std::getline(ss, priority);

        Stack<char> path;
        if(name[0] == 'E')
            AStar(start[0],end[0],path,graph);
        else
            dijkstra(start[0], end[0], path, graph); // calling dijstraks to calculate path
        path.pop();
        string next_path = "";
        next_path += start[0];
        next_path += path.topNode();
        Car* car = new Car(name, start[0], end[0], path, (priority == "High") ? 2 : (priority == "Medium") ? 1 : 0, graph.get_road_weight(next_path));
        graph.addCar(next_path,car); // inserting all cars
    }
    file.close();

}
void load_cars(Graph& graph, const string& filename = "csv/vehicles.csv", const string& filename2 = "csv/emergency_vehicles.csv") {
    readAndAddCars(graph, filename);
    readAndAddCars(graph, filename2);
}
void writeMenu(WINDOW*& menu) {
    wclear(menu);
    box(menu, 0, 0);
    
    mvwprintw(menu, 0, menu->_maxx / 2 - 2, "MENU");
    mvwprintw(menu, 1, 1, "1. Display City Traffic Network!");
    mvwprintw(menu, 2, 1, "2. Display Traffic Signal Status!");
    mvwprintw(menu, 3, 1, "3. Display Congestion Status!");
    mvwprintw(menu, 4, 1, "4. Display Road Status!");
    mvwprintw(menu, 5, 1, "5. Handle Emergency vehicle routing!");
    mvwprintw(menu, 6, 1, "6. Block Road!");
    mvwprintw(menu, 7, 1, "7. Simulate vechicle Routing!");
    mvwprintw(menu, 8, 1, "8. Exit Simulation!");

    wrefresh(menu);
}

int main() {
    Graph graph;
    graph.loadFromCSV("csv/road_network.csv");
    load_cars(graph);
    graph.readRoadSituations();
    graph.readGreenTime();

    // Initialize ncurses with additional setup
    initscr();            // Start curses mode
    cbreak();             // Line buffering disabled
    curs_set(0);
    noecho();             // Don't echo() while we getch
    keypad(stdscr, TRUE); // We get F1, F2 etc..

    // Refresh the main screen
    refresh();

    // Create three windows with recommended sizes
    WINDOW* menu = newwin(10, 150, 0, 0);      // Window for Menu
    WINDOW* output = newwin(28, 150, 10, 0);   // window for output
    if (menu == nullptr)
    {
        std::cerr << "Error creating menu window!" << std::endl;
        exit(1);  // Exit or handle gracefully
    }
    box(menu, 0, 0); // outline screen 
    box(output, 0, 0);

    wrefresh(menu);
    wrefresh(output);

    writeMenu(menu);
    
    char ch = 'A';
    bool end = false;
    
    auto start = std::chrono::high_resolution_clock::now(); // to keep check how many seconds have passed

    while (!end) {
        ch = getch();
        switch (ch)
        {
        case '1':
            graph.printIntersections(output);
            break;
        case '2':
            graph.printGreenLightTime(output);
            break;
        case '3':
            graph.printCongestionStatus(output);
            break;
        case '4':
            graph.printRoadStatus(output);
            break;
        case '5':
            // gotta write
            break;

        case '6':
        {
            string roadName = graph.blockRoad(output);
            if (roadName != "")
                block_routes(graph, roadName, output);
            break;
        }
        case '7':
            graph.printCarPaths(output);
            break;
        case '8':
            end = true;
            break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time_passed = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        start = end;
        
        if (time_passed.count() >= 1) {
            change_signals_state(time_passed.count(), graph);
            change_car_state(time_passed.count(), graph);
        }
    }
    delwin(menu);
    delwin(output);
    endwin(); // End curses mode

    return 0;
}
