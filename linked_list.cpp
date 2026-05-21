#include <iostream>
#include "linked_list.h"

Linked_List::Linked_List(void) {
    head = nullptr;
    tail = nullptr;
}

/**
 * Gets the size of the linked list
 * @return: an integer representing the number of elements in a list (its size)
 */
int Linked_List::size(void) const {
    Node* curr_node = head; // Counting starts at the head
    int num_elements = 0;
    while (curr_node != nullptr) { // Until we reach the end of the linked list
        ++num_elements;
        curr_node = curr_node->next; // Move to next node
    }
    return num_elements;
}

/**
 * Adds a node with a given value to the start of the linked list in front of the head
 * @param num: the integer value held by the node to be prepended
 */
void Linked_List::prepend(int num) {
    Node* new_node = new Node();
    new_node->data = num;
    new_node->next = head; // new_node now in front of the previous head node
    if (head == nullptr) { 
        tail = new_node; // new node is the only node in list (it's both head and tail)
    }
    head = new_node; // prepended node always becomes new head
}

/**
 * Adds a node to the end of the linked list after the tail
 * @param num: the integer value held by the node to be appended
 */
void Linked_List::append(int num) {
    Node* new_node = new Node();
    new_node->data = num;
    if (tail == nullptr) { // List is empty
        head = new_node; // Only one node in list now (it's both head and tail)
    } else { // List has at least one node
        tail->next = new_node; 
    }
    tail = new_node; // Appended node will always be new tail
}

/**
 * Inserts a node with a given value into the linked list at an index position
 * @param num: the integer value held by the node to be inserted
 * @param index: the index position to insert the node into
 */
void Linked_List::insert(int num, int index) {
    if (index == 0) { // Prepending
        prepend(num);
    } else if (index == size()) { // Appending
        append(num);
    } else if ((index > 0) && (index < size())) { // Insertions anywhere inside linked list besides start and end
        Node* curr_node = head;
        Node* next_node = curr_node->next; // Makes sure we do not lose the nodes after the insertion position
        Node* new_node = new Node(); 
        new_node->data = num; 
        int curr_index = 0; // We will insert node at index after this value
        while (curr_index != index - 1) { // Insertion will happen after curr_index (ensures the node is inserted in right position)
            ++curr_index;
            curr_node = curr_node->next; // curr_node becomes node after it
            next_node = curr_node->next; // next_node becomes node after the new curr_node
        }
        new_node->next = next_node; // Connect right side of insertion position to new_node
        curr_node->next = new_node; // Connect left side of insertion position to new_node
    }
}

/**
 * Pops the first/top/leftmost element in the linked list
 */
void Linked_List::pop_front(void) {
    if (size() > 0) { // Linked list not empty
        if (head == tail) { // only one item in linked list
            tail = nullptr;
        }
        head = head->next; // Node after head becomes new head (old head is forgotten)
    }
}

/**
 * Pops the last/bottom/rightmost element in the linked list
 */
void Linked_List::pop_back(void) {
    if (size() > 0) { // Linked list not empty
        if (head == tail) { // only one item in linked list
            // Empty the list (remove the only node in there)
            head = nullptr; 
            tail = nullptr;
        } else {
            Node* curr_node = head; // Start traversal at head
            while (curr_node->next != tail) { // Until we reach the node before tail
                curr_node = curr_node->next; // Move to next node
            }
            curr_node->next = nullptr; // forget the old tail
            tail = curr_node; // curr_node is now the new tail
        }
    }
}

/**
 * Removes the node at the specified index position
 * @param index: the index position where the node to remove is located
 */
void Linked_List::remove(int index) {
    if (index == 0) { // popping the front
        pop_front();
    } else if (index == size() - 1) { // popping the back
        pop_back();
    } else if ((index > 0) && (index < size() - 1)) { 
        Node* curr_node = head; // Start traversal at head node
        Node* next_node = curr_node->next; // Ensures we do not lose right side of removal position
        int curr_index = 0; // Removal will happen at the index position after this
        while (curr_index != index - 1) { // Until the node before the index position is reached
            // Move to next two nodes
            curr_node = curr_node->next;
            next_node = curr_node->next;
            ++curr_index;
        }   
        curr_node->next = next_node->next; // Disconnect the node after curr_node from linked list, effectively removing it
    }
}

/**
 * Checks whether or not the linked list has a node with the key value
 * @param key: the integer value being searched for
 * @return: true if the key is found, false otherwise
 */
bool Linked_List::contains(int key) const {
    Node* curr_node = head; 
    while (curr_node != nullptr) { // Until end of linked list is reached
        if (curr_node->data == key) { // Node with key is found
            return true;
        }
        curr_node = curr_node->next; // Move to next node
    }
    return false; // Node with key not in linked list
}

/**
 * Searches the linked list for the first node with a key value
 * @param key: the integer value being searched for
 * @return: the index position of the node with the key if it's in the linked list, -1 otherwise
 */
int Linked_List::search(int key) const {
    Node* curr_node = head; 
    int curr_index = 0; 
    while (curr_node != nullptr) { // Until end of linked list is reached
        if (curr_node->data == key) { // Node with key is found
            return curr_index;
        }
        curr_node = curr_node->next; // Move to next node
        ++curr_index; // Increment index by 1
    }
    return -1; // Node with key not in linked list
}

/**
 * Prints out the current linked list
 */
void Linked_List::print_list(void) const {
    Node* curr_node = head; 
    while (curr_node != nullptr) { // Until end of linked list reached
        if (curr_node->next == nullptr) { // Printing the tail node
            std::cout << curr_node->data << std::endl;
            break;
        }
        std::cout << curr_node->data << "->"; // Printing nodes that aren't the tail
        curr_node = curr_node->next; // Move to next node
    }
}