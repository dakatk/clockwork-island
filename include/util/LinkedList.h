#ifndef UTIL_LINKEDLIST_H__
#define UTIL_LINKEDLIST_H__
#include <iostream>

namespace util
{
    template <typename T>
    class LinkedList
    {
    private:
        struct Node
        {
            T* payload;
            struct Node* next;
        };
        struct Node* head;
        struct Node* current;

    public:
        LinkedList();
        ~LinkedList();

        void Push(T* value);
        T* Next();

        void Reset();
        bool Done();
    };

    template <typename T>
    LinkedList<T>::LinkedList()
    {
        this->head = nullptr;
        this->current = nullptr;
    }

    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        this->Reset();
        while (!this->Done())
        {
            std::cout << "Destructor called" << std::endl;
            struct Node* next = this->current->next;

            delete this->current->payload;
            delete this->current;

            this->current = next;
        }
    }

    template <typename T>
    void LinkedList<T>::Push(T* value)
    {
        auto* node = new Node();

        node->payload = value;
        node->next = this->head;

        this->head = node;
    }

    template <typename T>
    T* LinkedList<T>::Next()
    {
        if (this->Done())
            return nullptr;

        T* value = this->current->payload;
        this->current = this->current->next;

        return value;
    }

    template <typename T>
    void LinkedList<T>::Reset()
    {
        this->current = this->head;
    }

    template <typename T>
    bool LinkedList<T>::Done()
    {
        return this->current == nullptr;
    }
}

#endif /* UTIL_LINKEDLIST_H__ */
