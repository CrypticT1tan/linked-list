#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "node.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class Linked_List {
    private:
        Node<T>* head;
        Node<T>* tail; 
    public:
        Linked_List(void) {
            head = nullptr;
            tail = nullptr;
        }

        ~Linked_List(void) {
            if (size() > 0) {
                Node<T>* curr_node = head;
                Node<T>* next_node = curr_node->next; // To ensure we do not lose the link after deleting a node
                while (next_node != nullptr) { // Until there is only one element remaining
                    // Delete the current node and move to the next one
                    delete curr_node;
                    curr_node = next_node;
                    next_node = curr_node->next;
                }
                // Deleting the last node in the list
                delete curr_node;
            }
        }
        
        int size(void) const {
            /**
             * Gets the size of the linked list
             * @return: an integer representing the number of elements in a list (its size)
             */
            Node<T>* curr_node = head; // Counting starts at the head
            int num_elements = 0;
            while (curr_node != nullptr) { // Until we reach the end of the linked list
                ++num_elements;
                curr_node = curr_node->next; // Move to next node
            }
            return num_elements;
        }

        void prepend(T val) {
            /**
             * Adds a node with a given value to the start of the linked list in front of the head
             * @param val: the value held by the node to be prepended
             */
            Node<T>* new_node = new Node<T>();
            new_node->data = val;
            new_node->next = head; // new_node now in front of the previous head node
            if (head == nullptr) { 
                tail = new_node; // new node is the only node in list (it's both head and tail)
            }
            head = new_node; // prepended node always becomes new head
        }

        void append(T val) {
            /**
             * Adds a node to the end of the linked list after the tail
             * @param val: the value held by the node to be appended
             */
            Node<T>* new_node = new Node<T>();
            new_node->data = val;
            if (tail == nullptr) { // List is empty
                head = new_node; // Only one node in list now (it's both head and tail)
            } else { // List has at least one node
                tail->next = new_node; 
            }
            tail = new_node; // Appended node will always be new tail
        }

        void insert(T val, int index) {
            /**
             * Inserts a node with a given value into the linked list at an index position
             * @param val: the value held by the node to be inserted
             * @param index: the index position to insert the node into
             */
            if (index == 0) { // Prepending
                prepend(val);
            } else if (index == size()) { // Appending
                append(val);
            } else if ((index > 0) && (index < size())) { // Insertions anywhere inside linked list besides start and end
                Node<T>* curr_node = head;
                Node<T>* next_node = curr_node->next; // Makes sure we do not lose the nodes after the insertion position
                Node<T>* new_node = new Node<T>(); 
                new_node->data = val; 
                int curr_index = 0; // We will insert node at index after this value
                while (curr_index != index - 1) { // Insertion will happen after curr_index (ensures the node is inserted in right position)
                    ++curr_index;
                    curr_node = curr_node->next; // curr_node becomes node after it
                    next_node = curr_node->next; // next_node becomes node after the new curr_node
                }
                new_node->next = next_node; // Connect right side of insertion position to new_node
                curr_node->next = new_node; // Connect left side of insertion position to new_node
            } else {
                throw std::out_of_range("insertion index out of bounds");
            }
        }

        void pop_front(void) {
            /**
             * Pops the first/top/leftmost element in the linked list
             */
            if (size() > 0) { // Linked list not empty
                if (head == tail) { // only one item in linked list
                    // Remove the head/tail node, list is now empty
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    // Remove the head node
                    Node<T>* temp = head->next;
                    delete head;
                    head = temp; // Node after head becomes new head (old head is forgotten)
                }
            } else {
                throw std::out_of_range("removal index out of bounds");
            }
        }

        void pop_back(void) {   
            /**
             * Pops the last/bottom/rightmost element in the linked list
             */
            if (size() > 0) { // Linked list not empty
                if (head == tail) { // only one item in linked list
                    // Empty the list (remove the only node in there)
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    Node<T>* curr_node = head; // Start traversal at head
                    while (curr_node->next != tail) { // Until we reach the node before tail
                        curr_node = curr_node->next; // Move to next node
                    }
                    delete curr_node->next;
                    curr_node->next = nullptr; // forget the old tail
                    tail = curr_node; // curr_node is now the new tail
                }
            } else {
                throw std::out_of_range("removal index out of bounds");
            }
        }

        void remove(int index) {
            /**
             * Removes the node at the specified index position
             * @param index: the index position where the node to remove is located
             */
            if (index == 0) { // popping the front
                pop_front();
            } else if (index == size() - 1) { // popping the back
                pop_back();
            } else if ((index > 0) && (index < size() - 1)) { 
                Node<T>* curr_node = head; // Start traversal at head node
                Node<T>* next_node = curr_node->next; // Ensures we do not lose right side of removal position
                int curr_index = 0; // Removal will happen at the index position after this
                while (curr_index != index - 1) { // Until the node before the index position is reached
                    // Move to next two nodes
                    curr_node = curr_node->next;
                    next_node = curr_node->next;
                    ++curr_index;
                }   
                Node<T>* temp = next_node->next; // Ensure we do not lose nodes to the right of removed nodes
                delete next_node;
                curr_node->next = temp; // Disconnect the node after curr_node from linked list, effectively removing it
            } else {
                throw std::out_of_range("removal index out of bounds");
            }
        }

        bool contains(T val) const {
            /**
             * Checks whether or not the linked list has a node with a given value
             * @param val: the value being searched for
             * @return: true if the value is found, false otherwise
             */
            Node<T>* curr_node = head; 
            while (curr_node != nullptr) { // Until end of linked list is reached
                if (curr_node->data == val) { // Node with val is found
                    return true;
                }
                curr_node = curr_node->next; // Move to next node
            }
            return false; // Node with val not in linked list
        }

        int search(T val) const {
            /**
             * Searches the linked list for the first node with a given value
             * @param val: the value being searched for
             * @return: the index position of the node with the value if it's in the linked list, -1 otherwise
             */
            Node<T>* curr_node = head; 
            int curr_index = 0; 
            while (curr_node != nullptr) { // Until end of linked list is reached
                if (curr_node->data == val) { // Node with val is found
                    return curr_index;
                }
                curr_node = curr_node->next; // Move to next node
                ++curr_index; // Increment index by 1
            }
            return -1; // Node with val not in linked list
        }

        void replace(T val, int index) {
            /**
             * Replaces the value inside the node at the given index position with a new specified value
             * @param val: the value to replace the old node value with
             * @param index: the index position of the node that's having its the value replaced
             */
            if ((size() > 0) && (index >= 0) && (index < size())) {
                Node<T>* curr_node = head;
                int curr_index = 0;
                while (curr_index != index) {
                    curr_node = curr_node->next;
                    ++curr_index;
                }
                curr_node->data = val;
            } else {
                throw std::out_of_range("replacement index out of bounds");
            }
        }

        void print_list(void) const {
            /**
             * Prints out the current linked list
             */
            Node<T>* curr_node = head; 
            while (curr_node != nullptr) { // Until end of linked list reached
                if (curr_node->next == nullptr) { // Printing the tail node
                    std::cout << "(" << curr_node->data << ")" << std::endl;
                    break;
                }
                std::cout << "(" << curr_node->data << ")->"; // Printing nodes that aren't the tail
                curr_node = curr_node->next; // Move to next node
            }
        }
};

#endif