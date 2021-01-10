#include <iostream>
#include <string.h>
#include "init.h"
using namespace std;

int main(){
    string pwd = "zhgnnd";
    string salt = "hfT7jp2q";
    cout << "h = " << pwd_init(pwd, salt) << endl;
    return 0;
}