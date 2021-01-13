#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

const string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string to64(int v, int n) {
    string ret = "";
    for(int i = 0; i < n; i++) {
        ret += base64[v & 0x3f];
        v >>= 6;
    }

    return ret;
}

string finalize(string pwd, string salt, string h) {
    // h.length() returns 32 here, but should be length 16
    // each 2 indices of h represents a hex value, so we need to convert h to h_hex
    // ex, h = ed7a5307588e49ed3a2777d926d62f96
    //  ->h_hex = ed/7a/53/.../2f/96
    string h_hex = "";
    for(int ii = 0; ii < 32; ii += 2) {
        unsigned char hex_placeholder;
        string tmp = "0x";
        tmp = tmp + h[ii] + h[ii+1];
        hex_placeholder = stoul(tmp, nullptr, 16);
        h_hex += hex_placeholder;
    }

    return to64((h_hex[0] << 16) | (h_hex[6] << 8) | (h_hex[12]), 4) +
           to64((h_hex[1] << 16) | (h_hex[7] << 8) | (h_hex[13]), 4) +
           to64((h_hex[2] << 16) | (h_hex[8] << 8) | (h_hex[14]), 4) +
           to64((h_hex[3] << 16) | (h_hex[9] << 8) | (h_hex[15]), 4) +
           to64((h_hex[4] << 16) | (h_hex[10] << 8) | (h_hex[5]), 4) +
           to64(h_hex[11], 2);
}