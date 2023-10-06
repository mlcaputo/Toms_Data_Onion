#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>
#include "parityBitOperations.h"
using namespace std;


string removeParityBit(uint8_t input[8]){
    string result = "";
    uint8_t totalBitArray[56];
    
    for(int j = 0; j < 8; j++){
        uint8_t tempBinArray[8];
        int k = 7;
        for (int x = 0; x < 8; ++x) {
            tempBinArray[k] = (input[j] >> x) & 1;
            k--;
        }

        int index = 0;
        while(index < 7){
            totalBitArray[index + (j * 7)] = tempBinArray[index];
            index++;
        }   
    }

    for(int j = 0; j < 7; j++){
        int output = 0;
        int power = 128;

        for(int index = 0; index < 8; index++){
            output += totalBitArray[index + (j * 8)] * power;
            power = power / 2;
        }

        result += (unsigned char) output;
    }

    return result;
}

bool checkParityBit(uint8_t num){
    uint8_t binArray[8];
    int countOfOnes = 0;
    int k = 7;
    for (int j = 0; j < 8; ++j) {
        binArray[k] = (num >> j) & 1;
        if(binArray[k] == 1 && k != 7){
            countOfOnes++;
        }
        k--;
    }

    if(countOfOnes % 2 == 0 && binArray[7] == 0){
        return true;
    }

    if(countOfOnes % 2 == 1 && binArray[7] == 1){
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

