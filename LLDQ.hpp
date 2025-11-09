#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>

template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() : list(){}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        T temp = list.getHead()->data;
        list.removeHead();
        return temp;
    }
    T popBack() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        T temp = list.getTail()->data;
        list.removeTail();
        return temp;
    }

    // Element Accessors
    const T& front() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        return list.getHead()->data;
    }

    const T& back() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return static_cast<size_t>(list.getCount());
    }

    void PrintForward() {
        return list.printForward();
    }

    void PrintReverse() {
        return list.printReverse();
    }
};
