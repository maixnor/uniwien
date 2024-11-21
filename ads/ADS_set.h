// ADS_set.h

#ifndef ADS_SET_H
#define ADS_SET_H

<<<<<<< Updated upstream
template <typename Key, size_t N = 16, size_t BucketSize = 4>
=======
#include <cstddef> // for size_t
#include <functional> // for std::hash, std::equal_to
#include <utility> // for std::pair
#include <initializer_list>

// Linear Hashing implementation as an ADS_set container.
// This is designed based on the given requirements.

template <typename Key, size_t N = 8>
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
    using key_compare = std::less<key_type>;   // B+-Tree
    using key_equal = std::equal_to<key_type>; // Hashing
    using hasher = std::hash<key_type>;        // Hashing

private:
    struct Bucket {
        key_type* data;
        size_type size;
        size_type capacity;
        Bucket* overflow;

        Bucket(size_type capacity = BucketSize)
            : data(new key_type[capacity]), size(0), capacity(capacity), overflow(nullptr) {}

        ~Bucket() {
            delete[] data;
            delete overflow;
=======
    using const_iterator = const Node*;
    using iterator = const_iterator;
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
>>>>>>> Stashed changes
        }
        return *this;
    }

<<<<<<< Updated upstream
        void add(const key_type& key) {
            if (size < capacity) {
                data[size++] = key;
            } else {
                if (!overflow) overflow = new Bucket(capacity * 2); // Optional: increase capacity
                overflow->add(key);
            }
=======
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
>>>>>>> Stashed changes
        }
    }

<<<<<<< Updated upstream
        bool remove(const key_type& key) {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) {
                    data[i] = data[--size];
                    if (size == 0 && overflow) {
                        // Move data from overflow bucket
                        Bucket* old_overflow = overflow;
                        for (size_type j = 0; j < overflow->size; ++j) {
                            data[j] = overflow->data[j];
                        }
                        size = overflow->size;
                        overflow = overflow->overflow;
                        old_overflow->overflow = nullptr;
                        delete old_overflow;
                    }
                    return true;
                }
=======
    std::pair<iterator, bool> insert(const key_type &key) {
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

    iterator find(const key_type &key) const {
        size_t index = hash(key, (1 << level) + split_pointer);
        Node* node = table[index];
        while (node) {
            if (key_equal{}(node->key, key)) {
                return node;
            }
            node = node->next;
        }
        return end();
    }

    iterator begin() const {
        for (size_t i = 0; i < bucket_count; ++i) {
            if (table[i]) {
                return table[i];
>>>>>>> Stashed changes
            }
            if (overflow) return overflow->remove(key);
            return false;
        }
        return end();
    }

<<<<<<< Updated upstream
        bool contains(const key_type& key) const {
            for (size_type i = 0; i < size; ++i) {
                if (key_equal{}(data[i], key)) return true;
            }
            if (overflow) return overflow->contains(key);
            return false;
        }
    };

    Bucket** buckets;
    size_type table_size;
    size_type num_elements;

    void rehash() {
        size_type new_table_size = table_size * 2 + 1;
        Bucket** new_buckets = new Bucket*[new_table_size]();
        for (size_type i = 0; i < table_size; ++i) {
            Bucket* bucket = buckets[i];
            while (bucket) {
                for (size_type j = 0; j < bucket->size; ++j) {
                    const key_type& key = bucket->data[j];
                    size_type new_index = hasher{}(key) % new_table_size;
                    if (!new_buckets[new_index]) {
                        new_buckets[new_index] = new Bucket();
                    }
                    new_buckets[new_index]->add(key);
                }
                Bucket* old_bucket = bucket;
                bucket = bucket->overflow;
                old_bucket->overflow = nullptr;
                delete old_bucket;
            }
        }
        delete[] buckets;
        buckets = new_buckets;
        table_size = new_table_size;
    }

