#include "array.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(ArrayTest, Constructors) {
    Array<int> arr1;
    EXPECT_EQ(arr1.size(), 0);
    EXPECT_GE(arr1.capacity(), 8);

    Array<int> arr2(20);
    EXPECT_EQ(arr2.size(), 0);
    EXPECT_GE(arr2.capacity(), 20);
}

TEST(ArrayTest, InsertAtEnd) {
    Array<int> arr;

    arr.insert(1);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 1);

    arr.insert(2);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[1], 2);

    arr.insert(3);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, InsertAtIndex) {
    Array<int> arr;

    arr.insert(1);
    arr.insert(3);
    arr.insert(1, 2);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);

    arr.insert(0, 0);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr.size(), 4);
}

// Тест удаления
TEST(ArrayTest, Remove) {
    Array<int> arr;

    for (int i = 0; i < 5; ++i) {
        arr.insert(i);
    }

    arr.remove(2);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);

    arr.remove(0);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 4);

    arr.remove(arr.size() - 1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, SubscriptOperator) {
    Array<int> arr;

    arr.insert(10);
    arr.insert(20);
    arr.insert(30);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);

    const Array<int>& const_arr = arr;
    EXPECT_EQ(const_arr[0], 10);
}

TEST(ArrayTest, AutoResize) {
    Array<int> arr(2);

    arr.insert(1);
    arr.insert(2);
    arr.insert(3);

    EXPECT_EQ(arr.size(), 3);
    EXPECT_GE(arr.capacity(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, CopySemantics) {
    Array<int> arr1;
    arr1.insert(1);
    arr1.insert(2);
    arr1.insert(3);

    Array<int> arr2 = arr1;
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);

    arr2[0] = 99;
    EXPECT_EQ(arr1[0], 1);
    EXPECT_EQ(arr2[0], 99);

    Array<int> arr3;
    arr3 = arr1;
    EXPECT_EQ(arr3.size(), 3);
    EXPECT_EQ(arr3[1], 2);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> arr1;
    arr1.insert(1);
    arr1.insert(2);

    Array<int> arr2 = std::move(arr1);
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr1.size(), 0);

    Array<int> arr3;
    arr3 = std::move(arr2);
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr3[1], 2);
    EXPECT_EQ(arr2.size(), 0);
}

TEST(ArrayTest, Iterator) {
    Array<int> arr;
    for (int i = 1; i <= 5; ++i) {
        arr.insert(i * 10);
    }

    auto it = arr.iterator();
    EXPECT_EQ(it.get(), 10);

    it.next();
    EXPECT_EQ(it.get(), 20);

    int count = 0;
    for (auto it = arr.iterator();; it.next()) {
        count++;

        if (!it.hasNext()) {
            break;
        }
    }
    EXPECT_EQ(count, 5);

    for (auto it = arr.iterator();; it.next()) {
        it.set(it.get() * 2);

        if (!it.hasNext()) {
            break;
        }
    }
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[4], 100);
}

TEST(ArrayTest, ReverseIterator) {
    Array<int> arr;
    for (int i = 1; i <= 3; ++i) {
        arr.insert(i);
    }

    auto rit = arr.reverseIterator();
    EXPECT_EQ(rit.get(), 3);

    rit.next();
    EXPECT_EQ(rit.get(), 2);

    rit.next();
    EXPECT_EQ(rit.get(), 1);
    EXPECT_FALSE(rit.hasNext());
}

class TestStruct {
   public:
    int id_;
    std::string name_;

    TestStruct(int id = 0, const std::string& name = "") {
        id_ = id;
        name_ = name;
    }

    bool operator==(const TestStruct& other) const { return id_ == other.id_ && name_ == other.name_; }
};

TEST(ArrayTest, CustomType) {
    Array<TestStruct> arr;

    arr.insert(TestStruct(1, "Alice"));
    arr.insert(TestStruct(2, "Bob"));

    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0].id_, 1);
    EXPECT_EQ(arr[0].name_, "Alice");

    Array<TestStruct> arr2 = std::move(arr);
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr2[1].name_, "Bob");
}

TEST(ArrayTest, Clear) {
    Array<int> arr;

    for (int i = 0; i < 10; ++i) {
        arr.insert(i);
    }

    EXPECT_EQ(arr.size(), 10);

    while (arr.size() > 0) {
        arr.remove(0);
    }

    EXPECT_EQ(arr.size(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
