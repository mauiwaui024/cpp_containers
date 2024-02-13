#ifndef set_H
#define set_H

#include <initializer_list>
#include <limits>
#include <utility>

#include "RBT.h"

namespace s21 {

template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<key_type, value_type>::TreeIterator;
  using const_iterator =
      typename RBTree<key_type, value_type>::ConstTreeIterator;
  using size_type = std::size_t;

  set() noexcept = default;

  set(std::initializer_list<value_type> const &items) {
    for (const auto &item : items) {
      insert(item);
    }
  }

  set(const set &s) {
    for (const auto &pair : s) {
      insert(pair);
    }
  }

  set(set &&s) noexcept {
    clear();
    swap(s);
  }

  ~set() noexcept = default;

  set operator=(set &&s) {
    if (this != &s) {
      tree_ = std::move(s.tree_);
    }

    return *this;
  }

  iterator begin() const noexcept { return tree_.begin(); }

  iterator end() const noexcept { return tree_.end(); }

  bool empty() noexcept { return tree_.empty(); }

  size_type size() noexcept { return tree_.size(); }

  size_type max_size() noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() noexcept { tree_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    using TreeNode = typename s21::RBTree<value_type, value_type>::TreeNode;
    TreeNode *newNode = new TreeNode(value, value);
    return tree_.insertNode(newNode, tree_.root_);
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void swap(set &other) noexcept { tree_.swap(other.tree_); }

  void merge(set &other) noexcept {
    for (const auto &pair : other) {
      insert(pair);
    }
    other.clear();
  }

  iterator find(const Key &key) noexcept { return tree_.find(key); }

  bool contains(const Key &key) noexcept { return tree_.contains(key); }

 private:
  // в сете нет пары ключ значение поэтому в дерево я передаю ключ ключ
  RBTree<key_type, value_type> tree_;
};

}  // namespace s21

#endif  // set_H
