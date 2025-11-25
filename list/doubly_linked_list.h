#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;

        Node(const T &val) : data(val), prev(nullptr), next(nullptr) {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    size_t count = 0;

public:
    DoublyLinkedList() = default;

    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList &) = delete;

    DoublyLinkedList &operator=(const DoublyLinkedList &) = delete;

    DoublyLinkedList(DoublyLinkedList &&other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            count = other.count;
            other.head = other.tail = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void push_front(const T &value) {
        Node *node = new Node(value);
        node->next = head;
        if (head) head->prev = node;
        else tail = node;
        head = node;
        ++count;
    }

    void push_back(const T &value) {
        Node *node = new Node(value);
        node->prev = tail;
        if (tail) tail->next = node;
        else head = node;
        tail = node;
        ++count;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("List is empty");
        Node *node = head;
        T value = node->data;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete node;
        --count;
        return value;
    }

    T pop_back() {
        if (!tail) throw std::runtime_error("List is empty");
        Node *node = tail;
        T value = node->data;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete node;
        --count;
        return value;
    }

    T &front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T &back() {
        if (!tail) throw std::runtime_error("List is empty");
        return tail->data;
    }

    bool contains(const T &value) const {
        for (Node *curr = head; curr; curr = curr->next) {
            if (curr->data == value) return true;
        }
        return false;
    }

    bool remove(const T &value) {
        for (Node *curr = head; curr; curr = curr->next) {
            if (curr->data == value) {
                if (curr->prev) curr->prev->next = curr->next;
                else head = curr->next;

                if (curr->next) curr->next->prev = curr->prev;
                else tail = curr->prev;

                delete curr;
                --count;
                return true;
            }
        }
        return false;
    }

    void clear() {
        while (head) {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    class Iterator {
        Node *curr;

    public:
        Iterator(Node *n) : curr(n) {
        }

        T &operator*() { return curr->data; }

        Iterator &operator++() {
            curr = curr->next;
            return *this;
        }

        Iterator &operator--() {
            curr = curr->prev;
            return *this;
        }

        bool operator!=(const Iterator &o) const { return curr != o.curr; }
    };

    class ReverseIterator {
        Node *curr;

    public:
        ReverseIterator(Node *n) : curr(n) {
        }

        T &operator*() { return curr->data; }

        ReverseIterator &operator++() {
            curr = curr->prev;
            return *this;
        }

        bool operator!=(const ReverseIterator &o) const { return curr != o.curr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    ReverseIterator rbegin() { return ReverseIterator(tail); }
    ReverseIterator rend() { return ReverseIterator(nullptr); }
};


#endif //DOUBLY_LINKED_LIST_H
