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

  REP(i, Q) {
    ll ans = infty * N;
    stack<pair<int,int> > s;
    vector<ll> cost_le(N), cost_ri(N);

    s.push(make_pair(infty+1, 0));
    ll cost = 0;
    for (int x = L[i]; x <= R[i]; x++) {
      int w = 1;
      while (s.top().first <= H[x]) {
        cost += ll(H[x] - s.top().first) * s.top().second;
        w += s.top().second;
        s.pop();
      }
      cost_le[x] = cost;
      s.push(make_pair(H[x], w));
      cost += H[x];
    }

    while (s.size() > 1) {
      s.pop();
    }
    cost = 0;
    for (int x = R[i]; x >= L[i]; x--) {
      int w = 1;
      while (s.top().first <= H[x]) {
        cost += ll(H[x] - s.top().first) * s.top().second;
        w += s.top().second;
        s.pop();
      }
      cost_ri[x] = cost;
      s.push(make_pair(H[x], w));
      cost += H[x];

      ans = min(ans, cost_le[x] + H[x] + cost_ri[x]);
    }
    C[i] = ans;
  }

  return C;
}
