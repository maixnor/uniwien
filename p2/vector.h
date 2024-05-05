#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
#include<stdexcept>
#include<memory>
#include<initializer_list>
#include<algorithm>

template <typename T>
class Vector{
  private:
    size_t size_;
    size_t capacity_;
    T* data_;
  
  public:
    // constructor
    Vector(size_t initialSize = 0) : size_(0), capacity_(initialSize) {
        data_ = new T[capacity_];
    }

    // destructor
    ~Vector() { delete[] data_; }

    // copy constructor
    Vector(const Vector<T>& other)
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // assignment operator
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new T[capacity_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    // move constructor
    Vector(Vector<T>&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = other.data_;
        other.data_ = nullptr;  // indicate that the vector is no longer valid
    }

    // move assignment operator
    Vector<T>& operator=(Vector<T>&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = other.data_;
            other.data_ = nullptr;  // indicate that the vector is no longer valid
        }
        return *this;
    }

    // at() - returns a reference to the element at the given index
    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // at() - returns a const reference to the element at the given index
    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    // front() - returns a reference to the first element
    T& front() { return data_[0]; }
    T& begin() { return data_[0]; }

    // front() - returns a const reference to the first element
    const T& front() const { return data_[0]; }
    const T& begin() const { return data_[0]; }

    // back() - returns a reference to the last element
    T& back() { return data_[size_ - 1]; }
    T& end() { return data_[size_ - 1]; }

    // back() - returns a const reference to the last element
    const T& back() const { return data_[size_ - 1]; }
    const T& end() const { return data_[size_ - 1]; }

    // size() - returns the number of elements in the vector
    size_t size() const { return size_; }

    // capacity() - returns the maximum number of elements the vector can hold
    size_t capacity() const { return capacity_; }

    // clear() - removes all elements from the vector
    void clear() {
        size_ = 0;
        if (data_) delete[] data_;
        data_ = new T[capacity_];  // reset the array to its original size
    }

    // resize() - changes the capacity of the vector
    void resize(size_t newCapacity) {
        if (newCapacity > capacity_) {
            T* newData = new T[newCapacity];
            std::copy(data_, data_ + size_, newData);
            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        } else if (newCapacity < size_) {
            T* newData = new T[newCapacity];
            std::copy(data_, data_ + newCapacity, newData);
            delete[] data_;
            data_ = newData;
            size_ = newCapacity;
        }
    }


};  

#endif

