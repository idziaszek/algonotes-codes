// Task: Seats (IOI 2018)
// Solves subtask 6
// Author: Tomasz Idziaszek
// Explanation: algonotes.com/en/solutions-ioi2018


#include <bits/stdc++.h>
#include "seats.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


struct info_t {
  int hl;
  int hr;
  int cnt;
  info_t() : hl(0), hr(0), cnt(1) { }
};

info_t join(const info_t& L, const info_t& R) {
  info_t I;
  int diff = L.hr - R.hl;
  if (diff == 0) {
    I.hl = L.hl;
    I.hr = R.hr;
    I.cnt = L.cnt + R.cnt - (L.hr == 0);
  } else if (diff < 0) {
    I.hl = L.hl - diff;
    I.hr = R.hr;
    I.cnt = R.cnt;
  } else {
    I.hl = L.hl;
    I.hr = R.hr + diff;
    I.cnt = L.cnt;
  }
  return I;
}

info_t single(int val) {
  info_t I;
  I.hl = max(-val, 0);
  I.hr = max(val, 0);
  I.cnt = 1 + (val == 0);
  return I;
}

struct prefixsum_zeros_tree_t {
  vector<info_t> tree;
  int base;
  int n;

  prefixsum_zeros_tree_t(const vector<int>& vals) {
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

  int count_prefixsum_zeros() {
    return tree[1].cnt - 1;
  }

  void update(int x, int val) {
    x += base;
    tree[x] = single(val);
    while (x > 1) {
      x /= 2;
      tree[x] = join(tree[2*x], tree[2*x+1]);
    }
  }
};


int H, W;
vector<int> R, C;
vector<vector<int> > grid;
vector<int> delta_2;
prefixsum_zeros_tree_t* delta_2_tree;


int calc_delta_2(int i) {
  if (i == 0) return 0;
  int num_1 = 0, num_3 = 0;
  REP(ir, 2) REP(ic, 2) {
    int cnt = 0;
    REP(iir, 2) REP(iic, 2) {
      int nr = R[i] - 1 + ir + iir;
      int nc = C[i] - 1 + ic + iic;
      if (nr < 0 || nr >= H || nc < 0 || nc >= W || grid[nr][nc] > i) ++cnt;
    }
    if (cnt == 1) num_1++;
    else if (cnt == 2) num_1--;
    else if (cnt == 3) num_3++;
    else num_3--;
  }
  return num_1 + num_3;
}

void update_delta_2(int r, int c) {
  if (r < 0 || r >= H || c < 0 || c >= W) return;
  int i = grid[r][c];
  delta_2[i] = calc_delta_2(i);
  delta_2_tree->update(i, delta_2[i]);
}


void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
  ::H = H; ::W = W;
  ::R = R; ::C = C;
  grid.assign(H, vector<int>(W));
  REP(i, H*W) {
    grid[R[i]][C[i]] = i;
  }

  delta_2.assign(H*W, 0);
  REP(i, H*W) {
    delta_2[i] = calc_delta_2(i);
  }
  delta_2_tree = new prefixsum_zeros_tree_t(delta_2);
}

int swap_seats(int a, int b) {
  swap(R[a], R[b]);
  swap(C[a], C[b]);
  swap(grid[R[a]][C[a]], grid[R[b]][C[b]]);
  for (int ir = -1; ir <= 1; ir++) {
    for (int ic = -1; ic <= 1; ic++) {
      update_delta_2(R[a]+ir, C[a]+ic);
      update_delta_2(R[b]+ir, C[b]+ic);
    }
  }

  return delta_2_tree->count_prefixsum_zeros();
}
