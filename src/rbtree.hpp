#include <iostream>
#include <functional>
#include <iterator>
#include "node.hpp"

template <typename T, typename CMP>
class RBTree {

  private:
    Node<T> *root; // pointer to the root of the tree
    Node<T> *nil; // pointer to the NIL node (sentinel)

    void preOrder(Node<T> *node) { // recursive function for preorder traversal
      if (node != nil) {
        std::cout << node->key << " ";
        preOrder(node->left);
        preOrder(node->right);
      }
    }

    void inOrder(Node<T> *node) { // recursive function for inorder traversal
      if (node != nil) {
        inOrder(node->left);
        std::cout << node->key << " ";
        inOrder(node->right);
      }
    }

    void postOrder(Node<T> *node) { // recursive function for postorder traversal
      if (node != nil) {
        postOrder(node->left);
        postOrder(node->right);
        std::cout << node->key << " ";
      }
    }

    // Rotations

    void LeftRotate(Node<T> *x) { // left rotation
      Node<T> *y = x->right;
      x->right = y->left;
      if (y->left != nil)
        y->left->p = x;
    
      y->p = x->p;
      if (x->p == nil)
        root = y;
      else if (x == x->p->left)
        x->p->left = y;
      else
        x->p->right = y;
    
      y->left = x;
      x->p = y;
    }

    void RightRotate(Node<T> *x) { // right rotation
      Node<T> *y = x->left;
      x->left = y->right;
      
      if (y->right != nil)
        y->right->p = x;
  
      y->p = x->p;
      if (x->p == nil)
        root = y;
      else if (x == x->p->right)
        x->p->right = y;
      else
        x->p->left = y;
      
      y->right = x;
      x->p = y;
    }

    // Insertion & Deletion Fixups

    void InsertFixup(Node<T> *node) { // fix the tree modified by the insertion
      
      Node<T> *y;

      while (node->p->color == RED) {
        
        if (node->p == node->p->p->left) {
          
          y = node->p->p->right;
          
          if (y->color == RED) {
            node->p->color = BLACK;
            y->color = BLACK;
            node->p->p->color = RED;
            node = node->p->p;
          } 
          else {
            if (node == node->p->right) {
              node = node->p;
              LeftRotate(node);
            }
            
            node->p->color = BLACK;
            node->p->p->color = RED;
            RightRotate(node->p->p);
          }
        }
        else {
          y = node->p->p->left;
          
          if (y->color == RED) {
            node->p->color = BLACK;
            y->color = BLACK;
            node->p->p->color = RED;
            node = node->p->p;  
          } 
          else {
            if (node == node->p->left) {
              node = node->p;
              RightRotate(node);
            }
            
            node->p->color = BLACK;
            node->p->p->color = RED;
            LeftRotate(node->p->p);
          }
        }
        
        if (node == root)
          break;
      }
      root->color = BLACK;
    }

    void DeleteFixup(Node<T> *x) { // fix the tree modified by the deletion
      
      Node<T> *w;
      while (x != root && x->color == BLACK) {
        
        if (x == x->p->left) {
          
          w = x->p->right;
          
          if (w->color == RED) {
            w->color = BLACK;
            x->p->color = RED;
            LeftRotate(x->p);
            w = x->p->right;
          }
          
          if (w->left->color == BLACK && w->right->color == BLACK) {
            w->color = RED;
            x = x->p;
          }
          else {
            
            if (w->right->color == BLACK) {
              w->left->color = BLACK;
              w->color = RED;
              RightRotate(w);
              w = x->p->right;
            }
            
            w->color = x->p->color;
            x->p->color = BLACK;
            w->right->color = BLACK;
            LeftRotate(x->p);
            x = root;
          }
        }
        else {
          
          w = x->p->left;
          
          if (w->color == RED) {
            w->color = BLACK;
            x->p->color = RED;
            RightRotate(x->p);
            w = x->p->left;
          }
          
          if (w->right->color == BLACK && w->left->color == BLACK) {
            w->color = RED;
            x = x->p;
          }
          else {
            
            if (w->left->color == BLACK) {
              w->right->color = BLACK;
              w->color = RED;
              LeftRotate(w);
              w = x->p->left;
            }
            
            w->color = x->p->color;
            x->p->color = BLACK;
            w->left->color = BLACK;
            RightRotate(x->p);
            x = root;
          }
        }
      }
      x->color = BLACK;
    }

    void Transplant(Node<T> *u, Node<T> *v) { // transplant the subtree rooted at node u with the subtree rooted at node v
      if (u->p == nil)
        root = v;
      else if (u == u->p->left)
        u->p->left = v;
      else
        u->p->right = v;

      v->p = u->p;
    }

    // Printing

    void printTree(const Node<T> *node, const std::string& prefix, bool isleft) {
      if (node != nil) {
        std::cout << prefix;
        
        if (node != root)
          std::cout << (isleft ? "├──" : "└──" );
        else 
          std::cout << "┌──";
        
        std::cout << node->key << "(" << (node->color == RED ? "R" : "B") << ")" << std::endl;

        printTree(node->left, prefix + (isleft ? "│   " : "    "), true);
        printTree(node->right, prefix + (isleft ? "│   " : "    "), false);
      }
    }
  
  public:
    
    // constructor and destructor
    RBTree() {
      nil = new Node<T>(true);
      root = nil;
    }

    RBTree(const Node<T> *node) {
      nil = new Node<T>(true);
      root = nil;
      Insert(node);
    }

    ~RBTree() {
      delete nil;
    }

    class const_iterator; // forward declaration

