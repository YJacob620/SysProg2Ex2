// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#pragma once
#include "Graph.hpp"

namespace ex2 {
  namespace Algorithms {
    using namespace ex2;

    /// @brief Checks if a graph is connected.
    ///        Throws an error if the graph is not loaded.
    /// @param g Graph to check.
    /// @return True if the graph is connected, False otherwise.
    bool isConnected(const Graph& g);

    /// @brief Finds the shortest path between 2 vertices in a graph and prints it (if a path exists).
    ///        Throws an error if the graph is not loaded or if the received vertices indexes are out of range.
    /// @param g Given graph.
    /// @param vertex1 Index of source vertex.
    /// @param vertex2 Index of destination vertex.
    /// @return A string representing the path, or "No path" if there is no path.
    string shortestPath(const Graph& g, unsigned vertex1, unsigned vertex2);

    /// @brief Checks if a graph contains a cycle. Prints such cycle if it does.
    ///        Throws an error if the graph is not loaded.
    /// @param g Graph to check.
    /// @return True if the graph contains a cycle, False otherwise.
    bool isContainsCycle(const Graph& g);


    /// @brief Checks if a graph is bipartite. If it is prints its 2 partitions.
    /// @param g Graph to check.
    /// @return True if the graph is bipartite, False otherwise.
    bool isBipartite(const Graph& g);

    /// @brief Checks if a graph contains a negative cycle. Prints such cycle if it does.
    /// @param g Graph to check.
    /// @return True if the graph contains a negative cycle, False otherwise.
    bool negativeCycle(const Graph& g);
  };
};
