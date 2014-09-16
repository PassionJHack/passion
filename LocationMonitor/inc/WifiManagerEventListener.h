/*
 * WifiManagerEventListener.h
 *
 *  Created on: Sep 17, 2014
 */

#ifndef WIFIMANAGEREVENTLISTENER_H_
#define WIFIMANAGEREVENTLISTENER_H_

#include <FNet.h>

class WifiManagerEventListener
	: public Tizen::Net::Wifi::IWifiManagerEventListener
{
public:
	WifiManagerEventListener (void);
	~WifiManagerEventListener (void);

	void OnWifiActivated (result r);
	void OnWifiConnected (const Tizen::Base::String &ssid, result r);
	void OnWifiDeactivated (result r);
	void OnWifiDisconnected (void);
	void OnWifiRssiChanged (long rssi);
	void OnWifiScanCompletedN (const Tizen::Base::Collection::IList *pWifiBssInfoList, result r);
};

#endif /* WIFIMANAGEREVENTLISTENER_H_ */
