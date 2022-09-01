# Red-Black Trees

A red–black tree is a type of self-balancing binary search tree, a data structure used in computer science. It is complex, but has good worst-case running time for its operations and is efficient in practice: it can search, insert, and delete in $O(log n)$ time, where $n$ is the total number of elements in the tree. A red–black tree is a binary search tree that inserts and deletes in such a way that the tree is always reasonably balanced. It has the following requirements:

- every node is either red or black;
- the root is black;
- every leaf ( $NIL$ ) is black;
- if a node is red, then its children are black;
- for each node $x$, all the simple paths from x to descendant leaves contains the same number of black nodes.
