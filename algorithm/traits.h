#ifndef TRAITS_H
#define TRAITS_H
#include <type_traits>

template<typename T, typename = void>
struct has_next : std::false_type {
};

template<typename T>
struct has_next<T, std::void_t<decltype(std::declval<T>().next)> >
        : std::true_type {
};

template<typename T, typename = void>
struct has_prev : std::false_type {
};

template<typename T>
struct has_prev<T, std::void_t<decltype(std::declval<T>().prev)> >
        : std::true_type {
};

template<typename T, typename = void>
struct has_npx : std::false_type {
};

template<typename T>
struct has_npx<T, std::void_t<decltype(std::declval<T>().npx)> >
        : std::true_type {
};

template<typename T>
inline constexpr bool is_singly_v =
        has_next<T>::value && !has_prev<T>::value && !has_npx<T>::value;

template<typename T>
inline constexpr bool is_doubly_v =
        has_next<T>::value && has_prev<T>::value;

template<typename T>
inline constexpr bool is_xor_v =
        has_npx<T>::value && !has_next<T>::value;

template<typename T>
struct SinglyNode {
    T data;
    SinglyNode *next = nullptr;

    explicit SinglyNode(const T &val = T{}) : data(val) {
    }
};

template<typename T>
struct DoublyNode {
    T data;
    DoublyNode *prev = nullptr;
    DoublyNode *next = nullptr;

    explicit DoublyNode(const T &val = T{}) : data(val) {
    }
};

template<typename T>
struct XORNode {
    T data;
    XORNode *npx = nullptr;

    explicit XORNode(const T &val = T{}) : data(val) {
    }
};

#endif //TRAITS_H
