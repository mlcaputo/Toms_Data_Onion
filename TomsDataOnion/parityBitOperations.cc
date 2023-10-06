#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>
#include "parityBitOperations.h"
using namespace std;


string removeParityBit(uint8_t input[8]){
    string result = "";
    
    for (int j = 0; j < 7; j++) {
        input[j] = input[j] >> 1; // Shift right and left once to remove parity bit
        input[j] = input[j] << 1;

        input[j] = (input[j] << j) | (input[j + 1] >> (7 - j));
        result += (unsigned char) input[j];
    }
  
    return result;
}

bool checkParityBit(uint8_t num){
    int countOfOnes = 0;

    while (num != 0) {
        num = num & (num - 1); // Removes a sig 1 with each pass
        countOfOnes++;
    }

    if(countOfOnes % 2 == (num & (1 << 1)) ){
        return true;
    }
    if(countOfOnes % 2 == (num & (1 << 1)) ){
        return true;
    }

    return false;      
}

string parityBitOperation(string input){
    string result = "";
    int inputLen = 0;
    inputLen = input.size();
    int numOfValidBytes = 0;
    uint8_t validByteArray[8];

    for(int i = 0; i < inputLen; i++){
        uint8_t temp = (uint8_t) input[i];
        if(checkParityBit(temp)){
            validByteArray[numOfValidBytes] = temp;
            numOfValidBytes++;
        }
        
        if(numOfValidBytes == 8){
            result += removeParityBit(validByteArray);
            numOfValidBytes = 0;
        }
    }

    return result;
}

