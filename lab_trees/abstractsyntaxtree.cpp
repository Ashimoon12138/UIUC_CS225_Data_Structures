#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */

double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    if(root == NULL) {
      return 0;
    }
    else
    return _eval(root);
}


double AbstractSyntaxTree::_eval(Node* subRoot) const {
  if (subRoot == NULL)
  return 0;

  else if (subRoot->left == NULL && subRoot->right == NULL)
  return std::stod(subRoot->elem);

  else if (subRoot->elem == "+")
  return (_eval(subRoot->left) + _eval(subRoot->right));

  else if (subRoot->elem == "-")
  return (_eval(subRoot->left) - _eval(subRoot->right));

  else if (subRoot->elem == "*")
  return (_eval(subRoot->left) * _eval(subRoot->right));

  else if (subRoot->elem == "/")
  return (_eval(subRoot->left) / _eval(subRoot->right));

  else
  return 0;

}
