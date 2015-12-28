#pragma once
#include "Serial.h"
#include <iostream>
#include <string>

using namespace std;

class SerialUtil{
public:
	char port[15];
	char incomingData[256];
	int incomingDataLength;
	int readResult;
	string receive_command;

	char outgoingData[256];
	int outgoingDataLength;

	bool clearedRX;
public:
	static Serial* SP;
	SerialUtil();
	SerialUtil(string port);
	void write(string& str);
	string read();
};