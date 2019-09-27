#pragma once

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <vector>
using std::vector;

#include <algorithm>

class DisjointSets {
    public:

    DisjointSets() {};
    DisjointSets(int num);
    DisjointSets(const DisjointSets &);
    ~DisjointSets() { this->disjointSets = vector<int>(); };

    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);

    private:
    vector<int> disjointSets;
};
