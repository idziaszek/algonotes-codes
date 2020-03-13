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
  int ans[2];

  REP(bit, 17) {
    REP(i, N) {
      grp[i] = !!(i & 1<<bit);
    }
    if (different_sets(grp)) {
      grp_diff = grp;
    }
  }

  REP(j, 2) {
    int lb = 0, ub = N-1;
    while (lb != ub) {
      int mid = (lb + ub) / 2;
      REP(i, N) {
        grp[i] = (grp_diff[i] ^ j) && lb <= i && i <= mid;
      }
      if (different_sets(grp)) {
        ub = mid;
      } else {
        lb = mid+1;
      }
    }
    ans[j] = lb;
  }

  answer(ans[0], ans[1]);
}
