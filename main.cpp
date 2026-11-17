#include <iostream>
#include <cassert>
#include "doublelist.hpp"

int main() {
    DoubleList<int> list;
    
    assert(list.empty());
    assert(list.size() == 0);

    list.push_back(10);
    list.push_back(30);
    assert(list.size() == 2);
    assert(list.back() == 30);
    assert(list.front() == 10);

    list.push_front(5);
    assert(list.size() == 3);
    assert(list.front() == 5);
    assert(list[1] == 10);

    list.insert(2, 20);
    assert(list.size() == 4);
    assert(list[2] == 20);

    assert(list.index(20) == 2);
    assert(list.index(99) == -1);

    list.erase(1);
    assert(list.size() == 3);
    assert(list[1] == 20);

    list.pop_front();
    assert(list.front() == 20);
    
    list.pop_back();
    assert(list.back() == 20);
    assert(list.size() == 1);

    list.clear();
    assert(list.empty());

    return 0;
}