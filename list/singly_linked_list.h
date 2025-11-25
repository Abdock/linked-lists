#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H


template<typename T>
class SinglyLinkedList {
    struct Node {
        T data;
        Node *next;

        explicit Node(const T &val) : data(val), next(nullptr) {
        }
    };

    Node *head = nullptr;
    Node *tail = nullptr;
    size_t count = 0;

public:
    SinglyLinkedList() = default;

    ~SinglyLinkedList() { clear(); }

    SinglyLinkedList(const SinglyLinkedList &) = delete;

    SinglyLinkedList &operator=(const SinglyLinkedList &) = delete;

    SinglyLinkedList(SinglyLinkedList &&other) noexcept
        : head(other.head), tail(other.tail), count(other.count) {
        other.head = other.tail = nullptr;
        other.count = 0;
    }

    SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept {
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
        head = node;
        if (!tail) tail = node;
        ++count;
    }

    void push_back(const T &value) {
        Node *node = new Node(value);
        if (tail) {
            tail->next = node;
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
        head = head->next;
        if (!head) tail = nullptr;
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
        Node *prev = nullptr;
        for (Node *curr = head; curr; prev = curr, curr = curr->next) {
            if (curr->data == value) {
                if (prev) prev->next = curr->next;
                else head = curr->next;
                if (curr == tail) tail = prev;
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
        explicit Iterator(Node *n) : curr(n) {
        }

        T &operator*() { return curr->data; }

        Iterator &operator++() {
            curr = curr->next;
            return *this;
        }

        bool operator!=(const Iterator &o) const { return curr != o.curr; }
    };

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    void print() const {
        std::cout << "[";
        for (Node *curr = head; curr; curr = curr->next) {
            std::cout << curr->data;
            if (curr->next) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};


#endif //SINGLY_LINKED_LIST_H
