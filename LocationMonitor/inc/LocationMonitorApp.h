#ifndef _LOCATION_MONITOR_APP_H_
#define _LOCATION_MONITOR_APP_H_

#include "tizenx.h"

// LocationMonitorApp must inherit from ServiceApp class
// which provides basic features necessary to define an ServiceApp.
class LocationMonitorApp
	: public Tizen::App::ServiceApp
{
public:
	// [LocationMonitorApp] ServiceApp must have a factory method that creates an instance of itself.
	static Tizen::App::ServiceApp* CreateInstance(void);
	LocationMonitorApp(void);
	~LocationMonitorApp(void);

private:
	// Called when the ServiceApp is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// Called when the ServiceApp initializing is finished.
	bool OnAppInitialized(void); 

	// Called when the ServiceApp is requested to terminate.
	bool OnAppWillTerminate(void);

	// Called when the ServiceApp is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	// Called when the system memory is not sufficient to run the ServiceApp any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);
};

#endif // _LOCATION_MONITOR_APP_H_
