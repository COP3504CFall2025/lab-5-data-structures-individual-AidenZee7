#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5

    ABDQ() : data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0) {}

    explicit ABDQ(std::size_t capacity): data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0) {}

    ABDQ(const ABDQ& other) { // copy constr
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.size_;
        T* temp = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = other.data_[(other.front_ + i) % capacity_];
        }
        data_ = temp;
        temp = nullptr;
    }

    ABDQ(ABDQ&& other) noexcept { // move constr
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) { // copy assign
        if (this == &other) {
            return (*this);
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        T* temp = new T[size_];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = other.data_[(other.front_ + i) % capacity_];
        }
        delete[] data_;
        data_ = temp;
        temp = nullptr;
        return (*this);
    }

    ABDQ& operator=(ABDQ&& other) noexcept { // move assign
        if (this == &other) {
            return (*this);
        }
        delete[] data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = other.data_;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.data_ = nullptr;
        return (*this);
    }

    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        ensureCapacity();
        data_[(capacity_ + front_ - 1) % capacity_] = item;
        front_ = (capacity_ + front_ - 1) % capacity_;
        size_++;
        //shrinkIfNeeded();
    }

    void pushBack(const T& item) override {
        ensureCapacity();
        data_[(capacity_ + back_) % capacity_] = item;
        back_ = (capacity_ + back_ + 1) % capacity_;
        size_++;
        //shrinkIfNeeded();
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("X");
        }
        T temp = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        shrinkIfNeeded();
        return temp;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("X");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        T temp = data_[back_];
        size_--;
        shrinkIfNeeded();
        return temp;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) {
            throw(std::runtime_error("X"));
        }
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) {
            throw(std::runtime_error("X"));
        }
        return data_[(capacity_ + back_ - 1) % capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    void PrintForward() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << data_[(front_ + i) % capacity_] << " ";
        }
    }
    void PrintReverse() {
        for (size_t i = 0; i < size_; i++){
            std::cout << data_[(capacity_ + back_ - i - 1) % capacity_] << " ";
        }
    }

    void shrinkIfNeeded() {
        if (size_ <= (capacity_ / 2)) {
            T* temp = new T[capacity_/2];
            for (size_t i = 0; i < size_; i++) {
                temp[i] = data_[(front_ + i) % capacity_];
            }
            front_ = 0;
            back_ = size_;
            capacity_ /= 2;
            delete[] data_;
            data_ = temp;
            temp = nullptr;
        }
    }

    void ensureCapacity() {
        T* temp = new T[capacity_ * 2];
        for (size_t i = 0; i < size_; i++) {
            temp[i] = data_[(front_ + i) % capacity_];
        }
        capacity_ *= 2;
        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_;
        temp = nullptr;
    }

};
