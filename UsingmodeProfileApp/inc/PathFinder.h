//
// Tizen C++ SDK
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Flora License, Version 1.1 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://floralicense.org/license
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an AS IS BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef _WEB_VIEWER_H_
#define _WEB_VIEWER_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FWeb.h>
#include <FLocations.h>
#include <FBaseDataType.h>
#include <FLocLocationProvider.h>
#include <FLocLocationCriteria.h>


class PathFinder
	: public Tizen::App::Application
	, public Tizen::System::IScreenEventListener
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::ITextEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Web::Controls::ILoadingListener
	, public Tizen::Web::Controls::IWebKeypadEventListener
	, public Tizen::Web::Controls::IWebUiEventListener
	, public Tizen::Ui::IOrientationEventListener
	, public Tizen::Locations::ILocationProviderListener
	, public Tizen::App::IAppControlResponseListener
	, public Tizen::Web::Controls::IJavaScriptBridge
{
public:
	PathFinder(void);
	~PathFinder(void);

	// The application must have a factory method that creates an instance of the application.
	static Tizen::App::Application* CreateInstance(void);

	// This method is called when the application is on initializing.
	virtual bool OnAppInitializing(Tizen::App::AppRegistry& appRegistry);

	// This method is called when the application is on terminating.
	virtual bool OnAppTerminating(Tizen::App::AppRegistry& appRegistry, bool forcedTermination = false);

	// Thie method is called when the application is brought to the foreground
	virtual void OnForeground(void);

	// This method is called when the application is sent to the background.
	virtual void OnBackground(void);

	// This method is called when the application has little available memory.
	virtual void OnLowMemory(void);

	// This method is called when the device's battery level is changed.
	virtual void OnBatteryLevelChanged(Tizen::System::BatteryLevel batteryLevel);

	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	virtual void OnOrientationChanged(const Tizen::Ui::Control& source, Tizen::Ui::OrientationStatus orientationStatus);

	virtual void OnTextValueChangeCanceled(const Tizen::Ui::Control& source);
	virtual void OnTextValueChanged(const Tizen::Ui::Control& source);

	// Called when the screen turns on.
	virtual void OnScreenOn(void);

	// Called when the screen turns off.
	virtual void OnScreenOff(void);

	virtual bool OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication);
	virtual void OnHttpAuthenticationCanceled(void);
	virtual void OnLoadingStarted(void);
	virtual void OnLoadingCanceled(void);
	virtual void OnLoadingErrorOccurred(Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String& reason);
	virtual void OnLoadingCompleted(void);
	virtual void OnEstimatedProgress(int progress);
	virtual void OnPageTitleReceived(const Tizen::Base::String& title);
	virtual bool OnLoadingRequested(const Tizen::Base::String& url, Tizen::Web::Controls::WebNavigationType type);
	virtual Tizen::Web::Controls::DecisionPolicy OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	virtual void OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source);
	virtual void OnWebKeypadOpened(Tizen::Web::Controls::Web& source);
	virtual void OnWebKeypadClosed(Tizen::Web::Controls::Web& source);
	
	virtual void OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint);
	virtual void OnWebPageShowRequested(Tizen::Web::Controls::Web &source);
	virtual void OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source);
	virtual Tizen::Web::Controls::Web* OnWebWindowCreateRequested(void);


	void OnLocationUpdated(const Tizen::Locations::Location& location);
	void OnLocationUpdateStatusChanged(Tizen::Locations::LocationServiceStatus status);
	void OnAccuracyChanged(Tizen::Locations::LocationAccuracy accuracy);
	virtual void OnRegionEntered(Tizen::Locations::RegionId regionId);
	virtual void OnRegionLeft(Tizen::Locations::RegionId regionId);
	virtual void OnRegionMonitoringStatusChanged(Tizen::Locations::LocationServiceStatus status);
	virtual void OnAppControlCompleteResponseReceived(const Tizen::App::AppId &appId, const Tizen::Base::String &operationId, Tizen::App::AppCtrlResult appControlResult, const Tizen::Base::Collection::IMap *pExtraData){}
	virtual void HandleJavaScriptRequestN(Tizen::Web::Json::IJsonValue* pArg);
	virtual Tizen::Base::String GetName(void);
private:
	result CreateWebForm(void);
	Tizen::Base::String GetValidUrl(Tizen::Base::String& url);

	void SetUrl(const Tizen::Base::String& url);
	result CreateLocationManager(void);
	bool CheckLocationSetting(void);
	void LaunchLocationSettings(void);
	void ShowMessageBox(const const Tizen::Base::String& title, const const Tizen::Base::String& message);

private:
	const wchar_t* WEB_URL_PREFIX_HTTP;

	static const int AC_BUTTON_WEB_BACK = 3001;
	static const int AC_BUTTON_CALC = 3003;
	static const int AC_BUTTON_CLR = 3004;

	static const int BUTTON_WIDTH = 112;

	Tizen::Ui::Controls::Form* __pMainForm;
	Tizen::Web::Controls::Web* __pWeb;
	Tizen::Ui::Controls::Footer* pFooter;


	Tizen::Locations::LocationProvider* __pLocProvider;
};

#endif //_WEB_VIEWER_H_

