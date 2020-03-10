// Task: Combo (IOI 2018)
// Uses 2N guesses
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
    int len = press(s + LET[0] + s + LET[1]);
    int idx = 2*(len < i+1);
    len = press(s + LET[idx]);
    idx += (len < i+1);
    s += LET[idx];
  }

  return s;
}
