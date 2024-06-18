#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <iostream>
#include <stdexcept>
#include <iterator>
#include <vector>

template <typename Key, size_t N = 16>
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
    private:
        const ADS_set *set;
        size_type bucket;
        size_type index;

        void advance_past_empty_buckets() {
            while (bucket < set->table_size && (!set->buckets[bucket] || index >= set->buckets[bucket]->data.size())) {
                ++bucket;
                index = 0;
            }
        }
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
        std::vector<key_type> data;

        void add(const key_type &key) {
            data.push_back(key);
        }

        void remove(const key_type &key) {
            auto it = std::remove(data.begin(), data.end(), key);
            if (it != data.end()) data.erase(it, data.end());
        }

        bool contains(const key_type &key) const {
            return std::find(data.begin(), data.end(), key) != data.end();
        }
    };

    size_type table_size;
    size_type num_elements;
    std::vector<Bucket*> buckets;

    void rehash();
    size_type bucket_index(const key_type &key) const {
        return hasher{}(key) % table_size;
    }
};

template <typename Key, size_t N>
ADS_set<Key, N>::ADS_set() : table_size(N), num_elements(0), buckets(N, nullptr) {}

template <typename Key, size_t N>
ADS_set<Key, N>::ADS_set(std::initializer_list<key_type> ilist) : ADS_set() {
    insert(ilist.begin(), ilist.end());
}

template <typename Key, size_t N>
template<typename InputIt>
ADS_set<Key, N>::ADS_set(InputIt first, InputIt last) : ADS_set() {
    insert(first, last);
}

template <typename Key, size_t N>
ADS_set<Key, N>::ADS_set(const ADS_set &other) : table_size(other.table_size), num_elements(other.num_elements), buckets(other.table_size, nullptr) {
    for (size_type i = 0; i < table_size; ++i) {
        if (other.buckets[i]) {
            buckets[i] = new Bucket(*other.buckets[i]);
        }
    }
}

template <typename Key, size_t N>
ADS_set<Key, N>::~ADS_set() {
    clear();
}

template <typename Key, size_t N>
ADS_set<Key, N> &ADS_set<Key, N>::operator=(const ADS_set &other) {
    if (this == &other) return *this;
    ADS_set tmp(other);
    swap(tmp);
    return *this;
}

template <typename Key, size_t N>
ADS_set<Key, N> &ADS_set<Key, N>::operator=(std::initializer_list<key_type> ilist) {
    clear();
    insert(ilist);
    return *this;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::size_type ADS_set<Key, N>::size() const {
    return num_elements;
}

template <typename Key, size_t N>
bool ADS_set<Key, N>::empty() const {
    return num_elements == 0;
}

template <typename Key, size_t N>
void ADS_set<Key, N>::insert(std::initializer_list<key_type> ilist) {
    for (const auto &key : ilist) {
        insert(key);
    }
}

template <typename Key, size_t N>
template<typename InputIt>
void ADS_set<Key, N>::insert(InputIt first, InputIt last) {
    for (InputIt it = first; it != last; ++it) {
        insert(*it);
    }
}

template <typename Key, size_t N>
std::pair<typename ADS_set<Key, N>::const_iterator, bool> ADS_set<Key, N>::insert(const key_type &key) {
    size_type index = bucket_index(key);
    if (!buckets[index]) {
        buckets[index] = new Bucket;
    }
    Bucket* bucket = buckets[index];
    if (bucket->contains(key)) {
        return {const_iterator(this, index), false};
    }
    bucket->add(key);
    ++num_elements;
    if (num_elements > table_size * 2) rehash();
    return {const_iterator(this, index), true};
}

template <typename Key, size_t N>
void ADS_set<Key, N>::clear() {
    for (size_type i = 0; i < table_size; ++i) {
        delete buckets[i];
        buckets[i] = nullptr;
    }
    num_elements = 0;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::size_type ADS_set<Key, N>::erase(const key_type &key) {
    size_type index = bucket_index(key);
    if (!buckets[index] || !buckets[index]->contains(key)) return 0;
    buckets[index]->remove(key);
    --num_elements;
    return 1;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::size_type ADS_set<Key, N>::erase(const_iterator pos) {
    if (pos == end()) return 0;
    return erase(*pos);
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::size_type ADS_set<Key, N>::count(const key_type &key) const {
    size_type index = bucket_index(key);
    return buckets[index] && buckets[index]->contains(key) ? 1 : 0;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::const_iterator ADS_set<Key, N>::find(const key_type &key) const {
    size_type index = bucket_index(key);
    if (buckets[index] && buckets[index]->contains(key)) {
        for (size_type i = 0; i < buckets[index]->data.size(); ++i) {
            if (key_equal{}(buckets[index]->data[i], key)) {
                return const_iterator(this, index, i);
            }
        }
    }
    return end();
}

template <typename Key, size_t N>
void ADS_set<Key, N>::swap(ADS_set &other) {
    std::swap(table_size, other.table_size);
    std::swap(num_elements, other.num_elements);
    std::swap(buckets, other.buckets);
}

template <typename Key, size_t N>
void ADS_set<Key, N>::dump(std::ostream &o) const {
    for (size_type i = 0; i < table_size; ++i) {
        o << "Bucket " << i << ": ";
        if (buckets[i]) {
            for (const auto &key : buckets[i]->data) {
                o << key << " ";
            }
        }
        o << "\n";
    }
}

template <typename Key, size_t N>
void ADS_set<Key, N>::rehash() {
    size_type new_table_size = table_size * 2;
    std::vector<Bucket*> new_buckets(new_table_size, nullptr);
    for (size_type i = 0; i < table_size; ++i) {
        if (buckets[i]) {
            for (const auto &key : buckets[i]->data) {
                size_type new_index = hasher{}(key) % new_table_size;
                if (!new_buckets[new_index]) {
                    new_buckets[new_index] = new Bucket();
                }
                new_buckets[new_index]->add(key);
            }
            delete buckets[i];
        }
    }
    buckets.swap(new_buckets);
    table_size = new_table_size;
}

#endif // ADS_SET_H

