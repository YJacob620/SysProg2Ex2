// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#include "Graph.hpp"

namespace ex2 {
    /* Ex1 Functions */

    /// @brief Checks if an adjacency matrix is valid. A valid one is a square matrix 
    ///        where the elements in the main diagonal are zeros.
    /// @param matrix Matrix to check.
    /// @return True if the matrix is valid, False otherwise.
    bool isValid(const vector<vector<G>>& matrix) {
        // if (matrix.empty()) {
        //     return false;
        // }
        auto rows = matrix.size();
        for (int i = 0;i < rows;i++) {
            vector<G> vec = matrix[i];
            if (vec.size() != rows || vec[i] != 0) {
                return false;
            }
        }
        return true;
    }

    /// @brief Checks if an adjacency matrix is a directed graph. Assumes the matrix is valid.
    /// @param matrix Matrix to check.
    /// @return True if the matrix is directed, False otherwise.
    bool checkIfDirected(const vector<vector<G>>& matrix) {
        auto rows = matrix.size();
        for (int i = 0;i < rows;i++) {
            for (int j = i;j < rows;j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    return true;
                }
            }
        }
        return false;
    }

    /// @brief Prints a matrix.
    /// @param mat Matrix to print.
    void printMatrix(const vector<vector<G>>& mat, ostream& os) {
        for (const vector<G>& vec : mat) {
            for (G element : vec) {
                if (element == INF) {
                    os << "inf";
                }
                else {
                    os << element;
                }
                os << "   ";
            }
            os << endl;
        }
    }

    void Graph::run_FloydWarshall() {
        auto rows = this->matrix.size();
        this->SP_weights = vector<vector<G>>(rows, vector<G>(rows));
        this->SP_tree = vector<vector<G>>(rows, vector<G>(rows));

        /* Shortest paths matrix and SP-tree initialization */
        for (int i = 0;i < rows;i++) {
            for (int j = 0;j < rows;j++) {
                G val = this->matrix[i][j];
                SP_weights[i][j] = val;
                if (val == INF) {
                    SP_tree[i][j] = NOPATH;
                }
                else {
                    SP_tree[i][j] = i;
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            SP_tree[i][i] = i;
        }

        /* The "meat" of the algorithm */
        for (int k = 0;k < rows;k++) {
            for (int i = 0;i < rows;i++) {
                for (int j = 0;j < rows;j++) {
                    if (SP_weights[i][k] != INF && SP_weights[k][j] != INF) {
                        int new_path_weight = SP_weights[i][k] + SP_weights[k][j];
                        if (SP_weights[i][j] > new_path_weight) {
                            SP_weights[i][j] = new_path_weight;
                            SP_tree[i][j] = SP_tree[k][j];
                        }
                    }
                }
            }
        }
    }

    void Graph::loadGraph(const vector<vector<G>>& matrix) {
        if (!isValid(matrix)) {
            throw runtime_error("Invalid graph. A graph should be a non-empty square"
                "matrix where the elements in the main diagonal are zeros.");
            return;
        }
        this->matrix = matrix;
        this->directed = checkIfDirected(matrix);
        run_FloydWarshall();
        this->updated = true;
    }

    string Graph::printGraph() const {
        string ans;
        if (this->matrix.empty()) {
            cout << "Empty graph." << endl;
            return ans;
        }
        unsigned vertices = this->matrix[0].size();
        unsigned edges = 0;
        for (const vector<G>& vec : this->matrix) {
            for (G element : vec) {
                if (element != INF) {
                    edges++;
                }
            }
        }
        edges -= vertices; // No such thing as an edge between a vertex and itself.
        if (this->directed) {
            ans.append("Directed ");
        }
        else {
            ans.append("Undirected ");
            edges /= 2;
        }
        ans.append("graph with " + to_string(vertices) + " vertices and " + to_string(edges) + " edges.");
        cout << ans << endl;
        printMatrix(this->matrix, cout); //REMOVE MAYBE
        return ans;
    }

    vector<vector<G>> Graph::get_matrix() const {
        return this->matrix;
    }

    vector<vector<G>> Graph::get_SPT() const {
        return this->SP_tree;
    }

    vector<vector<G>> Graph::get_SPW() const {
        return this->SP_weights;
    }

    bool Graph::isLoaded() const {
        return !(this->matrix.empty()); // asd
    }

    bool Graph::isDirected() const {
        return this->directed;
    }

    /* Ex2 Functions */

    Graph::Graph() {
        this->directed = true;
    }

    Graph::Graph(const Graph& g) {
        this->matrix = g.matrix;
        this->SP_weights = g.SP_weights;
        this->SP_tree = g.SP_tree;
        this->directed = g.directed;
        this->updated = g.updated;
    }

    void Graph::checkSameSize(const Graph& g) const {
        if (g.get_matrix().size() != this->get_matrix().size()) {
            throw runtime_error("Invalid action. Graphs are not of the same size.");
        }
    }

    void Graph::update() {
        if (!this->updated) {
            this->directed = checkIfDirected(this->matrix);
            this->run_FloydWarshall();
            this->updated = true;
        }
    }

    bool Graph::isUpdated() const {
        return this->updated;
    }

    Graph Graph::operator+() const {
        return *this;
    }

    Graph Graph::operator-() const {
        Graph ans = *this;
        auto rows = ans.get_matrix().size();
        for (int i = 0; i < rows;i++) {
            for (int j = 0;j < rows;j++) {
                if (ans.matrix[i][j] != INF) {
                    ans.matrix[i][j] *= -1;
                }
            }
        }
        ans.updated = false;
        return ans;
    }

    Graph Graph::operator+(const Graph& g) const {
        this->checkSameSize(g);
        Graph ans = *this;
        auto rows = ans.get_matrix().size();
        for (int i = 0; i < rows;i++) {
            for (int j = 0;j < rows;j++) {
                if (ans.matrix[i][j] == INF || g.matrix[i][j] == INF) {
                    if (ans.matrix[i][j] == INF && g.matrix[i][j] == INF) {
                        continue;
                    }
                    if (g.matrix[i][j] != INF) {
                        ans.matrix[i][j] = g.matrix[i][j];
                    }
                }
                else {
                    ans.matrix[i][j] += g.matrix[i][j];
                }
            }
        }
        ans.updated = false;
        return ans;
    }

    Graph Graph::operator-(const Graph& g) const {
        Graph ans = *this + (-g);
        return ans;
    }

    void Graph::operator+=(const Graph& g) {
        this->matrix = (*this + g).matrix;
        this->updated = false;
    }

    void Graph::operator-=(const Graph& g) {
        *this += (-g);
        // this->matrix = (*this - (g)).matrix;
        // this->updated = false;
    }

    Graph Graph::operator++() { // ++g
        auto rows = this->matrix.size();
        Graph tmp;
        tmp.matrix = vector<vector<G>>(rows, vector<G>(rows, 1));
        for (int i = 0; i < rows;i++) {
            tmp.matrix[i][i] = 0;
        }
        *this += (tmp);
        return *this;
    }

    Graph Graph::operator--() { // --g
        auto rows = this->matrix.size();
        Graph tmp;
        tmp.matrix = vector<vector<G>>(rows, vector<G>(rows, -1));
        for (int i = 0; i < rows;i++) {
            tmp.matrix[i][i] = 0;
        }
        *this += (tmp);
        return *this;
    }

    Graph Graph::operator++(int) { // g++
        Graph ans = Graph(*this);
        this->operator++();
        return ans;
    }

    Graph Graph::operator--(int) { // g--
        Graph ans = Graph(*this);
        this->operator--();
        return ans;
    }

    bool Graph::operator==(const Graph& g) const {
        return this->matrix == g.matrix || (!(*this > g) && !(g > *this));
    }

    bool Graph::operator!=(const Graph& g) const {
        return !(*this == g);
    }

    bool Graph::operator>(const Graph& g) const {
        auto A = this->matrix;
        auto B = g.matrix;
        int sizeA = A.size();
        int sizeB = B.size();
        if (sizeB > sizeA) {
            return false;
        }

        // Check all possible positions in A where the top-left corner of B could fit
        for (int i = 0; i <= sizeA - sizeB; ++i) {
            for (int j = 0; j <= sizeA - sizeB; ++j) {
                bool subMatrixFound = true;
                for (int k = 0; k < sizeB; ++k) {
                    for (int l = 0; l < sizeB; ++l) {
                        if (B[k][l] != INF && A[i + k][j + l] != B[k][l]) {
                            subMatrixFound = false;
                            break;
                        }
                    }
                    if (!subMatrixFound) {
                        break;
                    }
                }
                if (subMatrixFound) {
                    return true;
                }
            }
        }
        // if (*this != g) { // CAUSES RUNTIME ERRORS!
        int edgesA = -sizeA;
        int edgesB = -sizeB;
        for (int i = 0; i < sizeA; ++i) {
            for (int j = 0; j < sizeA; ++j) {
                if (A[i][j] != INF) {
                    edgesA++;
                }
            }
        }
        for (int i = 0; i < sizeB; ++i) {
            for (int j = 0; j < sizeB; ++j) {
                if (B[i][j] != INF) {
                    edgesB++;
                }
            }
        }
        if (edgesA > edgesB) {
            return true;
        }
        return sizeA > sizeB;
        // if (sizeA == sizeB) {
        //     for (int i = 0; i < sizeA; ++i) {
        //         for (int j = 0; j < sizeA; ++j) {
        //             if (A[i][j] > B[i][j]) {
        //                 return true;
        //             }
        //         }
        //     }
    // }
    // return false;
    }

    bool Graph::operator>=(const Graph& g) const {
        return *this == g || *this > g;
    }

    bool Graph::operator<(const Graph& g) const {
        return g > *this;
    }

    bool Graph::operator<=(const Graph& g) const {
        return *this == g || *this < g;
    }

    Graph Graph::operator*(G scalar) {
        Graph ans = *this;
        auto rows = ans.get_matrix().size();
        for (int i = 0; i < rows;i++) {
            for (int j = 0;j < rows;j++) {
                if (ans.matrix[i][j] != INF) {
                    ans.matrix[i][j] *= scalar;
                }
            }
        }
        ans.updated = false;
        return ans;
    }

    Graph Graph::operator*(const Graph& g) const {
        this->checkSameSize(g);
        auto rows = this->matrix.size();
        Graph ans;
        ans.matrix = vector<vector<G>>(rows, vector<G>(rows, 0));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < rows; ++j) {
                for (int k = 0; k < rows; ++k) {
                    if (this->matrix[i][k] == INF || g.matrix[k][j] == INF) {
                        ans.matrix[i][j] = INF;
                    }
                    else if (ans.matrix[i][j] != INF) {
                        ans.matrix[i][j] += this->matrix[i][k] * g.matrix[k][j];
                    }
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            ans.matrix[i][i] = 0;   // Remove all self edges so that graph is valid. 
        }
        ans.updated = false;
        ans.directed = checkIfDirected(ans.matrix);
        return ans;
    }

    ostream& operator<<(ostream& os, const Graph& g) { // cout << g
        if (g.matrix.empty()) {
            os << "Empty graph." << endl;
            return os;
        }
        unsigned vertices = g.matrix[0].size();
        int edges = -vertices;
        for (const vector<G>& vec : g.matrix) {
            for (G element : vec) {
                if (element != INF) {
                    edges++;
                }
            }
        }
        string ans;
        if (g.directed) {
            ans.append("Directed ");
        }
        else {
            ans.append("Undirected ");
            edges /= 2;
        }
        ans.append("graph with " + to_string(vertices) + " vertices and " + to_string(edges) + " edges.");
        os << ans << endl;
        printMatrix(g.matrix, os);
        return os;
    }
}