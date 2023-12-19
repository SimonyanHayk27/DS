#include <iostream>
#include <cassert>

template<typename T>
class Set {
  struct Node {
    T value;
    Node *left;
    Node *right;
    Node *parent;
    int height;
    int balanceFactor;

    Node(const T &val) : value(val), left(nullptr), right(nullptr), parent(nullptr), height(1), balanceFactor(0) {}
  };

  Node *root{};
  size_t size_{};

  void updateHeightAndBalanceFactor(Node *node) {
    int leftHeight = (node->left) ? node->left->height : 0;
    int rightHeight = (node->right) ? node->right->height : 0;

    node->height = 1 + std::max(leftHeight, rightHeight);
    node->balanceFactor = leftHeight - rightHeight;
  }

  void rotateLeft(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left)
      y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
      root = y;
    else if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;

    y->left = x;
    x->parent = y;

    updateHeightAndBalanceFactor(x);
    updateHeightAndBalanceFactor(y);
  }

void rotateRight(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    updateHeightAndBalanceFactor(y);
    updateHeightAndBalanceFactor(x);
}

  void rebalance(Node *node) {
    while (node) {
      updateHeightAndBalanceFactor(node);

      if (node->balanceFactor > 1) {
        if (node->left->balanceFactor < 0)
          rotateLeft(node->left);
        rotateRight(node);
      } else if (node->balanceFactor < -1) {
        if (node->right->balanceFactor > 0)
          rotateRight(node->right);
        rotateLeft(node);
      }

      node = node->parent;
    }
  }

public:
  class iterator {
    Node *current;

  public:
    using value_type = T;
    using reference = T &;
    using pointer = T *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    iterator() : current(nullptr) {}

    iterator(Node *node) : current(node) {}

    reference operator*() const {
      return current->value;
    }

    pointer operator->() const {
      return &current->value;
    }

iterator &operator++() {
    if (current->right) {
        current = current->right;
        while (current->left)
            current = current->left;
    } else {
        Node *prev = nullptr;
        do {
            prev = current;
            current = current->parent;
        } while (current && prev == current->right);
    }
    return *this;
}
    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    friend bool operator==(iterator lhs, iterator rhs) {
      return lhs.current == rhs.current;
    }

    friend bool operator!=(iterator lhs, iterator rhs) {
      return !(lhs == rhs);
    }

    Node *getCurrent() const {
      return current;
    }
  };

  Set() : root(nullptr), size_(0) {}

  void insert(const T &value) {
    Node *newNode = new Node(value);

    if (!root) {
      root = newNode;
    } else {
      Node *current = root;
      Node *parent = nullptr;

      while (current) {
        parent = current;

        if (value < current->value)
          current = current->left;
        else if (value > current->value)
          current = current->right;
        else {
          delete newNode;
          return;
        }
      }

      newNode->parent = parent;
      if (value < parent->value)
        parent->left = newNode;
      else
        parent->right = newNode;

      rebalance(newNode);
    }

    size_++;
  }

  void print_inorder() {
    print_inorder(root);
    std::cout << std::endl;
  }

  iterator begin() {
    Node *current = root;
    while (current && current->left)
      current = current->left;
    return iterator(current);
  }

  iterator end() {
    return iterator(nullptr);
  }

  iterator find(const T &value) {
    Node *current = root;

    while (current) {
      if (value < current->value)
        current = current->left;
      else if (value > current->value)
        current = current->right;
      else
        return iterator(current);
    }

    return end();
  }

  void erase(iterator pos) {
    Node *nodeToDelete = pos.getCurrent();

    if (!nodeToDelete)
      return;

    if (!nodeToDelete->left) {
      transplant(nodeToDelete, nodeToDelete->right);
    } else if (!nodeToDelete->right) {
      transplant(nodeToDelete, nodeToDelete->left);
    } else {
      Node *successor = findMin(nodeToDelete->right);

      if (successor->parent != nodeToDelete) {
        transplant(successor, successor->right);
        successor->right = nodeToDelete->right;
        successor->right->parent = successor;
      }

      transplant(nodeToDelete, successor);
      successor->left = nodeToDelete->left;
      successor->left->parent = successor;
    }

    delete nodeToDelete;
    size_--;
  }

  ~Set() {
    destroy(root);
  }

private:
  void print_inorder(Node *node) {
    if (node) {
      print_inorder(node->left);
      std::cout << node->value << ' ';
      print_inorder(node->right);
    }
  }

  void destroy(Node *node) {
    if (node) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }

  Node *findMin(Node *node) {
    while (node->left)
      node = node->left;
    return node;
  }

  void transplant(Node *u, Node *v) {
    if (!u->parent)
      root = v;
    else if (u == u->parent->left)
      u->parent->left = v;
    else
      u->parent->right = v;

    if (v)
      v->parent = u->parent;
  }
};

int main() {
  Set<int> st;
  st.insert(10);
  st.insert(-10);
  st.insert(20);
  st.insert(10);
  st.insert(0);

  std::cout << "Inorder traversal: ";
  for (auto x : st) {
    std::cout << x << ' ';
  }
  std::cout << std::endl;

  auto it = st.find(10);
  std::cout << "Found element: " << *it << std::endl;

  st.erase(it);

  std::cout << "After erasing: ";
  for (auto x : st) {
    std::cout << x << ' ';
  }
  std::cout << std::endl;

  assert(st.find(3) == st.end());
  

  return 0;
}
