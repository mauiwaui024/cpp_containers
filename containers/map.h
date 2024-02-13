#ifndef map_H
#define map_H

#include <initializer_list>
#include <limits>
#include <utility>

#include "../containers.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<key_type, mapped_type>::TreeIterator;
  using const_iterator =
      typename RBTree<key_type, mapped_type>::ConstTreeIterator;
  using size_type = std::size_t;
  using TreeNode = typename s21::RBTree<key_type, mapped_type>::TreeNode;

  map() noexcept = default;

  map(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      insert(item);
    }
  }
  // copy constructor
  map(const map& other) : tree_(other.tree_) {}
  // Move constructor
  map(map&& m) noexcept : tree_(std::move(m.tree_)) {}
  // Move assignment operator

  map& operator=(map&& m) noexcept {
    if (this != &m) {
      tree_ = std::move(m.tree_);
    }
    return *this;
  }
  ~map() noexcept = default;

  iterator begin() noexcept { return tree_.begin(); }

  iterator end() noexcept { return tree_.end(); }

  bool empty() noexcept { return tree_.empty(); }

  size_type size() noexcept { return tree_.size(); }

  size_type max_size() noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  void clear() noexcept { tree_.clear(); }

  iterator find(const Key& key) { return tree_.find(key); }

  std::pair<iterator, bool> insert(const value_type& value) {
    // Create a new TreeNode
    TreeNode* newNode = new TreeNode(value.first, value.second);
    // Call the insertNode function on the RBTree instance (tree_)
    return tree_.insertNode(newNode, tree_.root_);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    // inserts value by key and returns iterator to where the element is in the
    // container and bool denoting whether the insertion took place
    TreeNode* newNode = new TreeNode(key, obj);
    return tree_.insertNode(newNode, tree_.root_);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    // Attempt to find the existing node with the given key
    TreeNode* existingNode = tree_.search(key);
    if (existingNode) {
      existingNode->value_ = obj;
      return std::make_pair(iterator(existingNode), false);
    } else {
      // If the key does not exist, insert a new node
      TreeNode* newNode = new TreeNode(key, obj);
      return tree_.insertNode(newNode, tree_.root_);
    }
  }

  void erase(iterator pos) { tree_.erase(pos); }

  void swap(map& other) {
    // проверка добавлена в самом дереве
    tree_.swap(other.tree_);
  }

  void merge(map& other) noexcept {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(it.getNode()->key_, it.getNode()->value_);
    }
  }

  T& at(const Key& key) { return tree_.at(key); }

  T& operator[](const Key& key) { return tree_[key]; }
  bool contains(const Key& key) {
    iterator it = find(key);
    if (it != end()) {
      return true;
    } else {
      return false;
    }
  }

 private:
  RBTree<key_type, mapped_type> tree_;
};

}  // namespace s21

#endif  // map_H
