#include "LocationListener.h"
#include <FNet.h>


using namespace Tizen::Locations;
using namespace Tizen::Net::Wifi;

LocationListener::LocationListener(void)
{

}

LocationListener::~LocationListener(void)
{

}


void
LocationListener::OnRegionEntered (Tizen::Locations::RegionId regionId)
{
	AppLogTag("LocationMonitor", "LocationListener::OnRegionEntered");
	WifiManager wifiMgr;
	result r;

	//Turn On WiFi
	if (!wifiMgr.IsActivated())
	{
		r = wifiMgr.Activate();
		if (IsFailed(r))
		{
			//TODO: error handling
		}
	}

	//Turn Off WiFi
	if (wifiMgr.IsActivated())
	{
		r = wifiMgr.Deactivate();
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
