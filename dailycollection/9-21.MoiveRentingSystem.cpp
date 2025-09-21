/*
    1912. 设计电影租借系统
    hard

    你有一个电影租借公司和 n 个电影商店。你想要实现一个电影租借系统，它支持查询、预订和返还电影的操作。同时系统还能生成一份当前被借出电影的报告。
    所有电影用二维整数数组 entries 表示，其中 entries[i] = [shopi, moviei, pricei] 表示商店 shopi 有一份电影 moviei 的拷贝，租借价格为 pricei 。每个商店有 至多一份 编号为 moviei 的电影拷贝。
    系统需要支持以下操作：
    Search：找到拥有指定电影且 未借出 的商店中 最便宜的 5 个 。商店需要按照 价格 升序排序，如果价格相同，则 shopi 较小 的商店排在前面。如果查询结果少于 5 个商店，则将它们全部返回。如果查询结果没有任何商店，则返回空列表。
    Rent：从指定商店借出指定电影，题目保证指定电影在指定商店 未借出 。
    Drop：在指定商店返还 之前已借出 的指定电影。
    Report：返回 最便宜的 5 部已借出电影 （可能有重复的电影 ID），将结果用二维列表 res 返回，其中 res[j] = [shopj, moviej] 表示第 j 便宜的已借出电影是从商店 shopj 借出的电影 moviej 。res 中的电影需要按 价格 升序排序；如果价格相同，则 shopj 较小 的排在前面；如果仍然相同，则 moviej 较小 的排在前面。如果当前借出的电影小于 5 部，则将它们全部返回。如果当前没有借出电影，则返回一个空的列表。
*/
#include <iostream>
#include <vector>
#include <unordered_map>    // map
#include <set>              // set
#include <utility>          // tuple
#include <functional>       // hash
#include <initializer_list>  // initializer_list<>

using namespace std;


class MovieRentingSystem {
    struct Pairhash
    {
        size_t operator ()(const pair<int, int> &p) const {
            auto hashfn = hash<int> ();
            return (hashfn(p.first) << 16) ^ hashfn(p.second);
        }
    };
    unordered_map<pair<int, int>, int, Pairhash> mvshop_pri_map;  // {shop, moive} : price
    unordered_map<int, set<pair<int, int>>> unrented_map;  // moive: set {price, shop}
    set<tuple<int, int, int>> rented_set;  // price, shop, moive

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto &entry: entries) {
            mvshop_pri_map[pair<int, int> {entry[0], entry[1]}] = entry[2];
            unrented_map[entry[1]].emplace(entry[2], entry[0]);
        }
    }

    // return top5 low price unrented shop for the moive
    vector<int> search(int movie) {
        vector<int> res {};
        auto iter = unrented_map[movie].begin();
        auto end = unrented_map[movie].end();
        for (int i = 0; i < 5 && iter != end; ++i, ++iter) {
            res.push_back(iter->second);
        }
        return res;
    }

    void rent(int shop, int movie) {
        int price = mvshop_pri_map[pair<int, int> {shop, movie}];
        rented_set.emplace(price, shop, movie);
        unrented_map[movie].erase({price, shop});
    }

    void drop(int shop, int movie) {
        int price = mvshop_pri_map[{shop, movie}];
        unrented_map[movie].emplace(price, shop);
        rented_set.erase({price, shop, movie});
    }

    // return top5 low price rented {shop, moive}
    vector<vector<int>> report() {
        vector<vector<int>> res {};
        auto iter = rented_set.begin();
        auto end = rented_set.end();
        for (int i = 0; i < 5 && iter != end; ++i, ++iter) {
            // res.emplace_back(get<1>(*iter), get<2>(*iter));
            // 注意，这里必须是initializer显示指定，因为vetor的初始化函数不止一种类型
            // 传入(2, 3)可能被理解成vector<int>(size_t n, int v)复制2个3！
            res.emplace_back(initializer_list<int>{get<1>(*iter), get<2>(*iter)});
        }
        return res;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */