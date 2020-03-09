// Task: Mechanical Doll (IOI 2018)
// Solves subtask 3
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

  vector<vector<int> > after(M+1);
  REP(i, N) {
    after[A[i]].push_back(A[(i+1) % N]);
  }
  int S = 0;
  REP(i, M+1) {
    const int size = after[i].size();
    if (size == 0) {
      ;
    } else if (size == 1) {
      C[i] = after[i][0];
    } else if (size == 2) {
      C[i] = --S;
      X.push_back(after[i][0]);
      Y.push_back(after[i][1]);
    } else if (size <= 4) {
      C[i] = --S;
      X.push_back(--S);
      Y.push_back(--S);
      if (size == 4) {
        X.push_back(after[i][0]);
        Y.push_back(after[i][2]);
        X.push_back(after[i][1]);
        Y.push_back(after[i][3]);
      } else {
        X.push_back(C[i]);
        Y.push_back(after[i][1]);
        X.push_back(after[i][0]);
        Y.push_back(after[i][2]);
      }
    }
  }

  answer(C, X, Y);
}
