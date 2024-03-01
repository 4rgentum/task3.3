#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H

#include <iostream>
#include <functional>
#include <concepts>
#include <limits>

/**
 * @brief A structure representing an entry in the hash table.
 *
 * @tparam T The type of value stored in the hash table.
 */
template<std::default_initializable T>
struct HashEntry{
    T value = T{}; /**< The value stored in the entry. */
    int busy = 0; /**< Indicates if the entry is occupied. */
    ~HashEntry() = default; /**< Destructor */
};

/**
 * @brief An iterator class for the Unordered_map class.
 *
 * @tparam T The type of value stored in the iterator.
 * @tparam IsConst Boolean indicating if the iterator is const or not.
 */
template<std::default_initializable T, bool IsConst>
class MapIterator{
private:
    using EntryPointer = std::conditional_t<IsConst, const HashEntry<T>*, HashEntry<T>*>; /**< Pointer to a hash table entry. */
    using EntryReference = std::conditional_t<IsConst, const HashEntry<T>&, HashEntry<T>&>; /**< Reference to a hash table entry. */

    friend MapIterator<T, !IsConst>;

    EntryPointer ptr; /**< Pointer to the current hash table entry. */
    std::size_t index; /**< Index of the current hash table entry. */
    std::size_t capacity; /**< Capacity of the hash table. */


public:
    using iterator_category = std::forward_iterator_tag; /**< Iterator category. */
    using value_type = T; /**< Value type of the iterator. */
    using difference_type = std::ptrdiff_t; /**< Difference type for the iterator. */
    using pointer = std::conditional_t<IsConst, const value_type*, value_type*>; /**< Pointer type of the iterator. */
    using reference = std::conditional_t<IsConst, const value_type&, value_type&>; /**< Reference type of the iterator. */

    /**
     * @brief Default constructor.
     */
    MapIterator() : ptr(nullptr), index(0), capacity(0) {}

    /**
     * @brief Constructor with parameters.
     *
     * @param ptr Pointer to the hash table entry.
     * @param index Index of the hash table entry.
     * @param capacity Capacity of the hash table.
     */
    MapIterator(EntryPointer ptr, std::size_t index, std::size_t capacity) : ptr(ptr), index(index), capacity(capacity) {}

    /**
     * @brief Move constructor.
     *
     * Constructs the iterator from rvalue reference to another iterator.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Rvalue reference to another iterator.
     */
    template<bool OtherConst>
    requires(IsConst >= OtherConst)
    explicit MapIterator(MapIterator<T, OtherConst>&& other) noexcept : ptr(other.ptr), index(other.index), capacity(other.capacity) {
        other.ptr = nullptr;
        other.index = 0;
        other.capacity = 0;
    }

    /**
     * @brief Copy constructor.
     *
     * Constructs the iterator from const reference to another iterator.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Const reference to another iterator.
     */
    template<bool OtherConst>
    requires(IsConst >= OtherConst)
    explicit MapIterator(const MapIterator<T, OtherConst>& other) : ptr(other.ptr), index(other.index), capacity(other.capacity) {}

    /**
     * @brief Destructor.
     *
     * Destroys the iterator object.
     */
    ~MapIterator() = default;

    /**
     * @brief Move assignment operator.
     *
     * Assigns the iterator from rvalue reference to another iterator.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Rvalue reference to another iterator.
     * @return Reference to the current iterator.
     */
    template<bool OtherConst>
    requires(IsConst >= OtherConst)
    MapIterator& operator=(MapIterator<T, OtherConst>&& other) noexcept {
        if (this != &other) {
            ptr = other.ptr;
            index = other.index;
            capacity = other.capacity;
            other.ptr = nullptr;
            other.index = 0;
            other.capacity = 0;
        }
        return *this;
    }

    /**
     * @brief Copy assignment operator.
     *
     * Assigns the iterator from const reference to another iterator.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Const reference to another iterator.
     * @return Reference to the current iterator.
     */
    template<bool OtherConst>
    requires(IsConst >= OtherConst)
    MapIterator& operator=(const MapIterator<T, OtherConst>& other) {
        if (this != &other) {
            ptr = other.ptr;
            index = other.index;
            capacity = other.capacity;
        }
        return *this;
    }

    /**
     * @brief Dereference operator.
     *
     * @return Reference to the value stored in the current hash table entry.
     */
    reference operator*() const {
        return ptr[index].value;
    }

    /**
     * @brief Arrow operator.
     *
     * @return Pointer to the value stored in the current hash table entry.
     */
    pointer operator->() const {
        return &ptr[index].value;
    }

