#pragma once
#include "anyoption.h"

class CCmdLineOptions
{
private:
	AnyOption anyOption;

	bool listDevicesCommand;
	bool forceTdrCommand;
public:
	CCmdLineOptions();

	bool ParseCmdline(int argc, char* argv[]);

	bool Get_ListDevicesCommand() const { return this->listDevicesCommand; }
	bool Get_ForceTDRCommand() const { return this->forceTdrCommand; }
};