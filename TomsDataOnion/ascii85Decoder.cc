#include "ascii85Decoder.h"
#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>
using namespace std;

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

    // Adds padding for payload
    if(moddedSize != 0){
        for(int i = 0; i < moddedSize; i++){
            payloadBase += "u";
            payloadSize++;
        }
    }

    
    int i = 0;
    while(i <= payloadSize - 5){
        string payLoadChunk  = payloadBase.substr(i, 5);

        // Checks for special character 'z'
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
        uint8_t buffer[4];
        uint8_t binArrayOfChunk[32];
    
        int symbol1 = int(payLoadChunk[0]) -33;
        int symbol2 = int(payLoadChunk[1]) -33;
        int symbol3 = int(payLoadChunk[2]) -33;
        int symbol4 = int(payLoadChunk[3]) -33;
        int symbol5 = int(payLoadChunk[4]) -33;

        // Convert to base 85
        symbol1 = symbol1 * 52200625;
        symbol2 = symbol2 * 614125;
        symbol3 = symbol3 * 7225;
        symbol4 = symbol4 * 85;
        chunkInt = symbol1 + symbol2 + symbol3 + symbol4 + symbol5;
        
        // Separates 32 bit int into individual bytes
        buffer[0] = (chunkInt >> 24) & 0xFF;
        buffer[1] = (chunkInt >> 16) & 0xFF;
        buffer[2] = (chunkInt >> 8) & 0xFF;
        buffer[3] = chunkInt & 0xFF;
        
        for(int j = 0; j < 4; j++){
            result += (unsigned char) buffer[j];
        }
    }

    return result;


}
