#include "stdafx.h"
#include "CmdLineOptions.h"

CCmdLineOptions::CCmdLineOptions()
	: listDevicesCommand(false), forceTdrCommand(false), listDX11FeaturesCommand(false)
{
	this->anyOption.addUsage("");
	this->anyOption.addUsage("Usage: ");
	this->anyOption.addUsage("");
	this->anyOption.addUsage(" -h  --help  		 Prints this help ");
	this->anyOption.addUsage(" -t  --forcetdr    Force a TDR ");
	this->anyOption.addUsage(" -l  --listdevices Prints a list of available devices");
	this->anyOption.addUsage(" -f  --listfeatures Prints DX11-features");
	this->anyOption.addUsage("");

	this->anyOption.setFlag("help", 'h');   /* a flag (takes no argument), supporting long and short form */
	this->anyOption.setFlag("listdevices", 'l');
	this->anyOption.setFlag("forcetdr", 'f');
}

bool CCmdLineOptions::ParseCmdline(int argc, char* argv[])
{
	this->anyOption.processCommandArgs(argc, argv);

	if (!this->anyOption.hasOptions())
	{ /* print usage if no options */
		this->anyOption.printUsage();
		return false;
	}

	if (this->anyOption.getFlag('l') || this->anyOption.getFlag("listdevices"))
	{
		this->listDevicesCommand = true;
	}

	if (this->anyOption.getFlag('t') || this->anyOption.getFlag("forcetdr"))
	{
		this->forceTdrCommand = true;
	}

	if (this->anyOption.getFlag('f') || this->anyOption.getFlag("listfeatures"))
	{
		this->listDX11FeaturesCommand = true;
	}

	return true;
}