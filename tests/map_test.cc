#include <map>
#include <stdio.h>
#include "test_start.h"

TEST(MapTest, ConstructorDefaultMap) {
  s21::map<char, int> myMap;
  std::map<char, int> stdMap;
  EXPECT_EQ(myMap.empty(), stdMap.empty());
}

TEST(MapTest, ConstructorInitializerMap) {
  s21::map<char, int> myMap = {
      {'x', 1},
      {'b', 2},
      {'z', 3},
      {'y', 4}
  };
  std::map<char, int> stdMap = {
      {'x', 1},
      {'b', 2},
      {'z', 3},
      {'y', 4}
  };
  EXPECT_EQ(myMap.size(), stdMap.size());
  auto myMapIt = myMap.begin();
  auto stdMapIt = stdMap.begin();
  for (; myMapIt != myMap.end() && stdMapIt != stdMap.end(); ++myMapIt, ++stdMapIt) {
    EXPECT_EQ(myMapIt.getNode()->key_, stdMapIt->first);
    EXPECT_EQ(myMapIt.getNode()->value_, stdMapIt->second);
  }
  EXPECT_EQ(myMapIt, myMap.end());
  EXPECT_EQ(stdMapIt, stdMap.end());
}

TEST(MapTest, ConstructorInitializerMap_CustomTypes) {
    s21::map<std::string, double> myMap = {
        {"apple", 2.5},
        {"banana", 1.8},
        {"orange", 3.2},
        {"grape", 2.1},
        {"kiwi", 4.0}
    };
    std::map<std::string, double> stdMap = {
        {"apple", 2.5},
        {"banana", 1.8},
        {"orange", 3.2},
        {"grape", 2.1},
        {"kiwi", 4.0}
    };
    EXPECT_EQ(myMap.size(), stdMap.size());
    auto myMapIt = myMap.begin();
    auto stdMapIt = stdMap.begin();
    for (; myMapIt != myMap.end() && stdMapIt != stdMap.end(); ++myMapIt, ++stdMapIt) {
        EXPECT_EQ(myMapIt.getNode()->key_, stdMapIt->first);
        EXPECT_EQ(myMapIt.getNode()->value_, stdMapIt->second);
    }
    EXPECT_EQ(myMapIt, myMap.end());
    EXPECT_EQ(stdMapIt, stdMap.end());
}

TEST(MapTest, ConstructorCopyMap) {

    s21::map<std::string, double> originalMyMap = {
        {"apple", 2.5},
        {"banana", 1.8},
        {"orange", 3.2},
        {"grape", 2.1},
        {"kiwi", 4.0}
    };
    s21::map<std::string, double> copiedMyMap(originalMyMap);
    std::map<std::string, double> originalStdMap = {
        {"apple", 2.5},
        {"banana", 1.8},
        {"orange", 3.2},
        {"grape", 2.1},
        {"kiwi", 4.0}
    };

    // Copy the original std::map using the copy constructor
    std::map<std::string, double> copiedStdMap(originalStdMap);
    // Verify that the sizes are equal
    EXPECT_EQ(originalMyMap.size(), copiedMyMap.size());
    EXPECT_EQ(originalStdMap.size(), copiedStdMap.size());
    auto myMapIt = originalMyMap.begin();
    auto copiedMyMapIt = copiedMyMap.begin();
    for (; myMapIt != originalMyMap.end() && copiedMyMapIt != copiedMyMap.end(); ++myMapIt, ++copiedMyMapIt) {
        EXPECT_EQ(myMapIt.getNode()->key_, copiedMyMapIt.getNode()->key_);
        EXPECT_EQ(myMapIt.getNode()->value_, copiedMyMapIt.getNode()->value_);
    }
    auto stdMapIt = originalStdMap.begin();
    auto copiedStdMapIt = copiedStdMap.begin();
    for (; stdMapIt != originalStdMap.end() && copiedStdMapIt != copiedStdMap.end(); ++stdMapIt, ++copiedStdMapIt) {
        EXPECT_EQ(stdMapIt->first, copiedStdMapIt->first);
        EXPECT_EQ(stdMapIt->second, copiedStdMapIt->second);
    }
}


