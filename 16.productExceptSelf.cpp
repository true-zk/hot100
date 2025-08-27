#include <vector>
#include <iostream>
using std::vector;
using std::cout; using std::endl;
using std::cin;


class Solution1 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix_prod(nums.size(), 1);
        vector<int> suffix_prod(nums.size(), 1);
        for (int i = 1; i < n; ++i) {
            prefix_prod[i] = prefix_prod[i - 1] * nums[i - 1];
        }
        for (int i = n - 2; i >= 0; --i) {
            suffix_prod[i] = suffix_prod[i + 1] * nums[i + 1];
        }
        for (int i = 0; i < n; ++i) {
            prefix_prod[i] = prefix_prod[i] * suffix_prod[i];
        }
        return prefix_prod;
    }
};


class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);
        for (int i = 1; i < n; ++i) {
            res[i] = res[i - 1] * nums[i - 1];  // prefix
        }
        int suffix = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            res[i] = res[i] * suffix;
            suffix = suffix * nums[i];
        }
        return res;
    }
};


class Solution3 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        res[0] = 1;  // rm init time consume
        for (int i = 1; i < n; ++i) {
            res[i] = res[i - 1] * nums[i - 1];  // prefix
        }
        int suffix = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            res[i] = res[i] * suffix;
            suffix = suffix * nums[i];
        }
        return res;
    }
};


int main() {
    cout << "Plz input a array: ";
    vector<int> nums;
    int tmp;
    while (cin >> tmp)
    {
        nums.push_back(tmp);
    }
    Solution2 sol;
    vector<int> result = sol.productExceptSelf(nums);
    cout << "The result is: ";
    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}