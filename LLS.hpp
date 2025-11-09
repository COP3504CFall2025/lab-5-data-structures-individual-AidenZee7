#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list() {}

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T pop() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        T temp = list.getTail()->data;
        list.removeTail();
        return temp;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        return list.getHead()->data;
    }

    //Getters
    std::size_t getSize() const noexcept override {
        return static_cast<std::size_t>(list.getCount());
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printReverse();
    }
};