// Task: Seats (IOI 2018)
// Solves subtask 5
// Author: Tomasz Idziaszek


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
vector<int> line;
vector<int> delta;
prefixsum_zeros_tree_t* delta_tree;


int calc_delta(int i) {
  if (i == 0) return 0;
  int c = C[i];
  int num = 0;
  num += (c == 0 || line[c-1] > i) ? 1 : -1;
  num += (c == W-1 || line[c+1] > i) ? 1 : -1;
  return num;
}

void update_delta(int c) {
  if (c < 0 || c >= W) return;
  int i = line[c];
  delta[i] = calc_delta(i);
  delta_tree->update(i, delta[i]);
}


void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
  ::H = H; ::W = W;
  ::R = R; ::C = C;
  line.assign(W, 0);
  delta.assign(W, 0);
  REP(i, W) {
    line[C[i]] = i;
  }
  REP(i, W) {
    delta[i] = calc_delta(i);
  }
  delta_tree = new prefixsum_zeros_tree_t(delta);
}

int swap_seats(int a, int b) {
  if (H != 1) return -1;
  swap(C[a], C[b]);
  swap(line[C[a]], line[C[b]]);
  for (int i = -1; i <= 1; i++) {
    update_delta(C[a]+i);
    update_delta(C[b]+i);
  }

  return delta_tree->count_prefixsum_zeros();
}
