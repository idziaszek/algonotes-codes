// Task: Meetings (IOI 2018)
// Solves subtask 2
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "meetings.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;


const ll infty = 1000000000;


vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
  int N = H.size();
  int Q = L.size();
  vector<ll> C(Q);

  vector<vector<ll> > cost_le(N, vector<ll>(N)), cost_ri(N, vector<ll>(N));
  REP(x, N) {
    ll cost = 0;
    int maxh = H[x];
    for (int k = x-1; k >= 0; k--) {
      maxh = max(maxh, H[k]);
      cost += maxh;
      cost_le[x][k] = cost;
    }
    cost = 0;
    maxh = H[x];
    for (int k = x+1; k < N; k++) {
      maxh = max(maxh, H[k]);
      cost += maxh;
      cost_ri[x][k] = cost;
    }
  }

  REP(i, Q) {
    ll ans = infty * N;
    for (int x = L[i]; x <= R[i]; x++) {
      ll cost = cost_le[x][L[i]] + H[x] + cost_ri[x][R[i]];
      ans = min(ans, cost);
    }
    C[i] = ans;
  }

  return C;
}
