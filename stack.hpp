////stack.hpp
//#ifndef STACK_H
//#define STACK_H
//#include<cstdlib>
//#include<stdexcept>
//
//using namespace std;
//template <typename T>
//
//class Stack
//{
//    private:
//        T *array;           // Array to store the elements of the stack
//        int capacity;       // Maximum capacity of the stack
//        int top;            // Index of the top element
//    public:
//        Stack(int capacity=10) : capacity(capacity), top(-1) {
//            array = new T[capacity];
//        }
//        ~Stack() {
//            delete[] array;
//        }
//        void push(T item) {
//            if (isFull()) {
//                throw runtime_error("Stack is full");
//            }
//            array[++top] = item;   // Increment top index and add item to the stack
//        }
//        T pop() {
//            if (isEmpty()) {
//                throw runtime_error("Stack is empty");
//            }
//            return array[top--];   // Return the top element and decrement top index
//        }
//        bool isEmpty() {
//            return top == -1;      // Check if the stack is empty
//        }
//        bool isFull() {
//            return top == capacity - 1;   // Check if the stack is full
//        }
//        T top_element() {
//            if (isEmpty()) {
//                throw runtime_error("Stack is empty");
//            }
//            return array[top];     // Return the top element
//        }
//};
//#endif
//
