#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() : list(){}

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        T temp = list.getHead()->data;
        list.removeHead();
        return temp;
    }

    // Access
    T peek() const override {
        if (list.getHead() == nullptr) {
            throw std::runtime_error("X");
        }
        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return static_cast<size_t>(list.getCount());
    }

    void PrintForward() {
        list.printForward();
    }

    void PrintReverse() {
        list.printReverse();
    }

};