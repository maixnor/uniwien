// ADS_set.h

#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <iterator>
#include <stdexcept>
#include <iostream>

template <typename Key, size_t N = 16, size_t BucketSize = 4>
class ADS_set {
public:
    using value_type = Key;
    using key_type = Key;
    using reference = const value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;

    class const_iterator;
    using iterator = const_iterator;

    // Constructors and Destructor
    ADS_set();
    ADS_set(std::initializer_list<key_type> ilist);
    ~ADS_set();

    // Modifiers
    bool insert(const key_type& key);
    size_type erase(const key_type& key);
    void clear();

    // Lookup
    size_type count(const key_type& key) const;
    const_iterator find(const key_type& key) const;

    // Iterators
    const_iterator begin() const;
    const_iterator end() const;

private:
    // Overflow bucket structure
    struct Bucket {
        key_type elements[BucketSize];
        size_t count;
        Bucket* next;

        Bucket() : count(0), next(nullptr) {}
    };

    // Main array and overflow buckets
    key_type main_array[N];
    bool occupied[N];
    Bucket* overflow_buckets[N];

    // Hash function
    size_t hash(const key_type& key) const;

public:
    // Iterator implementation
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = Key;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const key_type*;
        using reference         = const key_type&;

        const_iterator();
        reference operator*() const;
        pointer operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
            return lhs.container == rhs.container &&
                   lhs.index == rhs.index &&
                   lhs.bucket == rhs.bucket &&
                   lhs.bucket_pos == rhs.bucket_pos;
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
            return !(lhs == rhs);
        }

    private:
        const ADS_set* container;
        size_t index;
        Bucket* bucket;
        size_t bucket_pos;

        const_iterator(const ADS_set* c, size_t idx, Bucket* bkt, size_t pos)
            : container(c), index(idx), bucket(bkt), bucket_pos(pos) {}

        void advance();
        friend class ADS_set;
    };
};

// Implementation

// Constructor
template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set() {
    for (size_t i = 0; i < N; ++i) {
        occupied[i] = false;
        overflow_buckets[i] = nullptr;
    }
}

// Initializer List Constructor
template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set(std::initializer_list<key_type> ilist)
    : ADS_set() {
    for (const auto& key : ilist) {
        insert(key);
    }
}

// Destructor
template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::~ADS_set() {
    clear();
}

// Hash Function
template <typename Key, size_t N, size_t BucketSize>
size_t ADS_set<Key, N, BucketSize>::hash(const key_type& key) const {
    return std::hash<key_type>{}(key) % N;
}

// Insert Function
template <typename Key, size_t N, size_t BucketSize>
bool ADS_set<Key, N, BucketSize>::insert(const key_type& key) {
    size_t idx = hash(key);
    if (!occupied[idx]) {
        main_array[idx] = key;
        occupied[idx] = true;
        return true;
    } else {
        // Check if key already exists
        if (main_array[idx] == key) {
            return false;
        }
        Bucket* current = overflow_buckets[idx];
        while (current) {
            for (size_t i = 0; i < current->count; ++i) {
                if (current->elements[i] == key) {
                    return false;
                }
            }
            if (current->count < BucketSize) {
                current->elements[current->count++] = key;
                return true;
            }
            if (!current->next) {
                break;
            }
            current = current->next;
        }
        // Add new bucket if necessary
        if (!current || current->count == BucketSize) {
            Bucket* new_bucket = new Bucket();
            if (current) {
                current->next = new_bucket;
            } else {
                overflow_buckets[idx] = new_bucket;
            }
            new_bucket->elements[new_bucket->count++] = key;
            return true;
        }
    }
    return false;
}

// Erase Function
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::erase(const key_type& key) {
    size_t idx = hash(key);
    if (occupied[idx] && main_array[idx] == key) {
        // Move last element in overflow buckets to main array
        Bucket* current = overflow_buckets[idx];
        if (current) {
            main_array[idx] = current->elements[--current->count];
            if (current->count == 0) {
                overflow_buckets[idx] = current->next;
                delete current;
            }
        } else {
            occupied[idx] = false;
        }
        return 1;
    } else {
        Bucket* current = overflow_buckets[idx];
        Bucket* prev = nullptr;
        while (current) {
            for (size_t i = 0; i < current->count; ++i) {
                if (current->elements[i] == key) {
                    current->elements[i] = current->elements[--current->count];
                    if (current->count == 0 && prev) {
                        prev->next = current->next;
                        delete current;
                    }
                    return 1;
                }
            }
            prev = current;
            current = current->next;
        }
    }
    return 0;
}

