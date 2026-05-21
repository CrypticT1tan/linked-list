#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "node.h"

class Linked_List{
    private:
        Node* head;
        Node* tail; 
    public:
        Linked_List(void);
        int size(void) const;
        void prepend(int num);
        void append(int num);
        void insert(int num, int index);
        void pop_front(void);
        void pop_back(void);
        void remove(int index);
        bool contains(int key) const;
        int search(int key) const;
        void print_list(void) const;
};

#endif