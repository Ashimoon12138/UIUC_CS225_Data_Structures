/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  std::vector<Edge> edges = g_.getEdges();

  for(auto & edge : edges) {
    int weight = g_.getEdgeWeight(edge.source, edge.dest);

    residual_.insertEdge(edge.source, edge.dest);
    residual_.setEdgeWeight(edge.source, edge.dest, weight);

    residual_.insertEdge(edge.dest, edge.source);
    residual_.setEdgeWeight(edge.dest, edge.source, 0);

    flow_.insertEdge(edge.source, edge.dest);
    flow_.setEdgeWeight(edge.source, edge.dest, 0);
  }
  //Hello xuehao! try to comment out line 40 and see what happen
  //try to debug it use a single test case and try valgrind
  maxFlow_ = 0;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  // Graph graph(true, true);
  // return pathCapacity(graph, path);
  if(path.size() <= 1) { return 0;}

  std::vector<Vertex>::const_iterator it = path.begin();

  //this will change it!!!!
  // std::vector<Vertex>::const_iterator next = ++it;
  //this even reverse it and next!!!!
  // std::vector<Vertex>::const_iterator next = it++;

  // std::vector<Vertex>::const_iterator next = path.begin() + 1;
  std::vector<Vertex>::const_iterator next = it + 1;

  int min = residual_.getEdgeWeight((*it), (*next));
  while(next != path.end()) {
    int temp = residual_.getEdgeWeight((*it), (*next));
    if(temp < min) {
      min = temp;
    }
    it = next;
    next ++;
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  std::vector<Vertex> path;
  while(findAugmentingPath(source_, sink_,path)) {
    int change = pathCapacity(path);
    maxFlow_ += change;
    // std::cout << "change" << change <<'\n';
    Vertex cur = path[0];

    for (size_t i = 0; i < path.size() - 1; i++) {
      Vertex next = path[i + 1];

      if(!flow_.edgeExists(cur, next)) {
        int capacity1 = flow_.getEdgeWeight(next, cur);
        flow_.setEdgeWeight(next, cur, capacity1 - change);
      }
      else {
        int capacity2 = flow_.getEdgeWeight(cur, next);
        flow_.setEdgeWeight(cur, next, capacity2 + change);
      }

      int capacity3 = residual_.getEdgeWeight(cur, next);
      residual_.setEdgeWeight(cur, next, capacity3 - change);
      int capacity4 = residual_.getEdgeWeight(next, cur);
      residual_.setEdgeWeight(next, cur, capacity4 + change);

      cur = next;
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
