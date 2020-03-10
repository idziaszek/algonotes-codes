// Task: Seats (IOI 2018)
// Solves subtask 4
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "seats.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


int H, W;
vector<int> R, C;
vector<int> R_mins, R_maxs;
vector<int> C_mins, C_maxs;
vector<bool> beaut;
int total;


void update_maxmin(int i) {
  R_mins[i+1] = min(R_mins[i], R[i]);
  R_maxs[i+1] = max(R_maxs[i], R[i]);
  C_mins[i+1] = min(C_mins[i], C[i]);
  C_maxs[i+1] = max(C_maxs[i], C[i]);
  int Size = (R_maxs[i+1] + 1 - R_mins[i+1]) * (C_maxs[i+1] + 1 - C_mins[i+1]);
  if (i+1 == Size && !beaut[i+1]) {
    beaut[i+1] = true;
    total++;
  } else if (i+1 != Size && beaut[i+1]) {
    beaut[i+1] = false;
    total--;
  }
}


void give_initial_chart(int H, int W, vector<int> R, vector<int> C) {
  ::H = H; ::W = W;
  ::R = R; ::C = C;
  R_mins.assign(H*W+1, H*W);
  R_maxs.assign(H*W+1, -1);
  C_mins.assign(H*W+1, H*W);
  C_maxs.assign(H*W+1, -1);
  beaut.assign(H*W+1, false);

  REP(i, H*W) {
    update_maxmin(i);
  }
}

int swap_seats(int a, int b) {
  swap(R[a], R[b]);
  swap(C[a], C[b]);
  for (int i = min(a,b); i <= max(a,b); i++) {
    update_maxmin(i);
  }
  return total;
}
