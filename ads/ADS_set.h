#ifndef ADS_SET_H
#define ADS_SET_H

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
#include <functional>

template <typename Key, size_t N = 16, size_t BucketSize = 4>
class ADS_set {
public:
    using value_type = Key;
    using key_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using key_equal = std::equal_to<key_type>;
    using hasher = std::hash<key_type>;

    struct Bucket {
        key_type data[BucketSize];
        size_type size;
        Bucket* overflow;

        Bucket() : size(0), overflow(nullptr) {}

        Bucket(const Bucket& other) : size(other.size), overflow(nullptr) {
            for (size_type i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
            if (other.overflow) {
                overflow = new Bucket(*other.overflow);
            }
        }

        ~Bucket() {}

        bool isFull() const {
            return size == BucketSize;
        }

        size_type add(const key_type &key) {
            if (size < BucketSize) {
                data[size++] = key;
                return 1;
            }
            if (!overflow) {
                overflow = new Bucket();
            }
            return overflow->add(key);
        }

        size_type remove(const key_type &key) {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) {
                    for (size_type j = i + 1; j < size; ++j) {
                        data[j - 1] = data[j];
                    }
                    --size;
                    return 1;
                }
            }
            if (overflow) {
                return overflow->remove(key);
            }
            return 0;
        }

        bool contains(const key_type &key) const {
            return at(key).first != BucketSize + 1;
        }

