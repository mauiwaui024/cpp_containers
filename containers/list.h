#ifndef CONTAINERS_LIST_H
#define CONTAINERS_LIST_H

#include "../containers.h"

namespace s21 {

template <typename T>
class list {
 private:
  struct Node;
  class ListIterator;
  class ListConstIterator;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = list<value_type>::ListIterator;
  using const_iterator = const list<value_type>::ListConstIterator;
  using size_type = std::size_t;

  // дефолтный конструктор
  list() : head_(nullptr), size_(0), tail_(nullptr) {}

  // параметрический конструктор
  explicit list(size_type n) : list() {
    if (n == 0) {
      return;
    }
    head_ = new Node;
    tail_ = head_;
    Node* current_node = head_;
    for (size_t i = 1; i < n; i++) {
      current_node->next = new Node;
      current_node->next->prev = current_node;
      current_node = current_node->next;
      tail_ = current_node;
    }
    size_ = n;
  }

  list(std::initializer_list<value_type> const& items) : list() {
    for (auto item : items) {
      push_back(item);
    }
  }

  // copy constructor - NT
  list(const list& l) : list() {
    for (auto item : l) {
      push_back(item);
    }
  }

  // move constructor - NT
  list(list&& l) noexcept : list() {
    std::swap(this->head_, l.head_);
    std::swap(this->tail_, l.tail_);
    this->size_ = l.size();
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
  }

  // destructor
  ~list() { destructor_impl(head_); }

  // overload for moving - NT
  list& operator=(list&& l) noexcept {
    if (this != &l) {
      // Освобождаем ресурсы текущего объекта
      clear();
      // Обмениваем указатели на голову и хвост
      std::swap(this->head_, l.head_);
      std::swap(this->tail_, l.tail_);
      // Обмениваем размеры
      std::swap(this->size_, l.size_);
    }
    return *this;
  }

  list& operator=(const list& l) {
    if (this != &l) {
      // Освобождаем ресурсы текущего объекта
      clear();

      // Копируем элементы из списка l
      for (auto iter = l.begin(); iter != l.end(); ++iter) {
        push_back(*iter);
      }
    }
    return *this;
  }

  const_reference front() const {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    return head_->value;
  }

  const_reference back() const {
    if (empty()) {
      throw std::out_of_range("list is empty");
    }
    return tail_->value;
  }

  iterator begin() const noexcept { return iterator(head_); }

  const_iterator cbegin() const noexcept { return const_iterator(head_); }

  iterator end() const noexcept { return iterator(tail_->next); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  void clear() noexcept {
    while (head_ != nullptr) {
      Node* next_node = head_->next;
      delete head_;
      head_ = next_node;
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* newNode = new Node(value);
    if (!newNode) {
      throw std::bad_alloc();
    }
    if (pos.getNode() == nullptr) {
      if (empty()) {
        head_ = newNode;
        tail_ = newNode;
        size_++;
      } else {
        Node* tmp = tail_;
        tail_->next = newNode;
        newNode->prev = tmp;
        tail_ = newNode;
        size_++;
      }
    } else {
      Node* prevNode = pos.getNode()->prev;
      if (prevNode) {
        prevNode->next = newNode;
        newNode->prev = prevNode;
      }
      newNode->next = pos.getNode();
      pos.getNode()->prev = newNode;
      if (pos.getNode() == head_) {
        head_ = newNode;
      }
      size_++;
    }
    return iterator(newNode);
  }

  void erase(iterator pos) noexcept {
    if (pos == end()) {
      return;
    }
    Node* current_node = pos.getNode();
    Node* prev_node = current_node->prev;
    Node* next_node = current_node->next;
    if (prev_node) {
      prev_node->next = next_node;
    } else {
      head_ = next_node;
    }
    if (next_node) {
      next_node->prev = prev_node;
    } else {
      tail_ = prev_node;
    }
    delete current_node;
    size_--;
  }

  void push_back(const_reference value) {
    if (empty()) {
      insert(iterator(begin()), value);
    } else {
      insert(iterator(end()), value);
    }
  }

  void pop_back() noexcept {
    if (!empty()) {
      if (size_ == 1) {
        delete head_;
        head_ = nullptr;
        tail_ = nullptr;
      } else {
        erase(iterator(tail_));
      }
    }
    size_--;
  }

  void push_front(const_reference value) {
    if (empty()) {
      push_back(value);
    } else {
      insert(begin(), value);
    }
  }

  void pop_front() noexcept {
    if (!empty()) {
      erase(iterator(head_));
    }
  }

  void swap(list& other) noexcept {
    auto temp = std::move(other);
    other = std::move(*this);
    *this = std::move(temp);
  }

  void merge(list& other) {
    list<value_type> mergedList;
    iterator thisBegin = begin();
    iterator otherBegin = other.begin();
    while (thisBegin != end()) {
      mergedList.push_back(thisBegin.getNode()->value);
      thisBegin++;
    }
    while (otherBegin != other.end()) {
      mergedList.push_back(*otherBegin);
      otherBegin++;
    }
    mergedList.sort();
    *this = std::move(mergedList);
    other.clear();
  }

  void splice(const_iterator pos, list& other) noexcept {
    iterator tempIterator =
        iterator(const_cast<s21::list<int>::Node*>(pos.getNode()));

    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(tempIterator, *it);
    }
  }

  void reverse() noexcept {
    if (size_ <= 1) {
      return;
    }
    Node* current = head_;
    Node* temp = nullptr;
    while (current != nullptr) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }
    if (temp != nullptr) {
      auto temp = head_;
      head_ = tail_;
      tail_ = temp;
    }
  }

