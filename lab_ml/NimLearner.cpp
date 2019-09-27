/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */
    if(startingTokens < 1) { return; }

    for (int i = (int) startingTokens; i >= 0; i --) {
      g_.insertVertex("p1-" + std::to_string(i));
      g_.insertVertex("p2-" + std::to_string(i));
    }

    for (unsigned i = startingTokens; i >= 2; i --) {

      string p1 = "p1-" + std::to_string(i);
      string p11 = "p1-" + std::to_string(i-1);
      string p12 = "p1-" + std::to_string(i-2);

      string p2 = "p2-" + std::to_string(i);
      string p21 = "p2-" + std::to_string(i-1);
      string p22 = "p2-" + std::to_string(i-2);

      g_.insertEdge(p1, p21);
      g_.setEdgeWeight(p1, p21, 0);

      g_.insertEdge(p1, p22);
      g_.setEdgeWeight(p1, p22, 0);

      g_.insertEdge(p2, p11);
      g_.setEdgeWeight(p2, p11, 0);

      g_.insertEdge(p2, p12);
      g_.setEdgeWeight(p2, p12, 0);
    }

    g_.insertEdge("p1-" + std::to_string(1), "p2-" + std::to_string(0));
    g_.setEdgeWeight("p1-" + std::to_string(1), "p2-" + std::to_string(0), 0);
    g_.insertEdge("p2-" + std::to_string(1), "p1-" + std::to_string(0));
    g_.setEdgeWeight("p2-" + std::to_string(1), "p1-" + std::to_string(0), 0);

    // Vertex start = "p1-" + std::to_string(startingTokens);
    startingVertex_ = g_.getStartingVertex();


    // if(startingTokens >= 2) {
    //   string p11 = "p1-" + std::to_string(startingTokens-1);
    //   string p12 = "p1-" + std::to_string(startingTokens-2);
    //   string p2 = "p2-" + std::to_string(startingTokens);
    //   string p22 = "p2-" + std::to_string(startingTokens-2);
    //   g_.removeEdge(p2, p11);
    //   g_.removeEdge(p2, p12);
    //   g_.removeEdge(p11, p22);
    //
    //   if(startingTokens >= 3) {
    //     string p23 = "p2-" + std::to_string(startingTokens-3);
    //     g_.removeEdge(p11, p23);
    //   }
    // }
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
  unsigned startingTokens = g_.getVertices().size()/2 - 1;
  int i = (int) startingTokens;
  string start = "p1-" + std::to_string(i);
  // Vertex start = startingVertex_;

  //get all adjacent nodes until the end
  while (!g_.getAdjacent(start).empty()) {
    vector<Vertex> adjacent = g_.getAdjacent(start);
    int rdm = rand() % adjacent.size();
    Vertex dest = adjacent[rdm];
    Edge e = g_.getEdge(start, dest);
    path.push_back(e);
    start = dest;
    // i -= ram;
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 string winnerVertex = path.back().source;
 string winner = winnerVertex.substr(1,2);

 for(Edge i : path) {
   int weight = i.getWeight();
   if(i.source.substr(1,2) == winner) {
     g_.setEdgeWeight(i.source, i.dest, weight + 1);
   }else {
     g_.setEdgeWeight(i.source, i.dest, weight - 1);
   }
 }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
