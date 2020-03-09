// Task: Mechanical Doll (IOI 2018)
// Solves subtask 1
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "doll.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

void create_circuit(int M, vector<int> A) {
  A.push_back(0);
  int N = A.size();
  vector<int> C(M+1);
  vector<int> X, Y;

  REP(i, N) {
    C[A[i]] = A[(i+1) % N];
  }

  answer(C, X, Y);
}
