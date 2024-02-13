#ifndef array_H
#define array_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // конструкторы и деструктор
  // поля инициализируются по умолчанию поэтому default
  array() noexcept = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() != N) {
      throw std::runtime_error("unvaliable amount of elements");
    }
    std::copy(items.begin(), items.end(), data_);
  }

  // copy constructor
  array(const array &a) noexcept { std::copy(a.data_, a.data_ + N, data_); }

  // move constructor
  array(array &&a) noexcept { std::move(a.data_, a.data_ + N, data_); }

  ~array() noexcept {};

  // Операторы присваивания для lvalue и rvalue
  array &operator=(const array &a) noexcept {
    if (this != &a) {
      for (size_type i = 0; i < N; i++) {
        data_[i] = a.data_[i];
      }
    }
    return *this;
  }

  array &operator=(array &&a) noexcept {
    if (this != &a) {
      for (size_type i = 0; i < N; i++) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    return *this;
  }

  // Методы доступа к элементам
  reference at(size_type pos) {
    if (pos >= N) {
      throw std::out_of_range("array::at out of range");
    }
    return data_[pos];
  }

  reference operator[](size_type pos) { return at(pos); }

  const_reference front() const noexcept { return data_[0]; }

  const_reference back() const noexcept { return data_[N - 1]; }
  iterator data() noexcept { return data_; }

  // Методы для итерации по массиву
  iterator begin() noexcept { return data_; }
  const_iterator cbegin() const noexcept { return data_; }
  iterator end() noexcept { return data_ + N; }
  const_iterator cend() const noexcept { return data_ + N; }

  // Методы для определения размеров и пустоты
  bool empty() const noexcept { return N == 0; }
  size_type size() const noexcept { return N; }
  size_type max_size() const noexcept { return size(); }

  // Метод для обмена содержимым с другим массивом
  void swap(array &other) noexcept {
    std::swap_ranges(data_, data_ + N, other.data_);
  }

  // Метод для заполнения массива значениями
  void fill(const_reference value) noexcept {
    for (size_t i = 0; i < N; i++) {
      data_[i] = value;
    }
  }

 private:
  value_type data_[N] = {};
};

}  // namespace s21

#endif  // array_H