// Clear Function
template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::clear() {
    for (size_t i = 0; i < N; ++i) {
        if (overflow_buckets[i]) {
            Bucket* current = overflow_buckets[i];
            while (current) {
                Bucket* to_delete = current;
                current = current->next;
                delete to_delete;
            }
            overflow_buckets[i] = nullptr;
        }
        occupied[i] = false;
    }
}

// Count Function
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::count(const key_type& key) const {
    size_t idx = hash(key);
    if (occupied[idx] && main_array[idx] == key) {
        return 1;
    }
    Bucket* current = overflow_buckets[idx];
    while (current) {
        for (size_t i = 0; i < current->count; ++i) {
            if (current->elements[i] == key) {
                return 1;
            }
        }
        current = current->next;
    }
    return 0;
}

// Find Function
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator ADS_set<Key, N, BucketSize>::find(const key_type& key) const {
    size_t idx = hash(key);
    if (occupied[idx] && main_array[idx] == key) {
        return const_iterator(this, idx, nullptr, 0);
    }
    Bucket* current = overflow_buckets[idx];
    while (current) {
        for (size_t i = 0; i < current->count; ++i) {
            if (current->elements[i] == key) {
                return const_iterator(this, idx, current, i);
            }
        }
        current = current->next;
    }
    return end();
}

// Begin Iterator
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator ADS_set<Key, N, BucketSize>::begin() const {
    for (size_t i = 0; i < N; ++i) {
        if (occupied[i]) {
            // Check if there are overflow buckets
            if (overflow_buckets[i]) {
                return const_iterator(this, i, overflow_buckets[i], 0);
            } else {
                return const_iterator(this, i, nullptr, 0);
            }
        } else if (overflow_buckets[i]) {
            return const_iterator(this, i, overflow_buckets[i], 0);
        }
    }
    return end();
}

// End Iterator
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator ADS_set<Key, N, BucketSize>::end() const {
    return const_iterator(this, N, nullptr, 0);
}

// Iterator Default Constructor
template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::const_iterator::const_iterator()
    : container(nullptr), index(N), bucket(nullptr), bucket_pos(0) {}

// Iterator Dereference Operator
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator::reference
ADS_set<Key, N, BucketSize>::const_iterator::operator*() const {
    if (bucket) {
        return bucket->elements[bucket_pos];
    } else {
        return container->main_array[index];
    }
}

// Iterator Arrow Operator
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator::pointer
ADS_set<Key, N, BucketSize>::const_iterator::operator->() const {
    return &(**this);
}

// Iterator Prefix Increment
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator&
ADS_set<Key, N, BucketSize>::const_iterator::operator++() {
    advance();
    return *this;
}

// Iterator Postfix Increment
template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator
ADS_set<Key, N, BucketSize>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    advance();
    return temp;
}

// Iterator Advance Function
template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::const_iterator::advance() {
    if (bucket) {
        if (++bucket_pos < bucket->count) {
            return;
        } else if (bucket->next) {
            bucket = bucket->next;
            bucket_pos = 0;
            return;
        } else {
            bucket = nullptr;
        }
    } else {
        ++index;
    }

    while (index < container->N) {
        if (container->occupied[index]) {
            if (container->overflow_buckets[index]) {
                bucket = container->overflow_buckets[index];
                bucket_pos = 0;
                return;
            } else {
                return;
            }
        } else if (container->overflow_buckets[index]) {
            bucket = container->overflow_buckets[index];
            bucket_pos = 0;
            return;
        }
        ++index;
    }
}

// Example Usage
/*
#include "ADS_set.h"
#include <iostream>

int main() {
    ADS_set<int> my_set = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170};

    // Using range-based for loop
    for (const auto& elem : my_set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Using iterators explicitly
    for (auto it = my_set.begin(); it != my_set.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Find and erase
    auto it = my_set.find(70);
    if (it != my_set.end()) {
        std::cout << "Found: " << *it << std::endl;
        my_set.erase(70);
    }

    // Iterate after erase
    for (const auto& elem : my_set) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
*/

#endif // ADS_SET_H