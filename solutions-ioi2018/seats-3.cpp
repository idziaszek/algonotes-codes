// Task: Seats (IOI 2018)
// Solves subtask 3
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "seats.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


struct tree_t {
  vector<int> mins,maxs;
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

  void update(int x, int val) {
    x += base;
    mins[x] = maxs[x] = val;
    while (x > 1) {
      x /= 2;
      mins[x] = min(mins[2*x], mins[2*x+1]);
      maxs[x] = max(maxs[2*x], maxs[2*x+1]);
    }
  }
};


int H, W;
vector<int> R, C;
tree_t* rows_tree;
tree_t* cols_tree;


void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
  ::H = H; ::W = W;
  ::R = R; ::C = C;
  rows_tree = new tree_t(R);
  cols_tree = new tree_t(C);
}

int swap_seats(int a, int b) {
  swap(R[a], R[b]);
  swap(C[a], C[b]);
  rows_tree->update(a, R[a]); cols_tree->update(a, C[a]);
  rows_tree->update(b, R[b]); cols_tree->update(b, C[b]);

  int R_min, R_max;
  int C_min, C_max;
  int ans = 0, i = 0;
  while (i < H*W) {
    tie(R_min, R_max) = rows_tree->query(0, i);
    tie(C_min, C_max) = cols_tree->query(0, i);
    int Size = (R_max + 1 - R_min) * (C_max + 1 - C_min);
    if (i+1 == Size) {
      ans++;
      i++;
    } else {
      i = Size-1;
    }
  }
  return ans;
}