public:
    ADS_set() : table_size(N), num_elements(0) {
        buckets = new Bucket*[table_size]();
    }

    template <typename InputIt>
    ADS_set(InputIt first, InputIt last) : ADS_set() {
        insert(first, last);
    }

    ADS_set(std::initializer_list<key_type> ilist) : ADS_set() {
        insert(ilist);
    }

    ~ADS_set() {
        clear();
        delete[] buckets;
    }

    void insert(const key_type& key) {
        size_type index = hasher{}(key) % table_size;
        if (!buckets[index]) {
            buckets[index] = new Bucket();
        }
        if (!buckets[index]->contains(key)) {
            buckets[index]->add(key);
            ++num_elements;
            if (num_elements > table_size * BucketSize) {
                rehash();
            }
        }
    }

    template <typename InputIt>
    void insert(InputIt first, InputIt last) {
        for (; first != last; ++first) {
            insert(*first);
        }
    }

    void insert(std::initializer_list<key_type> ilist) {
        insert(ilist.begin(), ilist.end());
    }

    const key_type* find(const key_type& key) const {
        size_type index = hasher{}(key) % table_size;
        if (buckets[index]) {
            const Bucket* bucket = buckets[index];
            while (bucket) {
                for (size_type i = 0; i < bucket->size; ++i) {
                    if (key_equal{}(bucket->data[i], key)) {
                        return &bucket->data[i];
                    }
                }
                bucket = bucket->overflow;
            }
        }
        return nullptr;
    }

    size_type count(const key_type& key) const {
        return find(key) ? 1 : 0;
    }

    size_type erase(const key_type& key) {
        size_type index = hasher{}(key) % table_size;
        if (buckets[index] && buckets[index]->remove(key)) {
            --num_elements;
            return 1;
        }
        return 0;
    }

    void clear() {
        for (size_type i = 0; i < table_size; ++i) {
            delete buckets[i];
            buckets[i] = nullptr;
        }
        num_elements = 0;
    }

    void swap(ADS_set& other) {
        std::swap(table_size, other.table_size);
        std::swap(num_elements, other.num_elements);
        std::swap(buckets, other.buckets);
    }

    bool empty() const {
        return num_elements == 0;
    }

    size_type size() const {
        return num_elements;
    }

    class const_iterator {
    public:
        using value_type = key_type;
        using reference = const value_type&;
        using pointer = const key_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

    private:
        const ADS_set* set;
        size_type bucket_index;
        const Bucket* bucket;
        size_type data_index;

        void advance() {
            while (bucket_index < set->table_size) {
                if (bucket) {
                    if (data_index + 1 < bucket->size) {
                        ++data_index;
                        return;
                    } else if (bucket->overflow) {
                        bucket = bucket->overflow;
                        data_index = 0;
                        return;
                    }
                }
                ++bucket_index;
                if (bucket_index < set->table_size) {
                    bucket = set->buckets[bucket_index];
                    data_index = 0;
                    if (bucket && bucket->size > 0) {
                        return;
                    }
                } else {
                    bucket = nullptr;
                    bucket_index = set->table_size; // Set to end state
                }
            }
        }

    public:
        const_iterator(const ADS_set* set = nullptr, size_type bucket_index = 0, const Bucket* bucket = nullptr, size_type data_index = 0)
            : set(set), bucket_index(bucket_index), bucket(bucket), data_index(data_index) {}

        reference operator*() const { return bucket->data[data_index]; }
        pointer operator->() const { return &bucket->data[data_index]; }

        const_iterator& operator++() {
            advance();
            return *this;
        }

        const_iterator operator++(int) {
            auto tmp = *this;
            advance();
            return tmp;
        }

        bool operator==(const const_iterator& other) const {
            return set == other.set && bucket_index == other.bucket_index && bucket == other.bucket && data_index == other.data_index;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    using iterator = const_iterator;

    const_iterator begin() const {
        for (size_type i = 0; i < table_size; ++i) {
            if (buckets[i] && buckets[i]->size > 0) {
                return const_iterator(this, i, buckets[i], 0);
            }
        }
        return end();
    }

    const_iterator end() const {
        return const_iterator(this, table_size, nullptr, 0);
    }

    void dump(std::ostream& o = std::cerr) const {
        for (size_type i = 0; i < table_size; ++i) {
            o << "Bucket " << i << ": ";
            const Bucket* bucket = buckets[i];
            while (bucket) {
                for (size_type j = 0; j < bucket->size; ++j) {
                    o << bucket->data[j] << " ";
                }
                if (bucket->overflow) o << "-> ";
                bucket = bucket->overflow;
            }
            o << "\n";
        }
    }
};

#endif // ADS_SET_H
=======
    iterator end() const {
        return nullptr;
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
template <typename Key, size_t N>
bool operator==(const ADS_set<Key,N> &lhs, const ADS_set<Key,N> &rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (auto it = lhs.begin(); it != lhs.end(); ++it) {
        if (rhs.count(it->key) == 0) return false;
    }
    return true;
}

template <typename Key, size_t N>
bool operator!=(const ADS_set<Key,N> &lhs, const ADS_set<Key,N> &rhs) {
    return !(lhs == rhs);
}

template <typename Key, size_t N>
void swap(ADS_set<Key,N> &lhs, ADS_set<Key,N> &rhs) {
    lhs.swap(rhs);
}

#endif // ADS_SET_H

>>>>>>> Stashed changes
