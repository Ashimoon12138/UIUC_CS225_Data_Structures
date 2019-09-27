#include "dsets.h"

DisjointSets::DisjointSets(int num) {
  this->addelements(num);
}

DisjointSets::DisjointSets(const DisjointSets& rhs) {
  this->disjointSets = rhs.disjointSets;
}

void DisjointSets::addelements(int num) {
  if (num < 0) {
    cerr << "Wrong input parameter." << endl;
    cerr << "The input should always be the non-negative integer." << endl;
    return;
  }
  disjointSets.insert(disjointSets.end(), num, -1);
}

int DisjointSets::find(int elem) {
  if (disjointSets[elem] < 0) {
    return elem;
  } else {
    int root = find(disjointSets[elem]);
    disjointSets[elem] = root;
    return root;
  }
}

void DisjointSets::setunion(int a, int b) {
  int rootA = find (a);
  int rootB = find (b);
  int newSize = disjointSets[rootA] + disjointSets[rootB];

  if (disjointSets[rootA] <= disjointSets[rootB]) {
    disjointSets[rootB] = rootA;
    disjointSets[rootA] = newSize;
  } else {
    disjointSets[rootA] = rootB;
    disjointSets[rootB] = newSize;
  }
}

int DisjointSets::size(int elem) {
    int root = find(elem);
    return -disjointSets[root];
}