  void unique() {
    auto iter = begin();
    Node* current_node;
    Node* next_node;
    for (; iter != end();) {
      current_node = iter.getNode();
      next_node = current_node->next;
      if (next_node && current_node->value == next_node->value) {
        erase(iter);
        iter = iterator(next_node);
      } else {
        ++iter;
      }
    }
  }

  void sort() {
    for (auto iter = begin(); iter != end(); ++iter) {
      for (auto innerIter = begin(); innerIter != end(); ++innerIter) {
        auto nextIter = innerIter;
        ++nextIter;

        if (nextIter != end() &&
            innerIter.getNode()->value > nextIter.getNode()->value) {
          std::swap(*innerIter, *nextIter);
        }
      }
    }
  }

 private:
  struct Node {
    value_type value;
    Node* next = nullptr;
    Node* prev = nullptr;
    // default constructor
    Node() : value(), next(nullptr), prev(nullptr) {}
    // Constructor with a value parameter
    explicit Node(const_reference value)
        : value(value), next(nullptr), prev(nullptr) {}
  };

  void destructor_impl(Node* node) {
    while (node != nullptr) {
      Node* next_node = node->next;
      delete node;
      node = next_node;
    }
    delete node;
  }

  class ListIterator {
   public:
    ListIterator() : iter_(nullptr) {}
    ListIterator(const ListIterator& other) : iter_(other.iter_) {}
    explicit ListIterator(Node* iter) : iter_(iter) {}
    ListIterator& operator=(const ListIterator& other) {
      iter_ = other.iter_;
      return *this;
    }
    bool operator==(const ListIterator& other) const {
      return iter_ == other.iter_;
    }
    bool operator!=(const ListIterator& other) const {
      return iter_ != other.iter_;
    }

    ListIterator operator++() {
      iter_ = iter_->next;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp(*this);
      iter_ = iter_->next;
      return tmp;
    }

    ListIterator operator--() {
      iter_ = iter_->prev;
      return *this;
    }

    ListIterator operator--(int) {
      ListIterator tmp(*this);
      iter_ = iter_->prev;
      return tmp;
    }

    reference operator*() { return iter_->value; }

    T* operator->() { return &(iter_->value); }

    Node* getNode() { return iter_; };

   private:
    Node* iter_ = nullptr;
  };

  class ListConstIterator {
   public:
    // Default constructor
    ListConstIterator() : iter_(nullptr) {}
    // Copy constructor
    ListConstIterator(const ListConstIterator& other) : iter_(other.iter_) {}
    // Constructor that takes a const pointer to a Node
    explicit ListConstIterator(const Node* iter) : iter_(iter) {}
    // Copy assignment operator
    ListConstIterator& operator=(const ListConstIterator& other) {
      iter_ = other.iter_;
      return *this;
    }
    bool operator==(const ListConstIterator& other) const {
      return iter_ == other.iter_;
    }
    bool operator!=(const ListConstIterator& other) const {
      return iter_ != other.iter_;
    }

    ListConstIterator operator++() {
      iter_ = iter_->next;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator tmp(*this);
      iter_ = iter_->next;
      return tmp;
    }

    ListConstIterator operator--() {
      iter_ = iter_->prev;
      return *this;
    }

    ListConstIterator operator--(int) {
      ListConstIterator tmp(*this);
      iter_ = iter_->prev;
      return tmp;
    }

    const_reference operator*() const { return iter_->value; }

    const T* operator->() const { return &(iter_->value); }

    const Node* getNode() const { return iter_; }

   private:
    const Node* iter_ = nullptr;
  };

  Node* head_ = nullptr;  // указатель на начало списка
  size_type size_ = 0;    // размер списка
  Node* tail_ = nullptr;  // указатель на конец списка
};
}  // namespace s21
#endif
