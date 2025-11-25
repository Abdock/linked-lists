#ifndef LIST_SORT
#define LIST_SORT
#include "traits.h"

template<typename Node>
auto merge_sorted(Node *a, Node *b)
    -> std::enable_if_t<is_singly_v<Node>, Node *> {
    Node dummy{{}};
    Node *tail = &dummy;

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

template<typename Node>
auto merge_sorted(Node *a, Node *b)
    -> std::enable_if_t<is_doubly_v<Node>, Node *> {
    Node dummy{{}};
    Node *tail = &dummy;

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a->prev = tail;
            a = a->next;
        } else {
            tail->next = b;
            b->prev = tail;
            b = b->next;
        }
        tail = tail->next;
    }

    Node *rest = a ? a : b;
    tail->next = rest;
    if (rest) rest->prev = tail;

    Node *result = dummy.next;
    if (result) result->prev = nullptr;
    return result;
}

template<typename Node>
auto merge_sort(Node *head)
    -> std::enable_if_t<is_singly_v<Node>, Node *> {
    if (!head || !head->next) return head;

    Node *mid = get_middle(head);
    Node *right = mid->next;
    mid->next = nullptr;

    return merge_sorted(merge_sort(head), merge_sort(right));
}

template<typename Node>
auto merge_sort(Node *head)
    -> std::enable_if_t<is_doubly_v<Node>, Node *> {
    if (!head || !head->next) return head;

    Node *mid = get_middle(head);
    Node *right = mid->next;

    mid->next = nullptr;
    if (right) right->prev = nullptr;

    return merge_sorted(merge_sort(head), merge_sort(right));
}

#endif // LIST_SORT
