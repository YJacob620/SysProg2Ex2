// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <limits>

#define G int // Type of the elements in the matrix/sub-vectors.
#define INF std::numeric_limits<G>::max() // Maximum value of type T.
#define NOPATH -1 // Value which indicates "no path" between 2 in shortest paths tree.

namespace ex2 {
  using namespace std;

  class Graph {
    private:
    vector<vector<G>> matrix; // Adjacency matrix representing the graph.
    bool directed; // Whether the graph is directed or not.
    vector<vector<G>> SP_weights; // Shortest paths weights.
    vector<vector<G>> SP_tree; // Shortest paths tree.
    bool updated = false;

    /// @brief Runs Floyd Warshall algorithm on the graph to find all-pairs-shortest-paths and
    ///        to set the appropriate shortest-paths-tree to the graph.
    void run_FloydWarshall();

    /// @brief Checks if a given graph is of the same size as the current one. 
    ///        Throws a runtime error if it isn't.
    /// @param g Given graph.
    void checkSameSize(const Graph& g) const;

    public:
    /// @brief Loads an adjacency matrix (as a graph) to this Graph - as long as it's valid. 
    ///        Throws runtime_error if matrix is invalid.
    /// @param matrix Adjacency matrix to load as a graph.
    void loadGraph(const vector<vector<G>>& matrix);

    /// @brief Prints information about the graph.
    /// @return Some information about the graph as a string type.
    string printGraph() const;

    /// @return The adjacency matrix representing this graph.
    vector<vector<G>> get_matrix() const;

    /// @brief Get Shortest Paths Tree.
    /// @return The all-pairs-shortest-paths shortest-paths-tree of the graph.
    vector<vector<G>> get_SPT() const;

    /// @brief Get Shortest Paths Weights.
    /// @return The all-pairs-shortest-paths weights-matrix of the graph.
    vector<vector<G>> get_SPW() const;

    /// @brief Checks whether the graph is currently loaded (not empty).
    /// @return True if he graph is loaded, False otherwise.
    bool isLoaded() const;

    /// @brief Checks whether the graph is directed.
    /// @return True if he graph is directed, False otherwise.
    bool isDirected() const;

    Graph();

    /// @brief Copy constructor.
    /// @param g Given Graph to deep-copy into current one.
    Graph(const Graph& g);

    /// @brief Updates the graph's SPW and SPT matrices if necessary. Should be called 
    ///        after performing a series of arithmatic operations on the graph.
    void update();

    /// @brief Checks if the Graph's SPW and SPT matrices are updated.
    /// @return True if they are, Flase otherwise.
    bool isUpdated() const;

    Graph operator+() const;

    Graph operator-() const;

    Graph operator+(const Graph& g) const;

    Graph operator-(const Graph& g) const;

    void operator+=(const Graph& g);

    void operator-=(const Graph& g);

    Graph operator++();

    Graph operator--();

    Graph operator++(int);

    Graph operator--(int);

    bool operator==(const Graph& g) const;

    bool operator!=(const Graph& g) const;

    bool operator>(const Graph& g) const;

    bool operator>=(const Graph& g) const;

    bool operator<(const Graph& g) const;

    bool operator<=(const Graph& g) const;

    Graph operator*(G scalar);

    Graph operator*(const Graph& g) const;

    friend ostream& operator<<(ostream& os, const Graph& g); // cout << g
  };
};
