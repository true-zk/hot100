#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }

        unordered_set<char> word_set;
        int res = 0;
        auto right = s.cbegin();
        // word_set.insert(*right);

        for (auto left = s.cbegin(); left != s.end(); ++left) {
            while (right != s.end() && !word_set.count(*right)) {
                word_set.insert(*right);
                ++right;  // here, will cause the right iter points to the next word.
            }

            int tmp = right - left;
            if (tmp > res) {
                res = tmp;
            }
            word_set.erase(*left);

        }

        return res;
    }
};