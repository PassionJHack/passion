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

#include <FSysPowerManager.h>
#include "PathFinder.h"
#include<FLocTypes.h>

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Base::Utility;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::System;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Web::Controls;
using namespace Tizen::Locations;
using namespace Tizen::Base::Collection;
using namespace Tizen::Web::Json;

PathFinder::PathFinder(void)
	: WEB_URL_PREFIX_HTTP(L"http://")
	, __pMainForm(null)
	, __pWeb(null)
{
}


PathFinder::~PathFinder(void)
{
}


Application*
PathFinder::CreateInstance(void)
{
	// You can create the instance through another constructor.
	return new PathFinder();
}


bool
PathFinder::OnAppInitializing(AppRegistry& appRegistry)
{
	Frame* pAppFrame = new Frame();
	pAppFrame->Construct();
	AddFrame(*pAppFrame);

	result r = E_SUCCESS;

	r = CreateWebForm();
	TryCatch(r == E_SUCCESS, , "CreateWebForm() has failed.\n");
	CreateLocationManager();
	return true;

CATCH:
	return false;
}

bool
PathFinder::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	delete __pLocProvider;
	return true;
}


void
PathFinder::OnForeground(void)
{
	__pWeb->Resume();
}


void
PathFinder::OnBackground(void)
{
	__pWeb->Pause();
}


void
PathFinder::OnLowMemory(void)
{
}


void
PathFinder::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}

result
PathFinder::CreateWebForm(void)
{
	result r = E_SUCCESS;
	Rectangle bound;
	WebSetting setting;

	Header* pHeader;

	FooterItem footerItem1;
	FooterItem footerItemCal;
	FooterItem footerItemClr;
	IAppFrame* pAppFrame = GetAppFrame();


	Tizen::Base::String url = App::GetInstance()->GetAppRootPath() + L"data/index.html";


	TryReturn(pAppFrame != null, E_SYSTEM, "GetAppFrame() has failed.\n");

	//form
	__pMainForm = new (std::nothrow) Form();
	r = __pMainForm->Construct(FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR | FORM_STYLE_HEADER | FORM_STYLE_FOOTER);
	TryReturn(r == E_SUCCESS, r, "Form Construct() has failed. \n ");

	__pMainForm->AddOrientationEventListener(*this);
	__pMainForm->SetOrientation(ORIENTATION_AUTOMATIC_FOUR_DIRECTION);

	bound = __pMainForm->GetClientAreaBounds();

	pAppFrame->GetFrame()->AddControl(__pMainForm);
	pAppFrame->GetFrame()->SetCurrentForm(__pMainForm);

	//header
	pHeader = __pMainForm->GetHeader();
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pHeader->SetTitleText(L"Path Finder");


	//footer
	pFooter = __pMainForm->GetFooter();
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();
	pFooter->AddActionEventListener(*this);
	__pMainForm->SetFormBackEventListener(this);

	//footer item

	footerItemCal.Construct(AC_BUTTON_CALC);
	footerItemCal.SetText(L"Navigate");
	footerItemClr.Construct(AC_BUTTON_CLR);
	footerItemClr.SetText(L"Clear");
	footerItem1.Construct(AC_BUTTON_WEB_BACK);
	footerItem1.SetText(L"Back");
	pFooter->AddItem(footerItemCal);
	pFooter->AddItem(footerItemClr);
	pFooter->AddItem(footerItem1);

    __pMainForm->SetBackgroundColor(pFooter->GetColor());



	//Web
	__pWeb = new (std::nothrow) Web();

	bound = __pMainForm->GetClientAreaBounds();
	r = __pWeb->Construct(Rectangle(0, 0, bound.width, bound.height));
	TryReturn(r == E_SUCCESS, r, "Web Construct() has failed.\n ");

	r = __pMainForm->AddControl(__pWeb);
	TryReturn(r == E_SUCCESS, r, "Addcontrol() has failed.\n ");

	setting.SetInputStyle(INPUT_STYLE_OVERLAY);
	r = __pWeb->SetSetting(setting);
	TryReturn(r == E_SUCCESS, r, "SetSetting() has failed.\n ");

	__pWeb->SetLoadingListener(this);
	__pWeb->SetWebKeypadEventListener(this);
	__pWeb->SetWebUiEventListener(this);
	__pWeb->AddJavaScriptBridge(*this);
	__pWeb->SetFocus();

	__pWeb->LoadUrl(L"file://" + url);
	__pMainForm->RequestRedraw(true);
	return r;
}
result  PathFinder::CreateLocationManager(void)
{
	result r = E_SUCCESS;
	LocationCriteria criteria;

	criteria.SetAccuracy(LOC_ACCURACY_HUNDRED_METERS);
	__pLocProvider = new (std::nothrow) LocationProvider();
	r = __pLocProvider->Construct(criteria, *this);
	r = __pLocProvider->StartLocationUpdatesByDistance(100);
	if (r == E_USER_NOT_CONSENTED)
	 {
		// Check if either the GPS or network settings is enabled on the device Settings > Location menu
		bool isSettingEnabled = CheckLocationSetting();

		if (!isSettingEnabled)
		{
		   LaunchLocationSettings();
		}
		else
		{
		   ShowMessageBox(L"Privacy protection",
						  L"Allow the application to use your location by changing the Settings > Privacy setting.");
		}
	 }
	return r;
}

