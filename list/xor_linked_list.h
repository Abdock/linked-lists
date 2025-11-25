#ifndef XOR_LINKED_LIST_H
#define XOR_LINKED_LIST_H
#include <stdexcept>

template<typename T>
class XORLinkedList {
private:
    struct Node {
        T data;
        Node *npx;

        Node(const T &val) : data(val), npx(nullptr) {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    size_t count = 0;

    static Node *XOR(Node *a, Node *b) {
        return reinterpret_cast<Node *>(
            reinterpret_cast<uintptr_t>(a) ^ reinterpret_cast<uintptr_t>(b)
        );
    }

public:
    XORLinkedList() = default;

    ~XORLinkedList() {
        clear();
    }

    XORLinkedList(const XORLinkedList &) = delete;

    XORLinkedList &operator=(const XORLinkedList &) = delete;

    XORLinkedList(XORLinkedList &&other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    XORLinkedList &operator=(XORLinkedList &&other) noexcept {
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
        node->npx = head;

        if (head) {
            head->npx = XOR(node, head->npx);
        } else {
            tail = node;
        }
        head = node;
        ++count;
    }

    void push_back(const T &value) {
        Node *node = new Node(value);
        node->npx = tail;

        if (tail) {
            tail->npx = XOR(tail->npx, node);
        } else {
            head = node;
        }
        tail = node;
        ++count;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("List is empty");

        Node *node = head;
        T value = node->data;
        Node *next = node->npx;

        if (next) {
            next->npx = XOR(node, next->npx);
        } else {
            tail = nullptr;
        }
        head = next;
        delete node;
        --count;
        return value;
    }

    T pop_back() {
        if (!tail) throw std::runtime_error("List is empty");

        Node *node = tail;
        T value = node->data;
        Node *prev = node->npx;

        if (prev) {
            prev->npx = XOR(prev->npx, node);
        } else {
            head = nullptr;
        }
        tail = prev;
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
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            if (curr->data == value) return true;
            Node *next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        return false;
    }

    bool remove(const T &value) {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            if (curr->data == value) {
                Node *next = XOR(prev, curr->npx);

                if (prev) {
                    prev->npx = XOR(XOR(prev->npx, curr), next);
                } else {
                    head = next;
                }

                if (next) {
                    next->npx = XOR(prev, XOR(curr, next->npx));
                } else {
                    tail = prev;
                }

                delete curr;
                --count;
                return true;
            }
            Node *next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
        }
        return false;
    }

    void clear() {
        Node *curr = head;
        Node *prev = nullptr;

        while (curr) {
            Node *next = XOR(prev, curr->npx);
            prev = curr;
            delete curr;
            curr = next;
        }
        head = tail = nullptr;
        count = 0;
    }

    size_t size() const { return count; }
    bool empty() const { return count == 0; }

    class Iterator {
        Node *curr;
        Node *prev;

    public:
        Iterator(Node *c, Node *p) : curr(c), prev(p) {
        }

        T &operator*() { return curr->data; }

        Iterator &operator++() {
            Node *next = XOR(prev, curr->npx);
            prev = curr;
            curr = next;
            return *this;
        }

        bool operator!=(const Iterator &other) const {
            return curr != other.curr;
        }
    };

    Iterator begin() { return Iterator(head, nullptr); }
    Iterator end() { return Iterator(nullptr, tail); }
};

#endif //XOR_LINKED_LIST_H
