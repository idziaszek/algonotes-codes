// Task: Combo (IOI 2018)
// Uses 4N guesses
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "combo.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)


const int M = 4;
const char LET[] = "ABXY";


string guess_sequence(int N) {
  int len[M];
  string s;

  REP(i, N) {
    REP(j, M) {
      len[j] = press(s + LET[j]);
    }
    REP(j, M) {
      if (len[j] == i+1) {
        s += LET[j];
        break;
      }
    }
  }

  return s;
}