    /**
     * @brief Prefix increment operator.
     *
     * Increments the iterator to point to the next valid entry in the hash table.
     *
     * @return Reference to the incremented iterator.
     */
    MapIterator& operator++() {
        do {
            ++index;
        } while (index < capacity && ptr[index].busy != 1);
        return *this;
    }

    /**
     * @brief Postfix increment operator.
     *
     * Increments the iterator to point to the next valid entry in the hash table.
     *
     * @return Copy of the iterator before incrementing.
     */
    MapIterator operator++(int) {
        MapIterator temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Equality operator.
     *
     * Checks if two iterators are equal.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Iterator to compare with.
     * @return True if the iterators are equal, false otherwise.
     */
    template<bool OtherConst>
    bool operator==(const MapIterator<T, OtherConst>& other) const noexcept
    {
        return index == other.index;
    }

    /**
     * @brief Inequality operator.
     *
     * Checks if two iterators are not equal.
     *
     * @tparam OtherConst Boolean indicating if the other iterator is const or not.
     * @param other Iterator to compare with.
     * @return True if the iterators are not equal, false otherwise.
     */
    template<bool OtherConst>
    bool operator!=(const MapIterator<T, OtherConst>& other) const noexcept
    {
        return index != other.index;
    }
};

/**
 * @brief An unordered map implementation.
 *
 * @tparam Key Type of the keys stored in the map.
 * @tparam T Type of the values stored in the map.
 * @tparam Hash Hash function for computing hash values of keys.
 * @tparam KeyEqual Function object for comparing keys for equality.
 */
template<std::default_initializable Key, std::default_initializable T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
class Unordered_map{
public:
    typedef Key key_type; /**< Type of the keys stored in the map. */
    typedef T mapped_type; /**< Type of the values stored in the map. */
    typedef std::pair<Key, T> value_type; /**< Type representing key-value pairs stored in the map. */
    typedef Hash hasher; /**< Type of the hash function. */
    typedef KeyEqual key_equal; /**< Type of the function object for comparing keys for equality. */
    typedef std::pair<Key, T> reference; /**< Reference type for the key-value pairs stored in the map. */
    typedef const std::pair<Key, T> const_reference; /**< Const reference type for the key-value pairs stored in the map. */
    typedef MapIterator<value_type, false> iterator; /**< Iterator type for non-const access to elements. */
    typedef MapIterator<value_type, true> const_iterator; /**< Iterator type for const access to elements. */
    typedef value_type* pointer; /**< Pointer type for the key-value pairs stored in the map. */
    typedef const value_type* const_pointer; /**< Const pointer type for the key-value pairs stored in the map. */
    typedef ptrdiff_t difference_type; /**< Type representing the difference between two iterators. */
    typedef std::size_t size_type; /**< Type representing sizes and indices. */
    typedef HashEntry<value_type> entry_type; /**< Type of the hash table entry. */

    /**
     * @brief Default constructor.
     *
     * Constructs an empty unordered map.
     */
    Unordered_map() = default;

    /**
     * @brief Copy constructor.
     *
     * Constructs the unordered map with a copy of the contents of another unordered map.
     *
     * @param other Another unordered map to be copied.
     */
    Unordered_map(const Unordered_map& other) : size_(other.size_), capacity_(other.capacity_), step(other.step), max_load(other.max_load), array(new entry_type[other.capacity_]) {
        std::copy(other.array, other.array + other.capacity_, array);
    }

    /**
     * @brief Move constructor.
     *
     * Constructs the unordered map with the contents of another unordered map using move semantics.
     *
     * @param other Another unordered map to be moved.
     */
    Unordered_map(Unordered_map&& other) noexcept : size_(other.size_), capacity_(other.capacity_), step(other.step), max_load(other.max_load), array(other.array) {
        other.size_ = 0;
        other.capacity_ = 0;
        other.step = 1;
        other.max_load = 0.8f;
        other.array = nullptr;
    }

    /**
     * @brief Destructor.
     *
     * Destroys the unordered map object.
     */
    ~Unordered_map() {
        delete[] array;
    }

    /**
     * @brief Copy assignment operator.
     *
     * Replaces the contents with a copy of the contents of another unordered map.
     *
     * @param other Another unordered map to use as a source.
     * @return Reference to the current unordered map.
     */
    Unordered_map& operator=(const Unordered_map& other) {
        if (this != &other) {
            delete[] array;
            size_ = other.size_;
            capacity_ = other.capacity_;
            step = other.step;
            max_load = other.max_load;
            array = new entry_type[other.capacity_];
            std::copy(other.array, other.array + other.capacity_, array);
        }
        return *this;
    }

