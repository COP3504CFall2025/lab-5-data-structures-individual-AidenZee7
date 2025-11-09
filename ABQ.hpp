#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>
// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() : capacity_(1), curr_size_(0), array_(new T[capacity_]) {}

    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]) {}

    ABQ(const ABQ& other) { // copy constr
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ& operator=(const ABQ& rhs) { // copy assign
        if (this == &rhs) {
            return (*this);
        }
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < rhs.curr_size_; i++) {
            temp[i] = rhs.array_[i];
        }
        delete[] array_;
        array_ = temp;
        temp = nullptr;
        return (*this);
    }
    ABQ(ABQ&& other) noexcept { // move constr
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        array_ = other.array_;
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& rhs) noexcept { // move assign
        if (this == &rhs) {
            return (*this);
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        rhs.array_ = nullptr;
        return (*this);
    }
    ~ABQ() noexcept override {
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size_ == capacity_) {
            T* temp = new T[capacity_ * 2];
            for (size_t i = 0; i < curr_size_; i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            temp = nullptr;
            capacity_ *= 2;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("X");
        }
        return array_[0];
    }

    void newArray(size_t newCap) {
        T* temp = new T[newCap];
        for (size_t i = 0; i < curr_size_; i++) {
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        capacity_ = newCap;
    }

    // Deletion
    T dequeue() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("X");
        }
        T ret = array_[0];
        for (size_t i = 1; i < curr_size_; i++) {
            array_[i-1] = array_[i];
        }
        curr_size_--;
        if ((curr_size_ <= (capacity_ / 4)) && capacity_ > 1) {
            newArray(capacity_ /2);
        }
        return ret;
    }

    void PrintForward() {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << " ";
        }
    }

    void PrintReverse() {
        for (size_t i = curr_size_ - 1; i >= 0; i--) {
            std::cout << array_[i] << " ";
        }
    }

};