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

#include <new>
#include <FApp.h>
#include <FLocales.h>

#include "AppResourceId.h"
#include "ProfileDetailForm.h"
#include "SceneRegister.h"
#include "ProfileListForm.h"
#include "ProfileFormFactory.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::Social;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ProfileDetailForm::ProfileDetailForm()
//	: __pCalendarbook(null)
//	, __pProfile(null)
{
}

ProfileDetailForm::~ProfileDetailForm()
{
}

bool
ProfileDetailForm::Initialize(void)
{
	result r = E_SUCCESS;

	Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(r == E_SUCCESS, false, "[%s] Failed to construct the form.", GetErrorMessage(r));
	__currentID = -1;
	return true;
}

result
ProfileDetailForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	String getDetails;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DETAILS, getDetails);
	pHeader->SetTitleText(getDetails);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);


	String getEdit;
	Application::GetInstance()->GetAppResource()->GetString(IDS_EDIT, getEdit);
	FooterItem footerEdit;
	footerEdit.Construct(ID_FOOTER_EDIT);
	footerEdit.SetText(getEdit);
	pFooter->AddItem(footerEdit);


	String getDelete;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DELETE, getDelete);
	FooterItem footerDelete;
	footerDelete.Construct(ID_FOOTER_DELETE);
	footerDelete.SetText(getDelete);
	pFooter->AddItem(footerDelete);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4 + UI_X_POSITION_GAP;
	static const int UI_HEIGHT = 112;
	static const int UI_SPACE = 26;
	int yPosition = 0;

	ScrollPanel* pScrollPanel = new (std::nothrow) ScrollPanel();
	pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	String date;
	DateTime displayStartDate;
	DateTime displayDueDate;

	// Subject
	Label* pSubjectLabel = new (std::nothrow) Label();
	String getProfileName;
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME, getProfileName);
	pSubjectLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), getProfileName);
	pSubjectLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pSubjectLabel->SetTextColor(COLOR_TITLE_LABEL);
	pSubjectLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pSubjectLabel);

	__pSubjectLabelData = new (std::nothrow) Label();
	__pSubjectLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pSubjectLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pSubjectLabelData);

	// Start Date
	Label* pStartDateLabel = new (std::nothrow) Label();
	String getStartDatetime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_START_DATETIME, getStartDatetime);
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getStartDatetime);
	pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStartDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pStartDateLabel);

	__pStartDateLabelData = new (std::nothrow) Label();
	__pStartDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pStartDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pStartDateLabelData);

	// Due Date
	Label* pDueDateLabel = new (std::nothrow) Label();
	String getEndDatetime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_END_DATETIME, getEndDatetime);
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getEndDatetime);
	pDueDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDueDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDueDateLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pDueDateLabel);

	__pDueDateLabelData = new (std::nothrow) Label();
	__pDueDateLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pDueDateLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pDueDateLabelData);

	// Location
	Label* pLocationLabel = new (std::nothrow) Label();
	String getLocation;
	Application::GetInstance()->GetAppResource()->GetString(IDS_LOCATION, getLocation);
	pLocationLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getLocation);
	pLocationLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pLocationLabel->SetTextColor(COLOR_TITLE_LABEL);
	pLocationLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pLocationLabel);

	__pLocationLabelData = new (std::nothrow) Label();
	__pLocationLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pLocationLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pLocationLabelData);

	// Volume
	Label* pVolumeLabel = new (std::nothrow) Label();
	String getVolume;
	Application::GetInstance()->GetAppResource()->GetString(IDS_VOLUME, getVolume);
	pVolumeLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getVolume);
	pVolumeLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pVolumeLabel->SetTextColor(COLOR_TITLE_LABEL);
	pVolumeLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pVolumeLabel);

	__pVolumeLabelData = new (std::nothrow) Label();
	__pVolumeLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pVolumeLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pVolumeLabelData);

	// Wifi
	Label* pWifiLabel = new (std::nothrow) Label();
	String getWifi;
	Application::GetInstance()->GetAppResource()->GetString(IDS_WIFI, getWifi);
	pWifiLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getWifi);
	pWifiLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pWifiLabel->SetTextColor(COLOR_TITLE_LABEL);
	pWifiLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pWifiLabel);

	__pWifiLabelData = new (std::nothrow) Label();
	__pWifiLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pWifiLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pWifiLabelData);

	// Description
	Label* pDescriptionLabel = new (std::nothrow) Label();
	String getMemo;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION, getMemo);
	pDescriptionLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getMemo);
	pDescriptionLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDescriptionLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDescriptionLabel->SetBackgroundColor(Color(COLOR_BACKGROUND_LABEL));
	pScrollPanel->AddControl(pDescriptionLabel);

	__pDescriptionLabelData = new (std::nothrow) Label();
	__pDescriptionLabelData->Construct(Rectangle(UI_X_POSITION_MIDDLE, yPosition, UI_WIDTH * 3 / 4, UI_HEIGHT), L"");
	__pDescriptionLabelData->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pScrollPanel->AddControl(__pDescriptionLabelData);

	AddControl(pScrollPanel);

	return r;
}

