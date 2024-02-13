#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H

#include "../containers.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  stack() : data_(nullptr), size_(0) {}

  stack(std::initializer_list<value_type> const &items) : stack() {  //  - NT
    size_ = items.size();
    data_ = new value_type[size_];
    std::copy(items.begin(), items.end(), data_);
  }

  // copy constructor - NT
  stack(const stack &s) : stack() {
    size_ = s.size_;
    data_ = new value_type[size_];
    for (size_type i = 0; i < size_; i++) {
      data_[i] = s.data_[i];
    }
  }
  // move constructor - NT
  stack(stack &&s) : stack() { *this = std::move(s); }

  // destructor
  ~stack() {
    delete[] data_;
    size_ = 0;
    data_ = nullptr;
  }
  //
  // overload for moving - NT
  stack &operator=(stack &&s) {
    if (this != &s) {
      delete[] data_;
      size_ = s.size_;
      data_ = s.data_;
      s.size_ = 0;
      s.data_ = nullptr;
    }
    return *this;
  }
  /////////////////////////////////////////////////////

  const_reference top() noexcept {
    // мб надо вкинуть исключение
    return data_[size_ - 1];
  }
  bool empty() noexcept {
    bool empty = true;
    if (size_ > 0) {
      empty = false;
    }
    return empty;
  }

  size_type size() noexcept { return size_; }

  void push(const_reference value) {
    value_type *tempStack = data_;
    data_ = new value_type[size_ + 1];
    std::copy(tempStack, tempStack + size_, data_);
    delete[] tempStack;
    data_[size_] = value;
    size_++;
  }

  void pop() {
    if (size_ != 0) {
      size_--;
    }
  }

  void swap(stack &other) {
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
  }

 private:
  T *data_;
  size_type size_;
};
}  // namespace s21
#endif
