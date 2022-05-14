#ifndef ATOMJSON_DOUBLYLINKEDLIST_HPP
#define ATOMJSON_DOUBLYLINKEDLIST_HPP

#include "Object.hpp"

namespace AtomJson
{
    struct DoubleyLinkedListNode
    {
        Object::Item item;
        DoubleyLinkedListNode *prev, *next;

        typedef DoubleyLinkedListNode Node;

        DoubleyLinkedListNode() : prev(nullptr), next(nullptr) {}
    };

    typedef DoubleyLinkedListNode Node;
    typedef Node *Entry;

    /**
     * *Deep copy for doubly linked list
     * @brief Copy and return the copied head of doubly linked list
     *
     * @param head
     * @return Node*
     */
    Node *deepCopyDLL(Node *head)
    {
        if (head == nullptr)
            return nullptr;
        Node *dummy = new Node();
        bool first_visited = true;
        Node *src = nullptr, *target = nullptr;
        for (src = head, target = dummy; first_visited || src != head; src = src->next, target = target->next)
        {
            Node *node = new Node(*src);
            target->next = node;
            if (!first_visited)
                node->prev = target;
            node->next = dummy->next;
            first_visited = false;
        }
        dummy->next->prev = target;
    }

    /**
     * *Shallow copy for doubly linked list
     * @brief Copy and return the copied head of doubly linked list
     *
     * @param head
     * @return Node*
     */
    Node *shallowCopyDLL(Node *head)
    {
        return head;
    }

    /**
     * @brief Insert node at head, then return new head
     *
     * @param head
     * @param node
     * @return Node*
     */
    Node *insertDLLNode(Node *head, Node *node)
    {
        if (head != nullptr)
        {
            Node *tail = head->prev;
            head->prev = node;
            tail->next = node;

            node->next = head;
            node->prev = tail;
        }
        else
        {
            node->prev = node;
            node->next = node;
        }
        head = node;
        return head;
    }

    /**
     * @brief Delete the node at the head, then return new head
     *
     * @param head
     * @return Node*
     */
    Node *deleteDLLNode(Node *head)
    {
        if (head == nullptr)
            return nullptr;
        else
        {
            Node *tail = head->prev, *node = head;
            if (head == tail)
            {
                delete head;
                return nullptr;
            }
            head = head->next;
            head->prev = tail;
            tail->next = head;
            delete node;
            return head;
        }
    }
};
#endif