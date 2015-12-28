#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED
#pragma once
#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
private:
	HANDLE hSerial;
	bool connected;
	COMSTAT status;
	DWORD errors;

public:
	Serial(char *portName);
	~Serial();
	int ReadData(char *buffer, unsigned int nbChar);
	bool WriteData(char *buffer, unsigned int nbChar);
	bool IsConnected();

	HANDLE& getHandle();
};

#endif