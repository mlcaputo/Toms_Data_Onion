#include "ascii85Decoder.h"
#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>
using namespace std;

uint8_t binArrayToInt(uint8_t binArray[32], int positionNum){
    int output = 0;
    int power = 128;

    for(int index = 8 * positionNum; index < (8 * (positionNum + 1)); index++){
        output += binArray[index] * power;
        power = power / 2;
    }

    return output;
}


string ascii85Decoder(std::string payloadBase){

    string result = "";
    int payloadSize = 0;
    payloadSize = payloadBase.size();

    //Removes "<~" and "~>" from front and rear of string
    payloadBase.erase(payloadSize - 2, 2);
    payloadBase.erase(0, 2);
    payloadSize = payloadSize - 4;
    int moddedSize = 0;
    moddedSize = payloadSize % 5;

    if(moddedSize != 0){
        for(int i = 0; i < moddedSize; i++){
            payloadBase += "u";
            payloadSize++;
        }
    }

    int i = 0;
    while(i <= payloadSize - 5){
        string payLoadChunk  = payloadBase.substr(i, 5);

        if(payLoadChunk[0] == 'z'){
            payLoadChunk = "!!!!!";
            payloadBase += "u";
            payloadSize++;
            i++;
        }
        else{
            i = i + 5;
        }

        uint32_t chunkInt = 0;
        uint8_t binArrayOfChunk[32];
    
        int symbol1 = int(payLoadChunk[0]) -33;
        int symbol2 = int(payLoadChunk[1]) -33;
        int symbol3 = int(payLoadChunk[2]) -33;
        int symbol4 = int(payLoadChunk[3]) -33;
        int symbol5 = int(payLoadChunk[4]) -33;

        symbol1 = symbol1 * 52200625;
        symbol2 = symbol2 * 614125;
        symbol3 = symbol3 * 7225;
        symbol4 = symbol4 * 85;
        
        chunkInt = symbol1 + symbol2 + symbol3 + symbol4 + symbol5;
        
        int k = 31;
        for (int j = 0; j < 32; ++j) {
            binArrayOfChunk[k] = (chunkInt >> j) & 1;
            k--;
        }

        
        for(int j = 0; j < 4; j++){
            uint8_t temp  = 0;
            temp = binArrayToInt(binArrayOfChunk, j);
            result += (unsigned char) temp;
        }
    }

    return result;


}
