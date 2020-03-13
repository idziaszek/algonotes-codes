// Task: Highway Tolls (IOI 2018)
// Solves subtask 1
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "highway.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


vector<int> w;
long long W;
int M;


void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
  M = U.size();
  w.resize(M);
  W = ask(w);

  vector<int> deg(N);
  REP(i, M) {
    w[i] = 1;
    if (ask(w) != W) {
      deg[U[i]]++;
      deg[V[i]]++;
    }
    w[i] = 0;
  }
  int ans[2] = { -1, -1 };
  REP(i, N) {
    if (deg[i] == 1) {
      ans[ ans[0] != -1 ] = i;
    }
  }
  answer(ans[0], ans[1]);
}
