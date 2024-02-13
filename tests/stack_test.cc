#include "test_start.h"
#include <stack>

TEST(StackTest, Constructor_Default) {
  s21::stack<int> s21_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(StackTest, Constructor_Initializer_vector) {
  s21::stack<int> s21_stack;
  s21_stack.push(1);
  s21_stack.push(2);
  s21_stack.push(3);
  s21_stack.push(4);

  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std_stack.push(4);

  EXPECT_EQ(s21_stack.size(), std_stack.size());
  EXPECT_EQ(s21_stack.top(), std_stack.top());
}

TEST(StackTest, CopyConstructor_EmptyStack) {
  s21::stack<int> s21_stack1;
  s21::stack<int> s21_stack2(s21_stack1);
  EXPECT_TRUE(s21_stack2.empty());
  EXPECT_EQ(s21_stack2.size(), 0UL);

  std::stack<int> std_stack1;
  std::stack<int> std_stack2(std_stack1);
  EXPECT_TRUE(std_stack2.empty());
  EXPECT_EQ(std_stack2.size(), 0UL);
}
TEST(StackTest, CopyConstructor_NonEmptyStack) {
  s21::stack<int> s21_stack1;
  s21_stack1.push(1);
  s21_stack1.push(2);
  s21_stack1.push(3);
  s21_stack1.push(65);
  s21_stack1.push(6545);
  s21_stack1.push(45345);
  s21_stack1.push(-3);

  s21::stack<int> s21_stack2(s21_stack1);
  EXPECT_EQ(s21_stack2.size(), s21_stack1.size());
  while (!s21_stack1.empty()) {
    EXPECT_EQ(s21_stack2.top(), s21_stack1.top());
    s21_stack1.pop();
    s21_stack2.pop();
  }

  std::stack<int> std_stack1;
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);
  std_stack1.push(65);
  std_stack1.push(6545);
  std_stack1.push(45345);
  std_stack1.push(-3);

  std::stack<int> std_stack2(std_stack1);
  EXPECT_EQ(std_stack2.size(), std_stack1.size());
  while (!std_stack1.empty()) {
    EXPECT_EQ(std_stack2.top(), std_stack1.top());
    std_stack1.pop();
    std_stack2.pop();
  }
}
