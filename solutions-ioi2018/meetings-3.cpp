// Task: Meetings (IOI 2018)
// Solves subtask 3
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "meetings.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;


struct info_t {
  int best;
  int le,ri,len;
  info_t() : best(0), le(0), ri(0), len(0) { }
};

info_t single(int val) {
  info_t I;
  I.best = I.le = I.ri = val == 1;
  I.len = 1;
  return I;
}

info_t join(const info_t& L, const info_t& R) {
  info_t I;
  I.best = max(max(L.best, R.best), L.ri + R.le);
  I.le = L.le;
  if (L.best == L.len)
    I.le = max(I.le, L.len + R.le);
  I.ri = R.ri;
  if (R.best == R.len)
    I.ri = max(I.ri, L.ri + R.len);
  I.len = L.len + R.len;
  return I;
}

struct tree_t {
  vector<info_t> tree;
  int base;
  int n;

  tree_t(const vector<int>& vals) {
    n = vals.size();
    base = 1;
    while (base < n) { base *= 2; }
    tree.resize(2*base);
    REP(i, n) {
      tree[base + i] = single(vals[i]);
    }
    for (int i = base-1; i >= 1; i--) {
      tree[i] = join(tree[2*i], tree[2*i+1]);
    }
  }

  void update(int x, int val) {
    x += base;
    tree[x] = single(val);
    while (x > 1) {
      x /= 2;
      tree[x] = join(tree[2*x], tree[2*x+1]);
    }
  }

  info_t query(int xl, int xr) {
    xl += base;
    xr += base;
    if (xl == xr) {
      return tree[xl];
    }
    info_t IL = tree[xl], IR = tree[xr];
    while (xl/2 != xr/2) {
      if (~xl&1) { IL = join(IL, tree[xl+1]); }
      if (xr&1) { IR = join(tree[xr-1], IR); }
      xl /= 2;
      xr /= 2;
    }
    return join(IL, IR);
  }
};


vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
  int Q = L.size();
  vector<ll> C(Q);

  tree_t tree(H);
  REP(i, Q) {
    int size = tree.query(L[i], R[i]).best;
    C[i] = 2*(R[i] + 1 - L[i]) - size;
  }

  return C;
}
