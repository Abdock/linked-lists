#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H
#include <stdexcept>

template<typename T>
class CircularLinkedList {
private:
    struct Node {
        T data;
        Node *prev;
        Node *next;

        Node(const T &val) : data(val), prev(this), next(this) {
        }
    };

    Node *head = nullptr;
    size_t count = 0;

public:
    CircularLinkedList() = default;

    ~CircularLinkedList() { clear(); }

    CircularLinkedList(const CircularLinkedList &) = delete;

    CircularLinkedList &operator=(const CircularLinkedList &) = delete;

    CircularLinkedList(CircularLinkedList &&other) noexcept
        : head(other.head), count(other.count) {
        other.head = nullptr;
        other.count = 0;
    }

    CircularLinkedList &operator=(CircularLinkedList &&other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            count = other.count;
            other.head = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void push_front(const T &value) {
        Node *node = new Node(value);
        if (head) {
            node->next = head;
            node->prev = head->prev;
            head->prev->next = node;
            head->prev = node;
        }
        head = node;
        ++count;
    }

    void push_back(const T &value) {
        Node *node = new Node(value);
        if (head) {
            node->next = head;
            node->prev = head->prev;
            head->prev->next = node;
            head->prev = node;
        } else {
            head = node;
        }
        ++count;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("List is empty");
        Node *node = head;
        T value = node->data;

        if (count == 1) {
            head = nullptr;
        } else {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
        }
        delete node;
        --count;
        return value;
    }

    T pop_back() {
        if (!head) throw std::runtime_error("List is empty");
        Node *node = head->prev;
        T value = node->data;

        if (count == 1) {
            head = nullptr;
        } else {
            node->prev->next = head;
            head->prev = node->prev;
        }
        delete node;
        --count;
        return value;
    }

    T &front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T &back() {
        if (!head) throw std::runtime_error("List is empty");
        return head->prev->data;
    }

    void rotate_forward() {
        if (head) head = head->next;
    }

    void rotate_backward() {
        if (head) head = head->prev;
    }

    bool contains(const T &value) const {
        if (!head) return false;
        Node *curr = head;
        do {
            if (curr->data == value) return true;
            curr = curr->next;
        } while (curr != head);
        return false;
    }

    bool remove(const T &value) {
        if (!head) return false;

        Node *curr = head;
        do {
            if (curr->data == value) {
                if (count == 1) {
                    head = nullptr;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    if (curr == head) head = head->next;
                }
                delete curr;
                --count;
                return true;
            }
            curr = curr->next;
        } while (curr != head);
        return false;
    }

    void clear() {
        if (!head) return;
        Node *curr = head;
        do {
            Node *tmp = curr;
            curr = curr->next;
            delete tmp;
        } while (curr != head);
        head = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    class Iterator {
        Node *curr;
        Node *start;
        bool done;

    public:
        Iterator(Node *n, bool end = false)
            : curr(n), start(n), done(end || !n) {
        }

        T &operator*() { return curr->data; }

        Iterator &operator++() {
            curr = curr->next;
            if (curr == start) done = true;
            return *this;
        }

        bool operator!=(const Iterator &o) const {
            return !done || !o.done;
        }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(head, true); }
};

#endif //CIRCULAR_LINKED_LIST_H
