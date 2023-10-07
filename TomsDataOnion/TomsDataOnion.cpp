// TomsDataOnion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include "FileReader.h"
#include "ascii85Decoder.h"
#include "bitOperations.h"
#include "parityBitOperations.h"
#include "XORDecoder.h"
#include "NetworkDecoder.h"


using namespace std;

int main() {

#pragma region Layer 0
    // READS IN TEXT FROM TOM'S ONION
    string basePayload = readFile("Payload.txt");

    // ASCII85 DECODER
    string basePayloadOutput = ascii85Decoder(basePayload);

    // FINDS NEXT HINT AND PAYLOAD, SAVES NEXT PAYLOAD TO NEW TEXT FILE
    size_t startOfNewPayload = basePayloadOutput.find("<~");
    string layer1Info = basePayloadOutput.substr(0, startOfNewPayload);
    makeTextFile("Layer1Payload.txt", basePayloadOutput.substr(startOfNewPayload));
#pragma endregion 


#pragma region Layer 1
    // READS IN TEXT FROM LAYER1PAYLOAD FILE
    string layer1Payload = readFile("Layer1Payload.txt");

    // ASCII85 DECODING + BITWISE OPERATION
    string layer1PayloadOutput = ascii85Decoder(layer1Payload);
    layer1PayloadOutput = bitwiseOperations(layer1PayloadOutput);

    // FINDS NEXT HINT AND PAYLOAD, SAVES NEXT PAYLOAD TO NEW TEXT FILE
    startOfNewPayload = layer1PayloadOutput.find("<~");
    string layer2Info = layer1PayloadOutput.substr(0, startOfNewPayload);
    makeTextFile("Layer2Payload.txt", layer1PayloadOutput.substr(startOfNewPayload));
#pragma endregion 


#pragma region Layer 2
    // READS IN TEXT FROM LAYER2PAYLOAD FILE
    string layer2Payload = readFile("Layer2Payload.txt");

    // ASCII85 DECODING + PARITY BIT OPERATION
    string layer2PayloadOutput = ascii85Decoder(layer2Payload);
    layer2PayloadOutput = parityBitOperation(layer2PayloadOutput);

    // FINDS NEXT HINT AND PAYLOAD, SAVES NEXT PAYLOAD TO NEW TEXT FILE
    startOfNewPayload = layer2PayloadOutput.find("<~");
    string layer3Info = layer2PayloadOutput.substr(0, startOfNewPayload);
    makeTextFile("Layer3Payload.txt", layer2PayloadOutput.substr(startOfNewPayload));
#pragma endregion 


#pragma region Layer 3
    string layer3Payload = readFile("Layer3Payload.txt");
    string layer3PayloadOutput = ascii85Decoder(layer3Payload);
    layer3PayloadOutput = OperationXOR(layer3PayloadOutput);

    startOfNewPayload = layer3PayloadOutput.find("<~");
    string layer4Info = layer3PayloadOutput.substr(0, startOfNewPayload);
    makeTextFile("Layer4Payload.txt", layer3PayloadOutput.substr(startOfNewPayload));
#pragma endregion 


#pragma region Layer 4
    string layer4Payload = readFile("Layer4PayLoad.txt");
    string layer4PayloadOutput = ascii85Decoder(layer4Payload);
    layer4PayloadOutput = NetworkDecoder(layer4PayloadOutput);

    startOfNewPayload = layer4PayloadOutput.find("<~");
    string layer5Info = layer4PayloadOutput.substr(0, startOfNewPayload);
    makeTextFile("Layer5Payload.txt", layer4PayloadOutput.substr(startOfNewPayload));
#pragma endregion

    /*cout << layer1Info << "[ Saved in Text File ]" << "\n\n";
    cout << layer2Info << "[ Saved in Text File ]" << "\n\n";
    cout << layer3Info << "[ Saved in Text File ]" << "\n\n";*/
    cout << layer4Info << "[ Saved in Text File ]" << "\n\n";
    cout << layer5Info << "[ Saved in Text File ]" << "\n\n";

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
