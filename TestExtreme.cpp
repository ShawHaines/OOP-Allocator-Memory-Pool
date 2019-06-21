#include <chrono>
#include <iostream>
#include <random>
#include <vector>
// #include "../HxzAllocator/HxzAllocator/Hxzallocator.h"
#include "Allocator.h"
// include header of your allocator here
template <class T>
using MyAllocator =
    std::allocator<T>;  // replace the std::allocator with your allocator
using Point2D = std::pair<int, int>;
const int TestSize = 10000;

const int PickSize = 1000;
const int SmallSize = 100;
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);
    std::uniform_int_distribution<> dis_small(1, SmallSize);

    // vector creation
    using IntVec = std::vector<int, MyAllocator<int>>;
    std::vector<IntVec, MyAllocator<IntVec>> vecints1(TestSize);
    for (int i = 0; i < TestSize; i++) vecints1[i].resize(128);

    std::vector<IntVec, MyAllocator<IntVec>> vecints2(TestSize);
    for (int i = 0; i < TestSize; i++) vecints2[i].resize(32);

    using PointVec = std::vector<Point2D, MyAllocator<Point2D>>;
    std::vector<PointVec, MyAllocator<PointVec>> vecpts1(TestSize);
    for (int i = 0; i < TestSize; i++) vecpts1[i].resize(128);
    std::vector<PointVec, MyAllocator<PointVec>> vecpts2(TestSize);
    for (int i = 0; i < TestSize; i++) vecpts2[i].resize(32);

    // vector resize
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < PickSize; i++) {
        int idx = dis(gen) - 1;
        int size = dis_small(gen);
        vecints1[idx].resize(64);
        vecints2[idx].resize(64);
        vecpts1[idx].resize(64);
        vecpts2[idx].resize(64);
    }

    // vector element assignment
    {
        int val = 10;
        int idx1 = dis(gen) - 1;
        int idx2 = vecints1[idx1].size() / 2;
        vecints1[idx1][idx2] = val;
        if (vecints1[idx1][idx2] == val)
            std::cout << "correct assignment in vecints: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecints: " << idx1
                      << std::endl;
    }
    {
        Point2D val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = vecpts2[idx1].size() / 2;
        vecpts2[idx1][idx2] = val;
        if (vecpts2[idx1][idx2] == val)
            std::cout << "correct assignment in vecpts2: " << idx1 << std::endl;
        else
            std::cout << "incorrect assignment in vecpts2: " << idx1
                      << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds."
              << std::endl;

    return 0;
}