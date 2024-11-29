// ADS_set.h

#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <vector>

template <typename Key, size_t N = 16, size_t BucketSize = 4>
class ADS_set {
private:
    struct Node {
        Key key;
        Node* next;
        Node(const Key& key, Node* next = nullptr) : key(key), next(next) {}
    };

    Node** table;
    size_t current_size;
    size_t bucket_count;
    size_t split_pointer;
    size_t level;

    size_t hash(const Key& key, size_t mod) const {
        return hasher{}(key) % mod;
    }

    void rehash() {
        size_t new_bucket_count = bucket_count * 2;
        Node** old_table = table;
        size_t old_bucket_count = bucket_count;

        table = new Node*[new_bucket_count]();
        bucket_count = new_bucket_count;
        current_size = 0;
        split_pointer = 0;
        level++;

        for (size_t i = 0; i < old_bucket_count; ++i) {
            Node* node = old_table[i];
            while (node) {
                insert(node->key);
                Node* to_delete = node;
                node = node->next;
                delete to_delete;
            }
        }
        delete[] old_table;
    }

    void split() {
        if (split_pointer >= (1 << level)) {
            rehash();
        }
        size_t new_bucket_index = split_pointer + (1 << level);
        table[new_bucket_index] = nullptr;

        Node* prev = nullptr;
        Node* node = table[split_pointer];
        while (node) {
            size_t new_index = hash(node->key, bucket_count);
            if (new_index != split_pointer) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    table[split_pointer] = node->next;
                }
                node->next = table[new_bucket_index];
                table[new_bucket_index] = node;
                node = (prev) ? prev->next : table[split_pointer];
            } else {
                prev = node;
                node = node->next;
            }
        }
        split_pointer++;
        if (split_pointer == (1 << level)) {
            split_pointer = 0;
            level++;
        }
    }

public:
    using value_type = Key;
    using key_type = Key;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using key_equal = std::equal_to<key_type>;
    using hasher = std::hash<key_type>;

    ADS_set() : current_size(0), bucket_count(N), split_pointer(0), level(0) {
        table = new Node*[bucket_count]();
    }

    ADS_set(std::initializer_list<key_type> ilist) : ADS_set() {
        insert(ilist);
    }

    template<typename InputIt>
    ADS_set(InputIt first, InputIt last) : ADS_set() {
        insert(first, last);
    }

    ADS_set(const ADS_set &other) : ADS_set() {
        insert(other.begin(), other.end());
    }

    ~ADS_set() {
        clear();
        delete[] table;
    }

    ADS_set &operator=(const ADS_set &other) {
        if (this != &other) {
            clear();
            insert(other.begin(), other.end());
        }
        return *this;
    }

    ADS_set &operator=(std::initializer_list<key_type> ilist) {
        clear();
        insert(ilist);
        return *this;
    }

    size_type size() const {
        return current_size;
    }

    bool empty() const {
        return current_size == 0;
    }

    void insert(std::initializer_list<key_type> ilist) {
        for (const auto& key : ilist) {
            insert(key);
        }
    }

    std::pair<Node*, bool> insert(const key_type &key) {
        size_t index = hash(key, (1 << level) + split_pointer);
        Node* node = table[index];
        while (node) {
            if (key_equal{}(node->key, key)) {
                return {node, false};
            }
            node = node->next;
        }
        table[index] = new Node(key, table[index]);
        ++current_size;
        if (current_size > bucket_count) {
            split();
        }
        return {table[index], true};
    }

    template<typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (auto it = first; it != last; ++it) {
            insert(*it);
        }
    }

    void clear() {
        for (size_t i = 0; i < bucket_count; ++i) {
            Node* node = table[i];
            while (node) {
                Node* to_delete = node;
                node = node->next;
                delete to_delete;
            }
            table[i] = nullptr;
        }
        current_size = 0;
    }

    size_type erase(const key_type &key) {
        size_t index = hash(key, (1 << level) + split_pointer);
        Node* node = table[index];
        Node* prev = nullptr;
        while (node) {
            if (key_equal{}(node->key, key)) {
                if (prev) {
                    prev->next = node->next;
                } else {
                    table[index] = node->next;
                }
                delete node;
                --current_size;
                return 1;
            }
            prev = node;
            node = node->next;
        }
        return 0;
    }

    size_type count(const key_type &key) const {
        return find(key) != end() ? 1 : 0;
    }

    Node* find(const key_type &key) const {
        size_t index = hash(key, (1 << level) + split_pointer);
        Node* node = table[index];
        while (node) {
            if (key_equal{}(node->key, key)) {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    class const_iterator {
    public:
        using value_type = Key;
        using reference = const value_type&;
        using pointer = const value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        const_iterator() : table(nullptr), bucket_index(0), node(nullptr) {}

        const_iterator(Node** table, size_t bucket_index, Node* node)
            : table(table), bucket_index(bucket_index), node(node) {}

        reference operator*() const {
            return node->key;
        }

        pointer operator->() const {
            return &node->key;
        }

        const_iterator& operator++() {
            if (node) {
                node = node->next;
                while (!node && ++bucket_index < bucket_count) {
                    node = table[bucket_index];
                }
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return node == other.node;
        }

        bool operator!=(const const_iterator& other) const {
            return node != other.node;
        }

    private:
        Node** table;
        size_t bucket_index;
        Node* node;
    };

    using iterator = const_iterator;

    const_iterator begin() const {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (table[i]) {
                return const_iterator(table, i, table[i]);
            }
        }
        return end();
    }

    const_iterator end() const {
        return const_iterator(table, bucket_count, nullptr);
    }

    void swap(ADS_set &other) {
        std::swap(table, other.table);
        std::swap(current_size, other.current_size);
        std::swap(bucket_count, other.bucket_count);
        std::swap(split_pointer, other.split_pointer);
        std::swap(level, other.level);
    }

    void dump(std::ostream &o = std::cerr) const {
        for (size_t i = 0; i < bucket_count; ++i) {
            o << "Bucket " << i << ": ";
            Node* node = table[i];
            while (node) {
                o << node->key << " -> ";
                node = node->next;
            }
            o << "nullptr\n";
        }
    }
};

// Non-member functions
template <typename Key, size_t N, size_t BucketSize>
bool operator==(const ADS_set<Key, N, BucketSize> &lhs, const ADS_set<Key, N, BucketSize> &rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (auto it = lhs.begin(); it != lhs.end(); ++it) {
        if (rhs.count(*it) == 0) return false;
    }
    return true;
}

template <typename Key, size_t N, size_t BucketSize>
bool operator!=(const ADS_set<Key, N, BucketSize> &lhs, const ADS_set<Key, N, BucketSize> &rhs) {
    return !(lhs == rhs);
}

template <typename Key, size_t N, size_t BucketSize>
void swap(ADS_set<Key, N, BucketSize> &lhs, ADS_set<Key, N, BucketSize> &rhs) {
    lhs.swap(rhs);
}

#endif // ADS_SET_H