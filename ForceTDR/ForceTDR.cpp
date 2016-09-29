// ForceTDR.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CmdLineOptions.h"
#include "utilities.h"
#include <iomanip>
#include <regex> 
#include "cs.h"

using namespace std;

static void DoIt(const CCmdLineOptions& opts);
static void Do_ListDevices(const CCmdLineOptions& opts);
static void Do_ForceTDR(const CCmdLineOptions& opts);

int main(int argc, char* argv[])
{
	CCmdLineOptions cmdLineOpts;
	bool b = cmdLineOpts.ParseCmdline(argc, argv);
	if (b == false)
	{
		return EXIT_FAILURE;
	}

	DoIt(cmdLineOpts);

	return EXIT_SUCCESS;
}

void DoIt(const CCmdLineOptions& opts)
{
	if (opts.Get_ListDevicesCommand() == true)
	{
		Do_ListDevices(opts);
	}

	if (opts.Get_ForceTDRCommand() == true)
	{
		Do_ForceTDR(opts);
	}
}

void Do_ListDevices(const CCmdLineOptions& opts)
{
	CComPtr<IDXGIFactory> dxgiFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void **)&dxgiFactory);

	cout << "Listing the graphic-devices" << endl;
	cout << "---------------------------" << endl << endl;

	for (UINT i = 0;; ++i)
	{
		CComPtr<IDXGIAdapter> dxgiAdapter;
		hr = dxgiFactory->EnumAdapters(i, &dxgiAdapter.p);
		if (FAILED(hr))
		{
			break;
		}

		DXGI_ADAPTER_DESC adapterDesc;
		ZeroMemory(&adapterDesc, sizeof(adapterDesc));
		hr = dxgiAdapter->GetDesc(&adapterDesc);


		cout << "Adapter #" << i << endl;
		cout << " Description: \"" << convertToCurrentLocale(adapterDesc.Description).c_str() << "\"" << endl;
		cout << " PCI_ID: " << hex << setprecision(8) << uppercase << adapterDesc.VendorId << ':' << adapterDesc.DeviceId <<
			" - " << adapterDesc.SubSysId << ':' << adapterDesc.Revision << dec << endl;
		auto oldlocale = std::cout.imbue(locale(""));
		cout << " DedicatedVideoMemory: " << adapterDesc.DedicatedVideoMemory << endl;
		cout << " DedicatedSystemMemory: " << adapterDesc.DedicatedVideoMemory << endl;
		cout << " SharedSystemMemory: " << adapterDesc.SharedSystemMemory << endl;
		std::cout.imbue(oldlocale);
		cout << " AdapterLuid: " << hex << uppercase << adapterDesc.AdapterLuid.HighPart << ':' << adapterDesc.AdapterLuid.LowPart << endl;
		cout << endl;
	}
}

void Do_ForceTDR(const CCmdLineOptions& opts)
{
	ID3D11Device* dev = nullptr;
	ID3D11DeviceContext* con = nullptr;
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dev, nullptr, &con);
	ID3D11ComputeShader* cs = nullptr;
	dev->CreateComputeShader(ComputeShader, sizeof(ComputeShader), nullptr, &cs); // from compiled cs.h
	con->CSSetShader(cs, nullptr, 0);
	con->Dispatch(256, 1, 1);
	con->Flush(); // hangs, then TDRs
}