TEST(MapTest, MoveConstructor) {
    // Create a Map with some initial values
    s21::map<char, int> originalMap = {
        {'x', 1},
        {'b', 2},
        {'z', 3},
        {'y', 4}
    };
    // Move construct a new Map
    s21::map<char, int> movedMap = std::move(originalMap);
    // Ensure the original map is empty after the move
    EXPECT_TRUE(originalMap.empty());
    // Check the size and content of the moved map
    EXPECT_EQ(movedMap.size(), 4UL);
    auto movedMapIt = movedMap.begin();
    EXPECT_EQ(movedMapIt.getNode()->key_, 'b');
    EXPECT_EQ(movedMapIt.getNode()->value_, 2);
    ++movedMapIt;
    EXPECT_EQ(movedMapIt.getNode()->key_, 'x');
    EXPECT_EQ(movedMapIt.getNode()->value_, 1);
    ++movedMapIt;
    EXPECT_EQ(movedMapIt.getNode()->key_, 'y');
    EXPECT_EQ(movedMapIt.getNode()->value_, 4);
    ++movedMapIt;
    EXPECT_EQ(movedMapIt.getNode()->key_, 'z');
    EXPECT_EQ(movedMapIt.getNode()->value_, 3);
    ++movedMapIt;
    EXPECT_EQ(movedMapIt, movedMap.end());
}

TEST(MapTest, Insert) {
    // Create a Map
    s21::map<char, int> myMap;
    // Insert a value using the insert method
    std::pair<s21::map<char, int>::iterator, bool> result = myMap.insert({'x', 42});
    // Check that the insertion was successful
    EXPECT_TRUE(result.second);
    // Check the size of the map
    EXPECT_EQ(myMap.size(), 1UL);
    // Check the inserted value
    EXPECT_EQ(result.first.getNode()->key_, 'x');
    EXPECT_EQ(result.first.getNode()->value_, 42);
}
TEST(MapTest, InsertNonEmptyMap) {
    // Create a Map with some initial values
    s21::map<char, int> myMap = {
        {'a', 1},
        {'b', 2}
    };
    // Insert a new value using the insert method
    std::pair<s21::map<char, int>::iterator, bool> result = myMap.insert({'x', 42});
    // Check that the insertion was successful
    EXPECT_TRUE(result.second);
    // Check the size of the map
    EXPECT_EQ(myMap.size(), 3UL);
    // Check the inserted value
    EXPECT_EQ(result.first.getNode()->key_, 'x');
    EXPECT_EQ(result.first.getNode()->value_, 42);
    // Check the existing values in the map
    auto itA = myMap.find('a');
    EXPECT_NE(itA, myMap.end());
    EXPECT_EQ(itA.getNode()->value_, 1);
    auto itB = myMap.find('b');
    EXPECT_NE(itB, myMap.end());
    EXPECT_EQ(itB.getNode()->value_, 2);
}

TEST(MapTest, InsertKeyValue) {
    // Create a Map
    s21::map<char, int> myMap;
    // Insert a new key-value pair using the insert method
    std::pair<s21::map<char, int>::iterator, bool> result = myMap.insert({'x', 42});
    // Check that the insertion was successful
    EXPECT_TRUE(result.second);
    // Check the size of the map
    EXPECT_EQ(myMap.size(), 1UL);
    // Check the inserted value
    EXPECT_EQ(result.first.getNode()->key_, 'x');
    EXPECT_EQ(result.first.getNode()->value_, 42);
    // Attempt to insert a key that already exists
    result = myMap.insert({'x', 99});
    // Check that the insertion did not take place
    EXPECT_FALSE(result.second);
    // Check the size of the map remains the same
    EXPECT_EQ(myMap.size(), 1UL);
    // Check that the value was not changed
    EXPECT_EQ(result.first.getNode()->key_, 'x');
    EXPECT_EQ(result.first.getNode()->value_, 42);
}

TEST(MapTest, EraseFunction_CustomTypes) {
    s21::map<double, std::string> myMap = {
        {2.5, "apple"},
        {1.8, "banana"},
        {3.2, "orange"},
        {2.1, "grape"},
        {4.0, "kiwi"}
    };

    // Erase the element with key 3.2
 
    auto erasePosition = myMap.find(3.2);
    myMap.erase(erasePosition);

    std::map<double, std::string> stdMap = {
        {2.5, "apple"},
        {1.8, "banana"},
        {2.1, "grape"},
        {4.0, "kiwi"}
    };

    EXPECT_EQ(myMap.size(), stdMap.size());
    auto myMapIt = myMap.begin();
    auto stdMapIt = stdMap.begin();
    for (; myMapIt != myMap.end() && stdMapIt != stdMap.end(); ++myMapIt, ++stdMapIt) {
        EXPECT_EQ(myMapIt.getNode()->key_, stdMapIt->first);
        EXPECT_EQ(myMapIt.getNode()->value_, stdMapIt->second);
    }
    EXPECT_EQ(myMapIt, myMap.end());
    EXPECT_EQ(stdMapIt, stdMap.end());
}


