//vector.hpp
#ifndef VECTOR_H
#define VECTOR_H

#include<cstdlib>
#include <stdexcept>
using namespace std;

template <typename T>
class Vector
{
    private:
        T *data; // Pointer to the dynamic array
        int v_size; // Current size of the vector
        int v_capacity; // Current capacity of the vector

    public:
        typedef T* iterator;

        // Constructor
        Vector(int cap=0) : v_size(0), v_capacity(cap) {
            data = new T[v_capacity];
        }

        // Destructor
        ~Vector() {
            delete[] data;
        }

        // Returns the current size of the vector
        int size() const {
            return v_size;
        }

        // Returns the current capacity of the vector
        int capacity() const {
            return v_capacity;
        }

        // Checks if the vector is empty
        bool empty() const {
            return v_size == 0;
        }

        // Returns an iterator pointing to the beginning of the vector
        iterator begin(){
            return data;
        }

        // Returns an iterator pointing to the end of the vector
        iterator end(){
            return data + v_size;
        }

        // Returns a reference to the first element of the vector
        const T& front() {
            if (empty()) {
                throw runtime_error("Vector is empty");
            }
            return data[0];
        }

        // Returns a reference to the last element of the vector
        const T& back() {
            if (empty()) {
                throw runtime_error("Vector is empty");
            }
            return data[v_size - 1];
        }

        // Adds an element to the end of the vector
        void push_back(T element) {
            if (v_size == v_capacity) {
                // Increase the capacity of the vector
                v_capacity = (v_capacity == 0) ? 1 : v_capacity * 2;
                T* new_data = new T[v_capacity];

                // Copy the elements from the old array to the new array
                for (int i = 0; i < v_size; ++i) {
                    new_data[i] = data[i];
                }

                // Delete the old array and assign the new array to data
                delete[] data;
                data = new_data;
            }

            // Add the element to the end of the vector and increment the size
            data[v_size++] = element;
        }

        // Inserts an element at the specified index
        void insert(int index, T element) {
            if (index < 0 || index > v_size) {
                throw out_of_range("Index out of range");
            }

            if (v_size == v_capacity) {
                // Increase the capacity of the vector
                v_capacity *= 2;
                T* new_data = new T[v_capacity];

                // Copy the elements from the old array to the new array
                for (int i = 0; i < v_size; ++i) {
                    new_data[i] = data[i];
                }

                // Delete the old array and assign the new array to data
                delete[] data;
                data = new_data;
            }

            // Shift the elements to the right to make space for the new element
            for (int i = v_size; i > index; --i) {
                data[i] = data[i - 1];
            }

            // Insert the element at the specified index and increment the size
            data[index] = element;
            ++v_size;
        }

        // Erases the element at the specified position
        void erase(iterator position) {
            if (position < begin() || position >= end()) {
                throw out_of_range("Iterator out of range");
            }

            // Shift the elements to the left to remove the element at the specified position
            for (auto it = position; it < end() - 1; ++it) {
                *it = *(it + 1);
            }

            // Decrement the size
            --v_size;
        }

        // Returns a reference to the element at the specified index
        T& operator[](int index) {
            if (index < 0 || index >= v_size) {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        // Returns a reference to the element at the specified index
        T& at(int index) {
            return operator[](index);
        }

        // Shrinks the capacity of the vector to match the size
        void shrink_to_fit() {
            // Create a new array with the size of the vector
            T* temp = new T[v_size];

            // Copy the elements from the old array to the new array
            for (int i = 0; i < v_size; ++i) {
                temp[i] = data[i];
            }

            // Delete the old array and assign the new array to data
            delete[] data;
            data = temp;

            // Update the capacity to match the size
            v_capacity = v_size;
        }

        // Displays the elements of the vector
        void display() {
            for (int i = 0; i < v_size; ++i) {
                cout << data[i] << " ";
            }
            cout << endl;
        }
};
#endif
