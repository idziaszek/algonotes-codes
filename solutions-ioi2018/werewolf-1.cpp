// Task: Werewolf (IOI 2018)
// Solves subtask 1
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


bool reachable(vector<vector<int> >& adj, int N, int start, int end, int lo, int hi) {
  // Can we go from start to end using vertices in range [lo, hi]?
  queue<int> que;
  vector<bool> vis(N);
  if (lo <= start && start <= hi) {
    que.push(start);
    vis[start] = true;
  }

  while (!que.empty()) {
    int v = que.front();
    que.pop();
    for (int u : adj[v]) {
      if (lo <= u && u <= hi && !vis[u]) {
        que.push(u);
        vis[u] = true;
      }
    }
  }

  return vis[end];
}


vector<int> check_validity(int N, vector<int> X, vector<int> Y,
    vector<int> S, vector<int> E, vector<int> L, vector<int> R) {
  int Q = S.size();
  vector<int> A(Q);

  // Construct the graph
  vector<vector<int> > adj(N);
  int M = X.size();
  REP(i, M) {
    adj[X[i]].push_back(Y[i]);
    adj[Y[i]].push_back(X[i]);
  }

  REP(i, Q) {
    // Compute the i-th query

    REP(swi, N) {
      // Try switch vertex
      bool reach_S = reachable(adj, N, S[i], swi, L[i], N-1);
      bool reach_E = reachable(adj, N, swi, E[i], 0, R[i]);
      A[i] |= reach_S && reach_E;
    }
  }

  return A;
}
