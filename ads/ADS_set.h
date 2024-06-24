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

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ADS_set::value_type;
        using difference_type = ADS_set::difference_type;
        using pointer = const value_type*;
        using reference = const value_type&;

        Iterator(const ADS_set *set = nullptr, size_type bucket = 0, size_type index = 0) 
            : set(set), bucket(bucket), index(index) {
            advance_past_empty_buckets();
        }

        reference operator*() const { return set->buckets[bucket]->data[index]; }
        pointer operator->() const { return &set->buckets[bucket]->data[index]; }

        Iterator &operator++() {
            ++index;
            advance_past_empty_buckets();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++*this;
            return temp;
        }

        friend bool operator==(const Iterator &lhs, const Iterator &rhs) {
            return lhs.set == rhs.set && lhs.bucket == rhs.bucket && lhs.index == rhs.index;
        }

        friend bool operator!=(const Iterator &lhs, const Iterator &rhs) {
            return !(lhs == rhs);
        }

    private:
        const ADS_set *set;
        size_type bucket;
        size_type index;

        void advance_past_empty_buckets() {
            while (bucket < set->table_size && (!set->buckets[bucket] || index >= set->buckets[bucket]->size)) {
                ++bucket;
                index = 0;
            }
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

    const_iterator begin() const { return const_iterator(this); }
    const_iterator end() const { return const_iterator(this, table_size); }

private:
    struct Bucket {
        key_type data[BucketSize];
        size_type size;
        Bucket* overflow;

        Bucket() : size(0), overflow(nullptr) {}

        ~Bucket() { delete overflow; }

        size_type add(const key_type &key) {
            if (size < BucketSize) {
                data[size++] = key;
                return size;
            }
            if (!overflow) {
                overflow = new Bucket;
            }
            return overflow->add(key);
        }

        void remove(const key_type &key) {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) {
                    for (size_type j = i; j < size - 1; ++j) {
                        data[j] = data[j + 1];
                    }
                    --size;
                    return;
                }
            }
            if (overflow) {
                overflow->remove(key);
                if (overflow->size == 0) {
                    delete overflow;
                    overflow = nullptr;
                }
            }
        }

        bool contains(const key_type &key) const {
            return at(key) != (size_type)-1;
        }

        size_type at(const key_type &key) const {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) {
                    return i;
                }
            }
            return overflow ? overflow->contains(key) : ((size_type)-1);
        }
    };

    size_type table_size;
    size_type num_elements;
    Bucket **buckets;

    void rehash();
    size_type bucket_index(const key_type &key) const {
        return hasher{}(key) % table_size;
    }
};

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set() : table_size(N), num_elements(0), buckets(new Bucket*[N]) {
    for (size_type i = 0; i < N; ++i) {
        buckets[i] = nullptr;
    }
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set(std::initializer_list<key_type> ilist) : ADS_set() {
    insert(ilist.begin(), ilist.end());
}

template <typename Key, size_t N, size_t BucketSize>
template<typename InputIt>
ADS_set<Key, N, BucketSize>::ADS_set(InputIt first, InputIt last) : ADS_set() {
    insert(first, last);
}

template <typename Key, size_t N, size_t BucketSize>
ADS_set<Key, N, BucketSize>::ADS_set(const ADS_set &other) : table_size(other.table_size), num_elements(other.num_elements), buckets(new Bucket*[other.table_size]) {
    for (size_type i = 0; i < table_size; ++i) {
        if (other.buckets[i]) {
            buckets[i] = new Bucket(*other.buckets[i]);
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
    for (size_type i = 0; i < ilist.size(); ++i) {
        insert(*(ilist.begin() + i));
    }
}

template <typename Key, size_t N, size_t BucketSize>
template<typename InputIt>
void ADS_set<Key, N, BucketSize>::insert(InputIt first, InputIt last) {
    for (InputIt it = first; it != last; ++it) {
        insert(*it);
    }
}

template <typename Key, size_t N, size_t BucketSize>
std::pair<typename ADS_set<Key, N, BucketSize>::const_iterator, bool> ADS_set<Key, N, BucketSize>::insert(const key_type &key) {
    size_type index = bucket_index(key);
    if (!buckets[index]) {
        buckets[index] = new Bucket;
    }
    Bucket* bucket = buckets[index];
    size_type idx = bucket->at(key);
    if (idx != (size_type)-1) {
        return {const_iterator(this, index, idx), false};
    }
    idx = bucket->add(key);
    ++num_elements;
    if (num_elements > table_size * 2) rehash();
    return {const_iterator(this, index, idx), true};
}

template <typename Key, size_t N, size_t BucketSize>
void ADS_set<Key, N, BucketSize>::clear() {
    for (size_type i = 0; i < table_size; ++i) {
        Bucket *current = buckets[i];
        while (current) {
            if (!current->overflow) {
              current = nullptr;
              delete current;
              break;
            }
            Bucket *next = current->overflow;
            current = nullptr;
            delete current;
            current = next;
        }
        buckets[i] = nullptr;
    }
    num_elements = 0;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::erase(const key_type &key) {
    size_type index = bucket_index(key);
    if (!buckets[index] || !buckets[index]->contains(key)) return 0;
    buckets[index]->remove(key);
    --num_elements;
    return 1;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::erase(const_iterator pos) {
    if (pos == end()) return 0;
    return erase(*pos);
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::size_type ADS_set<Key, N, BucketSize>::count(const key_type &key) const {
    size_type index = bucket_index(key);
    return buckets[index] && buckets[index]->contains(key) ? 1 : 0;
}

template <typename Key, size_t N, size_t BucketSize>
typename ADS_set<Key, N, BucketSize>::const_iterator ADS_set<Key, N, BucketSize>::find(const key_type &key) const {
    size_type index = bucket_index(key);
    if (buckets[index] && buckets[index]->contains(key) > 0) {
        size_type i = 0;
        Bucket *bucket = buckets[index]; 
        while (bucket) {
            for (; i < bucket->size; ++i) {
                if (key_equal{}(bucket->data[i], key)) {
                    return const_iterator(this, index, i);
                }
            }
            bucket = bucket->overflow;
        }
    }
    return end();
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
            for (size_type j = 0; j < bucket->size; ++j) {
                o << bucket->data[j] << " ";
            }
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
    Bucket **new_buckets = new Bucket*[new_table_size];
    for (size_type i = 0; i < new_table_size; ++i) {
        new_buckets[i] = nullptr;
    }

    for (size_type i = 0; i < table_size; ++i) {
        Bucket *bucket = buckets[i];
        while (bucket) {
            for (size_type j = 0; j < bucket->size; ++j) {
                const key_type &key = bucket->data[j];
                size_type new_index = hasher{}(key) % new_table_size;
                if (!new_buckets[new_index]) {
                    new_buckets[new_index] = new Bucket();
                }
                new_buckets[new_index]->add(key);
            }
            if (!bucket->overflow) {
              bucket = nullptr;
              continue;
            }
            Bucket *old_bucket = bucket;
            bucket = bucket->overflow;
            old_bucket = nullptr;
            delete old_bucket;
        }
    }
    delete[] buckets;
    buckets = new_buckets;
    table_size = new_table_size;
}

#endif // ADS_SET_H