    /**
     * @brief Move assignment operator.
     *
     * Replaces the contents with those of another unordered map using move semantics.
     *
     * @param other Another unordered map to be moved.
     * @return Reference to the current unordered map.
     */
    Unordered_map& operator=(Unordered_map&& other) noexcept {
        if (this != &other) {
            delete[] array;
            size_ = other.size_;
            capacity_ = other.capacity_;
            step = other.step;
            max_load = other.max_load;
            array = other.array;
            other.size_ = 0;
            other.capacity_ = 0;
            other.step = 1;
            other.max_load = 0.8f;
            other.array = nullptr;
        }
        return *this;
    }

    /**
     * @brief Returns an iterator to the beginning of the unordered map.
     *
     * @return Iterator to the beginning.
     */
    iterator begin() {
        size_t index = 0;
        while (index < capacity_ && array[index].busy != 1) {
            ++index;
        }
        return iterator(array, index, capacity_);
    }

/**
 * @brief Returns a const iterator to the beginning of the unordered map.
 *
 * @return Const iterator to the beginning.
 */
    const_iterator begin() const {
        size_t index = 0;
        while (index < capacity_ && array[index].busy != 1) {
            ++index;
        }
        return const_iterator(array, index, capacity_);
    }

    /**
     * @brief Returns an iterator to the end of the unordered map.
     *
     * @return Iterator to the end.
     */
    iterator end() {
        return iterator(array, capacity_, capacity_);
    }

    /**
     * @brief Returns a const iterator to the end of the unordered map.
     *
     * @return Const iterator to the end.
     */
    const_iterator end() const {
        return const_iterator(array, capacity_, capacity_);
    }

    /**
     * @brief Returns the number of elements in the unordered map.
     *
     * @return Number of elements in the unordered map.
     */
    size_type size() const {
        return size_;
    }

    /**
     * @brief Returns the number of elements that the unordered map can hold.
     *
     * @return Capacity of the unordered map.
     */
    size_type capacity() const {
        return capacity_;
    }

    /**
     * @brief Returns the maximum number of elements the unordered map can hold.
     *
     * @return Maximum size of the unordered map.
     */
    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    /**
     * @brief Checks if the unordered map is empty.
     *
     * @return True if the unordered map is empty, false otherwise.
     */
    bool empty() const {
        return size_ == 0;
    }

    /**
     * @brief Calculates the load factor of the unordered map.
     *
     * @return Load factor of the unordered map.
     */
    float load() const {
        if (capacity_ == 0) {
            return 0.0f;
        }
        return static_cast<float>(size_) / capacity_;
    }

    /**
     * @brief Returns the maximum load factor of the unordered map.
     *
     * @return Maximum load factor of the unordered map.
     */
    float get_max_load() const {
        return max_load;
    }

    /**
     * @brief Clears the contents of the unordered map.
     */
    void clear() {
        delete[] array;
        size_ = 0;
        capacity_ = 0;
        step = 1;
        max_load = 0.8f;
        array = nullptr;
    }

    /**
     * @brief Finds an element with a specific key in the unordered map.
     *
     * @param key The key of the element to search for.
     * @return Iterator to the element with the specified key if found, end() otherwise.
     */
    iterator find(const Key& key) {
        size_t hashValue = hasher{}(key);
        size_t index = hashValue % capacity_;
        size_t start = index;

        while (true) {
            if (array[index].busy == 0) {
                return end();
            } else if (array[index].value.first == key && array[index].busy != -1) {
                return iterator(array, index, capacity_);
            }

            index = (index + 1) % capacity_;
            if (index == start) {
                return end();
            }
        }
    }

    /**
     * @brief Finds an element with a specific key in the unordered map (const version).
     *
     * @param key The key of the element to search for.
     * @return Const iterator to the element with the specified key if found, end() otherwise.
     */
    const_iterator find(const Key& key) const {
        size_t hashValue = hasher{}(key);
        size_t index = hashValue % capacity_;
        size_t start = index;

        while (true) {
            if (array[index].busy == 0) {
                return end();
            } else if (array[index].value.first == key && array[index].busy != -1) {
                return const_iterator(array, index, capacity_);
            }

            index = (index + 1) % capacity_;
            if (index == start) {
                return end();
            }
        }
    }

