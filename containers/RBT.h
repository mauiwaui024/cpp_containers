#ifndef CONTAINERS_RB_TREE_H
#define CONTAINERS_RB_TREE_H

#include <iostream>
#include <utility>  // for std::pair

#include "stack.h"

namespace s21 {
template <typename Key, typename Value>
class RBTree {
 public:
  class TreeIterator;
  class ConstTreeIterator;
  struct TreeNode;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = TreeIterator;
  using const_iterator = ConstTreeIterator;
  using size_type = size_t;
  using pointer = value_type*;
  // Конструктор для дерева
  RBTree() : root_(nullptr), size_(0) {}
  // копирование
  // копирование рекурсивное
  RBTree(const RBTree& other) : root_(nullptr), size_(0) {
    // теперь увеличивается размер в самой функции copyTree
    if (other.root_) {
      root_ = copyTree(other.root_, nullptr);
    }
  }
  // перемещение
  RBTree(RBTree&& other) noexcept : root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.size_ = 0;
  }

  RBTree& operator=(const RBTree&& other) noexcept {
    if (this != &other) {
      clear();
      root_ = other.root_;
      size_ = other.size_;
      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }
  RBTree& operator=(RBTree&& other) noexcept {
    if (this != &other) {
      clear();
      root_ = other.root_;
      size_ = other.size_;
      other.root_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  // деструктор
  ~RBTree() {
    clear();
    root_ = nullptr;
  }

  iterator begin() const noexcept {
    // Find the leftmost node, which has the smallest key
    TreeNode* current = root_;
    while (current && current->left_) {
      current = current->left_;
    }
    return iterator(current);
  }

  iterator end() const noexcept { return iterator(nullptr); }
  const_iterator cbegin() {
    // Find the leftmost node, which has the smallest key
    TreeNode* current = root_;
    while (current && current->left_) {
      current = current->left_;
    }
    return const_iterator(current);
  }

  const_iterator cend() {
    // The end iterator points beyond the last node (nullptr)
    return const_iterator(nullptr);
  }
  std::pair<iterator, bool> insertNode(TreeNode* newNode, TreeNode* root) {
    TreeNode* parent = nullptr;
    TreeNode* currentNode = root;
    while (currentNode) {
      parent = currentNode;
      if (newNode->key_ < currentNode->key_) {
        currentNode = currentNode->left_;
      } else if (newNode->key_ > currentNode->key_) {
        currentNode = currentNode->right_;
      } else {  // если существует такой ключ возвращаем false и текущий
                // итератор
        delete newNode;  // Free the memory allocated for newNode
        return std::make_pair(iterator(currentNode), false);
      }
    }
    if (parent) {
      newNode->parent_ = parent;
      if (newNode->key_ < parent->key_) {
        parent->left_ = newNode;
      } else {
        parent->right_ = newNode;
      }
    } else {  // если дерево пустое, то узел становится корнем
      root_ = newNode;
      newNode->color_ = Color::BLACK;
    }
    insertBalancing(newNode);
    size_++;
    return std::make_pair(iterator(newNode), true);
  }

  void insertBalancing(TreeNode* node) {
    while (node != root_ && node->parent_ &&
           node->parent_->color_ == Color::RED) {
      TreeNode* parent = node->parent_;
      TreeNode* gparent = parent->parent_;
      if (gparent && parent == gparent->left_) {
        TreeNode* uncle = parent->parent_->right_;
        // Родитель и дядя красные. Устанавливаем цвет родителя и дяди в
        // черный, а дедушки в красный. Затем сдвигаем текущий узел node на
        // дедушку.
        if (uncle && uncle->color_ == Color::RED) {
          uncle->color_ = Color::BLACK;
          parent->color_ = Color::BLACK;
          gparent->color_ = Color::RED;
          node = gparent;
        } else {
          // Родитель красный, дядя черный, и узел node - правый
          // потомок. Делаем левый поворот относительно родителя узла node.
          if (node == parent->right_) {
            node = parent;
            rotateLeft(node);
          }
          // Устанавливаем цвета родителя и дедушки так, чтобы сохранить
          // свойства красно-черного дерева. Выполняем правый поворот
          // относительно узла node. Этот поворот также выполняется для
          // восстановления баланса.
          parent->color_ = Color::BLACK;
          gparent->color_ = Color::RED;
          rotateRight(gparent);
        }
      } else {
        TreeNode* uncle = parent->parent_->left_;
        if (uncle && uncle->color_ == Color::RED) {
          uncle->color_ = Color::BLACK;
          parent->color_ = Color::BLACK;
          gparent->color_ = Color::RED;
          node = gparent;
        } else {
          if (node == parent->left_) {
            node = parent;
            rotateRight(node);
          }
          parent->color_ = Color::BLACK;
          gparent->color_ = Color::RED;
          rotateLeft(gparent);
        }
      }
    }
    root_->color_ = Color::BLACK;
  }

  // Эта функция изменяет структуру дерева так, чтобы правый потомок узла node
  // становился его новым родителем, а узел node становится левым потомком его
  // предыдущего правого потомка.
  void rotateLeft(TreeNode* node) {
    if (!node || !node->right_) {
      return;
    }
    TreeNode* rightChild = node->right_;
    node->right_ = rightChild->left_;
    if (rightChild->left_) {
      rightChild->left_->parent_ = node;
    }
    rightChild->parent_ = node->parent_;
    if (!node->parent_) {
      root_ = rightChild;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = rightChild;
    } else {
      node->parent_->right_ = rightChild;
    }
    rightChild->left_ = node;
    node->parent_ = rightChild;
  }

  // Эта функция изменяет структуру дерева так, чтобы левый потомок узла node
  // становился его новым родителем, а узел node становится правым потомком его
  // предыдущего левого потомка.
  void rotateRight(TreeNode* node) {
    if (!node || !node->left_) {
      return;
    }
    TreeNode* leftChild = node->left_;
    node->left_ = leftChild->right_;
    if (leftChild->right_) {
      leftChild->right_->parent_ = node;
    }
    leftChild->parent_ = node->parent_;
    if (!node->parent_) {
      root_ = leftChild;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = leftChild;
    } else {
      node->parent_->right_ = leftChild;
    }
    leftChild->right_ = node;
    node->parent_ = leftChild;
  }

  // erase - 3 сценария
  // 1.когда левый ребенок - nullptr
  // 2. когда правый ребенок - nullptr
  // 3. когда никакой из детей - nullptr
  void deleteNode(RBTree<Key, Value>& tree, TreeNode* nodeToDelete) {
    TreeNode* successorNode = nodeToDelete;
    TreeNode* successorChild = nullptr;
    RBTree<Key, Value>::Color successorOriginalColor = successorNode->color_;

    if (nodeToDelete->left_ == nullptr) {
      successorChild = nodeToDelete->right_;
      transplant(tree, nodeToDelete, nodeToDelete->right_);
    } else if (nodeToDelete->right_ == nullptr) {
      successorChild = nodeToDelete->left_;
      transplant(tree, nodeToDelete, nodeToDelete->left_);
    } else {
      successorNode = tree.minimum(nodeToDelete->right_);
      successorOriginalColor = successorNode->color_;
      successorChild = successorNode->right_;

      if (successorNode->parent_ != nodeToDelete) {
        transplant(tree, successorNode, successorNode->right_);
        successorNode->right_ = nodeToDelete->right_;
        successorNode->right_->parent_ = successorNode;
      }

      transplant(tree, nodeToDelete, successorNode);
      successorNode->left_ = nodeToDelete->left_;
      successorNode->left_->parent_ = successorNode;
      successorNode->color_ = nodeToDelete->color_;
    }

    delete nodeToDelete;
    size_--;
    if (successorOriginalColor == RBTree<Key, Value>::Color::BLACK) {
      deleteFixup(tree, successorChild);
    }
  }

  void erase(iterator pos) {
    if (contains(pos.getNode()->key_)) {
      deleteNode(*this, pos.getNode());
    }
  }

  void transplant(RBTree<Key, Value>& tree, TreeNode* sourceNode,
                  TreeNode* replacementNode) {
    // Если исходный узел - корень дерева
    if (sourceNode->parent_ == nullptr) {
      // Заменяем корень дерева на новый узел
      tree.root_ = replacementNode;
    } else if (sourceNode == sourceNode->parent_->left_) {
      // Если исходный узел - левый потомок своего родителя
      // Заменяем левого потомка родителя на новый узел
      sourceNode->parent_->left_ = replacementNode;
    } else {
      // Исходный узел - правый потомок своего родителя
      // Заменяем правого потомка родителя на новый узел
      sourceNode->parent_->right_ = replacementNode;
    }
    // Устанавливаем ссылку на родителя у нового узла
    if (replacementNode != nullptr) {
      replacementNode->parent_ = sourceNode->parent_;
    }
  }

  void deleteFixup(RBTree<Key, Value>& tree, TreeNode* deletedNode) {
    while (deletedNode && deletedNode != tree.root_ &&
           deletedNode->color_ == RBTree<Key, Value>::Color::BLACK) {
      TreeNode* sibling = (deletedNode == deletedNode->parent_->left_)
                              ? deletedNode->parent_->right_
                              : deletedNode->parent_->left_;
      if (sibling == nullptr) {
        break;
      }
      if (sibling->color_ == RBTree<Key, Value>::Color::RED) {
        sibling->color_ = RBTree<Key, Value>::Color::BLACK;
        deletedNode->parent_->color_ = RBTree<Key, Value>::Color::RED;
        if (deletedNode == deletedNode->parent_->left_) {
          tree.rotateLeft(deletedNode->parent_);
        } else {
          tree.rotateRight(deletedNode->parent_);
        }
        sibling = (deletedNode == deletedNode->parent_->left_)
                      ? deletedNode->parent_->right_
                      : deletedNode->parent_->left_;
      }

      if (sibling != nullptr) {
        if ((sibling->left_ == nullptr ||
             sibling->left_->color_ == RBTree<Key, Value>::Color::BLACK) &&
            (sibling->right_ == nullptr ||
             sibling->right_->color_ == RBTree<Key, Value>::Color::BLACK)) {
          sibling->color_ = RBTree<Key, Value>::Color::RED;
          deletedNode = deletedNode->parent_;
        } else {
          if (sibling->right_ == nullptr ||
              sibling->right_->color_ == RBTree<Key, Value>::Color::BLACK) {
            sibling->left_->color_ = RBTree<Key, Value>::Color::BLACK;
            sibling->color_ = RBTree<Key, Value>::Color::RED;
            if (deletedNode == deletedNode->parent_->left_) {
              tree.rotateLeft(sibling);
            } else {
              tree.rotateRight(sibling);
            }
            sibling = (deletedNode == deletedNode->parent_->left_)
                          ? deletedNode->parent_->right_
                          : deletedNode->parent_->left_;
          } else {
            sibling->right_->color_ = RBTree<Key, Value>::Color::BLACK;
            sibling->color_ = RBTree<Key, Value>::Color::RED;
            if (deletedNode == deletedNode->parent_->left_) {
              tree.rotateLeft(deletedNode->parent_);
            } else {
              tree.rotateRight(deletedNode->parent_);
            }
            sibling = (deletedNode == deletedNode->parent_->left_)
                          ? deletedNode->parent_->right_
                          : deletedNode->parent_->left_;
          }
        }
      }
    }
    if (deletedNode != nullptr) {
      deletedNode->color_ = RBTree<Key, Value>::Color::BLACK;
    }
  }

  // ищет минимальный узел в поддереве, начиная с заданного узла
  TreeNode* minimum(TreeNode* node) const {
    while (node && node->left_) {
      node = node->left_;
    }
    return node;
  }
  TreeNode* maximum(TreeNode* node) const noexcept {
    if (!node) {
      return nullptr;
    }
    while (node->right_) {
      node = node->right_;
    }
    return node;
  }

  /// ####################################SEARCH FOR RB
  ///  TREE###############################
  ConstTreeIterator find(const key_type& key) const {
    TreeNode* current = root_;
    while (current) {
      if (key == current->key_) {
        return ConstTreeIterator(current);
      } else if (key < current->key_) {
        current = current->left_;
      } else {
        current = current->right_;
      }
    }
    return end();  // Узел с таким ключом не найден
  }
  TreeIterator find(const key_type& key) {
    TreeNode* current = root_;
    while (current) {
      if (key == current->key_) {
        return TreeIterator(current);
      } else if (key < current->key_) {
        current = current->left_;
      } else {
        current = current->right_;
      }
    }
    return end();  // Узел с таким ключом не найден
  }
  TreeNode* search(const key_type& key) const {
    TreeNode* current = root_;
    while (current) {
      if (key == current->key_) {
        return current;
      } else if (key < current->key_) {
        current = current->left_;
      } else {
        current = current->right_;
      }
    }
    return nullptr;  // Узел с таким ключом не найден
  }

  value_type& at(const key_type& key) {
    TreeNode* node = search(key);
    if (node) {
      return node->value_;
    } else {
      throw std::out_of_range("Key not found in the tree");
    }
  }

  value_type& operator[](const key_type& key) { return at(key); }
  bool empty() { return size_ == 0; }

  size_type size() const { return size_; }

  void clear() {
    if (root_) {
      deleteSubtree(root_);
      size_ = 0;
      root_ = nullptr;
    }
  }

  void swap(RBTree& other) noexcept {
    if (root_ != other.root_) {
      std::swap(root_, other.root_);
      auto temp_size = size_;
      size_ = other.size_;
      other.size_ = temp_size;
    }
  }

  bool contains(const Key& key) const {
    TreeNode* node = search(key);
    return (node != nullptr);
  }

  // Итератор для дерева
  class TreeIterator {
    // эти определения типов позволяют итератору соответствовать требованиям STL
    // и обеспечивают совместимость с алгоритмами, предоставляемыми STL.
    using iterator_category = std::forward_iterator_tag;
    using value_type = RBTree::value_type;
    using reference = RBTree::reference;
    using pointer = RBTree::pointer;
    using difference_type = std::ptrdiff_t;

   public:
    TreeIterator() = delete;
    // default constructor - принимает указатель на node и становится текущим
    // узлом итератора
    TreeIterator(TreeNode* node) : current_(node) {}
    // разыменовываем указатель на текущий узел
    reference operator*() { return current_->value_; }

    TreeIterator& operator++() noexcept {
      if (current_->right_) {
        current_ = findLeftmost(current_->right_);
      } else {
        while (current_->parent_ && current_->parent_->right_ == current_) {
          current_ = current_->parent_;
        }
        current_ = current_->parent_;
      }
      return *this;
    }

    TreeIterator& operator++(int) noexcept {
      TreeIterator tmp(current_);
      ++(*this);
      return tmp;
    }
    TreeIterator& operator--() noexcept {
      if (current_->left_) {
        current_ = findRightmost(current_->left_);
      } else {
        while (current_->parent_ && current_->parent_->left_ == current_) {
          current_ = current_->parent_;
        }
        current_ = current_->parent_;
      }
      return *this;
    }

    bool operator==(const TreeIterator& other) const noexcept {
      return current_ == other.current_;
    }

    bool operator!=(const TreeIterator& other) const noexcept {
      return current_ != other.current_;
    }
    TreeNode* operator->() const noexcept { return current_; }

    TreeNode* getNode() { return current_; }

   private:
    TreeNode* current_;
    // Helper function to find the leftmost node in a subtree
    TreeNode* findLeftmost(TreeNode* node) {
      while (node && node->left_) {
        node = node->left_;
      }
      return node;
    }
    TreeNode* findRightmost(TreeNode* node) {
      while (node && node->right_) {
        node = node->right_;
      }
      return node;
    }
  };

  // Конст Итератор для дерева
  class ConstTreeIterator {
    // эти определения типов позволяют итератору соответствовать требованиям STL
    // и обеспечивают совместимость с алгоритмами, предоставляемыми STL.
    using iterator_category = std::forward_iterator_tag;
    using value_type = const RBTree::value_type;
    using reference = RBTree::reference;
    using pointer = const RBTree::pointer;
    using difference_type = std::ptrdiff_t;

   public:
    ConstTreeIterator() = delete;
    // default constructor - принимает указатель на node и становится текущим
    // узлом итератора
    explicit ConstTreeIterator(const TreeNode* node) : current_(node) {}
    // разыменовываем указатель на текущий узел
    reference operator*() const noexcept { return current_->value_; }

    const_iterator& operator++() noexcept {
      if (current_->right_) {
        current_ = findLeftmost(current_->right_);
      } else {
        while (current_->parent_ && current_->parent_->right_ == current_) {
          current_ = current_->parent_;
        }
        current_ = current_->parent_;
      }
      return *this;
    }

    const_iterator& operator++(int) noexcept {
      const_iterator tmp(current_);
      ++(*this);
      return tmp;
    }
    const_iterator& operator--() noexcept {
      if (current_->left_) {
        current_ = findRightmost(current_->left_);
      } else {
        while (current_->parent_ && current_->parent_->left_ == current_) {
          current_ = current_->parent_;
        }
        current_ = current_->parent_;
      }
      return *this;
    }

    bool operator!=(const TreeIterator& other) const noexcept {
      return current_ != other.current_;
    }

    bool operator==(const ConstTreeIterator& other) const noexcept {
      return current_ == other.current_;
    }

    TreeNode* operator->() const noexcept { return current_; }

   private:
    const TreeNode* current_;
    // Helper function to find the leftmost node in a subtree
    TreeNode* findLeftmost(const TreeNode* node) {
      while (node && node->left_) {
        node = node->left_;
      }
      return node;
    }
    TreeNode* findRightmost(TreeNode* node) {
      while (node && node->right_) {
        node = node->right_;
      }
      return node;
    }
  };

  enum class Color { RED, BLACK };

  struct TreeNode {
    // параметрический конструктор
    TreeNode(key_type key, value_type value, Color color)
        : key_(key),
          value_(value),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr),
          color_(color){};
    TreeNode(key_type key, value_type value)
        : key_(key),
          value_(value),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr),
          color_(Color::RED){};

    key_type key_;
    value_type value_;
    TreeNode* parent_ = nullptr;
    TreeNode* left_ = nullptr;
    TreeNode* right_ = nullptr;
    Color color_ = Color::RED;
    friend class RBTree<Key, Value>;
  };

  TreeNode* root_;
  size_type size_ = 0;

  TreeNode* copyTree(const TreeNode* srcNode, TreeNode* parent) {
    if (!srcNode) {
      return nullptr;
    }
    // создаем новый узел дерева через парам конструктор с теми же значениями
    // что в передаваемом узле
    TreeNode* newNode =
        new TreeNode(srcNode->key_, srcNode->value_, srcNode->color_);
    newNode->parent_ = parent;
    // рекурсивно копируем левое и правое поддерево
    newNode->left_ = copyTree(srcNode->left_, newNode);
    newNode->right_ = copyTree(srcNode->right_, newNode);
    ++size_;
    return newNode;
  }

  void deleteSubtree(TreeNode* node) {
    if (node) {
      // Рекурсивно вызываем удаление для левого и правого поддерева
      deleteSubtree(node->left_);
      deleteSubtree(node->right_);
      // Удаляем текущий узел
      delete node;
    }
  }
};
}  // namespace s21
#endif