result
ProfileDetailForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void
ProfileDetailForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_FOOTER_EDIT:
	{
		// TODO: should be modified!!!!!!!!!!
		MessageBox messageBox;
		String getError, getFailEdit;
		Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
		Application::GetInstance()->GetAppResource()->GetString(IDS_FAIL_EDIT, getFailEdit);
		messageBox.Construct(getError, getFailEdit, MSGBOX_STYLE_OK, 0);
		int doModal;
		messageBox.ShowAndWait(doModal);
	}
	break;

	case ID_FOOTER_DELETE:
	{
		DeleteProfile();
	}
	break;

	default:
	{
	}
	break;
	}
}

void
ProfileDetailForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_LIST));
}

void
ProfileDetailForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	result r = E_SUCCESS;

	if (pArgs != null)
	{
		Integer* pId = static_cast< Integer* >(pArgs->GetAt(0));

		if (pId == null)
		{
			MessageBox messageBox;
			String getError, getFailGet;
			Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
			Application::GetInstance()->GetAppResource()->GetString(IDS_FAIL_GET, getFailGet);
			messageBox.Construct(getError, getFailGet, MSGBOX_STYLE_OK, 0);
			int doModal;
			messageBox.ShowAndWait(doModal);

			AppLogException("[%s] Failed to get Profile.", GetErrorMessage(r));
		}
		else
		{
			__currentID = pId->ToInt();
			String* pSubjectValue = static_cast< String* >(pArgs->GetAt(1));
			if (pSubjectValue == null) {
				__pSubjectLabelData->SetText(L"(No subject)");
			} else {
				__pSubjectLabelData->SetText(*pSubjectValue);
			}
			Integer* pYear = static_cast< Integer* >(pArgs->GetAt(2));
			Integer* pMonth = static_cast< Integer* >(pArgs->GetAt(3));
			Integer* pDay = static_cast< Integer* >(pArgs->GetAt(4));
			Integer* pHour = static_cast< Integer* >(pArgs->GetAt(5));
			Integer* pMinute = static_cast< Integer* >(pArgs->GetAt(6));
			String startString;
			startString.Format(30, L"%d/%02d/%02d %02d:%02d", pYear->ToInt(), pMonth->ToInt(), pDay->ToInt(), pHour->ToInt(), pMinute->ToInt());
			__pStartDateLabelData->SetText(startString);
			Integer* pYear2 = static_cast< Integer* >(pArgs->GetAt(7));
			Integer* pMonth2 = static_cast< Integer* >(pArgs->GetAt(8));
			Integer* pDay2 = static_cast< Integer* >(pArgs->GetAt(9));
			Integer* pHour2 = static_cast< Integer* >(pArgs->GetAt(10));
			Integer* pMinute2 = static_cast< Integer* >(pArgs->GetAt(11));
			String startString2;
			startString2.Format(30, L"%d/%02d/%02d %02d:%02d", pYear2->ToInt(), pMonth2->ToInt(), pDay2->ToInt(), pHour2->ToInt(), pMinute2->ToInt());
			__pDueDateLabelData->SetText(startString2);
			//TODO: Should be modified!!!!

			Integer* pVolume = static_cast< Integer* >(pArgs->GetAt(14));
			__pVolumeLabelData->SetText(pVolume->ToString());
			Integer* pWifi = static_cast< Integer* >(pArgs->GetAt(15));
			__pWifiLabelData->SetText(pWifi->ToInt()==1?"On":"Off");
			String* pMemo = static_cast< String* >(pArgs->GetAt(16));
			String PropertyValue = L"(No description)";
			if (pMemo != null) {
				PropertyValue = *pMemo;
			}
			__pDescriptionLabelData->SetText(PropertyValue);

			Invalidate(true);
		}

		pArgs->RemoveAll(true);
		delete pArgs;
	}
}

void
ProfileDetailForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
}

void
ProfileDetailForm::DeleteProfile(void)
{
	ProfileListForm *pProfileListForm = static_cast< ProfileListForm* >(Application::GetInstance()->GetAppFrame()->GetFrame()->GetControl(FORM_LIST));
	if (pProfileListForm != NULL)
	{
		if (pProfileListForm->DeleteProfile(__currentID))
		{
			SceneManager* pSceneManager = SceneManager::GetInstance();
			AppAssert(pSceneManager);

			pSceneManager->GoBackward(BackwardSceneTransition(SCENE_LIST));
		}
	}
	else
	{
		MessageBox messageBox;
		String getError, getFailDelete;
		Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
		Application::GetInstance()->GetAppResource()->GetString(IDS_FAIL_DELETE, getFailDelete);
		messageBox.Construct(getError, getFailDelete, MSGBOX_STYLE_OK, 0);
		int doModal;
		messageBox.ShowAndWait(doModal);
	}

}
