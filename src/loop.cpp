#include "init.h"
#include "md5.h"
#include <string.h>
using namespace std;

string loop(string pwd, string salt, string h) {
    //h.length() returns 32 here, but should be length 16. 
    //each 2 indices of h represents a hex value, so we need to convert h
    //to h_hex
    //ex, h = ed7a5307588e49ed3a2777d926d62f96
    //  ->h_hex = ed/7a/53/.../2f/96
    //cout << "In loop, h is " << h.length() << endl;
    for(int i = 0; i < 1000; i++) {
        string h_hex = "";
        for(int ii = 0; ii < 32; ii += 2) {
            unsigned char hex_placeholder;
            string tmp = "0x";
            tmp = tmp + h[ii] + h[ii+1];
            hex_placeholder = stoul(tmp, nullptr, 16);
            h_hex += hex_placeholder;
        }
        string tmp = "";

        if((i % 2) != 0) {
            tmp += pwd;
        }
        else {
            tmp += h_hex;
        }

        if((i % 3) != 0) {
            tmp += salt;
        }
        if((i % 7) != 0) {
            tmp += pwd;
        }
        if((i % 2) != 0) {
            tmp +=h_hex;
        }
        else {
            tmp += pwd;
        }

        h = md5(tmp);
    }
    //cout << "In loop: " << h << endl;
    return h;
}