    /**
     * @brief Inserts an element or updates the element if the key already exists.
     *
     * @param value The key-value pair to insert or update.
     * @return Pair with an iterator to the inserted or updated element and a bool indicating whether the insertion took place.
     */
    std::pair<iterator, bool> insert(const value_type& value) {
        if (size_ + 1 > max_load * capacity_) rehash();
        size_t hashValue = hasher{}(value.first);
        size_t index = hashValue % capacity_;
        size_t start = index;

        while (true) {
            if (array[index].busy == 0) {
                array[index].value = value;
                array[index].busy = 1;
                size_++;
                return {iterator(array, index, capacity_), true};
            } else if (array[index].value.first == value.first) {
                return {iterator(array, index, capacity_), false};
            }

            index = (index + 1) % capacity_;
            if (index == start) {
                rehash();
                return insert(value);
            }
        }
    }

    /**
     * @brief Inserts an element or updates the element if the key already exists (move version).
     *
     * @param value The key-value pair to insert or update.
     * @return Pair with an iterator to the inserted or updated element and a bool indicating whether the insertion took place.
     */
    std::pair<iterator, bool> insert(value_type&& value) {
        if (size_ + 1 > max_load * capacity_) rehash();
        size_t hashValue = hasher{}(value.first);
        size_t index = hashValue % capacity_;
        size_t start = index;

        while (true) {
            if (array[index].busy == 0) {
                array[index].value = std::move(value);
                array[index].busy = 1;
                size_++;
                return {iterator(array, index, capacity_), true};
            } else if (array[index].value.first == value.first) {
                return {iterator(array, index, capacity_), false};
            }

            index = (index + 1) % capacity_;
            if (index == start) {
                rehash();
                return insert(std::move(value));
            }
        }
    }

    /**
     * @brief Inserts a new element into the unordered map using a key and arguments for the value constructor.
     *
     * @tparam Args Types of the arguments for the value constructor.
     * @param key The key of the new element.
     * @param args Arguments for the value constructor.
     * @return Pair with an iterator to the inserted element and a bool indicating whether the insertion took place.
     */
    template<typename... Args>
    std::pair<iterator, bool> emplace(const key_type& key, Args&&... args) {
        iterator it = find(key);
        if (it != end()) {
            return {it, false};
        } else {
            if (size_ + 1 > max_load * capacity_) {
                rehash();
            }
            size_type index = hasher{}(key) % capacity_;
            while (array[index].busy != 0) {
                index = (index + step) % capacity_;
            }
            array[index].value = {key, mapped_type(std::forward<Args>(args)...)};
            array[index].busy = 1;
            ++size_;
            if(load() >= max_load) rehash();
            return {iterator(array, index, capacity_), true};
        }
    }

