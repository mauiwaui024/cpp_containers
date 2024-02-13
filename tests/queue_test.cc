#include "test_start.h"
#include <queue>

TEST(QueueTest, Constructor_Default) {
  s21::queue<int> s21_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.empty(), std_queue.empty());
}

TEST(QueueTest, Constructor_Initializer_vector) {
  s21::queue<int> s21_queue = {1,2,3,4};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std_queue.push(4);

  EXPECT_EQ(s21_queue.size(), std_queue.size());
  EXPECT_EQ(s21_queue.front(), std_queue.front());
  EXPECT_EQ(s21_queue.back(), std_queue.back());
}

TEST(QueueTest, CopyConstructor_EmptyQueue) {
  s21::queue<int> s21_queue1;
  s21::queue<int> s21_queue2(s21_queue1);
  EXPECT_TRUE(s21_queue2.empty());
  EXPECT_EQ(s21_queue2.size(), 0UL);

  std::queue<int> std_queue1;
  std::queue<int> std_queue2(std_queue1);
  EXPECT_TRUE(std_queue2.empty());
  EXPECT_EQ(std_queue2.size(), 0UL);
}

TEST(QueueTest, CopyConstructor_NonEmptyQueue) {
  s21::queue<int> s21_queue1 = {1,2,3,65,6545,45345,-3};
  s21::queue<int> s21_queue2(s21_queue1);
  EXPECT_EQ(s21_queue2.size(), s21_queue1.size());
  while (!s21_queue1.empty()) {
    EXPECT_EQ(s21_queue2.front(), s21_queue1.front());
    EXPECT_EQ(s21_queue2.back(), s21_queue1.back());
    s21_queue1.pop();
    s21_queue2.pop();
  }

  std::queue<int> std_queue1;
  std_queue1.push(1);
  std_queue1.push(2);
  std_queue1.push(3);
  std_queue1.push(65);
  std_queue1.push(6545);
  std_queue1.push(45345);
  std_queue1.push(-3);

  std::queue<int> std_queue2(std_queue1);
  EXPECT_EQ(std_queue2.size(), std_queue1.size());
  while (!std_queue1.empty()) {
    EXPECT_EQ(std_queue2.front(), std_queue1.front());
    EXPECT_EQ(std_queue2.back(), std_queue1.back());
    std_queue1.pop();
    std_queue2.pop();
  }
}



TEST(QueueTest, PushPop) {
  // Test pushing elements to the queue
  s21::queue<int> q;
  for (int i = 0; i < 200; ++i) {
    q.push(i);
  }
  EXPECT_EQ(q.size(), 200UL);

  // Test popping elements from the queue
  for (int i = 0; i < 100; ++i) {
    q.pop();
  }
  EXPECT_EQ(q.size(), 100UL);

  EXPECT_EQ(q.front(), 100);
  EXPECT_EQ(q.back(), 199);
}

TEST(QueueTest, ConstructorInitializerList) {

  s21::queue<int> q = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
                       110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
  
  EXPECT_EQ(q.size(), 20UL);

  EXPECT_EQ(q.front(), 10);
  EXPECT_EQ(q.back(), 200);


  std::vector<int> expected_elements = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
                                       110, 120, 130, 140, 150, 160, 170, 180, 190, 200};
  for (size_t i = 0; i < expected_elements.size(); ++i) {
    EXPECT_EQ(q.front(), expected_elements[i]);
    q.pop();
  }
}

TEST(QueueTest, FrontOnEmptyQueue) {
    s21::queue<int> emptyQueue;
    ASSERT_THROW(emptyQueue.front(), std::out_of_range);
}

TEST(QueueTest, BackOnEmptyQueue) {
    s21::queue<int> emptyQueue;
    ASSERT_THROW(emptyQueue.back(), std::out_of_range);
}

TEST(QueueTest, FrontAfterPush) {
    s21::queue<int> queueWithElement;
    queueWithElement.push(42);
    ASSERT_EQ(queueWithElement.front(), 42);
}

TEST(QueueTest, BackAfterPush) {
    s21::queue<int> queueWithElement;
    queueWithElement.push(99);
    ASSERT_EQ(queueWithElement.back(), 99);
}