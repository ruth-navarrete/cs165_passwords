#include <iostream>
#include <string.h>
#include <vector>
#include "init.h"
using namespace std;
string goal = "gseq";
string answer;
void pwd_recurs(vector<char>,string,int);
int checkPwd(string);
int main(){
    vector<char> alphabat;
    for(int i = 0; i < 26; i++){
        alphabat.push_back((char)(97 + i));
    }
    // for(auto a : alphabat){
    //     cout << a <<endl;
    // }
    // string pwd = "zhgnnd";
    // string salt = "hfT7jp2q";
    // cout << "h = " << pwd_init(pwd, salt) << endl;
    for(int i = 1; i < 7; i++){
        pwd_recurs(alphabat, "", i);
    }
    //pwd_recurs(alphabat, "", 0);
    return 0;
}

//use backtracking to get through all the possible candidates
void pwd_recurs(vector<char> alphabat, string curr, int pwdlen){
    if(pwdlen == 0){
        if(checkPwd(curr)){
            exit(0);
        }
        return;
    }

    // if(checkPwd(curr)){
    //     exit(0);
    // }
    // if(pwdlen == 6){
    //     return;
    // }
    for(int ii = 0; ii < alphabat.size(); ii++){
        string candidate;
        candidate = curr + alphabat[ii];
         cout << candidate << endl;
        pwd_recurs(alphabat, candidate, pwdlen - 1);
    }
}

int checkPwd(string curr){
    if(curr == goal){
        cout << "Found:  " << curr << endl;
        return 1;
    }
    return 0;
}