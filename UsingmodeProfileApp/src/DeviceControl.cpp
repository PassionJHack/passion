/*
 * DeviceControl.cpp
 *
 *  Created on: Sep 17, 2014
 */

#include "DeviceControl.h"

using namespace Tizen::Locations;
using namespace Tizen::Net::Wifi;


DeviceControl::DeviceControl(void)
{
	result r;
	r = _wifiMgr.Construct(*this);
}

DeviceControl::~DeviceControl(void)
{

}

void
DeviceControl::WifiActivate()
{
	AppLogTag("DeviceControl::WifiActivate");

	//Note:
	//You can test the Wi-Fi functionality only on target devices.
	//The Emulator currently does not support this feature.

	result r;

	//Turn On WiFi
	if (!_wifiMgr.IsActivated())
	{
		r = _wifiMgr.Activate();
		if (IsFailed(r))
		{
			//TODO: error handling
		}
	}

}

void
DeviceControl::WifiDeactivate()
{
	AppLogTag("DeviceControl::WifiDeactivate");

	result r;

	//Turn Off WiFi
	if (_wifiMgr.IsActivated())
	{
		r = _wifiMgr.Deactivate();
		if (IsFailed(r))
		{
			//TODO: error handling
		}
	}
}


//-------------------------------------------------

void
DeviceControl::OnWifiActivated (result r)
{
	AppLogTag("DeviceControl::OnWifiActivated");
}
void
DeviceControl::OnWifiConnected (const Tizen::Base::String &ssid, result r)
{

}
void
DeviceControl::OnWifiDeactivated (result r)
{
	AppLogTag("DeviceControl::OnWifiDeactivated");
}
void
DeviceControl::OnWifiDisconnected (void)
{

}
void
DeviceControl::OnWifiRssiChanged (long rssi)
{

}
void
DeviceControl::OnWifiScanCompletedN (const Tizen::Base::Collection::IList *pWifiBssInfoList, result r)
{

}


