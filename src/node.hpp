#include <iostream>

enum Color {RED, BLACK};

template <typename T>
struct Node {
    T key; // holds the key
    Node *left; // pointer to left child
    Node *right; // pointer to right child
    Node *p; // pointer to the parent
    Color color; // color of the node
    bool sentinel = false; // true if the node is the NIL node

    // Constructors & destructors
    Node() : left(nullptr), right(nullptr), p(nullptr), color(RED) {}
    Node(T _value, Node *_p, Color _color) : key(_value), p(_p), color(_color), left(nullptr), right(nullptr) {}
    Node(T _value, Node *_p) : key(_value), p(_p), color(RED), left(nullptr), right(nullptr) {}
    explicit Node(const T &_value) : key(_value), p(nullptr), color(RED), left(nullptr), right(nullptr) {}
    explicit Node(bool _sentinel) : sentinel(_sentinel), p(nullptr), color(BLACK), left(nullptr), right(nullptr) {}
    
    ~Node() = default;

    // Utility functions
    Node *max() {
      return (right->is_nil()) ? this : right->max(); // returns the maximum node in the subtree rooted at this node
    }

    Node *min() {
      return (left->is_nil()) ? this : left->min(); // returns the minimum node in the subtree rooted at this node
    }

    Node *sibling() {
      if (p == nullptr)
        return nullptr;       
      return (is_left_child()) ? p->right : p->left;  // returns the sibling of current node
    }

    Node *successor() { // returns the successor of current node
      if (!right->is_nil())
        return right->min();
      
      Node<T> *x = this;
      Node<T> *y = p;
      while (!y->is_nil() && x == y->right) {
        x = y;
        y = y->p;
      }
      return y;
    }

    Node *predecessor() { // returns the predecessor of current node
      if (!left->is_nil())
        return left->max();
      
      Node<T> *x = this;
      Node<T> *y = p;
      while (!y->is_nil() && x == y->left) {
        x = y;
        y = y->p;
      }
      return y;
    }

    const bool is_left_child() const { // returns true if the current node is the left child of its parent
      return p != nullptr && p->left == this;
    }

    const bool is_right_child() const { // returns true if the current node is the right child of its parent
      return p != nullptr && p->right == this;
    }

    const bool is_root() const { // returns true if the current node is the root of the tree
      return p == nullptr;
    }

    const bool is_nil() const { // returns true if the current node is the NIL node
      return sentinel;
    }

    // Operators
    bool operator==(const Node<T> &other) const {
      return key == other.key && p == other.p;
    }

    bool operator==(const T& value) const {
      return key == value;
    }

    bool operator!=(const Node<T> &other) const {
      return key != other.key;
    }

    bool operator<(const Node<T> &other) const {
      return key < other.key;
    }

    bool operator>(const Node<T> &other) const {
      return key > other.key;
    }

    bool operator<=(const Node<T> &other) const {
      return key <= other.key;
    }

    bool operator>=(const Node<T> &other) const {
      return key >= other.key;
    }

    friend std::ostream &operator<<(std::ostream &os, const Node<T> &node) {
      os << node.key;
      return os;
    }

    friend std::istream &operator>>(std::istream &is, Node<T> &node) {
      is >> node.key;
      return is;
    }

};