    const_iterator max() {return root == nil ? end() : const_iterator(root->max());}
    const_iterator min() {return root == nil ? end() : const_iterator(root->min());}
    const_iterator begin() const {return root->min();}
    const_iterator end() const {return nil;}
 
    // Insertion

    void Insert(int value) { // insert a new node with key "value"
      
      Node<T> *node = new Node<T>(value);
      node->left = nil;
      node->right = nil;
      
      Node<T> *y = nil;
      Node<T> *x = root;

      while (x != nil) {
        y = x;
        if (CMP()(value, x->key))
          x = x->left;
        else
          x = x->right;
      }

      node->p = y;
      if (y == nil)
        root = node;
      else if (CMP()(value, y->key))
        y->left = node;
      else
        y->right = node;

      if (node->p == nullptr) {
        node->color = BLACK;
        return;
      }

      InsertFixup(node);
    }


    // Deletion

    void Delete(Node<T> *z) { // delete the node z
      
      Node<T> *y = z;
      Color y_original_color = y->color;
      Node<T> *x;
      
      if (z->left == nil) {
        x = z->right;
        Transplant(z, z->right);
      }
      else if (z->right == nil) {
        x = z->left;
        Transplant(z, z->left);
      }
      else {
        y = Minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->p == z)
          x->p = y;
        else {
          Transplant(y, y->right);
          y->right = z->right;
          y->right->p = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
      }

      if (y_original_color == BLACK)
        DeleteFixup(x);

    }

    bool Delete(const T& value) { // delete the node with key "value"
      
      Node<T> *z = nil;
      Node<T> *node = root;
      while (node != nil) {
        
        if (node->key == value)
          z = node;
  
        if (CMP()(node->key, value))
          node = node->right;
        else
          node = node->left;
      }

      if (z == nil) {
        std::cout << "Value not found, couldn't delete." << std::endl;
        return false;
      }
      
      Node<T> *y = z;
      Color y_original_color = y->color;
      Node<T> *x;
      
      if (z->left == nil) {
        x = z->right;
        Transplant(z, z->right);
      } 
      else if (z->right == nil) {
        x = z->left;
        Transplant(z, z->left);
      } 
      else {
        y = Minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->p == z)
          x->p = y;
        else {
          Transplant(y, y->right);
          y->right = z->right;
          y->right->p = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
      }

      if (y_original_color == BLACK)
        DeleteFixup(x);

      std::cout << "Value deleted." << std::endl;
      return true;
    }

    // Minimum & Maximum
    
    Node<T> *Minimum(Node<T> *x) { // return the node with the minimum key in the subtree rooted at x
      while (x->left != nil)
        x = x->left;
      return x;
    }

    Node<T> *Maximum(Node<T> *x) { // return the node with the maximum key in the subtree rooted at x
      while (x->right != nil)
        x = x->right;
      return x;
    }

    // Successor & Predecessor

    Node<T> *Successor(Node<T> *x) { // return the node with the smallest key greater than x->key
      if (x->right != nil)
        return Minimum(x->right);
      
      Node<T> *y = x->p;
      while (y != nil && x == y->right) {
        x = y;
        y = y->p;
      }
      return y;
    }

    Node<T> *Predecessor(Node<T> *x) { // return the node with the largest key smaller than x->key
      if (x->left != nil)
        return Maximum(x->left);
      
      Node<T> *y = x->p;
      while (y != nil && x == y->left) {
        x = y;
        y = y->p;
      }
      return y;
    }

    // Search

    bool Contains(const T& value) { // return true if the tree contains a node with key "value"

      Node<T> *node = root;
      while (node != nil) {
        if (node->key == value) {
          std::cout << "Value found." << std::endl;
          return true;
        }
        if (CMP()(node->key, value))
          node = node->right;
        else
          node = node->left;
      }
      std::cout << "Value not found." << std::endl;
      return false;
    }

    Node<T> *Get_root(){ // return the root of the tree
		  return root;
	  }

    void print() { // print the tree
      printTree(root, "", false);
    }

    void printPostOrder() { // print the tree in post-order
      postOrder(root);
      std::cout << std::endl;
    }

    void printPreOrder() { // print the tree in pre-order
      preOrder(root);
      std::cout << std::endl;
    }
 
    void printInOrder() { // print the tree in-order
      inOrder(root);
      std::cout << std::endl;
    }
};

// definition of the inner class "const_iterator"

template <typename T, typename CMP>
class RBTree<T,CMP>::const_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {

  protected:
    Node<T> *Iterator;
  
  public:
    
    // Constructors & Destructor
    explicit const_iterator(void): Iterator(nullptr) {};
    const_iterator(Node<T> *node) : Iterator(node) {}
    const_iterator(const const_iterator &other) : Iterator(other.Iterator) {}

    ~const_iterator() {}

    // Operators
    
    const T* operator->() const {
      return &Iterator->key;
    }

    const T& operator*() const {
      return Iterator->key;
    }

    const_iterator& operator++() { // pre-increment the iterator
      Iterator = Iterator->successor();
      return *this;
    }

    const_iterator operator++(int) { // post-increment the iterator
      Node<T>* temp = Iterator;
      operator++();
      return const_iterator(temp);
    }

    const_iterator& operator--() { // pre-decrement the iterator
      Iterator = Iterator->predecessor();
      return *this;
    }

    const_iterator operator--(int) { // post-decrement the iterator
      Node<T>* temp = Iterator;
      operator--();
      return const_iterator(temp);
    }

    bool operator==(const const_iterator &other) const { // check if the iterators are equal
      return Iterator == other.Iterator;
    }

    bool operator!=(const const_iterator &other) const { // check if the iterators are not equal
      return Iterator != other.Iterator;
    }
};