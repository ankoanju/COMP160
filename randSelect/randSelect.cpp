/*
 * randSelect.cpp
 * COMP160
 * Fall 2020
 *
 * Implementation of the Randomized Selection.
 * Given an array containing n numbers, and a positive integer k <= n, 
 * randSelect returns the k-th smallest element. 
 *
 *
 * Modified by: Anju Ishizaki (aishiz01)
 *          on: November 1st 2020
 *
 */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "randSelect.h"

using namespace std;

int partition(std::vector<int> &v, int arraySize, int pivot_val);
void checkinput(std::vector<int> v, int rankIndex);


// printVector 
// Paramters: vector v
// Returns: none
// Does: Prints vector. Provided in starter code
void printVector(std::vector<int> v) {
    cout << "[ ";
    for (int i : v)
        cout << i << " ";
    cout << "]\n";
}


// checkinput 
// Paramters: vector v, int rankIndex
// Returns: none
// Does: Checks if rankIndex is within the range of vector index
//       Aborts if not. 
void checkinput(std::vector<int> v, int rankIndex) {
    if ( rankIndex >= static_cast<int>(v.size()) ) {
        cerr << "Please enter valid index" << endl;
        abort();
    }
}


// randSelect 
// Paramters: vector v, int rankIndex
// Returns: integer which is the element at the rank requested 
// Does: Calls partition. Recursively calls to find the integer which is the
//       element at the rank requested. Prints each step with different 
//       pivot. 
int randSelect(std::vector<int> v, int rankIndex) {
    
    checkinput(v, rankIndex);
    int num_input = (int)v.size();
    cout << "num input is " << num_input << endl;

    cout << "Looking for value with rank " << rankIndex << " in the array:\n";
    printVector(v);

    // get a random number between 0 and (n-1)
    int rand_pivot = rand() % (int)v.size();
    cout << "rand_pivot_index is" << rand_pivot << endl;


    // randomized element v[rand_pivot]
    cout << "Selected " << v[rand_pivot] << " as the pivot; its rank is ";

    // perform partition on random number
    int pos = partition(v, num_input, rand_pivot);

    cout << pos;
    cout << "; Thus, we recurse on ";
    
    // three cases 
    if ( pos == rankIndex ) {
        cout << "nothing. We are done.";
        return v[pos];
    } else if ( pos > rankIndex ) {
        cout << "the left. \n";
        vector<int> part_left = vector<int>(v.begin(), v.begin() + (pos));
        cout << "this is new left";
        printVector(part_left);
        return randSelect(part_left, rankIndex);
    } else {
        cout << "the right. \n";
        vector<int> part_right = vector<int>(v.begin() + (pos + 1), v.end() );  
        cout << "this is new right";
        printVector(part_right);    
        return randSelect(part_right, rankIndex-pos-1);
    }

}


// partition 
// Paramters: vector v, int arraySize, int rankIndex
// Returns: the index of the pivot in the new array
// Does: Rearranges the elements of the list so that values smaller (or equal) 
//       than the pivot are to the left of the pivot, then the pivot, and 
//       finally the values that are larger than the pivot. Does without using
//       additional memory.
int partition(vector<int> &v, int arraySize, int rand_pivot) {
    int smaller = 0;
    int larger = 0;
    int counter = 1;

    //swap 
    swap(v[0], v[rand_pivot]);

    while ( counter < arraySize ) {
        if ( v[0] < v[smaller + larger + 1] ) {
            larger++;
        } else {
            swap(v[smaller + 1], v[smaller + larger + 1]);
            smaller++;
        }
        // printVector(v);
        counter++;
    }

    // swapback to put it in the middle
    swap(v[0], v[smaller]);
    
    return smaller;
}
