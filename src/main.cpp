#include <iostream>
#include <functional>
#include "rbtree.hpp"

int main() {
  RBTree<int, std::less<int>> tree;
  tree.Insert(8);
  tree.Insert(18);
  tree.Insert(5);
  tree.Insert(15);
  tree.Insert(17);
  tree.Insert(25);
  tree.Insert(40);
  tree.Insert(80);
  
  tree.Delete(18);
  tree.Contains(40);
  std::cout << "\n";

  tree.print();
  std::cout << "\n";

  RBTree<int, std::less<int>>::const_iterator it = tree.begin();
  RBTree<int, std::less<int>>::const_iterator it_end = tree.end();

  std::cout << "First value: " << *it << "\n";
  std::cout << "Second value: " << *(++it) << "\n";
  std::cout << "Previous value: " << *(--it) << "\n\n";


  while (it != it_end) {
    std::cout << "value: " << *it << "\n";
    ++it;
  }

  return 0;
}
