// Task: Highway Tolls (IOI 2018)
// Solves subtask 5
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "highway.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


vector<int> w, U, V;
int M;


bool different_sets(const vector<int>& grp) {
  REP(i, M) {
    w[i] = grp[U[i]] == grp[V[i]];
  }
  return ask(w) % 2 == 1;
}


void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
  ::U = U; ::V = V;
  M = U.size();
  w.resize(M);

  vector<int> grp(N), grp_diff;
  int s_xor_t = 0;

  REP(bit, 17) {
    REP(i, N) {
      grp[i] = !!(i & 1<<bit);
    }
    if (different_sets(grp)) {
      s_xor_t |= 1 << bit;
      grp_diff = grp;
    }
  }

  int lb = 0, ub = N-1;
  while (lb != ub) {
    int mid = (lb + ub) / 2;
    REP(i, N) {
      grp[i] = grp_diff[i] && lb <= i && i <= mid;
    }
    if (different_sets(grp)) {
      ub = mid;
    } else {
      lb = mid+1;
    }
  }

  answer(lb, lb ^ s_xor_t);
}
