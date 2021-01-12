#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

const string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string to64(int v, int n) {
    string ret ="";
    for(int i = 0; i < n; i++) {
        ret += base64[v&0x3f];
        v >>= 6;
    }

    return ret;
}

string finalize(string pwd, string salt, string h) {
    return to64((h[0] << 16) | (h[6] << 8) | (h[12]), 4) +
           to64((h[1] << 16) | (h[7] << 8) | (h[13]), 4) +
           to64((h[2] << 16) | (h[8] << 8) | (h[14]), 4) +
           to64((h[3] << 16) | (h[9] << 8) | (h[15]), 4) +
           to64((h[4] << 16) | (h[10] << 8) | (h[5]), 4) +
           to64(h[11], 2);
}