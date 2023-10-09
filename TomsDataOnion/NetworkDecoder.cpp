#include "NetworkDecoder.h"
#include <string>
#include <vector>
#include <iostream>
#include <Bits.h>
#include <stdio.h>

using namespace std;

string NetworkDecoder(string input) {
	string result = "";
	int strLength = 0;
	strLength = input.size();
	uint16_t IPv4Header[10];
	uint16_t IPv4totalLength = 0;
	uint32_t IPv4SourceIP = 0;
	uint32_t IPv4DestinationIP = 0;
	uint32_t IPv4CheckSum = 0;

	uint16_t UDPHeader[4];
	uint32_t UDPCheckSum = 0;


	uint16_t temp1 = 0;
	uint16_t temp2 = 0;

	int posCount = 0;
	int badPacket = 0;

	while (posCount < strLength) {
		int j = 0;
		IPv4CheckSum = 0;
		UDPCheckSum = 0;
		for (int i = posCount; i < (20 + posCount); i = i + 2) {

			if (i > strLength) {
				break;
			}

			temp1 = (uint8_t)input[i];
			temp2 = (uint8_t)input[i + 1];

			IPv4Header[j] = 256 * temp1 + temp2;
			IPv4CheckSum += IPv4Header[j];
			j++;
		}
		j = 0;
		uint16_t carryOver = (IPv4CheckSum >> 16);
		IPv4CheckSum += carryOver;
		uint16_t IPv4trunkCheckSum = IPv4CheckSum; // check sum works

		IPv4totalLength = IPv4Header[1];
		IPv4SourceIP = (IPv4Header[6] << 16) | IPv4Header[7];
		IPv4DestinationIP = (IPv4Header[8] << 16) | IPv4Header[9];

		uint16_t IPv4IHL = (IPv4Header[0] << 4);
		IPv4IHL = (IPv4IHL >> 12);
		IPv4IHL = (IPv4IHL * 32) / 8;
		uint16_t IPv4dataLength = IPv4totalLength - IPv4IHL;

		if ((IPv4trunkCheckSum == 0xffff) && (IPv4SourceIP == 0x0a01010a) && (IPv4DestinationIP == 0x0a0101c8)) {
			UDPCheckSum = IPv4Header[6] + IPv4Header[7] + IPv4Header[8] + IPv4Header[9] + 0x0011 + IPv4dataLength;
			posCount = posCount + IPv4IHL;
			
			for (int i = posCount; i < (8 + posCount); i = i + 2) {
				temp1 = (uint8_t)input[i];
				temp2 = (uint8_t)input[i + 1];

				UDPHeader[j] = 256 * temp1 + temp2;
				UDPCheckSum += UDPHeader[j];
				j++;
			}
			j = 0;
			posCount = posCount + 8;
			int UDPDataLength = IPv4dataLength - 8;
			vector<uint16_t> UDPData;

			if (UDPDataLength % 2 == 0) {
				for (int i = posCount; i < (posCount + UDPDataLength); i = i + 2) {
					temp1 = (uint8_t)input[i];
					temp2 = (uint8_t)input[i + 1];

					UDPData.push_back(256 * temp1 + temp2);
					UDPCheckSum += (uint16_t)(256 * temp1 + temp2);
				}
				posCount = posCount + UDPDataLength;
			}
			else {
				for (int i = posCount; i < (posCount + UDPDataLength - 1); i = i + 2) {
					temp1 = (uint8_t)input[i];
					temp2 = (uint8_t)input[i + 1];

					UDPData.push_back(256 * temp1 + temp2);
					UDPCheckSum += (uint16_t)(256 * temp1 + temp2);
				}
				posCount = posCount + UDPDataLength;
				temp1 = (uint8_t)input[posCount - 1];
				temp2 = (uint8_t)0x00;

				UDPData.push_back(256 * temp1 + temp2);
				UDPCheckSum += (uint16_t)(256 * temp1 + temp2);
				
			}
		
			carryOver = (UDPCheckSum >> 16);
			UDPCheckSum += carryOver;
			uint16_t UDPTrunkCheckSum = UDPCheckSum;

			if (UDPTrunkCheckSum == 0xffff && UDPHeader[1] == 42069) {
				for(auto it = UDPData.begin(); it != UDPData.end(); ++it) {
					uint16_t temp = *it;
					result += (unsigned char) (temp >> 8);
					temp = (temp << 8);
					result += (unsigned char) (temp >> 8);
				}
			}
			else {
				badPacket++;
				//cout << badPacket << "\n";
			}
			
		}
		else {
			posCount += IPv4totalLength;
			badPacket++;
			//cout << badPacket << "\n";
		}

	}	

	return result;
}