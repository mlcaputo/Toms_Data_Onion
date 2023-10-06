#include "bitOperations.h"
#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>
#include <climits>

using namespace std;


uint8_t flipEveryOther(uint8_t num){
    uint8_t mask = 85; // 0101 0101
    num ^= mask;       // num XOR mask 
    return num;

}

uint8_t rotateRight(uint8_t num){
    return (num >> 1) | (num << 7); // OR combines right shift(1x) and left shifts(7x)
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
