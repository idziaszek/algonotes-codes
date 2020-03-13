// Task: Highway Tolls (IOI 2018)
// Solves subtask 2
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


void dfs(int v, int par) {
  for (auto& i : adj[v]) {
    if (i.second != par) {
      vert[E] = i.second;
      edge[i.first] = E++;
      dfs(i.second, v);
    }
  }
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
  dfs(0, -1);

  int el = get_last_edge();
  answer(0, vert[el]);
}
