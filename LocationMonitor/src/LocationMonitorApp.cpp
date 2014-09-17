#include "LocationMonitorApp.h"
#include "LocationListener.h"
#include "MockLocationListener.h"
#include <new>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Locations;

LocationMonitorApp::LocationMonitorApp(void)
{
}

LocationMonitorApp::~LocationMonitorApp(void)
{
}

ServiceApp*
LocationMonitorApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new (std::nothrow) LocationMonitorApp();
}

bool
LocationMonitorApp::OnAppInitializing(AppRegistry& appRegistry)
{
	// TODO:
	// Initialize App specific data, and add your initialization code here
	// The App's permanent data and context can be obtained from the appRegistry.
	//
	// If this method is successful, return true; otherwise, return false.
	// If this method returns false, the App will be terminated.

	LocationListener* pListener = null;
	pListener = new LocationListener();

	LocationCriteria criteria;
	criteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);

	LocationProvider* pLocProvider = new LocationProvider();
	pLocProvider->Construct(criteria, *pListener);

	//bool awake = true;
	//pLocProvider->KeepLocationUpdateAwake(awake);

	Coordinates coord;
	coord.Set(27.0, 125.0, 0.0); //result 	Set (double latitude, double longitude, double altitude)
	RegionId regionId;
	pLocProvider->AddMonitoringRegion(coord, 100, regionId);

	MockLocationListener* timer = new MockLocationListener();
	timer->StartApp();

	return true;
}

bool
LocationMonitorApp::OnAppInitialized(void)
{
	AppLogTag("LocationMonitor", "LocationMonitorApp::OnAppInitialized");
	return true;
}

bool
LocationMonitorApp::OnAppWillTerminate(void)
{
	AppLogTag("LocationMonitor", "LocationMonitorApp::OnAppWillTerminate");
	return true;
}

bool
LocationMonitorApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this App for termination, and add your termination code here
	// The App's permanent data and context can be saved via appRegistry.
	return true;
}

void
LocationMonitorApp::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the App.
	AppLogTag("LocationMonitor", "LocationMonitorApp::OnLowMemory");
}

void
LocationMonitorApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
	AppLogTag("LocationMonitor", "LocationMonitorApp::OnBatteryLevelChanged");
}
