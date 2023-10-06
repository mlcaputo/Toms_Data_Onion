#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <Bits.h>
#include "XORDecoder.h"

using namespace std;

string decodeXOR(string input, uint8_t key[32]){
    int inputLen = 0;
    inputLen = input.length();
    string result = "";
    int keyIndex = 0;

    for(int i = 0; i < inputLen; i++){ // change 128 to inputLen to decode entire payload
        uint8_t temp = (uint8_t) input[i];
        if(keyIndex % 32 == 0 && keyIndex != 0){
            keyIndex = 0;
            temp = temp ^ key[keyIndex];
            keyIndex++;
        }
        else {
            temp = key[keyIndex] ^ temp;
            keyIndex++;
        }

        result += (unsigned char) temp;
    }
    return result;
}

string findKey(string input){
    uint8_t keyhint[32];
    uint8_t key[32];

    string hint = "==[ Layer 4/6: Network Traffic ]";

    for(int i = 0; i < 32; i++){
        keyhint[i] = (uint8_t) hint[i];
        
    }

    for(int i = 0; i < 32; i++){
        uint8_t temp = (uint8_t) input[i];
        key[i] = keyhint[i] ^ temp;
    }

    string result = decodeXOR(input, key);
    
    return result;
}



string OperationXOR(string input){
    return findKey(input);
}

