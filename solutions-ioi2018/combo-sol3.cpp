// Task: Combo (IOI 2018)
// Uses 2.25N guesses on average
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "combo.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


const int M = 4;
const char LET[] = "ABXY";


string guess_sequence(int N) {
  int idx[M];
  REP(i, M) { idx[i] = i; }
  string s;

  REP(i, N) {
    random_shuffle(idx, idx+M);
    REP(j, M-1) {
      int len = press(s + LET[idx[j]]);
      if (len == i+1) {
        s += LET[idx[j]];
        break;
      }
    }
    if (s.size() != i+1) {
      s += LET[idx[M-1]];
    }
  }

  return s;
}
