#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

string pwd_init(string pwd, string salt) {
    string res = pwd + "$1$" + salt;
    string h = md5(pwd + salt + pwd);
    int length = pwd.size();

    while(length > 0) {
        for(int i = 0; i < min(16, length) * 2; i += 2) {
            unsigned char hex_placeholder;
            string tmp = "0x";
            tmp = tmp + h[i] + h[i+1];
            hex_placeholder = stoul(tmp, nullptr, 16);
            res += hex_placeholder;
        }
        length -= 16;
    }

    for(int i = pwd.size(); i != 0; i >>= 1) {
        if(i&1) {
            res += '\0';
        }
        else {
            res += pwd[0];
        }
    }
    
    return md5(res);
}