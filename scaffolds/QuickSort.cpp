#include <iostream>
#include <vector>


// Lomuto (pivot = arr[right], 单指针)
// 单个指针指向比pivot小的右边界，
// 即过程中是这样的：[l, i] [i + 1, r - 1] [r], r为pivot
// - [l, i] < pivot，已经处理好
// - 如果当前(j)比pivot小，将其放到左边区间，交换arr[i+1]和arr[j]
int Lomutopartition(std::vector<int> &arr, int l, int r) {
    int pivot = arr[r];  // Lomuto use right elem as pivot.
    int i = l - 1;       // Uses 1 pointer. 指向小于pivot的最后一个位置
    // i 指向了已处理部分的右边界

    for (int j = l; j < r; ++j) {
        if (arr[j] <= pivot) {  // <= pivot的放左边；这里可以写成<，但是<=会让==pivot的分布在两侧，而不是集中在右侧，如果有重复元素，<=会更好
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    // 最后，[l, i]都比pivot小，那自然，pivot应该放到 i + 1
    std::swap(arr[i + 1], arr[r]);
    return i + 1;
}


void LomutoQuickSort(std::vector<int> &arr, int l, int r){
    if (l < r) {
        int p = Lomutopartition(arr, l, r);  // [l, p - 1] p [p + 1, r]
        LomutoQuickSort(arr, l, p - 1);
        LomutoQuickSort(arr, p + 1, r);
    }
}


// Hoare (pivot = arr[left], 双指针)
// Hoare算法返回的分界点j只保证了
// - [l, j] <= pivot
// - [j+1, r] >= pivot
// 但是不保证j的位置是pivot!
int Hoarepartition(std::vector<int> &arr, int l, int r) {
    int pivot = arr[l];
    int i = l - 1;
    int j = r + 1;
    while (true)
    {
        do { ++i; } while (arr[i] < pivot);  // i 指向左边第一个>=pivot的
        do { --j; } while (arr[j] > pivot);  // j 指向右边第一个<=pivot的
        
        if (i >= j) return j;  // 相遇的时候返回划分位置

        std::swap(arr[i], arr[j]);
    }
}


void HoareQuickSort(std::vector<int> &arr, int l, int r) {
    if (l < r) {
        int p = Hoarepartition(arr, l, r);  // [l, p] [p + 1, r]
        HoareQuickSort(arr, l, p);      // 
        HoareQuickSort(arr, p + 1, r);  // 
    }
}


int main() {
    std::vector<int> v = {3, 6, 8, 10, 1, 2, 1};

    LomutoQuickSort(v, 0, v.size() - 1);

    std::cout << "Sorted: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    v = {3, 6, 8, 10, 1, 2, 1};

    HoareQuickSort(v, 0, v.size() - 1);

    std::cout << "Sorted: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}