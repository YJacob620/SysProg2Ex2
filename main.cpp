// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace ex2;
using namespace Algorithms;

int main() {
  Graph g;
  vector<vector<G>> v2 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 <-> 1 , 0 -> 4
        {INF,0,INF,-5,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
  };
  g.loadGraph(v2);
  g.printGraph();
  cout << endl;
  cout << "isConnected(g) = " + to_string(isConnected(g)) << endl << endl;
  cout << "shortestPath(g,1,4) = " + shortestPath(g, 1, 4) << endl << endl;
  cout << "isContainsCycle(g) = " + to_string(isContainsCycle(g)) << endl << endl;
  cout << "isBipartite(g) = " + to_string(isBipartite(g)) << endl << endl;
  cout << "negativeCycle(g) = " + to_string(negativeCycle(g)) << endl << endl;
}