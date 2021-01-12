#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

string loop(string pwd, string salt, string h) {
    for(int i = 0; i < 1000; i++) {
        string tmp = "";

        if((i % 2) != 0) {
            tmp += pwd;
        }
        else {
            tmp += h;
        }

        if((i % 3) != 0) {
            tmp += salt;
        }
        if((i % 7) != 0) {
            tmp += pwd;
        }
        if((i % 2) != 0) {
            tmp +=h;
        }
        else {
            tmp += pwd;
        }

        h = md5(tmp);
    }
    
    return h;
}