    /**
     * @brief Accesses the mapped value associated with the given key.
     *
     * @param key The key of the element to access.
     * @return Reference to the mapped value of the element with the specified key.
     * @throw std::out_of_range if the key is not found.
     */
    mapped_type& at(const key_type& key) {
        iterator it = find(key);
        if (it != end()) {
            return it->second;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    /**
     * @brief Accesses the mapped value associated with the given key (const version).
     *
     * @param key The key of the element to access.
     * @return Const reference to the mapped value of the element with the specified key.
     * @throw std::out_of_range if the key is not found.
     */
    const mapped_type& at(const key_type& key) const {
        const_iterator it = find(key);
        if (it != end()) {
            return it->second;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    /**
     * @brief Accesses or inserts an element with the given key.
     *
     * @param key The key of the element to access or insert.
     * @return Reference to the mapped value of the accessed or inserted element.
     * @throw std::out_of_range if the key is not found.
     */
    mapped_type& operator[](const key_type& key) {
        iterator it = find(key);
        if (it != end()) {
            return it->second;
        } else {
            emplace(key, mapped_type{});
            return find(key)->second;
        }
    }

    /**
     * @brief Accesses or inserts an element with the given key (const version).
     *
     * @param key The key of the element to access or insert.
     * @return Const reference to the mapped value of the accessed or inserted element.
     * @throw std::out_of_range if the key is not found.
     */
    const mapped_type& operator[](const key_type& key) const {
        const_iterator it = find(key);
        if (it != end()) {
            return it->second;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    /**
     * @brief Erases an element from the unordered map at a specified position.
     *
     * @param pos Iterator pointing to the element to erase.
     * @return Iterator following the removed element.
     */
    iterator erase(iterator pos) {
        size_type idx = find_index(pos->first);
        array[idx].busy = -1;
        --size_;
        return pos;
    }

    /**
     * @brief Erases an element from the unordered map at a specified position (const version).
     *
     * @param pos Const iterator pointing to the element to erase.
     * @return Const iterator following the removed element.
     */
    const_iterator erase(const_iterator pos) {
        size_type idx = find_index(pos->first);
        array[idx].busy = -1;
        --size_;
        return pos;
    }

    /**
     * @brief Erases an element from the unordered map with a specified key.
     *
     * @param key The key of the element to erase.
     * @return Number of elements erased (0 or 1).
     */
    size_type erase(const key_type& key) {
        size_type idx = find_index(key);
        if (idx != capacity_) {
            array[idx].busy = -1;
            --size_;
            return 1;
        }
        return 0;
    }

    /**
     * @brief Reserves space for a specified number of elements.
     *
     * @param new_capacity The new capacity of the unordered map.
     */
    void reserve(size_type new_capacity) {
        if (new_capacity <= capacity_)
            return;

        auto* new_array = new entry_type[new_capacity];
        for (size_type i = 0; i < capacity_; ++i) {
            if (array[i].busy == 1) {
                size_type new_index = hasher{}(array[i].value.first) % new_capacity;
                while (new_array[new_index].busy != 0) {
                    new_index = (new_index + step) % new_capacity;
                }
                new_array[new_index].value = std::move(array[i].value);
                new_array[new_index].busy = 1;
            }
        }
        delete[] array;
        array = new_array;
        capacity_ = new_capacity;
    }

    /**
     * @brief Counts the number of elements with a specific key.
     *
     * @param key The key of the elements to count.
     * @return Number of elements with the specified key (0 or 1).
     */
    size_type count(const key_type& key) const {
        size_type count = 0;
        size_type idx = find_index(key);
        if (idx != capacity_) {
            count = 1;
        }
        return count;
    }

    /**
     * @brief Swaps the contents of two unordered maps.
     *
     * @param other Another unordered map to swap with.
     */
    void swap(Unordered_map& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(step, other.step);
        std::swap(max_load, other.max_load);
        std::swap(array, other.array);
    }

    /**
     * @brief Checks if the unordered map contains an element with the given key.
     *
     * @param key The key to search for.
     * @return True if the unordered map contains an element with the key, false otherwise.
     */
    bool contains(const key_type& key) const {
        return find_index(key) != capacity_;
    }

    /**
     * @brief Merges the contents of another unordered map into this one.
     *
     * @param other Another unordered map to merge with.
     */
    void merge(Unordered_map& other) {
        for (auto& entry : other) {
            insert(std::move(entry));
        }
        other.clear();
    }

private:

    std::size_t size_ = 0; /**< Number of elements in the unordered map. */
    std::size_t capacity_ = 0; /**< Capacity of the hash table. */
    std::size_t step = 1; /**< Step size for resolving collisions. */
    float max_load = 0.8f; /**< Maximum load factor before rehashing. */
    entry_type* array = nullptr; /**< Array of hash table entries. */

    /**
    * @brief Reallocates memory for the hash table with a new capacity.
    *
    * @param new_capacity The new capacity of the hash table.
    */
    void reallocate(std::size_t new_capacity) {
        auto* new_array = new entry_type[new_capacity];
        for (std::size_t i = 0; i < capacity_; ++i) {
            if (array[i].busy == 1) {
                std::size_t new_index = hasher{}(array[i].value.first) % new_capacity;
                while (new_array[new_index].busy == 1) {
                    new_index = (new_index + step) % new_capacity;
                }
                new_array[new_index].value = std::move(array[i].value);
                new_array[new_index].busy = 1;
            }
        }
        if(capacity_ != 0) delete[] array;
        array = new_array;
        capacity_ = new_capacity;
    }

    /**
     * @brief Rehashes the contents of the unordered map.
     */
    void rehash() {
        reallocate((capacity_ == 0 ? 1 : capacity_ * 2));
    }

    /**
     * @brief Finds the index of an element with a specified key in the hash table.
     *
     * @param key The key of the element to find.
     * @return Index of the element in the hash table, or capacity_ if not found.
     */
    size_type find_index(const key_type& key) const {
        size_type idx = hasher()(key) % capacity_;
        size_type initial_idx = idx;

        while (array[idx].busy == 1) {
            if (key_equal()(array[idx].value.first, key)) {
                return idx;
            }
            idx = (idx + step) % capacity_;
            if (idx == initial_idx) {
                break;  // Если мы вернулись в начальную позицию, значит элемент не найден
            }
        }

        return capacity_;  // Возвращаем capacity_, если элемент не найден
    }
};

#endif //UNORDERED_MAP_H
