/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->right;
    t->right = y->left;
    y->left = t;
    _updateHeight(t);
    t = y;
   _updateHeight(t);
  // _updateHeight(y);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* y = t->left;
    // if(y != NULL) {
      t->left = y->right;
      y->right= t;
      _updateHeight(t);
      t = y;
    // }
      _updateHeight(t);
    // _updateHeight(y);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  if (subtree == NULL) return;
  int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

  if(balance == -2) {
      int balance1 = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(balance1 == -1) {
        rotateRight(subtree);
      }
      else
        rotateLeftRight(subtree);
    }
  else if(balance == 2) {
    int balance2 = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
    if(balance2 == 1) {
      rotateLeft(subtree);
    }
    else
      rotateRightLeft(subtree);
  }
  _updateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::_updateHeight(Node*& subtree)
{
  if (subtree == NULL) return;
  else  {
    subtree->height = 1 + std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    //error: (std::max || max)call to function 'max' that is neither visible in the template definition nor found by argument-dependent lookup
    // QUESTION: how to updat the height of red one
  }
}

// template <class K, class V>
// typename AVLTree<K, V>::Node *& AVLTree<K, V>::_find(Node*& subtree, const K & key) const
// {
//   if(subtree == NULL) return subtree; //base case *****
//   if(key == subtree->key) return subtree;
//   if(key < subtree->key) {
//     return _find(subtree->left, key);
//   }
//   else {
//     return _find(subtree->right, key);
//   }
// }

// template <class K, class V>
// typename AVLTree<K, V>::Node * AVLTree<K, V>::_findIop(Node*& subtree) {// QUESTION: THis is not a good method?
//   Node* t = subtree->left;
//   while(t->right != NULL) {
//     t = t->right;
//   }
//     // K k = t->key;
//     // Node *& iop = _find(subtree, k);
//     // return iop;
//     return t;
// }

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    // Node*& t = _find(subtree, key);
    // if (t == NULL) {
    //   t = new Node(key, value);
    //   return;
    // }
    // else
    //  t->value = value;
    if(subtree == NULL) {
      subtree = new Node(key, value);
      return; //*****
    }

    if(key < subtree->key) {
      insert(subtree->left, key, value);
    }
    else if(key > subtree->key) {
      insert(subtree->right, key, value);
    }
    else
      subtree->value = value;
      _updateHeight(subtree); //QUESTION: just update the subtree?? recursively used!
      rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove (subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove (subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            // Node* t = _findIop(subtree);
            Node* t = subtree->left;  //YOU CAN USE a pointer as the *& input!!!
              while(t->right != NULL) {
                t = t->right;
              }
            swap(subtree, t);
            remove(subtree->left, key);//!!!!!!!!!!!!!!
            // delete t;
            // t = NULL;
        } else {
            /* one-child remove */
            // your code here
            if(subtree->left != NULL) {
              Node* temp = subtree;
              subtree = subtree->left;
              delete temp;
              temp = NULL;
            }
            else {
              Node* temp = subtree;
              subtree = subtree->right;
              delete temp;
              temp = NULL;
            }
        }
          // _updateHeight(subtree);
          // rebalance(subtree);//QUESTION: HOW CAN i rebalance the whole tree?
        // your code here
    }
      _updateHeight(subtree);
      rebalance(subtree);//QUESTION: HOW CAN i rebalance the whole tree?
}
