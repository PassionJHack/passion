/*
 * LocationMapForm.cpp
 *
 *  Created on: Sep 17, 2014
 *      Author: mobilehunter
 */
#include <new>
#include <FApp.h>


#include "AppResourceId.h"
#include "LocationMapForm.h"
#include "CreateProfileForm.h"
#include "EditProfileForm.h"
#include "ProfileFormFactory.h"
#include "SceneRegister.h"

using namespace Tizen::App;
using namespace Tizen::Base;

using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

using namespace Tizen::Web::Controls;
using namespace Tizen::Web::Json;
using namespace Tizen::Graphics;

LocationMapForm::LocationMapForm()
{
}

LocationMapForm::~LocationMapForm()
{
}
bool
LocationMapForm::Initialize(void)
{
	result r = E_SUCCESS;

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));

	return true;
}

result
LocationMapForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_BUTTON_SELECT);
	String getSelect;
	Application::GetInstance()->GetAppResource()->GetString(IDS_SELECT, getSelect);
	footerSave.SetText(getSelect);
	pFooter->AddItem(footerSave);
	pFooter->AddActionEventListener(*this);

	__pWeb = new (std::nothrow) Web();

	Rectangle bound = this->GetClientAreaBounds();


	__pWeb->Construct( Rectangle ( 0 , 0  , bound.width , bound.height));

	Tizen::Base::String url = "file://"+App::GetInstance()->GetAppDataPath() + L"index.html";
	__pWeb->SetLoadingListener(this);
	__pWeb->SetWebUiEventListener(this);
	__pWeb->AddJavaScriptBridge(*this);
	this->AddControl(__pWeb);

	SetFormBackEventListener(this);

	__pWeb->LoadUrl(url);

	this->RequestRedraw(true);

	return r;
}

result
LocationMapForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}

DecisionPolicy
LocationMapForm::OnWebDataReceived(const Tizen::Base::String& mime, const Tizen::Net::Http::HttpHeader& header)
{
	return WEB_DECISION_CONTINUE;
}

void
LocationMapForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_BUTTON_SELECT:
		pSceneManager->GoBackward(BackwardSceneTransition());
		Tizen::Ui::Controls::Frame* pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		AppLog("test====1");
		if (pSceneManager->GetCurrentSceneId().Equals(SCENE_CREATION, true)) {
			AppLog("test====2");
			CreateProfileForm *pCreateProfileForm = static_cast< CreateProfileForm* >(pFrame->GetControl(FORM_CREATION));
			if (pCreateProfileForm != NULL) {
				pCreateProfileForm->SetMap(this->__latitude, this->__longitude);
			}
		} else if (pSceneManager->GetCurrentSceneId().Equals(SCENE_EDITION, true)) {
			AppLog("test====3");
			EditProfileForm *pEditProfileForm = static_cast< EditProfileForm* >(pFrame->GetControl(FORM_EDITION));
			AppLog("test====3-1");
			if (pEditProfileForm != NULL) {
				pEditProfileForm->SetMap(this->__latitude, this->__longitude);
			}
		}
		AppLog("test====4");

		break;
	}

}

void
LocationMapForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition());
}

Tizen::Base::String LocationMapForm::GetName (void)
{
	return String(L"MyJsBridge");
}
void  LocationMapForm::HandleJavaScriptRequestN (Tizen::Web::Json::IJsonValue *pArg)
{
	 AppLog("PathFinder:: HandleJavaScriptRequestN");
	 result r = E_SUCCESS;
	 JsonObject* pJsonObject = static_cast< JsonObject* >(pArg);
	 IJsonValue* pValue = null;
	 JsonString* pJsonStringValue = null;
	 String key(L"data");

	 r = pJsonObject->GetValue(&key, pValue);
	 pJsonStringValue = static_cast< JsonString* >(pValue);
	 const wchar_t* mapPointString = pJsonStringValue->GetPointer();

	 AppLog("data: %ls\n", mapPointString);

	 String *tmpString = new String(mapPointString);

	 Float x , y;

	 int idx = 0;


	 tmpString->IndexOf(' ' , 0 , idx);

	 String *tmpString2 = new String ( mapPointString + idx + 1 );

	 const wchar_t* tmpChar =  tmpString->GetPointer();
	 wchar_t* tmpChar3 = const_cast<wchar_t*>(tmpChar);
	 tmpChar3[idx] = '\0';
	 const wchar_t* tmpChar2 = tmpString2->GetPointer();

	 x.Parse(tmpChar3 , this->__latitude );
	 y.Parse(tmpChar2 , this->__longitude );
}

bool
LocationMapForm::OnHttpAuthenticationRequestedN(const Tizen::Base::String& host, const Tizen::Base::String& realm, const Tizen::Web::Controls::AuthenticationChallenge& authentication)
{
	return false;
}

void
LocationMapForm::OnHttpAuthenticationCanceled(void)
{
}

void
LocationMapForm::OnLoadingStarted(void)
{
	//SetButtonCancelImage();
}

void
LocationMapForm::OnLoadingCanceled(void)
{
	//SetButtonGotoImage();
}

void
LocationMapForm::OnLoadingErrorOccurred(LoadingErrorType error, const String& reason)
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
LocationMapForm::OnLoadingCompleted(void)
{
	SetUrl(__pWeb->GetUrl());
	//SetButtonGotoImage();
}

void
LocationMapForm::OnWebKeypadWillOpen(Tizen::Web::Controls::Web& source)
{
	Rectangle bound = this->GetClientAreaBounds();
	AppLog("OnWebKeypadWillOpen.");

	if (source.IsVisible())
	{
		source.SetSize(bound.width, bound.height );
	}
}

void
LocationMapForm::OnWebKeypadOpened(Tizen::Web::Controls::Web& source)
{
	AppLog("OnWebKeypadOpened.");
}

void
LocationMapForm::OnWebKeypadClosed(Tizen::Web::Controls::Web& source)
{
	AppLog("OnWebKeypadClosed.");
	Rectangle bound = this->GetClientAreaBounds();
	source.SetSize(bound.width, bound.height );
}


void
LocationMapForm::OnEstimatedProgress(int progress)
{
}

void
LocationMapForm::OnPageTitleReceived(const Tizen::Base::String& title)
{
}

bool
LocationMapForm::OnLoadingRequested(const Tizen::Base::String& url, WebNavigationType type)
{
	AppLog("%S",url.GetPointer());
	SetUrl(url);
	return false;
}


void
LocationMapForm::SetUrl(const Tizen::Base::String& url)
{
	result r = E_SUCCESS;
	if (url.GetLength() )
	{
		TryReturnVoid(r == E_SUCCESS, "Fail to update URL in the EditField.");
		this->RequestRedraw (true);
	}
	else
	{
		AppLog("The length of the URL exceeds the limit of the length of text in this EditField.");
	}
}
void
LocationMapForm::OnWebPageBlockSelected(Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint)
{
}

void
LocationMapForm::OnWebPageShowRequested(Tizen::Web::Controls::Web &source)
{
}

void
LocationMapForm::OnWebWindowCloseRequested(Tizen::Web::Controls::Web &source)
{
}

Tizen::Web::Controls::Web*
LocationMapForm::OnWebWindowCreateRequested(void)
{
	MessageBox messageBox;
	messageBox.Construct(L"", L"LocationMapForm doesn't include new window creation.", MSGBOX_STYLE_NONE, 3000);

	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);

	return null;
}
