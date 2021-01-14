#include <iostream>
#include <string.h>
#include <vector>
#include "init.h"
#include "loop.h"
#include "finalize.h"
#include <stdio.h>
#include "omp.h"
using namespace std;
#define MAX_THREADS 5
// team2:$1$4fTgjp6q$Gd5qwn1CNK8AbBmGkbmT10:16653:0:99999:7:::
// change goal to Gd5qwn1CNK8AbBmGkbmT10

string salt = "4fTgjp6q";
string goal = "Gd5qwn1CNK8AbBmGkbmT10";

// actual
//string salt = "4fTgjp6q";
//string goal = "Gd5qwn1CNK8AbBmGkbmT10";

// testing
// team0:$1$hfT7jp2q$wPwz7GC6xLt9eQZ9eJkaq.:16653:0:99999:7:::(zhgnnd)


void pwd_recurs(vector<char>,string,int);

int main(){
    vector<char> alphabet;
    int lowest_length = 1;
    int upper_bound = 7;
    double start_time;
    cout << "step 0: main" << endl;

    for(int i = 0; i < 26; i++) {
        alphabet.push_back((char)(97 + i));
    }
    // string curr = "zhgnnd";
    // string salt_test = "hfT7jp2q";
    // string result = pwd_init(curr, salt_test);
    // cout << "The result after init is: " << result << endl;
    //     result = loop(curr, salt_test, result);
    //     cout << "The result after loop is: " << result << endl;
    //     result = finalize(result);
    //     cout << "The result after finalize is: " << result << endl;
    //     if(result == "wPwz7GC6xLt9eQZ9eJkaq.") {
    //         cout << "Found:  " << curr << endl;
    //         // terminate the function early once we find the password
    //         exit(0);
    //     }
    omp_set_num_threads(MAX_THREADS);
    int i;
    start_time = omp_get_wtime();
    for(int i = 1; i < 2; i++) {
        string starting_letter = string(1,alphabet[i]);
        cout << "Currently checking string starting with: " << starting_letter << endl;
        pwd_recurs(alphabet, starting_letter, 5);
        cout << "Passwords starts with " << alphabet[i] << " are cleared.\n";
    }
    double end_time = omp_get_wtime() -start_time;
    cout << "Total elaspsed time = " << end_time << endl;
    return 0;
}

// use backtracking to get through all the possible candidates
void pwd_recurs(vector<char> alphabet, string curr, int pwdlen) {
    // if no more combinations of password to try, current combination length is done
    if(pwdlen == 0) {
        // check given hash and generated hash here
        // curr is the current string being tested, goal is the hashed password

        //cout << curr << endl;

        string result = pwd_init(curr, salt);
        result = loop(curr, salt, result);
        result = finalize(curr, salt, result);
        if(result == goal) {
            cout << "Found:  " << curr << endl;
            // terminate the function early once we find the password
            exit(0);
        }
        return;
    }
    
    // if there are still combinations to check
    // iterate over the letters in alphabet
    int ii;
    #pragma omp parallel for private(ii)
    for(int ii = 0; ii < alphabet.size(); ii++) {
        string candidate;
        // append the current letter to the current combination
        candidate = curr + alphabet[ii];
        // check next letter 
        
        pwd_recurs(alphabet, candidate, pwdlen - 1);
    }
}