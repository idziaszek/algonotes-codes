// Task: Meetings (IOI 2018)
// Solves subtask 1
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

  REP(i, Q) {
    ll ans = infty * N;
    for (int x = L[i]; x <= R[i]; x++) {
      // test candidate x
      ll cost = 0;
      int maxh = H[x];
      for (int k = x; k >= L[i]; k--) {
        maxh = max(maxh, H[k]);
        cost += maxh;
      }
      maxh = H[x];
      for (int k = x+1; k <= R[i]; k++) {
        maxh = max(maxh, H[k]);
        cost += maxh;
      }
      ans = min(ans, cost);
    }
    C[i] = ans;
  }

  return C;
}
