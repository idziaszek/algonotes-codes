// Task: Werewolf (IOI 2018)
// Solves subtask 2
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


vector<bool> reachable(vector<vector<int> >& adj, int N, int start, int lo, int hi) {
  // Where can we go from start using vertices in range [lo, hi]?
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

  return vis;
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

    vector<bool> reach_S = reachable(adj, N, S[i], L[i], N-1);
    vector<bool> reach_E = reachable(adj, N, E[i], 0, R[i]);

    REP(swi, N) {
      // Try switch vertex
      A[i] |= reach_S[swi] && reach_E[swi];
    }
  }

  return A;
}
