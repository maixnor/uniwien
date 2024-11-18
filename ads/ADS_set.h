// ADS_set.h

#ifndef ADS_SET_H
#define ADS_SET_H

template <typename Key, size_t N = 16, size_t BucketSize = 4>
class ADS_set {
public:
    using value_type = Key;
    using key_type = Key;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
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
        }

        void add(const key_type& key) {
            if (size < capacity) {
                data[size++] = key;
            } else {
                if (!overflow) overflow = new Bucket(capacity * 2); // Optional: increase capacity
                overflow->add(key);
            }
        }

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
            }
            if (overflow) return overflow->remove(key);
            return false;
        }

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