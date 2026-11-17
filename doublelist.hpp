#ifndef DOUBLELIST_HPP
#define DOUBLELIST_HPP

#include <iostream>
#include <cassert>
#include <utility>

template <typename T>
struct DoubleNode {
    T value;
    DoubleNode *next, *prev;
    DoubleNode() : value(T()), next(nullptr), prev(nullptr) {}
    DoubleNode(const T& item, DoubleNode *nptr=nullptr, DoubleNode *pptr=nullptr)
        : value(item), next(nptr), prev(pptr) {}
    ~DoubleNode() = default;
};

template <typename T>
class DoubleList {
    DoubleNode<T> *head, *tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList() { clear(); }

    DoubleList(const DoubleList& other);
    DoubleList(DoubleList&& other);
    DoubleList& operator=(const DoubleList& other);
    DoubleList& operator=(DoubleList&& other);

    bool empty() const { return head == nullptr; }
    bool full() const { return false; }
    std::size_t size() const;
    void push_front(const T& item);
    void push_front(T&& item);
    void push_back(const T& item);
    void push_back(T&& item);
    T& front() { assert(!empty()); return head->value; }
    T& back() { assert(!empty()); return tail->value; }
    void pop_front();
    void pop_back();
    void clear();
    void display() const;
    void display_reversed() const;

    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;
    void erase(std::size_t pos);
    int index(const T& item) const;
    void insert(std::size_t pos, const T& item);
    void insert(std::size_t pos, T&& item);
};

template <typename T>
DoubleList<T>::DoubleList(const DoubleList& other) : head(nullptr), tail(nullptr) {
    for (DoubleNode<T>* node = other.head; node != nullptr; node = node->next) {
        push_back(node->value);
    }
}

template <typename T>
DoubleList<T>::DoubleList(DoubleList&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(const DoubleList& other) {
    if (this != &other) {
        clear();
        for (DoubleNode<T>* node = other.head; node != nullptr; node = node->next) {
            push_back(node->value);
        }
    }
    return *this;
}

template <typename T>
DoubleList<T>& DoubleList<T>::operator=(DoubleList&& other) {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
    }
    return *this;
}

template <typename T>
std::size_t DoubleList<T>::size() const {
    std::size_t count = 0;
    for (DoubleNode<T>* node = head; node != nullptr; node = node->next) {
        ++count;
    }
    return count;
}

template <typename T>
void DoubleList<T>::push_front(const T& item) {
    if (!empty()) {
        head = new DoubleNode<T>(item, head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_front(T&& item) {
    if (!empty()) {
        head = new DoubleNode<T>(std::move(item), head);
        head->next->prev = head;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::push_back(const T& item) {
    if (!empty()) {
        tail = new DoubleNode<T>(item, nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(item);
    }
}

template <typename T>
void DoubleList<T>::push_back(T&& item) {
    if (!empty()) {
        tail = new DoubleNode<T>(std::move(item), nullptr, tail);
        tail->prev->next = tail;
    } else {
        head = tail = new DoubleNode<T>(std::move(item));
    }
}

template <typename T>
void DoubleList<T>::pop_front() {
    assert(!empty());
    DoubleNode<T>* node = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete node;
}

template <typename T>
void DoubleList<T>::pop_back() {
    assert(!empty());
    DoubleNode<T>* node = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete node;
}

template <typename T>
void DoubleList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template <typename T>
void DoubleList<T>::display() const {
    for (DoubleNode<T>* node = head; node != nullptr; node = node->next) {
        std::cout << node->value << " ";
    }
    std::cout << "\n";
}

template <typename T>
void DoubleList<T>::display_reversed() const {
    for (DoubleNode<T>* node = tail; node != nullptr; node = node->prev) {
        std::cout << node->value << " ";
    }
    std::cout << "\n";
}

template <typename T>
T& DoubleList<T>::operator[](std::size_t pos) {
    assert(pos < size());
    DoubleNode<T>* node = head;
    for (std::size_t i = 0; i < pos; ++i) {
        node = node->next;
    }
    return node->value;
}

template <typename T>
const T& DoubleList<T>::operator[](std::size_t pos) const {
    assert(pos < size());
    DoubleNode<T>* node = head;
    for (std::size_t i = 0; i < pos; ++i) {
        node = node->next;
    }
    return node->value;
}

template <typename T>
void DoubleList<T>::erase(std::size_t pos) {
    assert(pos < size());
    if (pos == 0) {
        pop_front();
    } else if (pos == size() - 1) {
        pop_back();
    } else {
        DoubleNode<T>* node = head;
        for (std::size_t i = 0; i < pos; ++i) {
            node = node->next;
        }
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }
}

template <typename T>
int DoubleList<T>::index(const T& item) const {
    DoubleNode<T>* node = head;
    int idx = 0;
    while (node != nullptr) {
        if (node->value == item) return idx;
        node = node->next;
        ++idx;
    }
    return -1;
}

template <typename T>
void DoubleList<T>::insert(std::size_t pos, const T& item) {
    assert(pos <= size());
    if (pos == 0) {
        push_front(item);
    } else if (pos == size()) {
        push_back(item);
    } else {
        DoubleNode<T>* node = head;
        for (std::size_t i = 0; i < pos; ++i) {
            node = node->next;
        }
        DoubleNode<T>* newNode = new DoubleNode<T>(item, node, node->prev);
        node->prev->next = newNode;
        node->prev = newNode;
    }
}

template <typename T>
void DoubleList<T>::insert(std::size_t pos, T&& item) {
    assert(pos <= size());
    if (pos == 0) {
        push_front(std::move(item));
    } else if (pos == size()) {
        push_back(std::move(item));
    } else {
        DoubleNode<T>* node = head;
        for (std::size_t i = 0; i < pos; ++i) {
            node = node->next;
        }
        DoubleNode<T>* newNode = new DoubleNode<T>(std::move(item), node, node->prev);
        node->prev->next = newNode;
        node->prev = newNode;
    }
}

#endif