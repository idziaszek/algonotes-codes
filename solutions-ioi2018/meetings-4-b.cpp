// Task: Meetings (IOI 2018)
// Solves subtask 4
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "meetings.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;


vector<int> H;


struct node_t {
  int best;
  int xl, xr;
  int xh;
  node_t* L;
  node_t* R;
  node_t(int xl, int xr) : best(0), xl(xl), xr(xr) { }
};

node_t* create_tree(int xl, int xr) {
  node_t* no = new node_t(xl, xr);
  if (xl < xr) {
    int top = *max_element(H.begin() + xl, H.begin() + xr);

    vector<int> maxes;
    for(int i=xl; i<xr; ++i) {
      if (H[i] == top) maxes.push_back(i);
    }

    int xh = maxes[maxes.size()/2];

    node_t* L = create_tree(xl, xh);
    node_t* R = create_tree(xh+1, xr);

    no->best = min(L->best + H[xh] * (xr - xh),
                   H[xh] * (xh+1 - xl) + R->best);
    no->xh = xh;
    no->L = L;
    no->R = R;
  }
  return no;
}

int query(node_t* no, int xl, int xr) {
  if (no->xl == no->xr) {
    return 0;
  } else if (xr <= no->xh) {
    return query(no->L, xl, xr);
  } else if (no->xh+1 <= xl) {
    return query(no->R, xl, xr);
  } else if (xl == no->xl && no->xr == xr) {
    return no->best;
  } else {
    return min(query(no->L, xl, no->xh) + H[no->xh] * (xr - no->xh),
               H[no->xh] * (no->xh+1 - xl) + query(no->R, no->xh+1, xr));
  }
}


vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
  ::H = H;
  int N = H.size();
  int Q = L.size();
  vector<ll> C(Q);

  node_t* root = create_tree(0, N);
  REP(i, Q) {
    C[i] = query(root, L[i], R[i]+1);
  }

  return C;
}
