#ifndef CLASSES_HPP
#define CLASSES_HPP

#include <iostream>

using namespace std;

#define BUCKETS 53
#define vertices 26

struct Edge
{
    string name;
    int Weight;
    explicit Edge(string name = "", const int w = -1) : name(std::move(name)), Weight(w) {}
};

class Car
{
    std::string plate;
    int x, y;
    int velocity;
    int priority;

public:
    Car(int P = 0) : priority(P) {}
    Car(std::string Plate, int X, int Y, int V, int P = 0) : plate(std::move(Plate)), x(X), y(Y), velocity(V), priority(P) {}

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    int getVelocity() const { return velocity; }
    int getPriority() const { return priority; }
    std::string getPlate() const { return plate; }

    // Setters
    void setX(int X) { x = X; }
    void setY(int Y) { y = Y; }
    void setVelocity(int V) { velocity = V; }
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
        return this->priority == obj.priority;
    }
};

class Map
{
    int arr[BUCKETS];

    // private functions
    int hashFunc(std::string name)
    {
        float hash = 0, KnuthConstant = 0.618033;

        for (char& c : name)
            hash += c;
        hash *= KnuthConstant;
        hash = int(BUCKETS * (hash - int(hash)));
        return int(hash);
    }

public:
    Map()
    {
        for (int i = 0; i < BUCKETS; i++)
        {
            arr[i] = 0;
        }
    }

    void insert(const Edge& obj, int val)
    {
        const int key = hashFunc(obj.name);
        arr[key] = val;
    }

    int& operator[](const Edge& obj)
    {
        const int key = hashFunc(obj.name);
        return arr[key];
    }

    void reset(const Edge& obj)
    {
        const int key = hashFunc(obj.name);
        arr[key] = 0;
    }
};

class Graph
{
    Edge adjacencyMatrix[vertices][vertices];
    int size;

public:
    Graph()
    {
        size = vertices;
    }

    // Add a weighted edge to the graph
    void addEdge(int i, int j, const Edge& road_name)
    {
        if (i < 0 || j < 0 || i >= size || j >= size)
        {
            cout << "Invalid vertex indices. Cannot add edge.\n";
            return;
        }
        if (road_name.Weight <= 0)
        {
            cout << "Invalid weight. Weight must be positive.\n";
            return;
        }

        adjacencyMatrix[i][j] = road_name; // Directed edge
        cout << "Edge added from " << i << " to " << j << " with weight " << road_name.Weight << ".\n";
    }

    // Remove edge from the graph
    void removeEdge(int i, int j)
    {
        if (i < 0 || j < 0 || i >= size || j >= size)
        {
            cout << "Invalid vertex indices. Cannot remove edge.\n";
            return;
        }

        if (adjacencyMatrix[i][j].Weight == -1)
        {
            cout << "No edge exists from " << i << " to " << j << " to remove.\n";
            return;
        }

        adjacencyMatrix[i][j].Weight = -1;
        adjacencyMatrix[i][j].name = "";
        cout << "Edge removed from " << i << " to " << j << ".\n";
    }

    void displayMatrix() const
    {
        for (int i = 0; i < size; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                if (adjacencyMatrix[i][j].Weight == -1)
                    cout << "   ";
                else
                    cout << adjacencyMatrix[i][j].name << " ";
            }
            cout << endl;
        }
    }

    // Check if an edge exists
    bool isEdge(int i, int j) const
    {
        if (i < 0 || j < 0 || i >= size || j >= size)
        {
            cout << "Invalid vertex indices. Cannot check edge.\n";
            return false;
        }
        return adjacencyMatrix[i][j].Weight != -1;
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
    Stack() : top(NULL) {}
    ~Stack()
    {
        removeAll();
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
        while (top)
        {
            StackNode<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        temp = nullptr;
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
class Heap
{
protected:
    T* heap;
    int capacity;
    int size;

    virtual void heapify_down() {}
    virtual void heapify_up() {}

public:
    Heap(int cap = 5) : capacity(cap), size(0)
    {
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
    virtual void merge(Heap<T>& to, Heap<T>& from)
    {
        // merge from heap into to heap
        while (!from.isEmpty())
        {
            T val = from.pop();
            to.insert(val);
        }
    }
    virtual void pathToRoot(int index)
    {
        if (index >= this->size)
            return;
        std::cout << "Path to root: ";
        for (int i = index; i >= 0; i = (i - 1) / 2)
        {
            std::cout << heap[i] << ' ';
        }
        std::cout << '\n';
    }
    virtual void TopMelements(int m)
    {
        T* arr = new int[this->size];

        for (int j = 0; j < this->size; j++)
        {
            int count = 0;
            int curr = this->heap[j];
            arr[j] = -1;
            for (int i = 0; i < this->size; i++)
            {
                if (curr == heap[i])
                    curr++;
            }
            arr[count] = curr;
        }

        for (int i = this->size; i >= 0; --i)
        {
            if (arr[i] != -1)
                std::cout << arr[i] << ' ';
        }
        delete[] arr;
    }
    virtual void range(T lower, T higher)
    {
        for (int i = 0; i < this->size; i++)
        {
            if (heap[i] >= lower && heap[i] <= higher)
                std::cout << this->heap[i] << ' ';
        }
        std::cout << '\n';
    }
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

    int getTopK(int k)
    {
        MaxHeap<T> temp(k);
        for (int i = 0; i < k; i++)
        {
            temp.insert(this->heap[i]);
        }
        return temp.peek();
    }

    void heapSort(T arr[], int n)
    {
        MaxHeap<T> temp(n);
        for (int i = 0; i < this->size; i++)
            temp.insert(arr[i]);
        for (int i = this->size - 1; i >= 0; i--)
            arr[i] = temp.pop();
    }
};


#endif //CLASSES_HPP