/*
 * DeviceControl.cpp
 *
 *  Created on: Sep 17, 2014
 */

#include "DeviceControl.h"
#include <FBaseLog.h>

using namespace Tizen::Locations;
using namespace Tizen::Net::Wifi;
using namespace Tizen::System;

DeviceControl::DeviceControl(void)
{
	result r;
	r = _wifiMgr.Construct(*this);
}

DeviceControl::~DeviceControl(void)
{

}

void
DeviceControl::setVolum( int inSize )
{
	SettingInfo::SetValue(L"http://tizen.org/setting/sound.system.volume" , inSize );
}

void
DeviceControl::WifiActivate()
{
	AppLogTag("DeviceControl::WifiActivate","Activity");

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
	AppLogTag("DeviceControl::WifiActivate","Deativate");

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
	AppLogTag("DeviceControl::WifiActivate","Deativate");
}
void
DeviceControl::OnWifiConnected (const Tizen::Base::String &ssid, result r)
{

}
void
DeviceControl::OnWifiDeactivated (result r)
{
	AppLogTag("DeviceControl::WifiActivate","Deativate");
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


