#include <bits/stdc++.h>

using namespace std;

class Trie {
private:
    struct TrieNode {
        TrieNode *children[26] = {nullptr};
        bool isEnd;
    };

    TrieNode *root;

public:
    Trie() { root = new TrieNode(); }

    // 检查word的每个元素是否在树中
    void insert(string word) {
        TrieNode *node = root;
        for (char c : word) {
            int index = c - 'a';
            // 创建新节点
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEnd = true;
    }

    // 检查word中的每个元素是否在树中，并且判断最后一个字符的isend
    bool search(string word) {
        TrieNode *node = root;
        for (char c : word) {
            int index = c - 'a';
            // 不在
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return node->isEnd;
    }

    // 检查word中的每个元素是否在树中,不用判断最后一个字符
    bool startsWith(string prefix) {
        TrieNode *node = root;
        for (char c : prefix) {
            int index = c - 'a';
            // 不在
            if (node->children[index] == nullptr) {
                return false;
            }
            node = node->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */