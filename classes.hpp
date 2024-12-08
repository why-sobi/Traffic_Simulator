#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <curses.h>

using namespace std;

enum CONSTANTS {
    EDGES = 41,
    CARS = 53,     // Cars
    vertices = 26
};

bool isPrime(int num) {
    int count = 0;
    int start = sqrt(num);

    while (start > 0) {
        if (num % start == 0) count++;
        start--;
    }

    return count == 1;
}
int getNextPrime(int num)
{
    if (isPrime(num)) return num;
    while (!isPrime(num)) num++;
    return num;
}
bool isAlphaChar(std::string str) {
    for (int i = 0; i < str.length(); i++)
        if (str[i] < 'A' || str[i] > 'Z') {
            return false;
        }
    return true;
}

template <typename T1, typename T2>
class Pair {
    T1 first;
    T2 second;

public:
    // Default constructor
    Pair() : first(T1()), second(T2()) {}

    // Parameterized constructor
    Pair(T1 f, T2 s) : first(f), second(s) {}

    // Getter methods
    T1& getFirst()  {
        return first;
    }

    T2& getSecond()  {
        return second;
    }

    // Setter methods
    void setFirst(T1 f) {
        first = f;
    }

    void setSecond(T2 s) {
        second = s;
    }

    // Display function
    friend ostream& operator <<(ostream& out, Pair& obj)
    {
        out << "(" << obj.first << ", " << obj.second << ")" << endl;
        return out;
    }
};

template <typename T>
class Heap
{
protected:
    T* heap;
    int capacity;
    int size;

    virtual void heapify_down() {}
    virtual void heapify_up() {}

public:
    Heap(int cap) : capacity(cap)
    {
        size = 0;
        this->heap = new T[capacity];
    }
    virtual ~Heap()
    {
        if (heap)
        {
            delete[] heap;
        }
        heap = nullptr;
    }

    // Methods
    virtual void insert(T& value)
    {
        if (this->size == capacity)
        {
            capacity *= 2;
            T* temp = new T[capacity];
            for (int i = 0; i < this->size; i++)
            {
                temp[i] = heap[i];
            }
            delete[] heap;
            heap = temp;
        }
        heap[this->size++] = value;
        heapify_up();
        return;
    }
    virtual T pop()
    {
        T val = heap[0];
        heap[0] = heap[--this->size];

        heapify_down();
        return val;
    }
    virtual T peek() { return heap[0]; }
    virtual bool isEmpty() { return this->size == 0; }
    virtual int getSize() const { return this->size; }
    void print()
    {
        for (int i = 0; i < this->size; i++)
            std::cout << heap[i] << ' ';
        std::cout << '\n';
    }
};

template <typename T>
class MinHeap : public Heap<T>
{
public:
    MinHeap() : Heap<T>(5){}
    MinHeap(int cap) : Heap<T>(cap){}
    void heapify_down()
    {
        int i = 0;
        while (i < this->size)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            // only one child can be larger since it is heapified after each node insertion and deletion
            if (left < this->size && this->heap[left] < this->heap[largest])
                largest = left;
            if (right < this->size && this->heap[right] < this->heap[largest])
                largest = right;

            if (largest != i)
            {
                std::swap(this->heap[i], this->heap[largest]);
            }
            i++;
        }
    }

    void heapify_up()
    {
        int i = this->size - 1;
        while (i >= 0)
        {
            // calculation of parent
            int parent = (i - 1) / 2;
            if (this->heap[parent] > this->heap[i])
            {
                std::swap(this->heap[parent], this->heap[i]);
            }
            if (i == 0)
                break;
            i = parent;
        }
    }

    void heapifySort(T arr[], int n)
    {
        MinHeap<T> temp(n);
        for (int i = 0; i < this->size; i++)
            temp.insert(arr[i]);
        for (int i = 0; i < this->size; i++)
            arr[i] = temp.pop();
    }
};

