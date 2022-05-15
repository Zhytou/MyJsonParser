#include "AtomJson.hpp"
#include "Object.hpp"
#include "DoublyLinkedList.hpp"

#define INITIAL_CAPACITY 16

namespace AtomJson
{
    Object::Item::Item(const Item &other)
    {
        key = other.key;
        val = new Value(*other.val);
    }

    Object::Item::Item(Item &&other)
    {
        key = std::move(other.key);
        val = other.val;
        other.val = nullptr;
    }

    Object::Item &Object::Item::operator=(const Item &other)
    {
        key = other.key;
        val = new Value(*other.val);
        return *this;
    }

    Object::Item &Object::Item::operator=(Item &&other)
    {
        key = std::move(other.key);
        val = other.val;
        other.val = nullptr;
        return *this;
    }

    Object::Item::~Item()
    {
        if (val)
            delete val;
    }

    Object::Object()
    {
        size = 0;
        occupiedEntry = 0;
        loadFactor = 0;
        capacity = INITIAL_CAPACITY;
        p = new Entry[capacity];
    }

    Object::Object(const Object &other)
    {
        size = other.size;
        occupiedEntry = other.occupiedEntry;
        capacity = other.capacity;
        loadFactor = other.loadFactor;

        p = new Entry[capacity];

        for (size_t i = 0; i < capacity; i++)
        {
            p[i] = deepCopyDLL(other.p[i]);
        }
    }

    Object::Object(Object &&other)
    {
        size = other.size;
        occupiedEntry = other.occupiedEntry;
        capacity = other.capacity;
        loadFactor = other.loadFactor;
        p = other.p;

        other.size = 0;
        other.occupiedEntry = 0;
        other.loadFactor = 0;
        other.capacity = 0;
        other.p = nullptr;
    }

    Object &Object::operator=(const Object &other)
    {
        size = other.size;
        occupiedEntry = other.occupiedEntry;
        capacity = other.capacity;
        loadFactor = other.loadFactor;

        p = new Entry[capacity];

        for (size_t i = 0; i < capacity; i++)
        {
            p[i] = deepCopyDLL(other.p[i]);
        }
        return *this;
    }

    Object &Object::operator=(Object &&other)
    {
        size = other.size;
        occupiedEntry = other.occupiedEntry;
        capacity = other.capacity;
        loadFactor = other.loadFactor;
        p = other.p;

        other.size = 0;
        other.occupiedEntry = 0;
        other.loadFactor = 0;
        other.capacity = 0;
        other.p = nullptr;
        return *this;
    }

    Object::~Object()
    {
        if (p)
            delete[] p;
        size = 0;
        capacity = 0;
        occupiedEntry = 0;
    }

    Value &Object::operator[](const String &key)
    {
        size_t idx = key.hashcode() % capacity;
        Node *node = nullptr;
        bool flag = true;

        for (node = p[idx]; node != nullptr; node = node->next)
        {
            if (!flag && node == p[idx])
            {
                node = nullptr;
                break;
            }

            flag = false;
            if (node->item.key == key)
            {
                // delete node and later insert it back to list in order to implenment the LRU.
                Node *prev = node->prev, *next = node->next;
                node->prev = nullptr;
                node->next = nullptr;

                prev->next = next;
                next->prev = prev;
                break;
            }
        }

        if (node == nullptr)
        {
            node = new Node(key, new Value());
            occupiedEntry += 1;
        }

        p[idx] = insertDLLNode(p[idx], node);

        return *(node->item.val);
    }

    bool Object::operator==(const Object &other)
    {
        // TODO:
        return false;
    }

    Array Object::keys()
    {
        Array a;
        for (size_t i = 0; i < capacity; i++)
        {
            bool flag = true;
            for (Node *node = p[i]; node != nullptr; node = node->next)
            {
                if (!flag && node == p[i])
                    break;
                flag = false;
                a.append(node->item.key);
            }
        }
        return std::move(a);
    }

    Array Object::values()
    {
        Array a;
        for (size_t i = 0; i < capacity; i++)
        {
            bool flag = true;
            for (Node *node = p[i]; node != nullptr; node = node->next)
            {
                if (!flag && node == p[i])
                    break;
                flag = false;
                a.append(*(node->item.val));
            }
        }
        return std::move(a);
    }

    void Object::resize()
    {
        size_t len = capacity;
        do
        {
            // ? 如何在改变容量的时候计算新情况的加载度？，因为占用entry数量可能会变化
            if (loadFactor < 0.3)
                capacity /= 1.5;
            else if (loadFactor > 0.75)
                capacity *= 1.5;
        } while (need_resize());

        occupiedEntry = 0;
        Node **np = new Entry[capacity];
        for (size_t i = 0; i < len; i++)
        {
            Node *head = p[i];
            while (head)
            {
                size_t idx = head->item.key.hashcode() % capacity;
                Node *node = new Node();
                node->item = std::move(p[i]->item);
                np[idx] = insertDLLNode(np[idx], node);
                occupiedEntry += 1;
                head = deleteDLLNode(head);
            }
        }

        if (p)
            delete[] p;
        p = np;
    }
} // namespace AtomJson
