#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>

template<typename T>

class Vector {
  public: 
    using value_type = T; 
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    class ConstIterator;
    class Iterator;
    using iterator = Vector::Iterator;
    using const_iterator = Vector::ConstIterator;
    using difference_type = std::ptrdiff_t;

  private:
    static const size_t min_sz = 0;
    size_type sz; 
    size_type max_sz; 
    pointer values; 

    void realloc(size_type new_sz) {
      pointer new_values = new value_type[new_sz];
      for (size_type s{0}; s < sz; ++s) {
        new_values[s] = values[s];
      }
      delete[] values;
      values = new_values;
      max_sz = new_sz;
    }

  public :
    Vector() : max_sz{min_sz}, sz{min_sz}  {
      values = new value_type[min_sz];
    }

    Vector(size_type max_sz) : max_sz{max_sz}, sz{0}, values{new value_type[this->max_sz]} {	
      if (max_sz < 0) {
        max_sz = min_sz;
        values = new value_type[this->max_sz];
      }
    }

    Vector(std::initializer_list<value_type> ilist) : Vector(ilist.size()) {
      for (const auto& val : ilist) {
        values[sz++] = val;
      }
    }

    Vector(const Vector &vec) : Vector(vec.sz){
      for (; sz < vec.sz; ++sz) {
        values[sz] = vec.values[sz];
      }
    }

    ~Vector() {	
      delete[] values;
    }

    size_type size() const {
      return sz;
    }

    bool empty() const {
      if (sz == 0) {
        return true;
      }
      return false;
    }

    void clear() {
      sz = 0;
    }

    void reserve(size_type n) {
      if (n == 0 || n <= max_sz) {
        return;
      }
      else if (n > max_sz) {
        realloc(n);
      }
    }

    void shrink_to_fit() {
      if (sz < min_sz) {
        return;
      }
      if (sz < max_sz) {
        realloc(sz);
      }
    }

    void push_back(const_reference x) {
      if (sz >= max_sz) {
        realloc(2*(max_sz+1));
      }
      values[sz++] = x;
    }

    void pop_back() {
      if (sz <= 0) {
        throw std::runtime_error("SegFault: deleting nonexistent values");
      }
      sz--;
    }

    value_type& operator[](size_type index) {
      if (index >= sz || sz < 0) {
        throw std::runtime_error("SegFault: Index out of bound!");
      }
      return values[index];
    }

    const value_type& operator[](size_type index) const{
      if (index >= sz || sz < 0) {
        throw std::runtime_error("SegFault: Index out of bound!");
      }
      return values[index];
    }

    size_type capacity() const {
      return this->max_sz;
    }

    Vector& operator=(Vector vec) {
      std::swap(max_sz, vec.max_sz);
      std::swap(sz, vec.sz);
      std::swap(values, vec.values);
      return *this;
    }

    std::ostream& print(std::ostream& o) const {
      o << "[";
      for (size_type s{0}; s < sz; ++s) {
        if (sz - s != 1) {
          o << values[s] << ", ";
        }
        else {
          o << values[s];
        }
      }
      o << "]";
      return o;
    }
    
    iterator begin() {
      return iterator(values);
    }

    iterator end() {
      return iterator(values + sz);
    }

    const_iterator begin() const {
      return const_iterator(values);
    }

    const_iterator end() const {
      return const_iterator(values + sz);
    }

    iterator insert(iterator pos, const_reference val){
      auto diff = pos-begin();
      if (diff < 0 || static_cast<size_type>(diff) > sz) {
        throw std::runtime_error("Iterator out of Bounds");
      }
      size_type current{static_cast<size_type> (diff)};
      if (sz >= max_sz) {
        reserve(2*(max_sz+1));
      }
      for (auto i{sz};i-- > current;) {
        values[i+1] = values[i];
      }
      values[current] = val;
      ++sz;
      return iterator{values+current};
    }
    
    iterator erase(iterator pos) {
      auto diff = pos-begin();
      if (diff<0 || static_cast<size_type>(diff) > sz) {
        throw std::runtime_error("Iterator out of Bounds");
      }
      size_type current{static_cast<size_type>(diff)}; 
      for (auto i{current}; i < sz-1; ++i) {
        values[i] = values[i+1];
      }
      --sz;
      return iterator{values+current};
    }

	class Iterator {
		public : 
			using value_type = Vector::value_type;
			using size_type = Vector::size_type;
			using reference = Vector::reference;
			using pointer = Vector::pointer;
			using difference_type = Vector::difference_type;
			using iterator_category = std::forward_iterator_tag;

		private : 
			pointer ptr;

		public:
      Iterator() {
        this->ptr = nullptr;
      }

      Iterator(pointer ptr) {
        this->ptr = ptr;
      }

      reference operator*() const {
        return *ptr;
      }

      pointer operator->()const {
        return ptr;
      }

      bool operator==(const const_iterator& iter) const {
        const_iterator help(*this);
        return (help == iter);
      }

      bool operator!=(const const_iterator& iter) const {
        return !(*this == iter);
      }

      iterator& operator++() {
        ++ptr;
        return *this;
      }

      iterator operator++(int) {
        iterator old(*this);
        ++(*this);
        return old;
      }

      operator const_iterator() const {
        return ConstIterator(ptr);
      }

      friend difference_type operator-(const iterator& i, const iterator& j) {
        return i.ptr - j.ptr;
      }
	};

	class ConstIterator{
		public: 
			using value_type = Vector::value_type;
			using size_type = Vector::size_type;
			using reference = Vector::const_reference;
			using pointer = Vector::const_pointer;
			using difference_type = Vector::difference_type;
			using iterator_category = std::forward_iterator_tag;

		private:
			pointer ptr;

		public:
      ConstIterator() {
        this->ptr = nullptr;
      }

      ConstIterator(pointer ptr) {
        this->ptr = ptr;
      }

      reference operator*() const {
        return *ptr;
      }

      pointer operator->()const {
        return ptr;
      }

      bool operator==(const const_iterator& iter) const {
        return (ptr==iter.ptr);
      }

      bool operator!=(const const_iterator& iter) const {
        return !(*this == iter);
      }

      const_iterator& operator++() {
        ++ptr;
        return *this;
      }

      const_iterator operator++(int) {
        const_iterator old(*this);
        ++(*this);
        return old;
      }

      friend difference_type operator-(const const_iterator& i,const const_iterator& j) {
        return i.ptr - j.ptr;
      }
  };

};

template <typename T>

std::ostream& operator<<(std::ostream& o, const Vector<T>& v) {
	return v.print(o); 
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

       // initializer list constructor
    Vector(std::initializer_list<T> initList) : size_(initList.size()), capacity_(initList.size()), data_(new T[capacity_]) {
        std::copy(initList.begin(), initList.end(), data_);
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

