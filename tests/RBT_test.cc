#include "test_start.h"
#include "stdio.h"


TEST(RBTreeTest, DefaultConstructor) {
    s21::RBTree<int, std::string> tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0UL);
}

TEST(RBTreeTest, CopyConstructor) {
    s21::RBTree<int, std::string> original;
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(1, "one"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(2, "two"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(3, "three"), original.root_);
    s21::RBTree<int, std::string> copy(original);
    EXPECT_EQ(copy.size(), original.size());
    auto originalIt = original.begin();
    auto copyIt = copy.begin();

    while (originalIt != original.end() && copyIt != copy.end()) {
        EXPECT_EQ(copyIt->key_, originalIt->key_);
        EXPECT_EQ(copyIt->value_, originalIt->value_);
        ++originalIt;
        ++copyIt;
    }

    EXPECT_TRUE(originalIt == original.end() && copyIt == copy.end());
}

TEST(RBTreeTest, MoveConstructor) {
    s21::RBTree<int, std::string> original;
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(1, "one"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(2, "two"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(3, "three"), original.root_);
    s21::RBTree<int, std::string> moved(std::move(original));
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(original.size(), 0UL);

    EXPECT_FALSE(moved.empty());
    EXPECT_EQ(moved.size(), 3UL);
}
TEST(RBTreeTest, MoveAssignmentOperator) {
    s21::RBTree<int, std::string> original;
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(1, "one"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(2, "two"), original.root_);
    original.insertNode(new s21::RBTree<int, std::string>::TreeNode(3, "three"), original.root_);
    s21::RBTree<int, std::string> other;
    other.insertNode(new s21::RBTree<int, std::string>::TreeNode(4, "four"), other.root_);
    other.insertNode(new s21::RBTree<int, std::string>::TreeNode(5, "five"), other.root_);
 
    original = std::move(other);
    EXPECT_TRUE(other.empty());
    EXPECT_EQ(other.size(), 0UL);
    EXPECT_FALSE(original.empty());
    EXPECT_EQ(original.size(), 2UL);
}

TEST(RBTreeTest, InsertNode) {
    s21::RBTree<int, std::string> tree;
    auto result = tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(1, "one"), tree.root_);
    EXPECT_TRUE(result.second);
    EXPECT_EQ(result.first->key_, 1);
    EXPECT_EQ(result.first->value_, "one");
    EXPECT_EQ(tree.size(), 1UL);
}

TEST(RBTreeTest, Erase) {
    // Create an RBTree
    s21::RBTree<int, std::string> tree;
    tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(1, "one"), tree.root_);
    tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(2, "two"),  tree.root_);
    tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(3, "three"),  tree.root_);
    EXPECT_EQ(tree.size(), 3UL);

    s21::RBTree<int, std::string>::iterator it = tree.find(2);
    ASSERT_NE(it, tree.end());
    tree.erase(it);
    EXPECT_EQ(tree.size(), 2UL);
    EXPECT_EQ(tree.find(2), tree.end());

}

// TEST(RBTreeTest, EraseMultipleValues) {
//     s21::RBTree<int, std::string> tree;
//     for (int i = 1; i <= 100; ++i) {
//         tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(i, "value" + std::to_string(i)), tree.root_);
//     }

//     //  for (auto it = tree.begin(); it != tree.end(); ++it) {
//     //     std::cout << "Key: " << it.getNode()->key_ << ", Value: " << it.getNode()->value_ << std::endl;
//     // }
//     // Erase specific nodes
//     auto it1 = tree.find(2);
//     ASSERT_NE(it1, tree.end());
//     tree.erase(it1);

// }


TEST(RBTreeTest, EraseFromTreeWith20Values) {
   s21::RBTree<int, std::string> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.insertNode(new s21::RBTree<int, std::string>::TreeNode(i, "value" + std::to_string(i)), tree.root_);
    }
    tree.erase(tree.find(1));
    tree.erase(tree.find(2));
    tree.erase(tree.find(10));
    tree.erase(tree.find(11));
}