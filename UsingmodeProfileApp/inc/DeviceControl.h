/*
 * DeviceControl.h
 *
 *  Created on: Sep 17, 2014
 */

#ifndef DEVICECONTROL_H_
#define DEVICECONTROL_H_

#include <FNet.h>

class DeviceControl
	: public Tizen::Net::Wifi::IWifiManagerEventListener
{

public:
	DeviceControl(void);
	~DeviceControl(void);

	void WifiActivate();
	void WifiDeactivate();

	//WifiManagerEventListener
	void OnWifiActivated (result r);
	void OnWifiConnected (const Tizen::Base::String &ssid, result r);
	void OnWifiDeactivated (result r);
	void OnWifiDisconnected (void);
	void OnWifiRssiChanged (long rssi);
	void OnWifiScanCompletedN (const Tizen::Base::Collection::IList *pWifiBssInfoList, result r);

private:
	Tizen::Net::Wifi::WifiManager _wifiMgr;

};


#endif /* DEVICECONTROL_H_ */
