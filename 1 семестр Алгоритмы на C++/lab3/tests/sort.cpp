#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

#include <gtest/gtest.h>

#include "sort.hpp"

TEST(SortTest, PrimitivesValid) {
    size_t N = 1000;
    std::vector<int32_t> arr(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100000, 100000);

    for (size_t i = 0; i < N; ++i) {
        arr[i] = dis(gen);
    }

    auto comp = [](int32_t a, int32_t b) {
        return a < b;
    };

    std::vector<int32_t> arr1 = arr;
    std::sort(arr1.begin(), arr1.end(), comp);

    sort(arr.begin(), arr.end(), comp);

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end(), comp));
    EXPECT_EQ(arr, arr1);
}

class TestStruct {
   public:
    int id_;
    std::string name_;

    explicit TestStruct(int id = 0, const std::string& name = "") {
        id_ = id;
        name_ = name;
    }

    bool operator==(const TestStruct& other) const { return id_ == other.id_ && name_ == other.name_; }
};

TEST(SortTest, CustomTypeValid) {
    size_t N = 1000;
    std::vector<TestStruct> arr(N);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-100000, 100000);

    for (size_t i = 0; i < N; ++i) {
        arr[i] = TestStruct(dis(gen));
    }

    auto comp = [](TestStruct a, TestStruct b) {
        return a.id_ < b.id_;
    };

    std::vector<TestStruct> arr1 = arr;
    std::sort(arr1.begin(), arr1.end(), comp);

    sort(arr.begin(), arr.end(), comp);

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end(), comp));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, Empty) {
    std::vector<int32_t> arr;
    std::vector<int32_t> arr1;
    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);

    int32_t* empty = nullptr;
    sort(empty, empty, [](int32_t a, int32_t b) { return a < b; });
    EXPECT_TRUE(std::is_sorted(empty, empty));
    EXPECT_EQ(empty, nullptr);
}

TEST(SortTest, OneElement) {
    std::vector<int32_t> arr = {1};
    std::vector<int32_t> arr1 = arr;
    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, ReverseOrder) {
    std::vector<int32_t> arr = {5, 4, 3, 2, 1};
    std::vector<int32_t> arr1 = {1, 2, 3, 4, 5};

    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, FirstUnsorted) {
    std::vector<int32_t> arr = {5, 1, 2, 3, 4};
    std::vector<int32_t> arr1 = {1, 2, 3, 4, 5};

    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, LastUnsorted) {
    std::vector<int32_t> arr = {2, 3, 4, 5, 1};
    std::vector<int32_t> arr1 = {1, 2, 3, 4, 5};

    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, AlreadySorted) {
    std::vector<int32_t> arr = {1, 2, 3, 4, 5};
    std::vector<int32_t> arr1 = arr;

    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

TEST(SortTest, SameElements) {
    std::vector<int32_t> arr = {5, 5, 5, 5, 5};
    std::vector<int32_t> arr1 = arr;

    sort(arr.begin(), arr.end(), [](int32_t a, int32_t b) { return a < b; });

    EXPECT_TRUE(std::is_sorted(arr.begin(), arr.end()));
    EXPECT_EQ(arr, arr1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
