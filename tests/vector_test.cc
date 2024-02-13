#include "test_start.h"

TEST(VectorTest, Constructor_Default) {
  s21::vector<int> s21_vector;
  std::vector<int> std_vector;
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(VectorTest, Constructor_Initializer_vector) {
  s21::vector<int> s21_vector = {1, 2, 3, 4};
  std::vector<int> std_vector = {1, 2, 3, 4};
  EXPECT_EQ(s21_vector.front(), std_vector.front());
  EXPECT_EQ(s21_vector.back(), std_vector.back());
  EXPECT_EQ(s21_vector.size(), std_vector.size());
  EXPECT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(VectorTest, CopyConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0UL);
}

TEST(VectorTest, CopyConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3, 65,6545,45345,-3};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, MoveConstructor_EmptyVector) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0UL);
}

TEST(VectorTest, MoveConstructor_NonEmptyVector) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 3UL);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0UL);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3UL);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

TEST(VectorTest, MoveAssignmentOperator_EmptyToNonEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0UL);
}

TEST(VectorTest, MoveAssignmentOperator_NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 3UL);
  EXPECT_TRUE(v1.empty());  // Source vector should be empty after move
}

//
TEST(VectorTest, At_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(0), 1);
  EXPECT_EQ(v.at(2), 3);
  EXPECT_EQ(v.at(4), 5);
}

TEST(VectorTest, At_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_THROW(v.at(5), std::out_of_range);
  EXPECT_THROW(v.at(10), std::out_of_range);
}

//
TEST(VectorTest, IndexOperator_ValidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, IndexOperator_InvalidIndex) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v[5]);
  EXPECT_ANY_THROW(v[10]);
}

TEST(VectorTest, ConstIndexOperator_ValidIndex) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[2], 3);
  EXPECT_EQ(v[4], 5);
}

///

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity + 10;
  v.reserve(newCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, Reserve_DecreaseCapacity) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  size_t newCapacity = initialCapacity - 2;
  v.reserve(newCapacity);
  EXPECT_LE(v.capacity(), initialCapacity);
  EXPECT_GE(v.capacity(), newCapacity);
}

TEST(VectorTest, PushBack_EmptyVector) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1UL);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, PushBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(4);
  EXPECT_EQ(v.size(), 4UL);
  EXPECT_EQ(v[3], 4);
}

TEST(VectorTest, PopBack_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2UL);
  EXPECT_EQ(v.back(), 2);
}

TEST(VectorTest, PopBack_EmptyVector) {
  s21::vector<int> v;
  v.pop_back();
  EXPECT_TRUE(v.empty());
}
TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::vector<int> v;
  v.shrink_to_fit();

  EXPECT_GE(v.capacity(), 0UL);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCapacity = v.capacity();
  v.pop_back();  
  v.shrink_to_fit();
  EXPECT_LE(v.capacity(), v.size());

  EXPECT_LE(v.capacity(), initialCapacity);
}
TEST(VectorTest, Swap_EmptyAndNonEmptyVectors) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3UL);
  EXPECT_FALSE(v1.empty());
  EXPECT_EQ(v2.size(), 0UL);
  EXPECT_TRUE(v2.empty());
}


TEST(VectorTest, Insert){
  s21::vector<int> myV = {1,2,3};
  std::vector<int> stdV = {1,2,3};
  // std::vector<int>::iterator iter1 = 
  stdV.insert(stdV.begin()+3, 43);
  // s21::vector<int>::iterator iter2 = 
  myV.insert(myV.begin()+3, 43);
  EXPECT_EQ(myV.size(), stdV.size()); // Compare sizes

  for (size_t i = 0; i < stdV.size(); ++i) {
    EXPECT_EQ(myV[i], stdV[i]); // Compare individual elements
  }

 
}

TEST(VectorTest, Insert1){
  s21::vector<int> myV = {1,2,3,4,5,6,7,6,5,6,5,4,123};
  std::vector<int> stdV = {1,2,3,4,5,6,7,6,5,6,5,4,123};
  stdV.insert(stdV.begin()+3, 43);
  stdV.insert(stdV.begin()+3, 43);
  stdV.insert(stdV.begin()+3, 43);
  stdV.insert(stdV.begin()+3, 43);

  myV.insert(myV.begin()+3, 43);
  myV.insert(myV.begin()+3, 43);
  myV.insert(myV.begin()+3, 43);
  myV.insert(myV.begin()+3, 43);
  EXPECT_EQ(myV.size(), stdV.size()); 
  for (size_t i = 0; i < stdV.size(); ++i) {
    EXPECT_EQ(myV[i], stdV[i]); 
  }
}


TEST(VectorExceptionsTest, AccessOutOfBounds) {
    s21::vector<int> myVector;
    EXPECT_THROW(myVector[0], std::out_of_range);
    ASSERT_THROW(myVector[0], std::out_of_range);
}


TEST(VectorExceptionsTest, FrontOnEmptyVector) {
    s21::vector<int> emptyVector;
    ASSERT_THROW(emptyVector.front(), std::out_of_range);
}

TEST(VectorExceptionsTest, BackOnEmptyVector) {
    s21::vector<int> emptyVector;
    ASSERT_THROW(emptyVector.back(), std::out_of_range);
}

TEST(VectorInsertTest, ReserveCalled) {
    s21::vector<int> myVector;
    myVector.reserve(5);
    ASSERT_THROW(myVector.insert(myVector.begin() + 10, 42), std::out_of_range);
}


