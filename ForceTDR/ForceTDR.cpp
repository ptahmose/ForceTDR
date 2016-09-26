// ForceTDR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cs.h"

int main()
{
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* con = nullptr;
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dev, nullptr, &con);
	ID3D11ComputeShader* cs = nullptr;
	dev->CreateComputeShader(ComputeShader, sizeof(ComputeShader), nullptr, &cs); // from compiled cs.h
	con->CSSetShader(cs, nullptr, 0);
	con->Dispatch(256, 1, 1);
	con->Flush(); // hangs, then TDRs
	return 0;
}

