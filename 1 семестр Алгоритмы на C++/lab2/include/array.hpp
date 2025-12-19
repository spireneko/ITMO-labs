#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <utility>

template <typename T>
class Array final {
   private:
    T* buf_;
    int32_t length_;
    int32_t capacity_;

    void resize() {
        capacity_ = capacity_ * 2 + 1;
        T* p = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));

        for (int32_t i = 0; i < length_; i++) {
            new (p + i) T(std::move(buf_[i]));
            buf_[i].~T();
        }

        free(buf_);
        buf_ = p;
    }

    class Iterator {
       private:
        T* ptr_;
        int32_t index_;
        int32_t length_;
        bool is_forward_;

       public:
        Iterator(T* ptr, int32_t index, int32_t length, bool is_forward) {
            ptr_ = ptr;
            index_ = index;
            length_ = length;
            is_forward_ = is_forward;
        }

        const T& get() const {
            assert(index_ >= 0 && index_ < length_);
            return ptr_[index_];
        };

        void set(const T& value) {
            assert(index_ >= 0 && index_ < length_);
            ptr_[index_] = value;
        };

        void next() {
            int32_t direction = is_forward_ ? 1 : -1;
            index_ += 1 * direction;
        };

        bool hasNext() const {
            if (is_forward_) {
                return index_ < length_ - 1;
            } else {
                return index_ > 0;
            }
        };
    };

    class ConstIterator {
       private:
        const T* ptr_;
        int32_t index_;
        int32_t length_;
        bool is_forward_;

       public:
        ConstIterator(const T* ptr, int32_t index, int32_t length, bool is_forward) {
            ptr_ = ptr;
            index_ = index;
            length_ = length;
            is_forward_ = is_forward;
        }

        const T& get() const {
            assert(index_ >= 0 && index_ < length_);
            return ptr_[index_];
        };

        void next() {
            int32_t direction = is_forward_ ? 1 : -1;
            index_ += 1 * direction;
        };

        bool hasNext() const {
            if (is_forward_) {
                return index_ < length_ - 1;
            } else {
                return index_ > 0;
            }
        };
    };

   public:
    explicit Array() : Array(8) {}

    explicit Array(int32_t capacity) {
        assert(capacity >= 0);

        length_ = 0;
        capacity_ = capacity;

        if (capacity_ > 0) {
            buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));
        } else {
            buf_ = nullptr;
        }
    }

    Array(const Array& rhs) {
        length_ = rhs.length_;
        capacity_ = rhs.capacity_;
        buf_ = static_cast<T*>(std::malloc(capacity_ * sizeof(T)));

        for (int32_t i = 0; i < length_; i++) {
            new (buf_ + i) T(rhs.buf_[i]);
        }
    }

    ~Array() {
        if (buf_) {
            clear();
            free(buf_);
        }
    }

    Array& operator=(const Array& rhs) {
        if (this != &rhs) {
            Array tmp = Array(rhs);
            swap(tmp);
        }

        return *this;
    }

    Array(Array&& rhs) {
        buf_ = rhs.buf_;
        length_ = rhs.length_;
        capacity_ = rhs.capacity_;

        rhs.buf_ = nullptr;
        rhs.length_ = 0;
        rhs.capacity_ = 0;
    }

    Array& operator=(Array&& rhs) {
        if (this != &rhs) {
            swap(rhs);
        }

        return *this;
    }

    void swap(Array& other) {
        std::swap(buf_, other.buf_);
        std::swap(length_, other.length_);
        std::swap(capacity_, other.capacity_);
    }

    void clear() {
        for (int32_t i = 0; i < length_; i++) {
            buf_[i].~T();
        }
        length_ = 0;
    }

    int insert(const T& value) {
        if (length_ == capacity_) {
            resize();
        }

        new (buf_ + length_) T(value);
        length_ += 1;

        return length_ - 1;
    };

    int insert(int index, const T& value) {
        assert(index >= 0 && index <= length_);

        if (length_ == capacity_) {
            resize();
        }

        for (int32_t i = length_; i > index; i--) {
            new (buf_ + i) T(std::move(buf_[i - 1]));
            buf_[i - 1].~T();
        }

        new (buf_ + index) T(value);
        length_ += 1;

        return index;
    };

    void remove(int index) {
        assert(index >= 0 && index < length_);

        length_ -= 1;

        for (int i = index; i < length_; ++i) {
            buf_[i].~T();
            new (buf_ + i) T(std::move(buf_[i + 1]));
        }

        buf_[length_].~T();
    };

    const T& operator[](int index) const {
        assert(index >= 0 && index < length_);
        return buf_[index];
    };

    T& operator[](int index) {
        assert(index >= 0 && index < length_);
        return buf_[index];
    };

    int size() const { return length_; };

    int capacity() const { return capacity_; };

    Iterator iterator() { return Iterator(buf_, 0, length_, true); };

    Iterator reverseIterator() { return Iterator(buf_, length_ - 1, length_, false); };

    ConstIterator iterator() const { return ConstIterator(buf_, 0, length_, true); };

    ConstIterator reverseIterator() const { return ConstIterator(buf_, length_ - 1, length_, false); };
};
