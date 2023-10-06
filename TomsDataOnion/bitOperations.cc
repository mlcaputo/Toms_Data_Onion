#include "bitOperations.h"
#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>

using namespace std;

uint8_t binArrayToInt(uint8_t binArray[8]){
    int output = 0;
    int power = 128;

    for(int index = 0; index < 8; index++){
        output += binArray[index] * power;
        power = power / 2;
    }

    return output;
}

uint8_t flipEveryOther(uint8_t num){
    uint8_t binArray[8];
    int k = 7;
    for (int j = 0; j < 8; ++j) {
        binArray[k] = (num >> j) & 1;
        k--;
    }

    for(int i = 0; i < 8; i++){
        if(i % 2 != 0){
            binArray[i] = !binArray[i];
        }
    }

    return binArrayToInt(binArray);

}

uint8_t rotateRight(uint8_t num){
    uint8_t binArray[8];
    int k = 7;
    for (int j = 0; j < 8; ++j) {
        binArray[k] = (num >> j) & 1;
        k--;
    }

    uint8_t hold = binArray[7];
    for(int i = 7; i >= 0; i--){
        if(i == 0){
            binArray[i] = hold;
        }
        else{
            binArray[i] = binArray[i - 1];
        }
    }

    return binArrayToInt(binArray);
}

string bitwiseOperations(string input){
    string result = "";
    int inputLen = 0;
    inputLen = input.size();

    for(int i = 0; i < inputLen; i++){
        uint8_t temp = (uint8_t) input[i];
        temp = flipEveryOther(temp);
        temp = rotateRight(temp);

        result += (unsigned char) temp; 

    }

    return result;
}
