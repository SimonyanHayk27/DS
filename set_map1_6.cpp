#include <iostream>
#include <map>

class Trie {
  class TrieNode {
  public:
    std::map<char, TrieNode *> children;
    bool isEndOfWord;

    TrieNode() {
      isEndOfWord = false;
    }
  };

  TrieNode *root;

public:
  Trie() {
    root = new TrieNode();
  }

  ~Trie() {
    deleteTrie(root);
  }

  void deleteTrie(TrieNode *node) {
    for (auto &[ch, child] : node->children) {
      deleteTrie(child);
    }
    delete node;
  }

  void insert(const std::string &word) {
    TrieNode *current = root;
    for (char ch: word) {
      if (current->children.find(ch) == current->children.end()) {
        current->children[ch] = new TrieNode();
      }
      current = current->children[ch];
    }
    current->isEndOfWord = true;
  }

  bool startsWith(const std::string &prefix) {
    TrieNode *current = root;
    for (char ch : prefix) {
      if (current->children.find(ch) == current->children.end()) {
        return false;
      }
      current = current->children[ch];
    }
    return true;
  }
};

int main() {
  Trie trie;
  trie.insert("Hello");
  trie.insert("Hey");
  trie.insert("World");

  std::cout << trie.startsWith("Hell") << std::endl; // Вывод: true
  std::cout << trie.startsWith("abc") << std::endl;  // Вывод: false
  std::cout << trie.startsWith("Wo") << std::endl;   // Вывод: true

  return 0;
}