bool
PathFinder::CheckLocationSetting(void)
{
   bool hasPrivilege = false;
   bool gpsEnabled = true;
   bool wpsEnabled = true;

   result gps = Tizen::System::SettingInfo::GetValue(L"http://tizen.org/setting/location.gps", gpsEnabled);
   result wps = Tizen::System::SettingInfo::GetValue(L"http://tizen.org/setting/location.wps", wpsEnabled);

   hasPrivilege = gpsEnabled | wpsEnabled;
   if (gps != E_SUCCESS || wps != E_SUCCESS || hasPrivilege == false)
   {
      return false;
   }

   return true;
}
void
PathFinder::ShowMessageBox(const String& title, const String& message)
{
	MessageBox messageBox;

	messageBox.Construct(title, message, MSGBOX_STYLE_OK);

	int ModalResult;
	messageBox.ShowAndWait(ModalResult);
}

void
PathFinder::LaunchLocationSettings(void)
{
	int res;

	MessageBox messageBox;
	messageBox.Construct(L"Information", L"Location services are disabled. Enable them in location settings?", MSGBOX_STYLE_YESNO);
	messageBox.ShowAndWait(res);

	if (res == MSGBOX_RESULT_YES)
	{
		HashMap extraData;
		extraData.Construct();
		String categoryKey = L"category";
		String categoryVal = L"Location";
		extraData.Add(&categoryKey, &categoryVal);

		AppControl* pAc = AppManager::FindAppControlN(L"tizen.settings", L"http://tizen.org/appcontrol/operation/configure/location");

		if (pAc)
		{
			pAc->Start(null,null,&extraData, this);
			delete pAc;
		}
	}
	return;
}


void
PathFinder::OnActionPerformed(const Control& source, int actionId)
{
	String url;
	switch (actionId)
	{
	case AC_BUTTON_WEB_BACK:
	{
		Terminate();
	}
	break;
	case AC_BUTTON_CALC:
		{
			String str;
			wchar_t* testStr = L"calcRoute()";
			str.Format(50, L" %ls; ", testStr);
			__pWeb->EvaluateJavascriptN(str);
		}
		break;
	case AC_BUTTON_CLR:
		{
			String str;
			wchar_t* testStr = L"clearRoute()";
			str.Format(50, L" %ls; ", testStr);
			__pWeb->EvaluateJavascriptN(str);
		}
		break;

	default:
		break;
	}

	return;

}

void
PathFinder::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus)
{
	Rectangle bound = __pMainForm->GetClientAreaBounds();


	if (__pWeb->IsVisible())
	{
		__pWeb->SetBounds(Rectangle(0, 0, bound.width, bound.height));
	}

	__pMainForm->Invalidate(true);
}

void
PathFinder::OnTextValueChangeCanceled(const Tizen::Ui::Control& source)
{
	__pMainForm->SetFocus();
}

void
PathFinder::OnTextValueChanged(const Tizen::Ui::Control& source)
{
	__pMainForm->SetFocus();
}

void
PathFinder::OnScreenOn(void)
{
}

void
PathFinder::OnScreenOff(void)
{
}

String
PathFinder::GetValidUrl(Tizen::Base::String& url)
{
	String absoluteUrl = url;
	Uri uri;

	uri.SetUri(url);
	if (uri.GetScheme() == L"")
	{
		absoluteUrl.Insert(WEB_URL_PREFIX_HTTP, 0);
	}
	return absoluteUrl;
}

bool
PathFinder::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	return false;
}

void
PathFinder::OnHttpAuthenticationCanceled(void)
{
}

void
PathFinder::OnLoadingStarted(void)
{
	//SetButtonCancelImage();
}

void
PathFinder::OnLoadingCanceled(void)
{
	//SetButtonGotoImage();
}

void
PathFinder::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
{
	Tizen::Ui::Controls::MessageBox msgBox;
	int modalresult = 0;
	Tizen::Base::String errReason;

	switch (error)
	{
	case WEB_REQUEST_TIMEOUT:
	{
		errReason = Tizen::Base::String(L"Request timeout");
	}
	break;

	case WEB_NO_CONNECTION:
	{
		errReason = Tizen::Base::String(L"Network is not in service");
	}
	break;

	case WEB_MIME_NOT_SUPPORTED:
	{
		errReason = Tizen::Base::String(L"The content type is not supported");
	}
	break;

	case WEB_BAD_URL:
	{
		errReason = Tizen::Base::String(L"The url is invalid");
	}
	break;

	case WEB_HTTP_RESPONSE:
	{
		errReason = Tizen::Base::String(L"HTTP response");
	}
	break;

	case WEB_OUT_OF_MEMORY:
	{
		errReason = Tizen::Base::String(L"Page Too Large");
	}
	break;

	case WEB_REQUEST_MAX_EXCEEDED:
	{
		errReason = Tizen::Base::String(L"Request Max Exceeded");
	}
	break;

	case WEB_ERROR_UNKNOWN:
	default:
	{
		errReason = Tizen::Base::String(L"An Unknown error");
	}
	break;
	}

	msgBox.Construct(L"LOADING ERROR TYPE", errReason, MSGBOX_STYLE_NONE, 3000);
	msgBox.ShowAndWait(modalresult);
}

void
PathFinder::OnLoadingCompleted(void)
{
	SetUrl(__pWeb->GetUrl());
	//SetButtonGotoImage();
}

void
PathFinder::OnEstimatedProgress(int progress)
{
}

void
PathFinder::OnPageTitleReceived(const Tizen::Base::String& title)
{
}

bool
PathFinder::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLog("%S",url.GetPointer());
	SetUrl(url);
	return false;
}


void
PathFinder::SetUrl(const Tizen::Base::String& url)
{
	result r = E_SUCCESS;
	if (url.GetLength() )
	{
		TryReturnVoid(r == E_SUCCESS, "Fail to update URL in the EditField.");
		__pMainForm->RequestRedraw (true);
	}
	else
	{
		AppLog("The length of the URL exceeds the limit of the length of text in this EditField.");
	}
}

DecisionPolicy
PathFinder::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	return WEB_DECISION_CONTINUE;
}

void
PathFinder::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	AppLog("OnFormBackRequested.");
	Terminate();
}

void
PathFinder::OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source)
{
	Rectangle bound = __pMainForm->GetClientAreaBounds();
	AppLog("OnWebKeypadWillOpen.");

	if (source.IsVisible())
	{
		source.SetSize(bound.width, bound.height );
	}
}

void
PathFinder::OnWebKeypadOpened(Tizen::Web::Controls::Web& source)
{
	AppLog("OnWebKeypadOpened.");
}

void
PathFinder::OnWebKeypadClosed(Tizen::Web::Controls::Web& source)
{
	AppLog("OnWebKeypadClosed.");
	Rectangle bound = __pMainForm->GetClientAreaBounds();
	source.SetSize(bound.width, bound.height );
}

void
PathFinder::OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint)
{
}

void
PathFinder::OnWebPageShowRequested(Tizen::Web::Controls::Web &source)
{
}

void
PathFinder::OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source)
{
}

Tizen::Web::Controls::Web*
PathFinder::OnWebWindowCreateRequested(void)
{
	MessageBox messageBox;
	messageBox.Construct(L"", L"PathFinder doesn't include new window creation.", MSGBOX_STYLE_NONE, 3000);

	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);

	return null;
}


void PathFinder:: OnLocationUpdated(const Tizen::Locations::Location& location)
{
	AppLog("PathFinder:: OnLocationUpdated");
	Coordinates coord = location.GetCoordinates();
	AppLog("Location Information: Latitude = %lf, Longitude = %lf, Altitude = %lf", coord.GetLatitude(), coord.GetLongitude(), coord.GetAltitude());

	String str;
	double lat = (coord.GetLatitude());
	double lon = (coord.GetLongitude());
	wchar_t* testStr = L"setposition";
	str.Format(50, L" %ls(%lf,%lf); ", testStr,lat,lon);

	__pWeb->EvaluateJavascriptN(str);
}
void PathFinder::OnLocationUpdateStatusChanged(Tizen::Locations::LocationServiceStatus status)
{
	AppLog("PathFinder:: OnLocationUpdateStatusChanged");
}
void PathFinder::OnAccuracyChanged(Tizen::Locations::LocationAccuracy accuracy)
{
	AppLog("PathFinder:: OnAccuracyChanged");
}
void PathFinder::OnRegionEntered(Tizen::Locations::RegionId regionId)
{
	AppLog("PathFinder:: OnRegionEntered");
}
void PathFinder::OnRegionLeft(Tizen::Locations::RegionId regionId)
{
	AppLog("PathFinder:: OnRegionLeft");
}
void PathFinder::OnRegionMonitoringStatusChanged(Tizen::Locations::LocationServiceStatus status)
{
	AppLog("PathFinder:: OnRegionMonitoringStatusChanged");
}

void PathFinder::HandleJavaScriptRequestN(Tizen::Web::Json::IJsonValue* pArg)
{
   AppLog("PathFinder:: HandleJavaScriptRequestN");
   result r = E_SUCCESS;
   JsonObject* pJsonObject = static_cast< JsonObject* >(pArg);
   IJsonValue* pValue = null;
   JsonString* pJsonStringValue = null;
   String key(L"data");

   r = pJsonObject->GetValue(&key, pValue);
   pJsonStringValue = static_cast< JsonString* >(pValue);

   AppLog("data: %ls\n", pJsonStringValue->GetPointer());


}
Tizen::Base::String PathFinder::GetName(void)
{
	AppLog("PathFinder:: GetName");
	return String(L"MyJsBridge");
}
