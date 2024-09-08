//queue.hpp
#ifndef QUEUE_H
#define QUEUE_H

#include<cstdlib>
#include<stdexcept>

using namespace std;

template <typename T>
class Queue
{
    private:
        T *array;           // Array to store the elements of the queue
        int capacity;       // Maximum capacity of the queue
        int size;           // Current size of the queue
        int front;          // Index of the front element
        int rear;           // Index of the rear element

    public:
        Queue(int capacity=10) : capacity(capacity), size(0), front(0), rear(-1) {
            array = new T[capacity];
        }

        ~Queue() {
            delete[] array;
        }

        void enqueue(T item) {
            if (isFull()) {
                throw runtime_error("Queue is full");
            }
            rear = (rear + 1) % capacity;   // Increment rear index circularly
            array[rear] = item;             // Add item to the rear of the queue
            size++;                         // Increase the size of the queue
        }

        T dequeue() {
            if (isEmpty()) {
                throw runtime_error("Queue is empty");
            }
            T item = array[front];           // Get the front element
            front = (front + 1) % capacity;  // Increment front index circularly
            size--;                         // Decrease the size of the queue
            return item;                     // Return the dequeued item
        }

        T front_element() {
            if (isEmpty()) {
                throw runtime_error("Queue is empty");
            }
            return array[front];              // Return the front element
        }

        bool isEmpty() {
            return size == 0;                  // Check if the queue is empty
        }

        bool isFull() {
            return size == capacity;           // Check if the queue is full
        }

        void display() {
            if (isEmpty()) {
                cout << "Queue is empty" << endl;
                return;
            }
            cout << "Queue: ";
            for (int i = front; i != rear; i = (i + 1) % capacity) {
                cout << array[i] << " ";       // Print each element of the queue
            }
            cout << array[rear] << endl;
        }
};

#endif
