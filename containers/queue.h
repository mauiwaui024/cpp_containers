#ifndef CONTAINERS_QUEUE_H
#define CONTAINERS_QUEUE_H

#include "../containers.h"
#include "stack.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // default
  queue() : data_(nullptr), size_(0) {}
  queue(std::initializer_list<value_type> const &items) : queue() {
    size_ = items.size();
    data_ = new value_type[size_];
    std::copy(items.begin(), items.end(), data_);
  }

  // copy
  queue(const queue &q) : queue() {
    size_ = q.size_;
    data_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      data_[i] = q.data_[i];
    }
  }
  // move
  queue(queue &&q) : queue() { *this = std::move(q); }
  ~queue() {
    delete[] data_;
    size_ = 0;
    data_ = nullptr;
  }

  queue &operator=(queue &&q) {
    if (this != q) {
      delete[] data_;
      size_ = q.size_;
      data_ = q.data_;
      q.size_ = 0;
      q.data_ = nullptr;
    }
  }
  const_reference front() const {
    if (!size_) {
      throw std::out_of_range("Queue is empty");
    }
    return data_[0];
  }
  const_reference back() const {
    if (!size_) {
      throw std::out_of_range("Queue is empty");
    }
    return data_[size_ - 1];

    // return data_.back();
  }
  bool empty() const noexcept { return size_ == 0; }
  size_type size() noexcept { return size_; }
  void print() const {
    if (empty()) {
      std::cout << "Queue is empty." << std::endl;
      return;
    }

    for (size_type i = 0; i < size_; ++i) {
      std::cout << data_[i] << " ";
    }

    std::cout << std::endl;
  }

  void push(const_reference value) {
    value_type *tempQueue = data_;
    data_ = new value_type[size_ + 1];
    std::copy(tempQueue, tempQueue + size_, data_);
    delete[] tempQueue;
    data_[size_] = value;
    size_++;
  }

  void pop() {
    if (size_ > 0) {
      for (size_type i = 0; i < size_ - 1; i++) {
        data_[i] = std::move(data_[i + 1]);
      }
      size_--;
    }
  }

  void swap(queue &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }

 private:
  T *data_;
  size_type size_;
};
}  // namespace s21
#endif