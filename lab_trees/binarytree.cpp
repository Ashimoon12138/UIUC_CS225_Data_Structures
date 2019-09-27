/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
   mirror(root);
   std::cout << std::endl;
    //your code here
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot) {
  if (subRoot == NULL) {
    return;
  }
  Node* temp = subRoot->left;
  subRoot->left = subRoot->right;
  subRoot ->right = temp;
  mirror(subRoot->left);
  mirror(subRoot->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    bool isOrder = true;
    if (root == NULL)
    return true;
    else {
      InorderTraversal<T> lst(root); //When define this class we used template, so we include <T>
      /*QUESTION: 1.line119 call ++ in List::TreeTravesal; overload++ call add;
                  2.<T>must be T can not be int because the function title used <T>,bt this test used int as test case ;
                  3.if not in the title, you can use any kind of T, no relationship with this function, depends on how to use it*/
      typename TreeTraversal<T>::Iterator it = lst.begin();
      // FOR typename: it was used when declared a variable(when we have used template to defined the class it belongs)
      int smallLeft = (*it)->elem;

      for(it = lst.begin(); it!=lst.end(); ++it) { //QUESTION:Iterator can only use ++i why ++it /it ++ DONE!
        if (smallLeft > (*it)->elem)
        isOrder = false;
        else
        smallLeft = (*it)->elem;
      }
      return isOrder;
    }

    // else
    // return isOrderedIterative(root);
    // your code here

}

// template <typename T>
// bool BinaryTree<T>::isOrderedIterative(const Node* subRoot) const // QUESTION: worry?
// {
//   InorderTraversal<int> lst(subRoot); ///QUESTION:  T=???? push Node? why int?//
//   int smallLeft;
//
//   for(typename TreeTraversal<int>::Iterator it = lst.begin(); it!=lst.end(); ++it) { //why ++it /it ++
//     if (smallLeft > (*it)->elem)
//     isOrder = false;
//     else
//     smallLeft = (*it)->elem;
//   }
//   return isOrder;
// }
/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
  if (root==NULL) {
    return true;
  }
  else
  return  isOrderedRecursive(root);
    // your code here

}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* subRoot) const
{
     bool isOrder = true;

     if (subRoot->left != NULL) {
       isOrder = isOrder && isOrderedRecursive (subRoot->left);
       if (isOrderedBig(subRoot->left) > subRoot->elem)
         isOrder = false;
     }

     if (subRoot->right != NULL) {
       isOrder = isOrder && isOrderedRecursive (subRoot->right);
       if (subRoot->elem > isOrderedSmall(subRoot->right))
         isOrder = false;
     }
     return isOrder;
}

template <typename T>
int BinaryTree<T>::isOrderedBig(Node* subRoot) const {

  InorderTraversal<T> lst(subRoot);
  typename TreeTraversal<T>::Iterator it = lst.begin();
  int  biggest = (*it)->elem;
  for (it = lst.begin(); it != lst.end(); ++it) {

    if (biggest < ((*it)->elem) )
      biggest = (*it)->elem;

  }
   return biggest;
}

template <typename T>
int BinaryTree<T>::isOrderedSmall(Node* subRoot) const {

  InorderTraversal<T> lst(subRoot);
  typename TreeTraversal<T>::Iterator it = lst.begin();
  int smallest = (*it)->elem;
  for (it = lst.begin(); it != lst.end(); ++it) {

    if (smallest > ((*it)->elem) )
    smallest = (*it)->elem;

  }
   return smallest;
}




/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::getPaths(std::vector<std::vector<T>>& paths) const
{
    T array[1000];
    int index_ = 0;
    _Paths(root, paths, array, index_);
    // your code here

}

template <typename T>
void BinaryTree<T>::_Paths(Node* subRoot, std::vector<std::vector<T>>& paths, T array[], int index_ ) const
{
  if(subRoot == NULL)
  return;
  array[index_] = subRoot->elem;
  index_ ++;
  if(subRoot->left == NULL && subRoot->right == NULL) {
    std::vector<T> in;
    for(int i = 0; i< index_; i++) {
      in.push_back(array[i]);
    }
    paths.push_back(in);
  }
  else {
    _Paths(subRoot->left, paths, array, index_);
    _Paths(subRoot->right, paths, array, index_);
  }
  index_--;
}


/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    if(root == NULL)
    // your code here
    return -1;
    else
    return _sumDistances(-1, root, 0);
}

template <typename T>
int BinaryTree<T>::_sumDistances(int height, Node* subRoot, int sum) const {
  height++;
  sum += height;
  if(subRoot->left != NULL)
   sum = _sumDistances(height, subRoot->left, sum);
  if(subRoot->right != NULL)
   sum = _sumDistances(height, subRoot->right, sum);
  return sum;
}
