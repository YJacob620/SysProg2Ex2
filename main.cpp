// ID: *****1536
// EMAIL: yairjacob620@gmail.com

#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace ex2;
using namespace Algorithms;

int main() {
  Graph g;
  vector<vector<G>> v1 = {
        {0,INF,INF,INF,1}, // 2 -> 4 <-> 3 <-> 1 , 0 -> 4
        {INF,0,INF,-5,INF},
        {INF,INF,0,INF,1},
        {INF,-1,INF,0,-9},
        {INF,INF,INF,-1,0}
  };
  g.loadGraph(v1);
  g.printGraph();
  cout << endl;
  cout << "isConnected(g) = " + to_string(isConnected(g)) << endl << endl;
  cout << "shortestPath(g,1,4) = " + shortestPath(g, 1, 4) << endl << endl;
  cout << "isContainsCycle(g) = " + to_string(isContainsCycle(g)) << endl << endl;
  cout << "isBipartite(g) = " + to_string(isBipartite(g)) << endl << endl;
  cout << "negativeCycle(g) = " + to_string(negativeCycle(g)) << endl << endl;

  Graph g1, g2;
  vector<vector<G>> v2;
  v2 = {
      {0,INF,INF,0,3},
      {INF,0,INF,1,0},
      {-6,INF,0,INF,-5},
      {INF,INF,INF,0,INF},
      {2,INF,6,INF,0}
  };
  g1.loadGraph(v2);
  v2 = {
      {0,-5,INF,0,INF},
      {INF,0,INF,1,0},
      {-6,0,0,0,-5},
      {-100,7,200,0,INF},
      {0,INF,INF,INF,0}
  };
  g2.loadGraph(v2);
  g2 += g1 * 7;
  cout << g2 << endl;
  cout << ++g2 << endl;
  cout << --g2 << endl;
  cout << (g1 != g2) << endl;
  cout << (g1 < g2 && g2 > g1) << endl;
  cout << (g2 > g1 && g1 < g2) << endl;
  g2.update();
  cout << "isConnected(g2) = " + to_string(isConnected(g2)) << endl << endl;
  cout << "shortestPath(g2, 2, 4) = " + shortestPath(g2, 2, 4) << endl << endl;
  cout << "isContainsCycle(g2) = " + to_string(isContainsCycle(g2)) << endl << endl;
  cout << "isBipartite(g2) = " + to_string(isBipartite(g2)) << endl << endl;
  cout << "negativeCycle(g2) = " + to_string(negativeCycle(g2)) << endl << endl;
}