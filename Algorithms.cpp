// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#include "Algorithms.hpp"

namespace ex2 {
    namespace Algorithms {
        /// @brief Checks if a graph is loaded and updated. Throws an exception if it isn't.
        /// @param g Graph to check.
        void checkValidity(const Graph& g) {
            if (!g.isLoaded()) {
                throw runtime_error("Invalid action - graph is not loaded. (2)");
            }
            if (!g.isUpdated()) {
                throw runtime_error("Invalid action - graph is not updated. "
                    "Use Graph::update() to update.");
            }
        }

        bool isConnected(const Graph& g) {
            checkValidity(g);
            unsigned rows = g.get_SPT().size();
            unsigned j_lim = rows;
            if (!g.isDirected()) {
                j_lim = 1;
            }
            for (int i = 0;i < rows; i++) {
                for (int j = 0;j < j_lim;j++) {
                    if (g.get_SPT()[i][j] == NOPATH) {
                        return false;
                    }
                }
            }
            return true;
        }

        /// @brief Reverses a vector.
        /// @param vec Vector to reverse.
        void reverseVector(vector<int>& vec) {
            unsigned n = vec.size();
            for (unsigned i = 0; i < n / 2; i++) {
                std::swap(vec[i], vec[n - 1 - i]);
            }
        }

        /// @brief Finds the shortest path between 2 verices in a graph and returns it. 
        /// @param g Given graph.
        /// @param src Source vertix.
        /// @param dest Destination vertix.f
        /// @param negCycle Whether to expect a negative cycle between src and dest.
        /// @return The shortest path between SRC and DEST as a vector of indexes of vertices. 
        ///         If no path exists returns an empty vector.
        vector<int> getShortestPath(const Graph& g, unsigned src, unsigned dest, bool negCycle) {
            vector<vector<G>> spt = g.get_SPT();
            unsigned rows = spt.size();
            if (src >= rows || dest >= rows) {
                throw runtime_error("Vertices out of range.");
            }
            if (spt[src][dest] == NOPATH) {
                return {};
            }
            // vector<vector<G>> mat = g.get_matrix();
            vector<int> inversePath;
            inversePath.push_back(dest);
            if (negCycle) {
                dest = spt[src][dest];
                inversePath.push_back(dest);
            }
            unsigned counter = 0;
            while (src != dest && counter != rows) {
                dest = spt[src][dest];
                inversePath.push_back(dest);
                ++counter;
            }
            if (counter == rows) {
                return { -1 };
            }
            reverseVector(inversePath);
            return inversePath;
        }

        string shortestPath(const Graph& g, unsigned src, unsigned dest) {
            checkValidity(g);
            vector<int> SP = getShortestPath(g, src, dest, false);
            if (SP.empty()) {
                cout << "No path" << endl;
                return "";
            }
            if (SP[0] == -1) {
                cout << "No path (encountered a negative cycle)" << endl;
                return "";
            }
            auto u = SP[0];
            string path = to_string(SP[0]);
            int pathWeight = 0;
            for (int i = 1;i < SP.size();i++) {
                auto v = SP[i];
                path += " -> " + to_string(v);
                pathWeight += g.get_matrix()[u][v];
                u = v;
            }

            string to_print = "Shortest path: [" + path + "], weight: [" + to_string(pathWeight) + "].";
            cout << to_print << endl;
            return path;
        }

        /// @brief Finds a cycle in a single DFS tree of a graph (is called iteratively to cover 
        ///        the entire DFS forest).
        /// @param g Given graph.
        /// @param u An index of a vertice in a DFS tree.
        /// @param visited Indexes vector that is used to tell which vertices are "finished" 
        ///                in a single iteration (and its recursions).
        /// @param rec_visited Indexes vector that is used to tell which vertices are 
        ///                    "finished" in all iterations/recursions.
        /// @param rec_cycle Indexes vector that is used to keep track of cycles.
        /// @return True if this DFS tree contains a cycle, False otherwise.
        bool dfsFindCycle(const Graph& g, unsigned u, vector<bool> visited,
            vector<bool>& rec_visited, vector<unsigned>& rec_cycle) {
            if (visited[u] == false) {
                visited[u] = true;
                rec_visited[u] = true;
                rec_cycle.push_back(u);
                for (unsigned v = 0; v < g.get_matrix().size(); v++) {
                    if (g.get_matrix()[u][v] != INF && u != v) {
                        if (!visited[v] && dfsFindCycle(g, v, visited, rec_visited, rec_cycle)) {
                            return true;
                        }
                        if (rec_visited[v]) {
                            return true;
                        }
                    }
                }
            }

            rec_visited[u] = false;
            rec_cycle.erase(rec_cycle.end() - 1);
            return false;
        }

