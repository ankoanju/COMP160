/*
 * memo.cpp
 * COMP160
 * Fall 2020
 *
 * Implementation of the memoization for the robbing and SBS algorithms.
 * Optional coding assignment for HW 07 about dynamic programming. 
 * I implemented memo_rob and memo_SBS that each calls helper functions to 
 * recurse and look at the database. 
 *
 *
 * Modified by: Anju Ishizaki (aishiz01)
 *          on: November 15th 2020
 *
 */
#include <unordered_map>
#include "memo.h"

using namespace std;

// struct pair_hash 
// I referenced StackExchange for this struct. (Link below)
// https://stackoverflow.com/questions/32685540/
//              why-cant-i-compile-an-unordered-map-with-a-pair-as-key 
// When I tried declaring the unorderedmap using two parameters pair and int, 
// I had a compiler error. I searched and realize that I need a third 
// parameter which is the struct here.
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &phash) const {
        auto h1 = std::hash<T1>{}(phash.first);
        auto h2 = std::hash<T2>{}(phash.second);
        return h1 ^ h2;  
    }
};


int saverobdb(const vector<int> &houses, int i, unordered_map<int, int> &db);
int saveSBSdb(const vector<int> &A, int target, int i, 
                unordered_map<std::pair<int,int>, int, pair_hash> &db);


// rob (provided in starter code)
int rob(const vector<int> &houses, int i) {
    if (i < 0) {
        return 0;
    } else if (i == 0) {
        return houses[0];
    } else {
        return max(rob(houses, i - 1), houses[i] + rob(houses, i - 2));
    }
}


// memo_rob 
// Paramters: const vector<int> &houses, int i
// Returns: saverobdb(houses, i, rob_database)
// Does: memoized version of rob. calls the helper function.
int memo_rob(const vector<int> &houses, int i) {
    // key will be of int type and mapped value will be of int type 
    unordered_map<int, int> rob_database;
    return saverobdb(houses, i, rob_database);
}


// saverobdb 
// Paramters: const vector<int> &houses, int i, unordered_map<int, int> &db
// Returns: number of houses we can rob 
// Does: Looks for basecases and returns the num of houses we can rob.
//       Otherwise, stores the num of houses in the database and memoize
//       so that when recursed, we can look back at the database.
int saverobdb(const vector<int> &houses, int i, unordered_map<int, int> &db){
    if (db.find(i) != db.end()) {
        return db[i];
    } 

    if (i < 0) {
        // since no houses to rob
        return 0;
    } else if (i == 0) {
        // since you can only rob the first house
        return houses[0];
    } else {
        // otherwise, save to database first and recurse.
        db[i] = max(saverobdb(houses, i - 1, db), houses[i] + saverobdb(houses, i - 2, db));
        return db[i];
    }
}


// SBS (provided in starter code)
bool SBS(const vector<int> &A, int target, int i) {
    if (target == 0) {
        return true;
    } else if (i < 0 and target != 0) {
        return false;
    } else if (A[i] > target) {
        return SBS(A, target, i - 1);
    } else {
        return SBS(A, target, i - 1) or SBS(A, target - A[i], i - 1);
    }
}


// memo_SBS
// Paramters: const vector<int> &A, int target, int i
// Returns: saveSBSdb(A, target, i, SBS_database)
// Does: memoized version of SBS. calls the helper function.
bool memo_SBS(const vector<int> &A, int target, int i) {
    unordered_map<std::pair<int,int>, int, pair_hash> SBS_database;
    return saveSBSdb(A, target, i, SBS_database);
}


// saveSBSdb 
// Paramters: const vector<int> &A, int target, int i, 
//            unordered_map<std::pair<int,int>, int, pair_hash> &db
// Returns: true if there is a subset where the numbers add up 
//          to the target value, otherwise false
// Does: Looks for basecases and returns if we can find a subset where the numbers 
//       add up. Otherwise, false.
//       Stores in database and memoize. So that will recurse only 
//       when it is not in database. 
int saveSBSdb(const vector<int> &A, int target, int i, unordered_map<std::pair<int,int>, int, pair_hash> &db) {
    std::pair<int, int> keypair = {target, i};

    if (db.find(keypair) != db.end()) {
        return db[keypair];
    } 

    if (target == 0) {
        return true;
    } else if (i < 0 and target != 0) {
        return false;
    } else if (A[i] > target) {
        db[keypair] = saveSBSdb(A, target, i - 1, db);
        return db[keypair];
    } else {
        db[keypair] = saveSBSdb(A, target, i - 1, db) or saveSBSdb(A, target - A[i], i - 1, db);
        return db[keypair];
    }
}
