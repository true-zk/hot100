/*
    1733. 需要教语言的最少人数
    medium
    在一个由 m 个用户组成的社交网络里，我们获取到一些用户之间的好友关系。
    两个用户之间可以相互沟通的条件是他们都掌握同一门语言。
    给你一个整数 n ，数组 languages 和数组 friendships ，它们的含义如下：

    总共有 n 种语言，编号从 1 到 n 。
    languages[i] 是第 i 位用户掌握的语言集合。
    friendships[i] = [u​​​​​​i​​​, v​​​​​​i] 表示 u​​​​​​​​​​​i​​​​​ 和 vi 为好友关系。
    你可以选择 一门 语言并教会一些用户，使得所有好友之间都可以相互沟通。请返回你 最少 需要教会多少名用户。

    请注意，好友关系没有传递性，也就是说如果 x 和 y 是好友，且 y 和 z 是好友， x 和 z 不一定是好友。

    n = 3, languages = [[2],[1,3],[1,2],[3]], friendships = [[1,4],[1,2],[3,4],[2,3]]
*/
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
    贪心：
        好友没有传递性，所以任何两个好友之间的languages必须有交集
        注意到，只能选一门语言，所以这个题其实很简单，直接找不能沟通的所有人的所有语言，
        然后找出会的人最多的语言就行了
*/
class Solution {
public:
    bool cantalk(vector<int> &langv, vector<int> &langu) {
        for (int &el1: langv) {
            for (int &el2: langu) {
                if (el1 == el2) {
                    return true;
                }
            }
        }
        return false;
    }

    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        unordered_set<int> cantTalk;
        for (auto &friendship: friendships) {
            if (!cantalk(languages[friendship[0] - 1], languages[friendship[1] - 1])) {
                cantTalk.insert(friendship[0]);
                cantTalk.insert(friendship[1]);
            }
        }

        int res = 0;
        int cantTalk_cnt = cantTalk.size();
        vector<int> langcnt(n, 0);
        for (auto &person: cantTalk){
            for (auto &lang: languages[person - 1]) {
                ++langcnt[lang - 1];
                res = max(res, langcnt[lang - 1]);
            }
        }

        return cantTalk_cnt - res;
    }
};


int main() {
    Solution sol;

    int n1 = 3;
    vector<vector<int>> languages1 = {{2},{1,3},{1,2},{3}};
    vector<vector<int>> friendships1 = {{1,4},{1,2},{3,4},{2,3}};
    cout << sol.minimumTeachings(n1, languages1, friendships1) << endl; // 2

    int n2 = 2;
    vector<vector<int>> languages2 = {{1},{2},{1,2}};
    vector<vector<int>> friendships2 = {{1,2},{1,3}, {2,3}};
    cout << sol.minimumTeachings(n2, languages2, friendships2) << endl; // 1

    int n3 = 4;
    vector<vector<int>> languages3 = {{1,2},{2,3},{3,4},{1,4}};
    vector<vector<int>> friendships3 = {{0,1},{1,2},{2,3},{0,3}};
    cout << sol.minimumTeachings(n3, languages3, friendships3) << endl; // 2

    return 0;
}