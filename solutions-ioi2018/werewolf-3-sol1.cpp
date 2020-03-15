// Task: Werewolf (IOI 2018)
// Solves subtask 3
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


struct tree_t {
  vector<int> mins, maxs;
  int base;
  int n;

  tree_t(const vector<int>& vals) {
    n = vals.size();
    base = 1;
    while (base < n) { base *= 2; }
    mins.resize(2*base);
    maxs.resize(2*base);
    REP(i, n) {
      mins[base + i] = maxs[base + i] = vals[i];
    }
    for (int i = base-1; i >= 1; i--) {
      mins[i] = min(mins[2*i], mins[2*i+1]);
      maxs[i] = max(maxs[2*i], maxs[2*i+1]);
    }
  }

  pair<int,int> query(int xl, int xr) {
    // Returns (min, max) on range [xl, xr]
    xl += base;
    xr += base;
    int mi = min(mins[xl], mins[xr]);
    int ma = max(maxs[xl], maxs[xr]);
    while (xl/2 != xr/2) {
      if (~xl&1) {
        mi = min(mi, mins[xl+1]);
        ma = max(ma, maxs[xl+1]);
      }
      if (xr&1) {
        mi = min(mi, mins[xr-1]);
        ma = max(ma, maxs[xr-1]);
      }
      xl /= 2;
      xr /= 2;
    }
    return make_pair(mi, ma);
  }

  int range_right(int x, int lo, int hi) {
    x += base;
    while (x > 1 && (x&1 || ++x && lo <= mins[x] && maxs[x] <= hi)) {
      x /= 2;
    }
    if (x == 1) { return n-1; }
    while (x < base) {
      if (lo <= mins[2*x] && maxs[2*x] <= hi) { x = 2*x+1; }
      else { x = 2*x; }
    }
    return x-1 - base;
  }

  int range_left(int x, int lo, int hi) {
    x += base;
    while (x > 1 && (~x&1 || x-- && lo <= mins[x] && maxs[x] <= hi)) {
      x /= 2;
    }
    if (x == 1) { return 0; }
    while (x < base) {
      if (lo <= mins[2*x+1] && maxs[2*x+1] <= hi) { x = 2*x; }
      else { x = 2*x+1; }
    }
    return x+1 - base;
  }
};


pair<int,int> calculate_range(tree_t& tree, int N, int x, int lo, int hi) {
  // Calculate maximal range of positions that contains position x
  // and elements are in range [lo, hi]
  return make_pair(tree.range_left(x, lo, hi), tree.range_right(x, lo, hi));
}

bool ranges_intersect(const pair<int,int>& a, const pair<int,int>& b) {
  return ! (a.second < b.first || b.second < a.first);
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
  vector<int> number(N);
  int begin = 0, prev = -1;
  REP(i, N) {
    if (adj[i].size() == 1) { begin = i; }
  }
  REP(i, N) {
    number[begin] = i;
    int idx = (adj[begin][0] == prev);
    prev = begin;
    begin = adj[begin][idx];
  }

  // Construct RMQ tree
  vector<int> numz(N);
  REP(i, N) {
    numz[number[i]] = i;
  }
  tree_t tree(numz);

  REP(i, Q) {
    // Compute the i-th query
    pair<int,int> Lrange = calculate_range(tree, N, number[S[i]], L[i], N-1);
    pair<int,int> Rrange = calculate_range(tree, N, number[E[i]], 0, R[i]);
    A[i] = ranges_intersect(Lrange, Rrange);
  }

  return A;
}