        std::pair<size_type, const Bucket*> at(const key_type &key) const {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) {
                    return {i, this};
                }
            }
            if (overflow) {
                return overflow->at(key);
            }
            return {BucketSize + 1, this};
        }
    };

    class Iterator {
        friend class ADS_set;
        const ADS_set* set;
        size_t bucket_idx;
        size_t elem_idx;
        Bucket* current_bucket;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Key;
        using difference_type = std::ptrdiff_t;
        using pointer = const Key*;
        using reference = const Key&;

        Iterator(const ADS_set* s = nullptr, size_t b_idx = 0, size_t e_idx = 0, Bucket* bucket = nullptr)
            : set(s), bucket_idx(b_idx), elem_idx(e_idx), current_bucket(bucket) {}

        reference operator*() const {
            return current_bucket->data[elem_idx];
        }

        const Key* operator->() const {
            if (current_bucket && elem_idx < current_bucket->size) {
                return &current_bucket->data[elem_idx];
            }
            return nullptr;
        }

        Iterator& operator++() {
            if (!set || !current_bucket) return *this;

            // Advance within current bucket
            if (elem_idx + 1 < current_bucket->size) {
                ++elem_idx;
                return *this;
            }

            // Move to overflow if present
            if (current_bucket->overflow && current_bucket->overflow->size > 0) {
                current_bucket = current_bucket->overflow;
                elem_idx = 0;
                return *this;
            }

            // Move to next non-empty bucket
            size_t next_bucket = bucket_idx + 1;
            while (next_bucket < set->table_size) {
                if (set->buckets[next_bucket] && set->buckets[next_bucket]->size > 0) {
                    bucket_idx = next_bucket;
                    current_bucket = set->buckets[bucket_idx];
                    elem_idx = 0;
                    return *this;
                }
                ++next_bucket;
            }

            // End
            bucket_idx = set->table_size;
            current_bucket = nullptr;
            elem_idx = 0;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return set == other.set && 
                   bucket_idx == other.bucket_idx && 
                   elem_idx == other.elem_idx &&
                   current_bucket == other.current_bucket;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        void print() const {
            std::cout << bucket_idx << " " << elem_idx << " " << std::endl;
        }
    };

    using iterator = Iterator;
    using const_iterator = Iterator;

    ADS_set();
    ADS_set(std::initializer_list<key_type> ilist);
    template<typename InputIt> ADS_set(InputIt first, InputIt last);
    ADS_set(const ADS_set &other);

    ~ADS_set();

    ADS_set &operator=(const ADS_set &other);
    ADS_set &operator=(std::initializer_list<key_type> ilist);

    size_type size() const;
    bool empty() const;

    void insert(std::initializer_list<key_type> ilist);
    template<typename InputIt> void insert(InputIt first, InputIt last);

    std::pair<const_iterator, bool> insert(const key_type &key);

    void clear();
    size_type erase(const key_type &key);
    size_type erase(const_iterator pos);

    size_type count(const key_type &key) const;
    const_iterator find(const key_type &key) const;

    void swap(ADS_set &other);

    void dump(std::ostream &o = std::cerr) const;

    friend bool operator==(const ADS_set &lhs, const ADS_set &rhs) {
        if (lhs.num_elements != rhs.num_elements) return false;
        for (const auto &key : lhs) {
            if (rhs.count(key) == 0) return false;
        }
        return true;
    }

    friend bool operator!=(const ADS_set &lhs, const ADS_set &rhs) {
        return !(lhs == rhs);
    }

    const_iterator begin() const {
        if (num_elements == 0) return end();
        
        for (size_t i = 0; i < table_size; ++i) {
            if (buckets[i] && buckets[i]->size > 0) {
                return const_iterator(this, i, 0, buckets[i]);
            }
        }
        return end();
    }

    const_iterator end() const {
        return const_iterator(this, table_size, 0, nullptr);
    }

private:
    size_type table_size;
    size_type num_elements;
    Bucket **buckets;

    void rehash();
    size_type bucket_index(const key_type &key) const {
        return hasher{}(key) % table_size;
    }
};

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set() : table_size(N), num_elements(0), buckets(new Bucket*[N]()) {
    for (size_type i = 0; i < N; ++i) {
        buckets[i] = nullptr;
    }
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set(std::initializer_list<key_type> ilist) : ADS_set() {
    insert(ilist.begin(), ilist.end());
}

template <typename Key, size_t N, size_t BucketSize>
template <typename InputIt>
ADS_set<Key, N, BucketSize>::ADS_set(InputIt first, InputIt last) : ADS_set() {
    insert(first, last);
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set(const ADS_set &other)
    : table_size(other.table_size), num_elements(other.num_elements), buckets(new Bucket*[other.table_size]()) {
    for (size_type i = 0; i < table_size; ++i) {
        if (other.buckets[i]) {
            buckets[i] = new Bucket(*other.buckets[i]); // Deep copy each bucket
        } else {
            buckets[i] = nullptr;
        }
    }
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::~ADS_set() {
    clear();
    delete[] buckets;
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize> &ADS_set<Key, N, BucketSize>::operator=(const ADS_set &other) {
    if (this == &other) return *this;
    ADS_set tmp(other);
    swap(tmp);
    return *this;
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize> &ADS_set<Key, N, BucketSize>::operator=(std::initializer_list<key_type> ilist) {
    clear();
    insert(ilist);
    return *this;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::size() const {
    return num_elements;
}

template <typename Key, size_t N, size_t BucketSize>
bool ADS_set<Key, N, BucketSize>::empty() const {
    return num_elements == 0;
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::insert(std::initializer_list<key_type> ilist) {
    for (const auto& key : ilist) {
        insert(key);
    }
}

template <typename Key, size_t N, size_t BucketSize>
template <typename InputIt>
void ADS_set<Key, N, BucketSize>::insert(InputIt first, InputIt last) {
    for (InputIt it = first; it != last; ++it) {
        insert(*it);
    }
}

template <typename Key, size_t N, size_t BucketSize>
std::pair<typename ADS_set<Key, N, BucketSize>::const_iterator, bool> ADS_set<Key, N, BucketSize>::insert(const key_type &key) {
    if (count(key))
        return {find(key), false};
    if (num_elements >= table_size * 2) {
        rehash(); 
    }
    size_type index = bucket_index(key);
    if (!buckets[index]) {
        buckets[index] = new Bucket();
    }
    Bucket* current = buckets[index];
    Bucket* prev = nullptr;
    
    // Traverse to the appropriate bucket (base or overflow)
    while (current) {
        if (!current->isFull()) {
            current->add(key);
            ++num_elements;
            return {const_iterator(this, index, current->size - 1, current), true};
        }
        prev = current;
        current = current->overflow;
    }

    // all buckets are already full, 
    // next overflow bucket is initialized and **linked**
    current = new Bucket(); 
    prev->overflow = current;
    current->add(key);
    ++num_elements;
    return {const_iterator(this, index, current->size - 1, current), true};
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::clear() {
    for (size_type i = 0; i < table_size; ++i) {
        Bucket *current = buckets[i];
        while (current) {
            Bucket *temp = current->overflow;
            delete current;
            current = temp;
        }
        buckets[i] = nullptr;
    }
    num_elements = 0;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::erase(const key_type &key) {
    size_type index = bucket_index(key);
    Bucket* current = buckets[index];
    if (!current) return 0;
    size_type removed = buckets[index]->remove(key);
    num_elements = num_elements - removed;
    if (current->size == 0) { // current is empty, replace with overflow
        auto temp = current->overflow;
        delete current;
        buckets[index] = temp;
    }
    return removed;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::erase(const_iterator pos) {
    if (pos == end()) return 0;
    return erase(*pos);
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::count(const key_type &key) const {
    size_type index = bucket_index(key);
    return (buckets[index] && buckets[index]->contains(key)) ? 1 : 0;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator ADS_set<Key, N, BucketSize>::find(const key_type &key) const {
    size_type index = bucket_index(key);
    if (!buckets[index]) return end();

    std::pair<size_type, const Bucket*> location = buckets[index]->at(key);
    if (location.first == (BucketSize + 1)) return end(); // Key not found

    return const_iterator(this, index, location.first, const_cast<Bucket*>(location.second));
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::swap(ADS_set &other) {
    std::swap(table_size, other.table_size);
    std::swap(num_elements, other.num_elements);
    std::swap(buckets, other.buckets);
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::dump(std::ostream &o) const {
    for (size_type i = 0; i < table_size; ++i) {
        o << "Bucket " << i << ": ";
        for (Bucket *bucket = buckets[i]; bucket; bucket = bucket->overflow) {
            o << "[ ";
            for (size_type j = 0; j < bucket->size; ++j) {
                o << bucket->data[j] << " ";
            }
            o << "] ";
            if (bucket->overflow) {
                o << "-> ";
            }
        }
        o << "\n";
    }
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::rehash() {
     size_type new_table_size = table_size * 2;
    Bucket **new_buckets = new Bucket*[new_table_size]();
    
    // Copy all keys and delete old buckets
    for (size_type i = 0; i < table_size; ++i) {
        Bucket *current = buckets[i];
        while (current) {
            for (size_type j = 0; j < current->size; ++j) {
                size_type new_index = hasher{}(current->data[j]) % new_table_size;
                if (!new_buckets[new_index]) {
                    new_buckets[new_index] = new Bucket();
                }
                new_buckets[new_index]->add(current->data[j]);
            }
            Bucket *to_delete = current;
            current = current->overflow;
            delete to_delete;
        }
    }
    
    delete[] buckets;
    buckets = new_buckets;
    table_size = new_table_size;
}

#endif // ADS_SET_H