#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <iostream>

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity_(1), curr_size_(0), array_(new T[1]){}

    explicit ABS(const size_t capacity) : capacity_(capacity), curr_size_(0), array_(new T[capacity_]){}

    ABS(const ABS& other) { // copy constr
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        array_ = new T[capacity_];
        for (size_t i = 0; i < other.curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABS& operator=(const ABS& rhs) { // copy assign
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
        return (*this);
    }

    ABS(ABS&& other) noexcept { // move constr
        array_ = other.array_;
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;
        other.array_ = nullptr;
        other.capacity_ = 0;
        other.curr_size_ = 0;
    }
    ABS& operator=(ABS&& rhs) noexcept { //move assign
        if (this == &rhs) {
            return (*this);
        }
        delete[] array_;
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = rhs.array_;
        rhs.array_ = nullptr;
        rhs.capacity_ = 0;
        rhs.curr_size_ = 0;
        return (*this);
    }
    ~ABS() noexcept override { // destructor
        delete[] array_;
        array_ = nullptr;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array_;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (capacity_ == curr_size_) {
            T* temp = new T[capacity_ * scale_factor_];
            for (size_t i = 0; i < curr_size_; i++) {
                temp[i] = array_[i];
            }
            delete[] array_;
            array_ = temp;
            temp = nullptr;
            capacity_ *= scale_factor_;
        }
        array_[curr_size_] = data;
        curr_size_++;
    }

    T peek() const override {
        if (curr_size_ == 0) {
            throw std::runtime_error("X");
        }
        return array_[curr_size_ - 1];
    }

    T pop() override {
        if (curr_size_ == 0) {
            throw std::runtime_error("X"); // if empty
        }
        return array_[--curr_size_];
    }

    void PrintForward() const {
        for (size_t i = 0; i < curr_size_; i++) {
            std::cout << array_[i] << " ";
        }
    }

    void PrintReverse() const {
        for (size_t i = curr_size_ - 1; i >= 0; i--) {
            std::cout << array_[i] << " ";
        }
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};