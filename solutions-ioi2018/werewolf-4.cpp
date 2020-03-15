// Task: Werewolf (IOI 2018)
// Solves subtask 4
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "werewolf.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


struct tree_2d_t {
  vector<pair<int,int> > pts;
  vector<vector<int> > nodes;
  int base;
  int n;

  tree_2d_t(const vector<pair<int,int> >& points) {
    pts = points;
    sort(pts.begin(), pts.end());
    n = pts.size();
    base = 1;
    while (base < n) { base *= 2; }
    nodes.resize(2*base);
    REP(i, n) {
      nodes[base + i].push_back(pts[i].second);
    }
    for (int i = base-1; i >= 1; --i) {
      merge(nodes[2*i].begin(), nodes[2*i].end(),
          nodes[2*i+1].begin(), nodes[2*i+1].end(),
          back_inserter(nodes[i]));
    }
  }

  int query(int x, int yl, int yr) {
    yl = lower_bound(nodes[x].begin(), nodes[x].end(), yl) - nodes[x].begin();
    yr = lower_bound(nodes[x].begin(), nodes[x].end(), yr+1) - nodes[x].begin();
    return yr - yl;
  }

  int query(int xl, int xr, int yl, int yr) {
    // Returns number of points in rectangle [xl, xr) x [yl, yr)
    xl = lower_bound(pts.begin(), pts.end(), make_pair(xl, -1)) - pts.begin();
    xr = lower_bound(pts.begin(), pts.end(), make_pair(xr+1, -1)) - pts.begin();
    int cnt = 0;
    xl += base;
    xr += base-1;
    cnt += query(xl, yl, yr);
    if (xl != xr) {
      cnt += query(xr, yl, yr);
    }
    while (xl/2 != xr/2) {
      if (~xl&1) { cnt += query(xl+1, yl, yr); }
      if (xr&1) { cnt += query(xr-1, yl, yr); }
      xl /= 2;
      xr /= 2;
    }
    return cnt;
  }
};


int fufind(vector<int>& fu, int x) {
  return fu[x] < 0 ? x : fu[x] = fufind(fu, fu[x]);
}

void fujoin(vector<int>& fu, vector<pair<int,int> >& tree, int x, int y) {
  x = fufind(fu, x);
  y = fufind(fu, y);
  if (x != y) {
    int p = fu.size();
    fu[y] = p;
    fu[x] = p;
    fu.push_back(-1);
    tree.push_back(make_pair(y, x));
  }
}


pair<int,int> dfs(vector<pair<int,int> >& tree, int v, int N, int& k) {
  if (v < N) {
    tree[v].first = tree[v].second = k;
    k++;
  } else {
    pair<int,int> A = dfs(tree, tree[v].first, N, k);
    pair<int,int> B = dfs(tree, tree[v].second, N, k);
    tree[v].first = min(A.first, B.first);
    tree[v].second = max(A.second, B.second);
  }
  return make_pair(tree[v].first, tree[v].second);
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

  // Inits
  vector<int> idx(Q+1);
  vector<int> fu(N);
  vector<pair<int,int> > tree(N);
  vector<int> leads(Q+1);
  vector<pair<int,int> > points(N);
  vector<pair<int,int> > Lrange(Q), Rrange(Q);

  // Sentinels
  L.push_back(0);
  R.push_back(N-1);
  S.push_back(0);
  E.push_back(0);

  REP(i, Q+1) {
    idx[i] = i;
  }

  // Process left
  REP(i, N) {
    fu[i] = -1;
  }
  sort(idx.begin(), idx.end(), [&L](int i, int j) { return L[i] > L[j]; });
  int next = N-1;

  REP(i, Q+1) {
    int limit = L[idx[i]];
    for ( ; next >= limit; next--) {
      // Try to join vertex next
      for (int u : adj[next]) {
        if (u >= limit) {
          fujoin(fu, tree, next, u);
        }
      }
    }
    int lead = fufind(fu, S[idx[i]]);
    leads[idx[i]] = lead;
  }

  int k = 0;
  dfs(tree, tree.size()-1, N, k);

  REP(i, Q) {
    Lrange[i] = tree[leads[i]];
  }
  REP(i, N) {
    points[i].first = tree[i].first;
  }

  // Process right
  REP(i, N) {
    fu[i] = -1;
  }
  fu.resize(N);
  tree.resize(N);
  sort(idx.begin(), idx.end(), [&R](int i, int j) { return R[i] < R[j]; });
  next = 0;

  REP(i, Q+1) {
    int limit = R[idx[i]];
    for ( ; next <= limit; next++) {
      // Try to join vertex next
      for (int u : adj[next]) {
        if (u <= limit) {
          fujoin(fu, tree, next, u);
        }
      }
    }
    int lead = fufind(fu, E[idx[i]]);
    leads[idx[i]] = lead;
  }

  k = 0;
  dfs(tree, tree.size()-1, N, k);

  REP(i, Q) {
    Rrange[i] = tree[leads[i]];
  }
  REP(i, N) {
    points[i].second = tree[i].first;
  }

  tree_2d_t tree_2d(points);

  // Answers
  REP(i, Q) {
    A[i] = tree_2d.query(Lrange[i].first, Lrange[i].second,
        Rrange[i].first, Rrange[i].second) > 0;
  }

  return A;
}
