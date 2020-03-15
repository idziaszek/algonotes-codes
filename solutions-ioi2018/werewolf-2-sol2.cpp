// Task: Werewolf (IOI 2018)
// Solves subtask 2
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


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
    int start = S[i]*2;
    int end = E[i]*2 + 1;
    queue<int> que;
    vector<bool> vis(2*N);
    que.push(start);
    vis[start] = true;

    while (!que.empty()) {
      int v = que.front();
      que.pop();
      int vert = v/2, form = v%2;

      // Move
      for (int u : adj[vert]) {
        if ((form == 0 && u >= L[i]) || (form == 1 && u <= R[i])) {
          int uu = u*2 + form;
          if (!vis[uu]) {
            que.push(uu);
            vis[uu] = true;
          }
        }
      }

      // Change form
      if (form == 0 && vert <= R[i]) {
        int uu = vert*2 + 1;
        if (!vis[uu]) {
          que.push(uu);
          vis[uu] = true;
        }
      }
    }

    A[i] = vis[end];
  }

  return A;
}
