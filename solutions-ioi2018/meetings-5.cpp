// Task: Meetings (IOI 2018)
// Solves subtask 5
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "meetings.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
typedef long long ll;


template<class T>
struct rmq_tree_t {
  vector<T> maxs;
  int base;
  int n;

  rmq_tree_t(const vector<T>& vals) {
    n = vals.size();
    base = 1;
    while (base < n) { base *= 2; }
    maxs.resize(2*base);
    REP(i, n) {
      maxs[base + i] = vals[i];
    }
    for (int i = base-1; i >= 1; i--) {
      maxs[i] = max(maxs[2*i], maxs[2*i+1]);
    }
  }

  T query(int xl, int xr) {
    // Returns max on range [xl, xr]
    xl += base;
    xr += base;
    T ma = max(maxs[xl], maxs[xr]);
    while (xl/2 != xr/2) {
      if (~xl&1) {
        ma = max(ma, maxs[xl+1]);
      }
      if (xr&1) {
        ma = max(ma, maxs[xr-1]);
      }
      xl /= 2;
      xr /= 2;
    }
    return ma;
  }
};


struct frag_t {
  ll alpha, beta;
  int len;

  frag_t() { }
  frag_t(ll alpha, ll beta, int len) : alpha(alpha), beta(beta), len(len) { }

  ll eval(int off) {
    return alpha * off + beta;
  }
};

struct node2_t {
  int x, xl, xr;
  node2_t* L;
  node2_t* R;

  int frag_len;
  ll frag_off;

  vector<pair<ll*,int> > queries;

  node2_t(int x) : x(x), L(0), R(0), frag_len(0), frag_off(0) { }
};


vector<pair<int,int> > H_pos;
map<int, frag_t> frags;
vector<node2_t*> nodes;


node2_t* merge(node2_t* L, node2_t* R) {
  if (!L) return R;
  if (!R) return L;
  if (H_pos[L->x] >= H_pos[R->x]) {
    L->R = merge(L->R, R);
    return L;
  } else {
    R->L = merge(L, R->L);
    return R;
  }
}

node2_t* create_tree2(int xl, int xr) {
  if (xr - xl == 1) {
    return new node2_t(xl);
  } else {
    int mid = (xl + xr) / 2;
    node2_t* L = create_tree2(xl, mid);
    node2_t* R = create_tree2(mid, xr);
    return merge(L, R);
  }
}


void precalculate(node2_t* no, int xl, int xr) {
  if (no->L) {
    precalculate(no->L, xl, no->x);
  }
  nodes[no->x] = no;
  no->xl = xl;
  no->xr = xr;
  if (no->R) {
    precalculate(no->R, no->x+1, xr);
  }
}

void calculate(node2_t* no) {
  ll Lcost = 0;
  int h = H_pos[no->x].first;

  if (no->L) {
    calculate(no->L);

    no->frag_len = no->L->frag_len;
    no->frag_off = no->L->frag_off;

    auto it = --frags.lower_bound(no->x);
    frag_t& he = it->second;
    Lcost = he.eval(he.len-1) + no->L->frag_off;
  }

  frags[no->x] = frag_t(0, Lcost + h - no->frag_off, 1);
  no->frag_len++;

  frag_t me = frag_t(h, Lcost + 2*h, 0);

  if (no->R) {
    calculate(no->R);

    ll gamma = ll(no->x - no->xl + 1) * h;
    no->R->frag_off += gamma;

    auto it = frags.find(no->R->xl);
    while (it != frags.end() && it->first < no->R->xr) {
      frag_t& he = it->second;
      ll my_end = me.eval(me.len + he.len-1);
      ll his_end = he.eval(he.len-1) + no->R->frag_off;
      if (my_end <= his_end) {
        me.len += he.len;
        auto it_prev = it++;
        frags.erase(it_prev);
        no->R->frag_len--;
      } else {
        break;
      }
    }

    if (it != frags.end() && it->first < no->R->xr) {
      frag_t& he = it->second;
      int lb = 0, ub = he.len-1;
      while (lb != ub) {
        int mid = (lb + ub) / 2;
        if (me.eval(me.len + mid) <= he.eval(mid) + no->R->frag_off) {
          lb = mid+1;
        } else {
          ub = mid;
        }
      }
      he.beta += lb * he.alpha;
      he.len -= lb;
      const_cast<int&>(it->first) += lb;
      me.len += lb;
    }

    if (me.len > 0) {
      me.beta -= no->frag_off;
      frags[no->x+1] = me;
      no->frag_len++;
    }

    if (no->frag_len < no->R->frag_len) {
      for (auto i = frags.find(no->xl); i != it; ++i) {
        i->second.beta += no->frag_off - no->R->frag_off;
      }
      no->frag_off = no->R->frag_off;
    } else {
      for ( ; it != frags.end() && it->first < no->R->xr; ++it) {
        it->second.beta += no->R->frag_off - no->frag_off;
      }
    }

    no->frag_len += no->R->frag_len;
  }

  for (auto& i : no->queries) {
    auto it = --frags.upper_bound(no->xl + i.second);
    int off = no->xl + i.second - it->first;
    frag_t& he = it->second;
    ll cost = he.eval(off) + no->frag_off;

    *(i.first) += cost;
  }
}


vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
  int N = H.size();
  int Q = L.size();
  vector<ll> C(Q);
  vector<ll> Cj[2];
  H_pos.resize(N);
  nodes.resize(N);

  REP(j, 2) {
    Cj[j].resize(Q);
    frags.clear();

    REP(i, N) {
      H_pos[i] = make_pair(H[i], j ? N-1-i : i);
    }
    rmq_tree_t<pair<int,int> > rmq_tree(H_pos);

    node2_t* root = create_tree2(0, N);
    precalculate(root, 0, N);

    REP(i, Q) {
      int x = rmq_tree.query(L[i], R[i]).second;
      if (j) { x = N-1-x; }

      ll cost = ll(x - L[i] + 1) * H[x];
      Cj[j][i] = cost;
      if (x != R[i]) {
        nodes[x]->R->queries.push_back(make_pair(&Cj[j][i], R[i] - x - 1));
      }
    }

    calculate(root);

    reverse(H.begin(), H.end());
    REP(i, Q) {
      L[i] = N-1-L[i];
      R[i] = N-1-R[i];
      swap(L[i], R[i]);
    }
  }

  REP(i, Q) {
    C[i] = min(Cj[0][i], Cj[1][i]);
  }

  return C;
}
