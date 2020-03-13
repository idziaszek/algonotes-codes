// Task: Highway Tolls (IOI 2018)
// Solves subtask 6 for partial points
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "highway.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


vector<int> w;
long long W;
int M;
vector<vector<pair<int,int> > > adj;
vector<int> edge, vert;
int E;


int get_first_edge() {
  int lb = 0, ub = M-1;
  while (lb != ub) {
    int mid = (lb + ub) / 2;
    REP(i, M) {
      w[i] = i <= mid;
    }
    if (ask(w) != W) {
      ub = mid;
    } else {
      lb = mid+1;
    }
  }
  return lb;
}

int get_last_edge() {
  int lb = -1, ub = E-1;
  while (lb != ub) {
    int mid = (lb + ub + 1) / 2;
    REP(i, M) {
      w[i] = edge[i] >= mid;
    }
    if (ask(w) != W) {
      lb = mid;
    } else {
      ub = mid-1;
    }
  }
  return lb;
}


void find_pair(int N, vector<int> U, vector<int> V, int A, int B) {
  M = U.size();
  w.resize(M);
  W = ask(w);

  adj.resize(N);
  REP(i, M) {
    adj[U[i]].push_back(make_pair(i, V[i]));
    adj[V[i]].push_back(make_pair(i, U[i]));
  }

  edge.resize(M);
  vert.resize(M);

  int e = get_first_edge();
  int v = U[e];
  int ans[2];

  REP(j, 2) {
    E = 0;
    queue<int> q;
    vector<int> d(N, -1);
    d[v] = 0;
    q.push(v);

    while (!q.empty()) {
      int w = q.front();
      q.pop();

      for (auto& i : adj[w]) {
        if (d[i.second] == -1) {
          d[i.second] = d[w] + 1;
          vert[E] = i.second;
          edge[i.first] = E++;
          q.push(i.second);
        } else if (d[i.second] == d[w] + 1) {
          edge[i.first] = N;
        }
      }
    }

    int el = get_last_edge();
    v = ans[j] = vert[el];
  }

  answer(ans[0], ans[1]);
}
