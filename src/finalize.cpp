#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

const string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


string to64(unsigned long v, int n) {
    string ret ="";
    for(int i = 0; i < n; i++) {
        ret += base64[v & 0x3f];
        v >>= 6;
    }
    return ret;
}


string finalize(string h) {
    string h_hex = "";
    for(int i = 0; i < 32; i += 2) {
        unsigned char hex_placeholder;
        string tmp = "0x";
        tmp = tmp + h[i] + h[i+1];
        
        hex_placeholder = stoul(tmp, nullptr, 16);

        h_hex += hex_placeholder;
    }
    h = h_hex;
    
    return to64((((unsigned char)h[0]) << 16) | (((unsigned char)h[6]) << 8) | ((unsigned char)h[12]), 4) +
           to64(((unsigned char)h[1] << 16) | ((unsigned char)h[7] << 8) | ((unsigned char)h[13]), 4) +
           to64(((unsigned char)h[2] << 16) | ((unsigned char)h[8] << 8) | ((unsigned char)h[14]), 4) +
           to64(((unsigned char)h[3] << 16) | ((unsigned char)h[9] << 8) | ((unsigned char)h[15]), 4) +
           to64(((unsigned char)h[4] << 16) | ((unsigned char)h[10] << 8) | ((unsigned char)h[5]), 4) +
           to64((unsigned char)h[11], 2);
