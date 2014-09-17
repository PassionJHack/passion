#include "LocationListener.h"
<<<<<<< HEAD
#include <FNet.h>

=======
#include "WifiManagerEventListener.h"
>>>>>>> 62392cdb77881b3ab52f6cf5d0e27fa04840b52b

using namespace Tizen::Locations;
using namespace Tizen::Net::Wifi;

LocationListener::LocationListener(void)
{
	result r;
	WifiManagerEventListener* listener = new WifiManagerEventListener();
	r = _wifiMgr.Construct(*listener);
}

LocationListener::~LocationListener(void)
{
	delete _wifiMgr;
}


void
LocationListener::OnRegionEntered (Tizen::Locations::RegionId regionId)
{
	AppLogTag("LocationMonitor", "LocationListener::OnRegionEntered");
<<<<<<< HEAD
	WifiManager wifiMgr;
=======

	//Note:
	//You can test the Wi-Fi functionality only on target devices.
	//The Emulator currently does not support this feature.

>>>>>>> 62392cdb77881b3ab52f6cf5d0e27fa04840b52b
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
LocationListener::OnRegionLeft (Tizen::Locations::RegionId regionId)
{
	AppLogTag("LocationMonitor", "LocationListener::OnRegionLeft");

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

void
LocationListener::OnRegionMonitoringStatusChanged (Tizen::Locations::LocationServiceStatus status)
{
	AppLogTag("LocationMonitor", "LocationListener::OnRegionMonitoringStatusChanged");
}

void
LocationListener::OnAccuracyChanged (Tizen::Locations::LocationAccuracy accuracy)
{
	AppLogTag("LocationMonitor", "LocationListener::OnAccuracyChanged");
}

void
LocationListener::OnLocationUpdated (const Tizen::Locations::Location &location)
{
	AppLogTag("LocationMonitor", "LocationListener::OnLocationUpdated");
}

void
LocationListener::OnLocationUpdateStatusChanged (Tizen::Locations::LocationServiceStatus status)
{
	AppLogTag("LocationMonitor", "LocationListener::OnLocationUpdateStatusChanged");
}
