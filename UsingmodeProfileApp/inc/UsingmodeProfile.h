//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license/
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _USINGMODEPROFILE_H_
#define _USINGMODEPROFILE_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

/**
 * [UsingmodeProfileApp] UiApp must inherit from UiApp class
 * which provides basic features necessary to define an UiApp.
 */
class UsingmodeProfileApp
	: public Tizen::App::UiApp
	, public Tizen::System::IScreenEventListener
{
public:
	/**
	 * [Test] UiApp must have a factory method that creates an instance of itself.
	 */
	static Tizen::App::UiApp* CreateInstance(void);

public:
	UsingmodeProfileApp(void);
	virtual ~UsingmodeProfileApp(void);

public:
	// Called when the UiApp is initializing.
	bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// Called when the UiApp initializing is finished.
	bool OnAppInitialized(void);

	// Called when the UiApp is requested to terminate.
	bool OnAppWillTerminate(void);

	// Called when the UiApp is terminating.
	bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	// Called when the UiApp's frame moves to the top of the screen.
	void OnForeground(void);

	// Called when this UiApp's frame is moved from top of the screen to the background.
	void OnBackground(void);

	// Called when the system memory is not sufficient to run the UiApp any further.
	void OnLowMemory(void);

	// Called when the battery level changes.
	void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	// Called when the screen turns on.
	void OnScreenOn(void);

	// Called when the screen turns off.
	void OnScreenOff(void);
};

#endif // _USINGMODEPROFILE_H_