TEST(MapTest, EraseFunction_ComplexTypes) {
    s21::map<std::string, int> myMap = {
        {"apple", 2},
        {"banana", 5},
        {"orange", 3},
        {"grape", 8},
        {"kiwi", 4},
        {"melon", 6}
    };

    // Erase the element with key "banana"
    std::string keyToErase = "banana";
    auto erasePosition = myMap.find(keyToErase);
    myMap.erase(erasePosition);

    // Insert new values
    myMap.insert({"pear", 7});
    myMap.insert({"peach", 1});

    // Erase the element with key "orange"
    keyToErase = "orange";
    erasePosition = myMap.find(keyToErase);
    myMap.erase(erasePosition);

    std::map<std::string, int> stdMap = {
        {"apple", 2},
        {"grape", 8},
        {"kiwi", 4},
        {"melon", 6},
        {"pear", 7},
        {"peach", 1}
    };

    EXPECT_EQ(myMap.size(), stdMap.size());
    auto myMapIt = myMap.begin();
    auto stdMapIt = stdMap.begin();
    for (; myMapIt != myMap.end() && stdMapIt != stdMap.end(); ++myMapIt, ++stdMapIt) {
        EXPECT_EQ(myMapIt.getNode()->key_, stdMapIt->first);
        EXPECT_EQ(myMapIt.getNode()->value_, stdMapIt->second);
    }
    EXPECT_EQ(myMapIt, myMap.end());
    EXPECT_EQ(stdMapIt, stdMap.end());
}


TEST(MapTest, SwapFunction_ComplexTypes) {
    // Create the first map
    s21::map<std::string, int> myMap1 = {
        {"apple", 2},
        {"banana", 5},
        {"orange", 3},
        {"grape", 8},
        {"kiwi", 4},
        {"melon", 6}
    };

    // Create the second map
    s21::map<std::string, int> myMap2 = {
        {"pear", 7},
        {"peach", 1},
        {"plum", 9}
    };

    // Swap the contents of the two maps
    myMap1.swap(myMap2);

    // Expected state after swap
    std::map<std::string, int> stdMap1 = {
        {"pear", 7},
        {"peach", 1},
        {"plum", 9}
    };

    std::map<std::string, int> stdMap2 = {
        {"apple", 2},
        {"banana", 5},
        {"orange", 3},
        {"grape", 8},
        {"kiwi", 4},
        {"melon", 6}
    };

    // Check the sizes of the maps after the swap
    EXPECT_EQ(myMap1.size(), stdMap1.size());
    EXPECT_EQ(myMap2.size(), stdMap2.size());

    // Check the contents of the first map after the swap
    auto myMap1It = myMap1.begin();
    auto stdMap1It = stdMap1.begin();
    for (; myMap1It != myMap1.end() && stdMap1It != stdMap1.end(); ++myMap1It, ++stdMap1It) {
        EXPECT_EQ(myMap1It.getNode()->key_, stdMap1It->first);
        EXPECT_EQ(myMap1It.getNode()->value_, stdMap1It->second);
    }
    EXPECT_EQ(myMap1It, myMap1.end());
    EXPECT_EQ(stdMap1It, stdMap1.end());

    // Check the contents of the second map after the swap
    auto myMap2It = myMap2.begin();
    auto stdMap2It = stdMap2.begin();
    for (; myMap2It != myMap2.end() && stdMap2It != stdMap2.end(); ++myMap2It, ++stdMap2It) {
        EXPECT_EQ(myMap2It.getNode()->key_, stdMap2It->first);
        EXPECT_EQ(myMap2It.getNode()->value_, stdMap2It->second);
    }
    EXPECT_EQ(myMap2It, myMap2.end());
    EXPECT_EQ(stdMap2It, stdMap2.end());
}
TEST(MapTest, ClearMap) {
    // Create an empty map
    s21::map<std::string, double> myMap;
    std::map<std::string, double> origMap;

    // Insert a key-value pair
    myMap.insert({"apple", 2.5});
    origMap.insert({"apple", 2.5});

    // Check if the maps are not empty and have the same size
    EXPECT_EQ(myMap.empty(), origMap.empty());
    EXPECT_EQ(myMap.size(), origMap.size());

    // Clear the maps
    myMap.clear();
    origMap.clear();

    // Check if the maps are empty and have the same size (0)
    EXPECT_EQ(myMap.empty(), origMap.empty());
    EXPECT_EQ(myMap.size(), origMap.size());
}


