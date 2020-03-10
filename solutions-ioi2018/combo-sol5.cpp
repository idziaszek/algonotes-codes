// Task: Combo (IOI 2018)
// Uses N+2 guesses
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "combo.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


const int M = 4;
const char LET[] = "ABXY";


int guess_one(const string& s) {
  int len = press(s + LET[0] + s + LET[1]);
  int idx = 2*(len < s.length()+1);
  len = press(s + LET[idx]);
  idx += (len < s.length()+1);
  return idx;
}


string guess_sequence(int N) {
  int idx[M];
  REP(i, M) { idx[i] = i; }
  string s;

  // First letter
  {
    int id = guess_one(s);
    s += LET[id];
    swap(idx[id], idx[M-1]);
  }

  // Almost rest
  REP(i, N-2) {
    string z;
    REP(j, M-1) {
      z += s + LET[idx[0]] + LET[idx[j]];
    }
    z += s + LET[idx[1]];
    int len = press(z);
    if (len == i+3) {
      s += LET[idx[0]];
    } else if (len == i+2) {
      s += LET[idx[1]];
    } else {
      s += LET[idx[2]];
    }
  }

  // Last letter
  if (N > 1) {
    int id = guess_one(s);
    s += LET[id];
  }

  return s;
}
