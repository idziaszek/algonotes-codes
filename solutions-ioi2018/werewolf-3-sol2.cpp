// Task: Werewolf (IOI 2018)
// Solves subtask 3
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


int fufind(vector<int>& fu, int x) {
  return fu[x] < 0 ? x : fu[x] = fufind(fu, fu[x]);
}

void fujoin(vector<int>& fu, vector<int>& pos_sml, vector<int>& pos_big, int x, int y) {
  x = fufind(fu, x);
  y = fufind(fu, y);
  if (x != y) {
    fu[y] = x;
    pos_sml[x] = min(pos_sml[x], pos_sml[y]);
    pos_big[x] = max(pos_big[x], pos_big[y]);
  }
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

  // Get numbering on the line
  vector<int> position(N);
  int v = 0, prev = -1;
  REP(i, N) {
    if (adj[i].size() == 1) { v = i; }
  }
  REP(i, N) {
    position[v] = i;
    int idx = (adj[v][0] == prev);
    prev = v;
    v = adj[v][idx];
  }

  // Inits
  vector<int> idx(Q);
  vector<int> fu(N), pos_sml(N), pos_big(N);
  vector<pair<int,int> > Lrange(Q), Rrange(Q);

  REP(i, Q) {
    idx[i] = i;
  }

  // Process left
  REP(i, N) {
    fu[i] = -1;
    pos_sml[i] = pos_big[i] = position[i];
  }
  sort(idx.begin(), idx.end(), [&L](int i, int j) { return L[i] > L[j]; });
  int next = N-1;

  REP(i, Q) {
    int limit = L[idx[i]];
    for ( ; next >= limit; next--) {
      // Try to join vertex next
      for (int u : adj[next]) {
        if (u >= limit) {
          fujoin(fu, pos_sml, pos_big, next, u);
        }
      }
    }
    int lead = fufind(fu, S[idx[i]]);
    Lrange[idx[i]] = make_pair(pos_sml[lead], pos_big[lead]);
  }

  // Process right
  REP(i, N) {
    fu[i] = -1;
    pos_sml[i] = pos_big[i] = position[i];
  }
  sort(idx.begin(), idx.end(), [&R](int i, int j) { return R[i] < R[j]; });
  next = 0;

  REP(i, Q) {
    int limit = R[idx[i]];
    for ( ; next <= limit; next++) {
      // Try to join vertex next
      for (int u : adj[next]) {
        if (u <= limit) {
          fujoin(fu, pos_sml, pos_big, next, u);
        }
      }
    }
    int lead = fufind(fu, E[idx[i]]);
    Rrange[idx[i]] = make_pair(pos_sml[lead], pos_big[lead]);
  }

  // Answers
  REP(i, Q) {
    A[i] = !( Lrange[i].second < Rrange[i].first || Rrange[i].second < Lrange[i].first );
  }

  return A;
}