TEST(MapTest, MergeMap) {
    s21::map<int, std::string> myMap = {
        {1, "apple"},
        {2, "banana"}
    };
    s21::map<int, std::string> myMergeMap = {
        {3, "orange"},
        {4, "grape"}
    };
    myMap.merge(myMergeMap);

    std::map<int, std::string> origMap = {
        {1, "apple"},
        {2, "banana"}
    };

    std::map<int, std::string> origMergeMap = {
        {3, "orange"},
        {4, "grape"}
    };
    origMap.merge(origMergeMap);

    auto my_it = myMap.begin();
    auto orig_it = origMap.begin();
    for (; my_it != myMap.end() && orig_it != origMap.end(); ++my_it, ++orig_it) {
        EXPECT_EQ(my_it.getNode()->key_, orig_it->first);
        EXPECT_EQ(my_it.getNode()->value_, orig_it->second);
    }
    EXPECT_EQ(origMap.size(), myMap.size());
}


TEST(MapTest, AtAndOperatorSquareBrackets) {
    // Arrange
    s21::map<int, std::string> myMap;
    
    // Act
    myMap.insert({1, "One"});
    myMap.insert({2, "Two"});
    myMap.insert({3, "Three"});

    // Assert
    EXPECT_EQ(myMap.at(1), "One");
    EXPECT_EQ(myMap.at(2), "Two");
    EXPECT_EQ(myMap.at(3), "Three");

    // Test operator[]
    EXPECT_EQ(myMap[1], "One");
    EXPECT_EQ(myMap[2], "Two");
    EXPECT_EQ(myMap[3], "Three");

    // Modify values using operator[]
    myMap[1] = "Uno";
    myMap[2] = "Dos";
    myMap[3] = "Tres";

    // Assert modified values
    EXPECT_EQ(myMap.at(1), "Uno");
    EXPECT_EQ(myMap.at(2), "Dos");
    EXPECT_EQ(myMap.at(3), "Tres");
}


TEST(MapTest, Contains) {
    // Arrange
    s21::map<int, std::string> myMap;

    // Act
    myMap.insert({1, "One"});
    myMap.insert({2, "Two"});
    myMap.insert({3, "Three"});

    // Assert
    EXPECT_TRUE(myMap.contains(1));
    EXPECT_TRUE(myMap.contains(2));
    EXPECT_TRUE(myMap.contains(3));
    EXPECT_FALSE(myMap.contains(4));
    EXPECT_FALSE(myMap.contains(5));
}


TEST(MapTestTest, InsertKeyValueMultiple) {
  s21::map<char, int> myMap;
  // Insert 200 key-value pairs
  for (char key = 'A'; key <= 'Z'; ++key) {
    std::pair<s21::map<char, int>::iterator, bool> result = myMap.insert({key, static_cast<int>(key)});
    // Check that the insertion was successful
    EXPECT_TRUE(result.second);
    // Check the size of the map
    EXPECT_EQ(myMap.size(), static_cast<size_t>(key - 'A') + 1);
    // Check the inserted value
    EXPECT_EQ(result.first.getNode()->key_, key);
    EXPECT_EQ(result.first.getNode()->value_, static_cast<int>(key));
  }

  // Attempt to insert keys that already exist
  for (char key = 'A'; key <= 'Z'; ++key) {
    std::pair<s21::map<char, int>::iterator, bool> result = myMap.insert({key, 99});

    // Check that the insertion did not take place
    EXPECT_FALSE(result.second);
    // Check the size of the map remains the same
    EXPECT_EQ(myMap.size(), 26UL);
    // Check that the value was not changed
    EXPECT_EQ(result.first.getNode()->key_, key);
    EXPECT_EQ(result.first.getNode()->value_, static_cast<int>(key));
  }
}