        bool isContainsCycle(const Graph& g) {
            checkValidity(g);
            unsigned vertices = g.get_matrix().size();
            vector<bool> visited(vertices, false);
            vector<bool> rec_visited(vertices, false);
            vector<unsigned> rec_cycle;

            for (unsigned i = 0;i < vertices; i++) {
                if (!visited[i] && dfsFindCycle(g, i, visited, rec_visited, rec_cycle)) {
                    while (g.get_matrix()[rec_cycle[rec_cycle.size() - 1]][rec_cycle[0]] == INF) {
                        rec_cycle.erase(rec_cycle.begin());
                    }
                    rec_cycle.push_back(rec_cycle[0]);
                    string path = to_string(rec_cycle[0]);
                    for (int i = 1;i < rec_cycle.size();i++) {
                        unsigned v = rec_cycle[i];
                        path += " -> " + to_string(v);
                    }
                    string to_print = "Cycle: [" + path + "].";
                    cout << to_print << endl;
                    return true;
                }
            }
            return false;
        }

        bool isBipartite(const Graph& g) {
            checkValidity(g);
            unsigned vertices = g.get_matrix().size();
            int blue = -1;
            int white = 0;
            int red = 1;
            vector<int> vColors(vertices, white);
            vector<unsigned> q;
            q.push_back(0);
            vColors[0] = blue;

        bfs_bipartite:
            while (!q.empty()) {
                unsigned u = q[0];
                q.erase(q.begin());
                for (unsigned v = 0; v < vertices; v++) {
                    if (g.get_matrix()[u][v] != INF && u != v) {
                        if (vColors[v] == vColors[u]) {
                            return false; // When the graph is not 2-colorable.
                        }
                        if (vColors[v] == white) {
                            if (vColors[u] == blue) {
                                vColors[v] = red;
                            }
                            else {
                                vColors[v] = blue;
                            }
                            q.push_back(v);
                        }
                    }
                }
            }
            vector<unsigned> blues, reds;
            for (unsigned v = 0; v < vColors.size(); v++) {
                if (vColors[v] == white) {
                    vColors[v] = blue;
                    for (unsigned w = 0; w < vertices; w++) {
                        if (w != v) {
                            if (g.get_matrix()[w][v] != INF || g.get_matrix()[v][w] != INF) {
                                if (vColors[w] != white) {
                                    vColors[v] = vColors[w] * -1;
                                    break;
                                }
                            }
                        }
                    }
                    q.push_back(v);
                    goto bfs_bipartite;
                }
                if (vColors[v] == blue) {
                    blues.push_back(v);
                }
                else {
                    reds.push_back(v);
                }
            }
            string to_print = "The graph is bipartite: A = {";
            for (unsigned vertice : blues) {
                to_print.append(to_string(vertice) + ", ");
            }
            to_print.erase(to_print.size() - 2);
            to_print.append("}, B = {");
            for (unsigned vertice : reds) {
                to_print.append(to_string(vertice) + ", ");
            }
            if (to_print[to_print.size() - 1] != '{') {
                to_print.erase(to_print.size() - 2);
            }
            to_print.append("}");
            cout << to_print << endl;
            return true;
        }

        bool negativeCycle(const Graph& g) {
            checkValidity(g);
            unsigned vertices = g.get_matrix().size();
            for (unsigned v = 0; v < vertices; v++) {
                if (g.get_SPW()[v][v] < 0) {
                    vector<int> negCyc = getShortestPath(g, v, v, true);
                    unsigned u = negCyc[0];
                    string path = to_string(negCyc[0]);
                    int pathWeight = 0;
                    for (int i = 1;i < negCyc.size();i++) {
                        unsigned v = negCyc[i];
                        path += " -> " + to_string(v);
                        pathWeight += g.get_matrix()[u][v];
                        u = v;
                    }
                    string to_print = "Negative cycle: [" + path + "], " +
                        "weight: [" + to_string(pathWeight) + "].";
                    cout << to_print << endl;
                    return true;
                }
            }
            return false;
        }
    }
}
