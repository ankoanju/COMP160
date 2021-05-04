////////////////////////////////////////////////////////////////////////////
//
//    Tufts University, Comp 160 DP coding assignment  
//
//    memo.h
//    DP
//
//    includes function students need to implement
//
////////////////////////////////////////////////////////////////////////////


#pragma once

#include <vector>

using namespace std;


int rob(const vector<int> &houses, int i);
int memo_rob(const vector<int> &houses, int i);


bool SBS(const vector<int> &A, int target, int i);
bool memo_SBS(const vector<int> &A, int target, int i);