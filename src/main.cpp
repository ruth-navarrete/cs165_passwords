#include <iostream>
#include <string.h>
#include <vector>
#include "init.h"
#include "loop.h"
#include "finalize.h"
using namespace std;
// team2:$1$4fTgjp6q$Gd5qwn1CNK8AbBmGkbmT10:16653:0:99999:7:::
// change goal to Gd5qwn1CNK8AbBmGkbmT10
string salt = "4fTgjp6q";
string goal = "Gd5qwn1CNK8AbBmGkbmT10";

void pwd_recurs(vector<char>,string,int);

int main(){
    vector<char> alphabat;

    cout << "step 0: main" << endl;

    for(int i = 0; i < 26; i++) {
        alphabat.push_back((char)(97 + i));
    }

    // example usage of pwd_init();
    // string pwd = "zhgnnd";
    // string salt = "hfT7jp2q";
    // cout << "h = " << pwd_init(pwd, salt) << endl;
    for(int i = 1; i < 7; i++) {
        pwd_recurs(alphabat, "", i);
    }

    return 0;
}

// use backtracking to get through all the possible candidates
void pwd_recurs(vector<char> alphabat, string curr, int pwdlen) {
    // if no more combinations of password to try, current combination length is done
    if(pwdlen == 0) {
        // check given hash and generated hash here
        // curr is the current string being tested, goal is the hashed password
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
    // iterate over the letters in alphabat
    for(int ii = 0; ii < alphabat.size(); ii++) {
        string candidate;
        // append the current letter to the current combination
        candidate = curr + alphabat[ii];
        // check next letter 
        pwd_recurs(alphabat, candidate, pwdlen - 1);
    }
}