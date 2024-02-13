#include <set>

#include "test_start.h"

TEST(SetTest, ConstructorDefaultset) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(SetTest, ConstructorInitializerset) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(SetTest, ConstructorInitializer2set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(SetTest, ConstructorCopyset) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

// TEST(SetTest, ConstructorMoveset) {
//   s21::set<int> my_set = {1, 2, 3, 4, 5};
//   std::set<int> orig_set = {1, 2, 3, 4, 5};
//   s21::set<int> my_set_copy = std::move(my_set);
//   std::set<int> orig_set_copy = std::move(orig_set);
//   EXPECT_EQ(my_set.size(), orig_set.size());
//   EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
//   auto my_it = my_set_copy.begin();
//   auto orig_it = orig_set_copy.begin();
//   for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
//     EXPECT_TRUE(*orig_it == *my_it);
//   }
// }

// TEST(SetTest, setIteratorsset) {
//   s21::set<std::string> my_set = {"This", "is", "my", "set"};
//   std::set<std::string> orig_set = {"This", "is", "my", "set"};
//   auto my_it = my_set.begin();
//   auto orig_it = orig_set.begin();
//   EXPECT_TRUE(*orig_it == *my_it);
//   my_it = my_set.end();
//   orig_it = orig_set.end();
//   --my_it;
//   --orig_it;
//   EXPECT_TRUE(*orig_it == *my_it);
// }

TEST(SetTest, Capacityset) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(SetTest, Clearset) {
  s21::set<int> my_empty_set;
  std::set<int> orig_empty_set;
  my_empty_set.insert(2);
  orig_empty_set.insert(2);
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(SetTest, Insertset) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(setTest, EraseFunction_ComplexTypes) {
    s21::set<int> mySet = {5, 4, 3, 2, 7, 8, 9};
    // Erase the element with value 7
    int valueToErase = 7;
    auto erasePosition = mySet.find(valueToErase);
    mySet.erase(erasePosition);
    // Insert new values
    mySet.insert(6);
    mySet.insert(1);
    // Erase the element with value 3
    valueToErase = 3;
    erasePosition = mySet.find(valueToErase);
    mySet.erase(erasePosition);

    std::set<int> stdSet = {1, 2, 4, 5, 6, 8, 9};

    EXPECT_EQ(mySet.size(), stdSet.size());
    auto mySetIt = mySet.begin();
    auto stdSetIt = stdSet.begin();
    for (; mySetIt != mySet.end() && stdSetIt != stdSet.end(); ++mySetIt, ++stdSetIt) {
        EXPECT_EQ(*mySetIt, *stdSetIt);
    }
    EXPECT_EQ(mySetIt, mySet.end());
    EXPECT_EQ(stdSetIt, stdSet.end());
}


TEST(SetTest, Swapset) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3UL);
  EXPECT_EQ(my_swap_set.size(), 1UL);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(SetTest, Mergeset) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
}

TEST(SetTest, Findset) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(SetTest, Containsset) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}
