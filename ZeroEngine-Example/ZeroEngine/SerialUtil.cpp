#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS
#include "SerialUtil.h"
Serial* SerialUtil::SP = NULL;
SerialUtil::SerialUtil()
{
	incomingData[0] = '\0';
	incomingDataLength = 256;
	readResult = 0;
	receive_command = "";

	strcpy(outgoingData, "");
	outgoingDataLength = 256;

	clearedRX = false;
	strcpy(port, "COM1");
	SP = new Serial(this->port);
	char str[17][100];
	int i = 0;
	while (!SP->IsConnected()){
		delete SP;
		i++;
		sprintf_s(str[i - 1], "COM%d", i+1);
		SP = new Serial(str[i-1]);
		strcpy(port, str[i - 1]);
		if (i > 15){
			return;
		}
	}

	/*if (SP->IsConnected())
		cout << "..Connected to Serial Port COM3(default)\n";
	else
		throw "Failed to open Serial Port!!";*/
}
SerialUtil::SerialUtil(string port)
{

	incomingData[0] = '\0';
	incomingDataLength = 256;
	readResult = 0;
	receive_command = "";

	strcpy(outgoingData, "");
	outgoingDataLength = 256;

	clearedRX = false;

	strcpy(this->port, port.c_str());
	SP = new Serial(this->port);

	if (SP->IsConnected())
		cout << "..Connected to Serial Port " << port << "\n";
	else
		throw "Failed to open Serial Port!!";
}
string SerialUtil::read()
{
	string read = "";

	readResult = SP->ReadData(incomingData, incomingDataLength);
	receive_command = (incomingData);
	strcpy(incomingData, "");
	clearedRX = PurgeComm(SP->getHandle(), PURGE_RXCLEAR);
	Sleep(10);

	read = string(receive_command);
	return read;
}
void SerialUtil::write(string& str)
{
	if (SP->IsConnected())
	{
		strcpy(outgoingData, str.c_str());
		clearedRX = PurgeComm(SP->getHandle(), PURGE_RXCLEAR);
		Sleep(10);
		SP->WriteData(outgoingData, outgoingDataLength);
		cout << "outgoingData:" << str << "\n";
		if (SP->IsConnected())
		{
			while ((receive_command.compare(str) != 0 && receive_command.compare("-") != 0) || receive_command.compare("") == 0)
			{
				readResult = SP->ReadData(incomingData, incomingDataLength);
				receive_command = (incomingData);
				strcpy(incomingData, "");
				clearedRX = PurgeComm(SP->getHandle(), PURGE_RXCLEAR);
				Sleep(10);
			}
			if (receive_command.compare(str) == 0)
				cout << "incomingData:" << str << "\n";
			if (receive_command.compare("-") == 0)
				cout << "incomingData:" << "BAD_COMMAND" << "\n";
			if (receive_command.compare("") == 0)
				cout << "incomingData:NULL returned" << receive_command << "\n";
		}
		receive_command = "";
		strcpy(incomingData, "\0");
		Sleep(10);
	}
}