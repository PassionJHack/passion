/*
 * LocationMapForm.h
 *
 *  Created on: Sep 17, 2014
 *      Author: mobilehunter
 */

#ifndef LOCATIONMAPFORM_H_
#define LOCATIONMAPFORM_H_

#include <FBase.h>
#include <FWeb.h>
#include <FUi.h>
#include <FApp.h>

class LocationMapForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Web::Controls::IJavaScriptBridge
	, public Tizen::Web::Controls::ILoadingListener
	, public Tizen::App::IAppControlResponseListener
	, public Tizen::Web::Controls::IWebUiEventListener
	, public Tizen::Web::Controls::IWebKeypadEventListener
{
public:
	LocationMapForm();
	virtual ~LocationMapForm();

	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual Tizen::Base::String  GetName (void);
	virtual void  HandleJavaScriptRequestN (Tizen::Web::Json::IJsonValue *pArg);
	virtual void  OnEstimatedProgress (int progress);
	virtual void  OnHttpAuthenticationCanceled (void);
	virtual bool  OnHttpAuthenticationRequestedN (const Tizen::Base::String &host, const Tizen::Base::String &realm, const Tizen::Web::Controls::AuthenticationChallenge &authentication);
	virtual void  OnLoadingCanceled (void);
	virtual void  OnLoadingCompleted (void);
	virtual void  OnLoadingErrorOccurred (Tizen::Web::Controls::LoadingErrorType error, const Tizen::Base::String &reason);
	virtual bool  OnLoadingRequested (const Tizen::Base::String &url, Tizen::Web::Controls::WebNavigationType type);
	virtual void  OnLoadingStarted (void);
	virtual void  OnPageTitleReceived (const Tizen::Base::String &title);
	virtual Tizen::Web::Controls::DecisionPolicy  OnWebDataReceived (const Tizen::Base::String &mime, const Tizen::Net::Http::HttpHeader &httpHeader);
	void SetUrl(const Tizen::Base::String& url);
	virtual void OnAppControlCompleteResponseReceived(const Tizen::App::AppId &appId, const Tizen::Base::String &operationId, Tizen::App::AppCtrlResult appControlResult, const Tizen::Base::Collection::IMap *pExtraData){}
	virtual void  OnWebPageBlockSelected (Tizen::Web::Controls::Web &source, Tizen::Graphics::Point &startPoint, Tizen::Graphics::Point &endPoint);
	virtual void  OnWebPageShowRequested (Tizen::Web::Controls::Web &source);
	virtual void  OnWebWindowCloseRequested (Tizen::Web::Controls::Web &source);
	virtual void  OnWebKeypadClosed (Tizen::Web::Controls::Web &source);
	virtual void  OnWebKeypadOpened (Tizen::Web::Controls::Web &source);
	virtual void  OnWebKeypadWillOpen (Tizen::Web::Controls::Web &source);
	virtual Tizen::Web::Controls::Web *  OnWebWindowCreateRequested (void);



private:
	static const int ID_BUTTON_SELECT = 100;
	result CreateWebForm();
	Tizen::Web::Controls::Web* __pWeb;
	Tizen::Ui::Controls::Footer* pFooter;
};



#endif /* LOCATIONMAPFORM_H_ */
