// Task: Mechanical Doll (IOI 2018)
// Solves subtasks 4, 5 and 6 for half points
// Author: Tomasz Idziaszek


#include <bits/stdc++.h>
#include "doll.h"
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

int generate(const vector<int>& after,
             int& S, vector<int>& X, vector<int>& Y) {
  const int size = after.size();
  if (size == 0) {
    return 0;
  } else if (size == 1) {
    return after[0];
  } else {
    int k = 1, K=0;
    while (k < size) { k *= 2; K++; }

    vector<int> revbits(k);
    REP(j, k) {
      revbits[j] = revbits[j/2]/2 | ((j&1) << K-1);
    }

    const int id = --S;
    REP(j, (k-1)/2) {
      X.push_back(--S);
      Y.push_back(--S);
    }
    REP(j, k) {
      vector<int>& where = j%2 ? Y : X;
      if (revbits[j] < (k-size)) {
        where.push_back(id);
      } else {
        where.push_back(after[ revbits[j] - (k-size) ]);
      }
    }
    return id;
  }
}

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
    C[i] = generate(after[i], S, X, Y);
  }

  answer(C, X, Y);
}
