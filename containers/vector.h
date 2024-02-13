#ifndef CONTAINERS_VECTOR_H
#define CONTAINERS_VECTOR_H
#include <algorithm>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <typename T>
class vector {
 public:
  // For readability
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // constructor default
  vector() : data_(nullptr), size_(0), capacity_(0) {}

  // parametrized constructor
  explicit vector(size_type n) : vector() {
    size_ = n;
    capacity_ = n;
    if (size_ > 0) {
      data_ = new value_type[n];
    }
  }

  vector(std::initializer_list<value_type> const &items)
      : data_(nullptr), size_(0), capacity_(0) {
    size_ = items.size();
    capacity_ = items.size();
    data_ = new value_type[capacity_];
    std::copy(items.begin(), items.end(), data_);
  }

  // copy constructor
  vector(const vector &v) : vector() {
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; i++) {
      data_[i] = v.data_[i];
    }
  }

  // move constructor - NT
  vector(vector &&v) : vector() { *this = std::move(v); }

  // destructor
  ~vector() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
  }
  // overload for moving - NT
  vector &operator=(vector &&v) {
    if (this != &v) {
      delete[] data_;
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = v.data_;
      // Обнуляем ресурсы в v, чтобы они не удалились при уничтожении v
      v.size_ = 0;
      v.capacity_ = 0;
      v.data_ = nullptr;
    }
    return *this;
  }

  //////////////////
  reference at(size_type pos) {
    if (pos < size_) {
      return data_[pos];
    } else {
      throw std::out_of_range("Position out of range");
    }
  }

  reference operator[](size_type pos) {
    if (pos < size_) {
      return data_[pos];
    } else {
      throw std::out_of_range("Index out of bounds");
    }
  }
  const_reference operator[](size_type pos) const {
    if (pos < size_) {
      return data_[pos];
    } else {
      throw std::out_of_range("Index out of bounds");
    }
  }
  const_reference front() const {
    if (!size_) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[0];
  }
  const_reference back() const {
    if (!size_) {
      throw std::out_of_range("Vector is empty");
    }
    return data_[size_ - 1];
  }

  iterator data() noexcept { return data_; }

  // iterators
  iterator begin() {
    return data_;
    // return &data[0];
  }
  iterator end() {
    return data_ + size_;
    // return &data[size_];
  }

  void reserve(size_type new_capacity) {
    if (new_capacity > capacity_) {
      value_type *tempVectorP = data_;
      data_ = new value_type[new_capacity];
      std::copy(tempVectorP, tempVectorP + size_, data_);
      delete[] tempVectorP;
      capacity_ = new_capacity;
    }
  }

  /// capacity
  bool empty() {
    bool res = false;
    if (size_ == 0) {
      res = true;
    }
    return res;
  }

  size_type size() const { return size_; }
  size_type capacity() const { return capacity_; }

  size_type max_size() const {
    // C++ template class that provides information about the properties of
    // fundamental data types. In this case, it's used with std::size_t
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
  }
  void shrink_to_fit() {
    if (capacity_ > size_) {
      // если капасити больше размера - надо сделать таким же как размер
      iterator new_data = new value_type[size_];
      std::copy(this->begin(), this->end(), new_data);
      delete[] data_;
      data_ = new_data;
      capacity_ = size_;
      // delete[] new_data;
    }
  }

  /// ///// modifiers!/////
  void pop_back() {
    if (size_ > 0) {
      size_--;
    }
  }
  void push_back(const_reference value) {
    // если capacity == 0, то делаем резерв на 1, увеличиваем также size на 1;
    // если capacity == size_,то делаем резерв capacity*2 size++
    if (capacity_ == 0) {
      reserve(1);
      size_++;
      data_[0] = value;
    } else if (capacity_ == size_) {
      reserve(capacity_ * 2);
      data_[size_] = value;
      size_++;
    }
  }
  void swap(vector &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }

  iterator insert(iterator pos, const_reference value) {
    size_type offset = pos - begin();
    if (offset > size_) {
      throw std::out_of_range("You stepped out of range");
    }

    size_type newCapacity = size() + 1;
    if (newCapacity > capacity_) {
      reserve(capacity_ * 2);
    } else if (capacity_ == 0 || capacity_ == 1) {
      reserve(newCapacity);
    }

    iterator concretePos = begin() + offset;
    value_type *newData = new value_type[capacity_];
    std::copy(data_, data_ + offset, newData);

    newData[offset] = value;
    std::copy(data_ + offset, data_ + size(), newData + offset + 1);

    delete[] data_;
    data_ = newData;
    ++size_;
    capacity_ = size_;

    return concretePos;
  }
  void erase(iterator pos) {
    size_type diff = pos - begin();
    if (diff >= size_) {
      throw std::out_of_range("You stepped out of range");
    }
    for (iterator it = pos; it != end(); it++) {
      *it = *(it + 1);
    }
    size_--;
  }

 private:
  T *data_;
  size_type size_;
  size_type capacity_;
};
}  // namespace s21
#endif
