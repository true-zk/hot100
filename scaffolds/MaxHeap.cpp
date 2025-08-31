#include <iostream>
#include <vector>
#include <stdexcept>


class MaxHeap {
    std::vector<int> data;

    // 从当前位置不断和其父节点比较，
    // 如果父>=子，ok
    // 如果父<子，交换，然后从父的位置继续，直到堆顶
    void sift_up(size_t i) {
        while (i > 0)
        {
            size_t p = (i - 1) / 2; // 父节点
            if (data[p] >= data[i]) break;  // 父 >= 子，ok
            std::swap(data[p], data[i]);    // 父 < 子，交换
            i = p;  // 继续
        }
    }

    // 比较父，左子，右子，最大的变成父，
    // - 最大的是左子，那么步进到 左子，继续
    // - 最大的是右子，步进到 右子， 继续
    // - 最大的是父，停止
    void sift_down(size_t i) {
        size_t n = data.size();
        while (true)
        {
            size_t l = 2 * i + 1; // 左孩子idx
            size_t r = 2 * i + 2; // 右孩子idx
            size_t largest = i;

            if (l < n && data[l] > data[largest]) largest = l;
            if (r < n && data[r] > data[largest]) largest = r;
            // 父最大，满足
            if (largest == i) break;
            // 否则，父和最大的孩子换，并更新i为孩子，继续
            std::swap(data[i], data[largest]);
            i = largest;
        }   
    }

    void build_heap() {
        if (data.empty()) return;
        // 从第一个非孩子开始，下沉堆，直到顶
        for (int i = static_cast<int>(data.size()) / 2 - 1; i >= 0; --i) {
            sift_down(i);
        }
    }

public:
    MaxHeap () = default;

    // 从现有的vector，原地构建最大堆
    explicit MaxHeap (std::vector<int> &vec): data(vec) {
        build_heap();
    }

    void push(int x) {
        data.push_back(x);
        sift_up(data.size() - 1);  // 插入之后重新维护, logn
    }

    int top() const {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        return data[0];
    }

    void pop() {
        if (data.empty()) throw std::out_of_range("Heap is empty");
        data[0] = data.back();  // 最后一个元素放到堆顶
        data.pop_back();
        if (!data.empty()) sift_down(0);  // 重新维护
    }

    bool empty() const {return data.empty();}
    size_t size() const {return data.size();}
};


int main() {
    std::vector<int> v = {3, 1, 6, 5, 2, 4};

    // 方式1：构造时传入
    MaxHeap heap1(v);

    std::cout << "Heap1 top: " << heap1.top() << "\n"; // 输出 6
}