template <typename T>
class MaxHeap : public Heap<T>
{
    public:
    MaxHeap() : Heap<T>(5){}
    MaxHeap(int cap) : Heap<T>(cap){}
    void heapify_down()
    {
        int i = 0;
        while (i < this->size)
        {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int largest = i;

            // only one child can be larger since it is heapified after each node insertion and deletion
            if (left<this->size && this->heap[left]> this->heap[largest])
                largest = left;
            if (right<this->size && this->heap[right]> this->heap[largest])
                largest = right;
            if (largest != i)
            {
                std::swap(this->heap[i], this->heap[largest]);
            }
            i++;
        }
    }
    void heapify_up()
    {
        int i = this->size - 1;
        while (i >= 0)
        {
            // calculation of parent
            int parent = (i - 1) / 2;
            if (this->heap[parent] < this->heap[i])
            {
                std::swap(this->heap[parent], this->heap[i]);
            }
            if (i == 0)
                break;
            i = parent;
        }
    }
    void delete_object(T& car)
    {
        int deleteIndex = -1;
        for(int i = 0; i < this->size; i++)
        {
            if (this->heap[i] == car)
            {
                deleteIndex = i;
                break;
            }
        }
        if(deleteIndex != -1)
            return;
        this->heap[deleteIndex] = this->heap[this->size - 1];
        --this->size;
        heapify_down();
    }
};

template <typename T>
class QueueNode
{
public:
    T data;
    QueueNode* next;

    QueueNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class Queue
{
private:
    QueueNode<T>* front;
    QueueNode<T>* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    ~Queue()
    {
        while (front)
        {
            dequeue();
        }
    }

    void enqueue(T x)
    {
        QueueNode<T>* newNode = new QueueNode<T>(x);
        if (!rear)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    T peek() {
        if (front == nullptr) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }

    void dequeue()
    {
        if (!front)
        {
            cout << "Queue empty\n";
            return;
        }
        QueueNode<T>* temp = front;
        front = front->next;
        if (!front)
        {
            rear = nullptr;
        }
        delete temp;
    }
    bool isEmpty()
    {
        return front == nullptr;
    }

    void display()
    {
        if (!front)
        {
            cout << "Queue empty\n";
            return;
        }
        QueueNode<T>* temp = front;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

template <typename T>
class StackNode
{
public:
    T data;
    StackNode* next;
    StackNode(T d) : data(d), next(nullptr) {}
};

template <typename T>
class Stack
{
    StackNode<T>* top;

public:
    Stack() : top(nullptr) {}
    ~Stack()
    {
        removeAll();
    }
    void moveOwnershipTo(Stack<T>& to) {
        to.top = this->top;
        this->top = nullptr;
    }
    void push(T val)
    {
        if (top)
        {
            StackNode<T>* newNode = new StackNode<T>(val);
            newNode->next = top;
            top = newNode;
            return;
        }
        top = new StackNode<T>(val);
    }
    T pop()
    {
        if (top)
        {
            T rVal = top->data;
            StackNode<T>* temp = top;
            top = top->next;
            delete temp;
            return rVal;
        }
        return T(); // Return default value for type T
    }
    T topNode()
    {
        if (top)
        {
            return top->data;
        }
        throw runtime_error("Stack is empty. No top node available.");
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    void removeAll()
    {
        StackNode<T>* temp = top;
        while (temp)
        {
            StackNode<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        top = nullptr;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty.\n";
            return;
        }
        StackNode<T>* temp = top;
        cout << "Stack: ";
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    StackNode<T>* getTop() { return top; }
};

template <typename T>
class DynamicArr
{
    T* arr = nullptr;
    int size = 0;
    int pos = 0;

    // private methods
    void allocateDouble()
    {
        T* temp = new T[size * 2];
        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        size *= 2;
        arr = temp;
    }

public:
    // Constructor
    DynamicArr() : size(0), pos(0), arr(nullptr) {}
    DynamicArr(int s) : size(s), pos(0), arr(new T[s]) {}
    DynamicArr(const DynamicArr<T>& obj)
    {
        if (!obj.arr)
            return;
        if (this->arr)
        {
            this->~DynamicArr();
        }
        if (!this->arr)
        {
            this->arr = new T[obj.size];
        }

        this->size = obj.size;
        this->pos = obj.pos;

        for (int i = 0; i < obj.pos; i++)
        {
            this->arr[i] = obj.arr[i];
        }
    }

    // Destructor
    ~DynamicArr()
    {
        if (arr)
        {
            delete[] arr;
            arr = nullptr;
        }
    }

    // Methods
    void push(T val)
    {
        if (!arr)
        {
            arr = new T[1];
            size = 1;
        }
        arr[pos++] = val;
        if (pos == size)
        {
            allocateDouble();
        }
    }

    T pop()
    {
        if (arr)
        {
            T val = arr[--pos];
            return val;
        }
        throw std::runtime_error("Cannot pop empty array");
    }

    bool isEmpty() const
    {
        return pos == 0;
    }

    void clear()
    {
        delete[] arr;
        arr = nullptr;
        size = 0;
        pos = 0;
    }

    void shrinkToFit()
    {
        if (size == 0 || pos == 0 || pos == size)
            return;
        T* newArr = new T[pos];

        for (int i = 0; i < pos; i++)
        {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        size = pos;
    }

    // Getters
    int getSize() const
    {
        return pos;
    }

    int getAllocated() const
    {
        return size;
    }

    // overloading operators
    void operator=(const DynamicArr<T>& obj)
    {
        if (this->arr)
        {
            this->~DynamicArr();
        }
        this->arr = new T[obj.size];

        this->size = obj.size;
        this->pos = obj.pos;

        for (int i = 0; i < obj.pos; i++)
        {
            this->arr[i] = obj.arr[i];
        }
    }
    T& operator[](int index)
    {
        if (index >= 0 && index < size)
        {
            return arr[index];
        }
        throw std::out_of_range("Index out of range");
    }
};

template <typename T>
class LinkedList
{

public:
    struct Node
    {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

private:
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {

        while (size > 0)
        {

            removeAtStart();
        }
    }

    Node* getHead() const
    {
        return head;
    }

    Node* getNode(int index) const
    {

        if (index < 0 || index >= size)
        {

            std::cout << "Index out of range!" << '\n';
            return nullptr;
        }

        Node* current = head;

        for (int i = 0; i < index; i++)
        {

            current = current->next;
        }

        return current;
    }
    Node* findNode(char val) {
        for (Node* curr = head; curr; curr = curr->next) {
            if (curr->data == val) {
                return curr;
            }
        }
        return nullptr;
    }
    void insertAtStart(T &value)
    {

        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void insertAtEnd(T &value)
    {

        Node* newNode = new Node(value);

        if (isEmpty())
        {

            head = newNode;
        }

        else
        {

            Node* tail = getNode(size - 1);

            if (tail)
            {

                tail->next = newNode;
            }
        }

        size++;
    }

    void insertAtIndex(int index, T &value)
    {

        if (index < 0 || index > size)
        {

            std::cout << "Index out of range!" << '\n';
            return;
        }

        if (index == 0)
        {

            insertAtStart(value);
        }

        else if (index == size)
        {

            insertAtEnd(value);
        }

        else
        {

            Node* prev = getNode(index - 1);

            if (prev)
            {

                Node* newNode = new Node(value);
                newNode->next = prev->next;
                prev->next = newNode;
                size++;
            }
        }
    }

    void removeAtStart()
    {

        if (isEmpty())
        {

            std::cout << "List is empty!" << '\n';
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
        size--;
    }

    void removeAtEnd()
    {

        if (isEmpty())
        {

            std::cout << "List is empty!" << '\n';
            return;
        }

        if (size == 1)
        {

            removeAtStart();
            return;
        }

        Node* prev = getNode(size - 2);

        if (prev)
        {

            delete prev->next;
            prev->next = nullptr;
            size--;
        }
    }

    void removeAtIndex(int index)
    {

        if (index < 0 || index >= size)
        {

            std::cout << "Index out of range!" << '\n';
            return;
        }

        if (index == 0)
        {

            removeAtStart();
        }

        else
        {

            Node* prev = getNode(index - 1);

            if (prev && prev->next)
            {

                Node* temp = prev->next;
                prev->next = temp->next;
                delete temp;
                size--;
            }
        }
    }

    void delete_objects()
    {
        for(Node* curr = head; curr; curr = curr->next)
        {
            delete curr->data;
            curr->data = nullptr;
        }
    }

    bool isEmpty() const
    {

        return size == 0;
    }

    void display() const
    {

        if (isEmpty())
        {

            std::cout << "List is empty!" << '\n';
            return;
        }

        Node* current = head;

        while (current)
        {

            std::cout << current->data << " -> ";
            current = current->next;
        }

        std::cout << "nullptr" << '\n';
    }

    int getSize() const
    {

        return size;
    }
    Node* return_Head()
    {
        return head;
    }
};

class Car
{
    std::string plate;
    int priority;
    char starting, ending;
    int current_time;
    Stack<char> path;

public:
    Car(int P = 0) : priority(P) {}
    Car(std::string Plate, char Start, char End, Stack<char>& Path, int P = 0, int ct = 0) : plate(std::move(Plate)), priority(P), starting(Start), ending(End), current_time(ct) {
        Path.moveOwnershipTo(path);
    }
    Car(Car& obj) {
        *this = obj;
        obj.path.moveOwnershipTo(this->path);
    }

    // Getters
    int getPriority() const { return priority; }
    char getStarting() const { return starting; }
    void setStarting(char s) { starting = s; }
    char getEnding() const { return ending; }
    std::string getPlate() const { return plate; }
    Stack<char>& getPath() { return path; }
    // Setters
    void setPlate(const std::string& Plate) { plate = Plate; }

    // Operator overload
    bool operator>(const Car& obj) const
    {
        return this->priority > obj.priority;
    }

    bool operator<(const Car& obj) const
    {
        return this->priority < obj.priority;
    }

    bool operator==(const Car& obj) const
    {
        return this->plate == obj.plate;
    }

    int getCurrentTime()
    {
        return current_time;
    }
    void setCurrentTime(int t)
    {
        current_time = t;
    }

    // Util Functions
    void printPath(WINDOW*& path_win, int x, int y) {
        /*mvwprintw(path_win, y, x, "%s with priority: %s", plate.c_str(), std::to_string(priority).c_str());
        x += 22;*/
        mvwprintw(path_win, y, x, "%s ", plate.c_str());
        x += 5;
        for (StackNode<char>* curr = path.getTop(); curr; curr = curr->next, x += 2) {
            mvwprintw(path_win, y, x, "%c ", curr->data);
        }
    }
};

template <typename T>
class Set
{
    T *arr;   // Pointer to an array that stores the characters in the set
    int size; // Size of the array

    void setDefault(int *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = INT_MAX;
    }
    void setDefault(char *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = '\0';
    }
    void setDefault(std::string *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = "";
    }

    bool checkDefault(std::string &str) { return str == ""; }
    bool checkDefault(char &ch) { return ch == '\0'; }
    bool checkDefault(int &num) { return num == INT_MAX; }

    // Multiplies the ASCII value of the character by 7 and takes modulo with size
    // 7 is a small prime number that helps in reducing collisions
    // (31, 37, 13, 41 etc) also can work but better to check through trial and error
    // 7 in this case have no collisions

    int hashFunction(int value) { return (value * 7) % size; }
    int hashFunction(std::string str)
    {
        int hash = 0;
        for (int i = 0; i < str.length(); i++)
            hash += str[i];

        return (hash * 7) % size;
    }
    int hashFunction(char ch) { return (int(ch) * 7) % size; }
    int linearProbe(int index) { return (index + 1) % size; }

public:
    // Constructor to initialize the set with a given size
    Set(int s = 31) : size(s)
    {
        arr = new T[size]; // Allocate memory for the array
        setDefault(arr);
    }

    // Destructor to clean up the allocated memory
    ~Set()
    {
        if (arr)          // Check if arr is not null
            delete[] arr; // Deallocate memory
        arr = nullptr;    // Set pointer to null
    }

    // Method to insert a character into the set
    void insert(T key_val)
    {
        int start = hashFunction(key_val); // Get the initial hash index
        if (arr[start] == key_val)
            return; // If the character is already present, do nothing
        int i = linearProbe(start);
        while (!checkDefault(arr[i])) // Linear probing to find an empty slot
        {
            i = linearProbe(i); // Get the next index using the hash function
            if (i == start)
                return; // If we've looped back to the start, the set is full
        }
        arr[i] = key_val; // Insert the character at the found index
    }

    // Method to check if a character is in the set
    bool has(T key_val)
    {
        int start = hashFunction(key_val); // Get the initial hash index
        if (arr[start] == '\0')
            return false; // If the slot is empty, the character is not present
        else if (arr[start] == key_val)
            return true; // If the character matches, return true

        int i = linearProbe(start); // Start probing from the next index
        while (!checkDefault(arr[i]) && arr[i] != key_val)
        {
            i = linearProbe(i); // Continue probing
            if (i == start)
                return false; // If we've looped back to the start, the character is not found
        }
        return arr[i] == key_val; // Return true if the character was found
    }

    // Method to print the contents of the set
    void print()
    {
        for (int i = 0; i < size; i++)
            checkDefault(arr[i]) ? std::cout << '.' : std::cout << arr[i] << ' '; // Print '.' for empty slots
        std::cout << '\n';                                                  // New line after printing all elements
    }
};

template <typename T, typename M>
class Map
{
public:
    T *key;
    M *value;
    int size;

    void setDefault(int *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = INT_MAX;
    }
    void setDefault(char *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = '\0';
    }
    void setDefault(std::string *&arr)
    {
        for (int i = 0; i < size; i++)
            arr[i] = "";
    }

    bool checkDefault(std::string &str) { return str == ""; }
    bool checkDefault(char &ch) { return ch == '\0'; }
    bool checkDefault(int &num) { return num == INT_MAX; }

    int hashFunction(int value) { return (value * 7) % size; }
    int hashFunction(std::string str)
    {
        int hash = 0;
        for (int i = 0; i < str.length(); i++)
            hash += str[i];

        return (hash * 7) % size;
    }
    int hashFunction(char ch) { return (int(ch) * 7) % size; }
    int linearProbe(int index) { return (index + 1) % size; }

public:
    Map(int s)
    {
        size = getNextPrime(s);
        key = new T[size];
        value = new M[size];

        setDefault(key);
    }
    ~Map()
    {
        if (key)
            delete[] key;
        if (value)
            delete[] value;

        key = nullptr;
        value = nullptr;
    }

    void insert(T key_val, M val_val)
    {
        int start = hashFunction(key_val);
        if (checkDefault(key[start]) || key[start] == key_val) {
            key[start] = key_val;
            value[start] = val_val;
            return;
        }

        int i = linearProbe(start);

        while (!checkDefault(key[i]))
        {
            if (i == start)
                throw std::runtime_error("Map is full");
            i = linearProbe(i);
        }

        if (checkDefault(key[i])) {
            key[i] = key_val;
        }
        value[i] = val_val;

    }

    bool find(T key_val)
    {
        int start = hashFunction(key_val);
        if (checkDefault(key[start]))
            return false;
        else if (key[start] == key_val) return true;

        int i = linearProbe(start);
        while (!checkDefault(key[i]) && key[i] != key_val)
        {
            if (i == start)
                return false;
            i = linearProbe(i);
        }
        if (checkDefault(key[i]))
            return false;
        return true;
    }

    M &operator[](T key_val)
    {
        if(!find(key_val))
            throw std::runtime_error("Invalid KEY!\n");
        int start = hashFunction(key_val);
        if (checkDefault(key[start]))
            throw std::runtime_error("Invalid KEY!\n");
        else if (key[start] == key_val) return value[start];

        int i = linearProbe(start);
        while (!checkDefault(key[i]) && key[i] != key_val)
        {
            if (i == start)
                throw std::runtime_error("Map is full");
            i = linearProbe(i);
        }
        if (checkDefault(key[i])) {
            throw std::runtime_error("Invalid KEY!\n");
        }
        return value[i];
    }

    void print() {
        for (int i = 0; i < size; i++) {
            checkDefault(key[i]) ? std::cout << "Def : ...\n" : std::cout << key[i] << " : " << value[i] << '\n';
        }
    }

    int getSize(){ return size; }
    DynamicArr<T> getKeys() {
        DynamicArr<T> keys_val;
        for (int i = 0; i < size; i++) {
            if (!checkDefault(key[i])) keys_val.push(key[i]);
        }
        return keys_val;
    }

};

struct GraphNode
{
    char targetIntersection;
    int travelTime; // weight
    int heuristic_value;
    int backup_value;
    std::string status;

    GraphNode(char target = '\0', int time = INT_MAX) : targetIntersection(target), travelTime(time), heuristic_value(INT_MAX), backup_value(0), status("Clear")
    {}

    friend ostream& operator << (ostream& out, GraphNode& obj)
    {
        out << obj.targetIntersection << " ";
        out << obj.travelTime;
        return out;
    }

    bool operator>(const GraphNode& obj) const
    {
        return this->travelTime > obj.travelTime;
    }
    bool operator<(const GraphNode& obj) const
    {
        return this->travelTime < obj.travelTime;
    }
    bool operator==(const GraphNode& obj) const
    {
        return this->travelTime == obj.travelTime;
    }

    bool operator == (char at) const {
        return this->targetIntersection == at;
    }

    friend std::ostream& operator << (std::ostream& out, const GraphNode& obj) {
        out << obj.targetIntersection;
        return out;
    }
};

// Graph Class to manage intersections and roads
class Graph
{
    /*Map<char,string> intersection_coordinates;*/
public:
    Map<string,MaxHeap<Car*>> carCount;
    Map<char, Pair<bool, Pair<int, int>>> greenTime;
    LinkedList<Car*> cars;
    LinkedList<GraphNode> adjacencyList[vertices];
    int vertexCount;

    Graph(): carCount(CARS), /*intersection_coordinates(vertices),*/ greenTime(CONSTANTS::vertices)
    {
        vertexCount = vertices;
    }

    // Add an edge (road) between two intersections
    void addEdge(char from, char to, int travelTime)
    {
        int fromIndex = from - 'A';  // Convert character to index (A=0, B=1, ..., Z=25)
        if (fromIndex < 0 || fromIndex >= vertexCount)
        {
            cout << "Invalid intersection!" << endl;
            return;
        }
        std::string roadName = "";
        roadName += from;
        roadName += to;

        GraphNode newNode(to, travelTime);
        adjacencyList[fromIndex].insertAtStart(newNode);
    }
    void addCar(string& roadName,Car*& car)
    {
        cars.insertAtStart(car);
        carCount[roadName].insert(car);
    }

    void displayGraph()
    {
        for (int i = 0; i < vertexCount; i++)
        {
            char intersection = 'A' + i;
            cout << "Intersection " << "with " << intersection << " has roads to : " << endl;
            adjacencyList[i].display();
        }
    }

    void print_path_and_weight()
    {
        for (LinkedList<Car*>::Node* temp = cars.getHead(); temp; temp = temp->next)
        {
            int weight = get_weight_of_path(temp->data->getPath().getTop());
            cout << weight << " ";
            cout << temp->data->getPath().getTop() << endl;
        }
    }

    int get_weight_of_path(StackNode<char>* path)
    {
        string roadName = "";
        StackNode<char>* temp = path;
        roadName += temp->data;
        temp = temp->next;
        int weight = 0;
        for(; temp; temp = temp->next)
        {
            roadName += temp->data;
            weight += get_road_weight(roadName);
            roadName = roadName[0];
        }
        return weight;
    }
    // Load graph from a CSV file
    void loadFromCSV(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string intersection1, intersection2;
            int travelTime;
            getline(ss, intersection1, ',');
            getline(ss, intersection2, ',');
            ss >> travelTime;
            // Add the edge to the graph
            addEdge(intersection1[0], intersection2[0], travelTime);
        }
        file.close();
    }
    /*void load_coordinates(const string& filename = "csv/intersection.csv")
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        getline(file, line);

        while (getline(file, line))
        {
            stringstream ss(line);
            string intersection, intersection2;
            getline(ss, intersection, ',');
            getline(ss, intersection2);
            intersection_coordinates.insert(intersection[0], intersection2);
        }
        file.close();
    }*/
    void readRoadSituations(const string& filename = "csv/road_closures.csv") {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        getline(file, line); // skipping the first line

        while (getline(file, line))
        {
            stringstream ss(line);
            string intersection, intersection2, status;
            getline(ss, intersection, ',');
            getline(ss, intersection2, ',');
            getline(ss, status);

            std::string road = intersection + intersection2;
            if (road.length() == 2)
                setRoadSituation(road, status);
        }
        file.close();
    }
    void readGreenTime(const string& filename = "csv/traffic_signals.csv") {
        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error opening file!" << endl;
            return;
        }

        string line;
        getline(file, line); // skipping the first line

        while (getline(file, line))
        {
            stringstream ss(line);
            string intersection, time;
            getline(ss, intersection, ',');
            getline(ss, time);

            Pair<int, int> timeInfo(std::stoi(time), std::stoi(time)); // time left, default time period
            Pair<bool, Pair<int, int>> intersectionInfo(true, timeInfo); // not 1 because computational cost

            greenTime.insert(intersection[0], intersectionInfo);
        }
        file.close();
    }

    int heuristic(char start, char goal)
    {
        // Pair<int, int> startCoords = get_coordinates(start);
        // Pair<int, int> goalCoords = get_coordinates(goal);
        // int d1 = startCoords.getFirst() - goalCoords.getFirst();
        // int d2 = startCoords.getSecond() - goalCoords.getSecond();
        // return sqrt(d1 * d1 + d2 * d2);
        Stack<char> path;
        BFSpathFinding(start, goal,path);
        int length = -1;
        while(!path.isEmpty())
        {
            path.pop();
            length++;
        }
        return length;
    }

    // Algos
    void BFSpathFinding(char source, char goal, Stack<char>& path) const {
        Queue<char> q;
        Set<char> visited(vertices); // as their are at max 26 vertices, closest prime number is 31
        Map<char, char> map(vertices);

        map.insert(source, '\0'); // considering source has no papa

        q.enqueue(source);
        bool done = false;

        while (!q.isEmpty() && !done)
        {
            char ch = q.peek();
            q.dequeue();
            visited.insert(ch); // to keep check of what nodes have been passed

            int childrenListIndex = ch - 'A';

            for (LinkedList<GraphNode>::Node* curr = adjacencyList[childrenListIndex].getHead(); curr && !done; curr = curr->next) {
                char currentChar = curr->data.targetIntersection;
                map.insert(currentChar, ch); // to keep track of papa beta relationship

                if (currentChar == goal) { // found goal node
                    done = true;
                }
                if (!visited.has(currentChar)) // add to visited set
                    q.enqueue(currentChar);
            }
        }
        // if goal wasn't found empty the path
        if (!done) {
            while (!path.isEmpty()) path.pop();
            return;
        }
        // else find the path by parent back tracking
        while (goal != source) {
            path.push(goal);
            goal = map[goal];
        }
        path.push(source);
    }

    // Setter/Getters/Utils
    /*Pair<int, int> get_coordinates(char intersection)
    {
        string coords = intersection_coordinates[intersection];
        int pos = coords.find(',');
        int x = stoi(coords.substr(0, pos));
        int y = stoi(coords.substr(pos + 1));
        return Pair<int, int>(x, y);
    }*/
    int get_Car_count(string& roadName)
    {
        return carCount[roadName].getSize();
    }
    void setRoadSituation(std::string roadName, std::string status) {
        LinkedList<GraphNode>::Node* found = adjacencyList[roadName[0] - 'A'].findNode(roadName[1]);
        if (found) {
            found->data.status = status;
        }
    }
    std::string getRoadSituation(std::string roadName) {
        LinkedList<GraphNode>::Node* found = adjacencyList[roadName[0] - 'A'].findNode(roadName[1]);        // getting the Graph node B from road A to B
        if (found == nullptr) return "None";
        return found->data.status;
    }

    std::string blockRoad(WINDOW*& output) {
        wclear(output);
        box(output, 0, 0);

        int col = 19;
        mvwprintw(output, 1, 1, "Enter Road Name: ");
        wrefresh(output);

        std::string roadName = "";
        char ch;

        while ((ch = getch()) != '\n')
        {
            mvwprintw(output, 1, col++, "%c", ch);
            roadName += ch;
            wrefresh(output);
        }

        if (roadName.length() != 2 || !isAlphaChar(roadName)) {
            mvwprintw(output, 2, 1, "Road doesn't exist!");
            wrefresh(output);
            return "";
        }
        return roadName;
    }

    int get_road_weight(std::string roadName)
    {
        LinkedList<GraphNode>::Node* found = adjacencyList[roadName[0] - 'A'].findNode(roadName[1]);
        return found->data.travelTime;
    }

    // printing functions
    void printIntersections(WINDOW*& roads) {
        wclear(roads);
        box(roads, 0, 0);

        for (int i = 0; i < CONSTANTS::vertices; i++) {
            char intersection = ('A' + i);
            mvwprintw(roads, i + 1, 1, "%c leads to ", intersection);
            int x = 12;
            for (LinkedList<GraphNode>::Node* curr = adjacencyList[i].getHead(); curr; curr = curr->next, x += 7) {
                char ch = curr->data.targetIntersection;
                std::string weight = std::to_string(curr->data.travelTime);
                mvwprintw(roads, i + 1, x, "(%c,%s) ", ch, weight.c_str());
            }
        }
        wrefresh(roads);
    }
    void printCarPaths(WINDOW*& path_win) {
        wclear(path_win);
        box(path_win, 0, 0);

        int row = 1;
        int col = 1;

        for (LinkedList<Car*>::Node* curr = cars.getHead(); curr; curr = curr->next) {
            curr->data->printPath(path_win, col, row);
            col += 26;
            if (col > 100) {
                col = 1;
                row++;
            }
        }
        wrefresh(path_win);
    }
    void printRoadStatus(WINDOW*& output) {
        wclear(output);
        box(output, 0, 0);

        int row = 1, col = 1;
        DynamicArr<std::string> keys = carCount.getKeys();
        for (int i = 0; i < keys.getSize(); i++) {
            mvwprintw(output, row, col, "Road %s: %s", keys[i].c_str(), getRoadSituation(keys[i]).c_str());
            col += 40;
            if (col > 121) {
                col = 1;
                row++;
            }
        }
        wrefresh(output);
    }
    void printCongestionStatus(WINDOW*& output) {
        wclear(output);
        box(output, 0, 0);

        int row = 1, col = 1;
        DynamicArr<std::string> keys = carCount.getKeys();
        for (int i = 0; i < keys.getSize(); i++) {
            std::string vNumber = std::to_string(carCount[keys[i]].getSize());
            mvwprintw(output, row, col, "Road %s has %s Vehicles!", keys[i].c_str(), vNumber.c_str());
            col += 40;
            if (col > 121) {
                col = 1;
                row++;
            }
        }

        wrefresh(output);
    }
    void printGreenLightTime(WINDOW*& output) {
        wclear(output);
        box(output, 0, 0);

        int row = 1, col = 1;
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            int timeLeft = greenTime[ch].getSecond().getFirst(); // greenTime[ch].getSecond() returns a Pair<int, int>
            if (greenTime[ch].getFirst()) {
                mvwprintw(output, row, col, "Intersection %c green for %d s", ch, timeLeft);
            }
            else {
                mvwprintw(output, row, col, "Intersection %c red for %d s", ch, timeLeft);
            }
            col += 50;
            if (col > 101) {
                col = 1;
                row++;
            }
        }
        wrefresh(output);
    }

    ~Graph()
    {
        cars.delete_objects();
    }
};


#endif //CLASSES_HPP