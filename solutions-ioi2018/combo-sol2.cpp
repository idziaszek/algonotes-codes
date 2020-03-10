// Task: Combo (IOI 2018)
// Uses 3N guesses
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "combo.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


const int M = 4;
const char LET[] = "ABXY";


string guess_sequence(int N) {
  string s;

  REP(i, N) {
    REP(j, M-1) {
      int len = press(s + LET[j]);
      if (len == i+1) {
        s += LET[j];
        break;
      }
    }
    if (s.size() != i+1) {
      s += LET[M-1];
    }
  }

  return s;
}
