// Task: Meetings (IOI 2018)
// Solves subtask 4
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "meetings.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;


template<class T>
inline void minimize(T& a, const T& b) { if (a > b) a = b; }

const int MAXH = 21;
const ll infty = 1000000000;

struct info2_t {
  int cost[MAXH][MAXH];
  int le[MAXH], ri[MAXH];
  int maxh;
  info2_t() {
    REP(hl, MAXH) REP(hr, MAXH) {
      cost[hl][hr] = infty;
    }
    REP(h, MAXH) {
      le[h] = ri[h] = infty;
    }
  }
};

info2_t single2(int val) {
  info2_t I;
  I.cost[val][val] = val;
  REP(h, MAXH) {
    I.le[h] = I.ri[h] = max(h, val);
  }
  I.maxh = val;
  return I;
}

info2_t join(const info2_t& L, const info2_t& R) {
  info2_t I;
  REP(h1, MAXH) {
    int h2 = L.maxh;
    minimize(I.cost[h1][max(h2, R.maxh)], L.cost[h1][h2] + R.ri[h2]);
  }
  REP(h1, MAXH) {
    int h2 = R.maxh;
    minimize(I.cost[max(h1, L.maxh)][h2], L.le[h1] + R.cost[h1][h2]);
  }
  REP(h2, MAXH) {
    int h1 = L.maxh;
    minimize(I.cost[h1][max(h2, R.maxh)], L.cost[h1][h2] + R.ri[h2]);
  }
  REP(h2, MAXH) {
    int h1 = R.maxh;
    minimize(I.cost[max(h1, L.maxh)][h2], L.le[h1] + R.cost[h1][h2]);
  }

  REP(h, MAXH) {
    minimize(I.le[h], L.le[max(h, R.maxh)] + R.le[h]);
    minimize(I.ri[h], L.ri[h] + R.ri[max(h, L.maxh)]);
  }
  I.maxh = max(L.maxh, R.maxh);
  return I;
}

struct tree2_t {
  vector<info2_t> tree;
  int base;
  int n;

  tree2_t(const vector<int>& vals) {
    n = vals.size();
    base = 1;
    while (base < n) { base *= 2; }
    tree.resize(2*base);
    REP(i, n) {
      tree[base + i] = single2(vals[i]);
    }
    for (int i = base-1; i >= 1; i--) {
      tree[i] = join(tree[2*i], tree[2*i+1]);
    }
  }

  void update(int x, int val) {
    x += base;
    tree[x] = single2(val);
    while (x > 1) {
      x /= 2;
      tree[x] = join(tree[2*x], tree[2*x+1]);
    }
  }

  info2_t query(int xl, int xr) {
    xl += base;
    xr += base;
    if (xl == xr) {
      return tree[xl];
    }
    info2_t IL = tree[xl], IR = tree[xr];
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

  tree2_t tree(H);
  REP(i, Q) {
    info2_t I = tree.query(L[i], R[i]);
    int ans = infty;
    REP(h1, MAXH) {
      int h2 = I.maxh;
      minimize(ans, I.cost[h1][h2]);
    }
    REP(h2, MAXH) {
      int h1 = I.maxh;
      minimize(ans, I.cost[h1][h2]);
    }
    C[i] = ans;
  }

  return C;
}
