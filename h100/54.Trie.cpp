/*
    medium
    [Trie] 前缀树，就是把字符串拆了，每个字母一个节点的前缀树
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Trie {
public:
    Trie(): children(26), isEnd(false) {}
    
    // 从根开始遍历树，如果没有该字符就插入
    void insert(string word) {
        Trie *node = this;
        for (char ch: word) {
            int index = ch - 'a';
            // 没有这个字符，加入
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie();
            }
            // 沿着这条前缀向下遍历
            node = node->children[index];
        }
        // 最后记得end标记
        node->isEnd = true;
    }
    
    bool search(string word) {
        Trie *node = this;
        for (char ch: word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) return false;
            else node = node->children[index];
        }
        return true && node->isEnd;  // 还必须是end结尾才算有这个单词
    }
    
    bool startsWith(string prefix) {
        Trie *node = this;
        for (char ch: prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) return false;
            else node = node->children[index];
        }
        return true;
    }
private:
    vector<Trie*> children;
    bool isEnd;
};


// 注意到search和startWith操作基本一致，可以合并一下
class Trie2 {
public:
    Trie2(): isEnd(false), children(26) {}

    void insert(string word) {
        Trie2 *node = this;
        for (char ch: word) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new Trie2;
            }
            node = node->children[index];
        }
        node->isEnd = true;
    }

    bool search(string word) {
        Trie2 *node = searchPrefix(word);
        return (node != nullptr) && (node->isEnd);
    }

    bool startsWith(string prefix) {
        return searchPrefix(prefix) != nullptr;
    }
private:
    bool isEnd;
    vector<Trie2*> children;
    Trie2 *searchPrefix(string &prefix) {
        Trie2 *node = this;
        for (char ch: prefix) {
            int index = ch - 'a';
            if (node->children[index] == nullptr) return nullptr;
            node = node->children[index];
        }
        return node;
    }
};


int main() {
    Trie2 trie;

    trie.insert("apple");
    cout << boolalpha << trie.search("apple") << endl;   // true
    cout << boolalpha << trie.search("app") << endl;     // false
    cout << boolalpha << trie.startsWith("app") << endl; // true
    trie.insert("app");
    cout << boolalpha << trie.search("app") << endl;     // true

    return 0;
}