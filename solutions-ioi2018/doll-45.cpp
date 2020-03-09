// Task: Mechanical Doll (IOI 2018)
// Solves subtask 4 and 5
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

    vector<int> revbits(k), go(k);
    REP(j, k) {
      revbits[j] = revbits[j/2]/2 | ((j&1) << K-1);
    }

    const int id = --S;
    REP(lev, K-1) {
      REP(j, 1<<lev) {
        if ((j << K-lev) + (1 << K-lev) <= (k-size)) {
          ;
        } else if ((j << K-lev) + (1 << K-lev-1) <= (k-size)) {
          X.push_back(id);
          Y.push_back(--S);
        } else {
          X.push_back(--S);
          Y.push_back(--S);
        }
      }
    }

    int ptr = 0;
    REP(j, k) {
      if (revbits[j] < (k-size)) {
        ;
      } else {
        go[ revbits[j] ] = after[ptr++];
      }
    }

    REP(j, k/2) {
      if (2*j + 2 <= (k-size)) {
        ;
      } else if (2*j + 1 <= (k-size)) {
        X.push_back(id);
        Y.push_back(go[2*j+1]);
      } else {
        X.push_back(go[2*j]);
        Y.push_back(go[2*j+1]);
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
