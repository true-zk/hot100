/*
    966. 元音拼写检查器
    medium

    在给定单词列表 wordlist 的情况下，我们希望实现一个拼写检查器，将查询单词转换为正确的单词。
    对于给定的查询单词 query，拼写检查器将会处理两类拼写错误：

    大小写：如果查询匹配单词列表中的某个单词（不区分大小写），则返回的正确单词与单词列表中的大小写相同。
    例如：wordlist = ["yellow"], query = "YellOw": correct = "yellow"
    例如：wordlist = ["Yellow"], query = "yellow": correct = "Yellow"
    例如：wordlist = ["yellow"], query = "yellow": correct = "yellow"
    元音错误：如果在将查询单词中的元音 ('a', 'e', 'i', 'o', 'u')  分别替换为任何元音后，能与单词列表中的单词匹配（不区分大小写），则返回的正确单词与单词列表中的匹配项大小写相同。
    例如：wordlist = ["YellOw"], query = "yollow": correct = "YellOw"
    例如：wordlist = ["YellOw"], query = "yeellow": correct = "" （无匹配项）
    例如：wordlist = ["YellOw"], query = "yllw": correct = "" （无匹配项）

    此外，拼写检查器还按照以下优先级规则操作：
    当查询完全匹配单词列表中的某个单词（区分大小写）时，应返回相同的单词。
    当查询匹配到大小写问题的单词时，您应该返回单词列表中的第一个这样的匹配项。
    当查询匹配到元音错误的单词时，您应该返回单词列表中的第一个这样的匹配项。
    如果该查询在单词列表中没有匹配项，则应返回空字符串。

    给出一些查询 queries，返回一个单词列表 answer，其中 answer[i] 是由查询 query = queries[i] 得到的正确单词。

*/
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <iostream>

using namespace std;


// 查询问题，用set来把时间复杂度降低到O(1)
// 1. idwords, identical to original words
// 2. lowerwords, equals to lower type of original words
// 3. rpvowelwords, replace vowels to *, and check if equals (all lower type)
class Solution {
    unordered_set<char> vowels {'a', 'e', 'i', 'o', 'u'};
    string lowerize(string s) {
        for (auto &c: s) {
            if (c >= 'A' && c <= 'Z') c = static_cast<char>('a' + c - 'A');
        }
        return s;
    }
    string rpvowels(string s) {
        string ls = lowerize(s);
        for (auto &c: ls) {
            if (vowels.count(c)) c = '*';
        }
        return ls;
    }
public:
    vector<string> spellchecker(vector<string> &wordlist, vector<string> &queries) {
        unordered_set<string> idwords_set;
        unordered_map<string, string> lowerwords_map;  // lower: origin
        unordered_map<string, string> rpvowels_map;            // rpvowel: origin
        for (auto &word: wordlist) {
            idwords_set.insert(word);
            string lw = lowerize(word);
            string vw = rpvowels(word);
            if (!lowerwords_map.count(lw)) lowerwords_map[lw] = word;  // keep the 1st origin
            if (!rpvowels_map.count(vw)) rpvowels_map[vw] = word;      // keep the 1st origin
        }
        vector<string> res;
        for (auto &query: queries) {
            if (idwords_set.count(query)) res.push_back(query);
            else {
                string lq = lowerize(query);
                string vq = rpvowels(query);
                if (lowerwords_map.count(lq)) res.push_back(lowerwords_map[lq]);
                else if (rpvowels_map.count(vq)) res.push_back(rpvowels_map[vq]);
                else res.push_back("");
            }
        }
        return res;
    }
};


//////////////////////////////////////////////////////////
// 题面不复杂
// 但是直接大模拟每次查询是O(n)，总时间复杂度为O(n^2)，超时
class Solution_overtime {
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
public:

    char lowerize(char c) {
        if (c >= 'A' && c <= 'Z') return static_cast<char>('a' + c - 'A');
        else return c;
    }

    // return priority
    // -1: not match
    // 0: vowel match
    // 1: lower or upper match
    // 2: totally match
    int compareWords(string &lstr, string &rstr) {
        if (lstr.size() != rstr.size()) return -1;

        int priority = 2;
        for (int i = 0; i < lstr.size(); ++i) {
            if (lstr[i] == rstr[i]) continue;  // 2

            char lc = lowerize(lstr[i]);
            char rc = lowerize(rstr[i]);
            if (lc == rc) {  // 2 -> 1
                priority = priority > 1 ? 1 : priority;
                continue;
            }
            else if (vowels.count(lc) && vowels.count(rc)) {  // 2;1 -> 0
                priority = priority > 0 ? 0 : priority;
                continue;
            }
            else {
                return -1;
            }
        }
        return priority;
    }

    string checkQuery(vector<string> &wordlist, string query) {
        int flag = -1;
        string cur = "";
        for (auto &word: wordlist) {
            int tmp_flag = compareWords(word, query);
            if (tmp_flag > flag) {
                flag = tmp_flag;
                cur = word;
            }
        }
        return cur;
    }

    vector<string> spellchecker(vector<string>& wordlist, vector<string>& queries) {
        vector<string> res;
        for (auto & q: queries) {
            res.push_back(checkQuery(wordlist, q));
        }
        return res;
    }
};


int main() {
    Solution sol;
    vector<string> wordlist = {"KiTe","kite","hare","Hare"};
        vector<string> queries1 = {"HARE"};
    // vector<string> queries1 = {"kite","Kite","KiTe","Hare","HARE","Hear","hear","keti","keet","keto"};
    auto res1 = sol.spellchecker(wordlist, queries1);
    for (auto &s : res1) cout << "\"" << s << "\" ";
    cout << endl;

    // vector<string> wordlist2 = {"Apple", "banana", "Orange"};
    // vector<string> queries2 = {"apple", "APPLE", "applo", "banena", "orange", "orenge", "pear"};
    // auto res2 = sol.spellchecker(wordlist2, queries2);
    // for (auto &s : res2) cout << "\"" << s << "\" ";
    // cout << endl;

    return 0;
}