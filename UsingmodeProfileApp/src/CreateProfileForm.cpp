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
#include "CreateProfileForm.h"
#include "ProfileListForm.h"
#include "ProfileFormFactory.h"
#include "SceneRegister.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::Social;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

static const int CONTEXT_POSITION = 200;


CreateProfileForm::CreateProfileForm()
{
}

CreateProfileForm::~CreateProfileForm()
{
}

bool
CreateProfileForm::Initialize(void)
{
	result r = E_SUCCESS;

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));
	SetName(FORM_CREATION);
	return true;
}

result
CreateProfileForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	String getProfileCreationTitle;
	Application::GetInstance()->GetAppResource()->GetString(IDS_CREATE_TITLE, getProfileCreationTitle);
	pHeader->SetTitleText(getProfileCreationTitle);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_BUTTON_SAVE);
	String getSave;
	Application::GetInstance()->GetAppResource()->GetString(IDS_SAVE, getSave);
	footerSave.SetText(getSave);
	pFooter->AddItem(footerSave);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4;
	static const int UI_HEIGHT = 112;
	static const int UI_SPACE = 26;
	int yPosition = 0;

	__pScrollPanel = new (std::nothrow) ScrollPanel();
	__pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	// Subject
	__pSubjectEditField = new (std::nothrow) EditField();
	__pSubjectEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	String getProfileName, getProfileNameGuid;
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME, getProfileName);
	Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_GUIDE, getProfileNameGuid);
	__pSubjectEditField->SetGuideText(getProfileNameGuid);
	__pSubjectEditField->SetName(L"Subject");
	__pSubjectEditField->SetTitleText(getProfileName);
	__pSubjectEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pSubjectEditField);

	// Start Date
	int minYear = Calendarbook::GetMinDateTime().GetYear() + 1;
	int maxYear = Calendarbook::GetMaxDateTime().GetYear() - 1;

	Label* pStartDateLabel = new (std::nothrow) Label();
	String getStartDateTime, getEndDateTime;
	Application::GetInstance()->GetAppResource()->GetString(IDS_START_DATETIME, getStartDateTime);
	Application::GetInstance()->GetAppResource()->GetString(IDS_END_DATETIME, getEndDateTime);
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getStartDateTime);
	pStartDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pStartDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStartDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStartDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pStartDateLabel);

	__pStartEditDate = new (std::nothrow) EditDate();
	__pStartEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pStartEditDate->SetCurrentDate();
	__pStartEditDate->SetYearRange(minYear, maxYear);
	__pStartEditDate->AddDateChangeEventListener(*this);
	__pScrollPanel->AddControl(__pStartEditDate);

	__pStartEditTime = new (std::nothrow) EditTime();
	__pStartEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pStartEditTime->SetCurrentTime();
	__pStartEditTime->AddTimeChangeEventListener(*this);
	__pScrollPanel->AddControl(__pStartEditTime);

	// Due Date
	Label* pDueDateLabel = new (std::nothrow) Label();
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getEndDateTime);
	pDueDateLabel->SetTextVerticalAlignment(ALIGNMENT_TOP);
	pDueDateLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pDueDateLabel->SetTextColor(COLOR_TITLE_LABEL);
	pDueDateLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pDueDateLabel);

	__pDueEditDate = new (std::nothrow) EditDate();
	__pDueEditDate->Construct(Point(UI_X_POSITION_GAP, yPosition + 10));
	__pDueEditDate->SetCurrentDate();
	__pDueEditDate->SetYearRange(minYear, maxYear);
	__pDueEditDate->AddDateChangeEventListener(*this);
	__pScrollPanel->AddControl(__pDueEditDate);

	DateTime endTime;
	endTime = __pStartEditTime->GetTime();
	endTime.AddHours(1);

	__pDueEditTime = new (std::nothrow) EditTime();
	__pDueEditTime->Construct(Point(UI_X_POSITION_MIDDLE * 2 + UI_SPACE, yPosition + 10));
	__pDueEditTime->SetTime(endTime);
	__pDueEditTime->AddTimeChangeEventListener(*this);
	__pScrollPanel->AddControl(__pDueEditTime);

	// Location
	String  getLocationGuide;
	Application::GetInstance()->GetAppResource()->GetString(IDS_LOCATION_GUIDE, getLocationGuide);

	__pLocationButton = new (std::nothrow) Button();
	__pLocationButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getLocationGuide);
	__pLocationButton->SetActionId(ID_LOCATION_BUTTON);
	__pLocationButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pLocationButton);

	// Volume
	String getVolume;
	Application::GetInstance()->GetAppResource()->GetString(IDS_VOLUME, getVolume);
	__pVolumeSlider = new (std::nothrow) Slider();
	__pVolumeSlider->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH/*GetClientAreaBounds().width*/, UI_HEIGHT + 30), BACKGROUND_STYLE_DEFAULT, true, 0, 15);
	__pVolumeSlider->SetValue(5);
	__pVolumeSlider->SetTitleText(getVolume);
	__pVolumeSlider->AddAdjustmentEventListener(*this);
	__pScrollPanel->AddControl(__pVolumeSlider);

	// Wifi
	String getWifi;
	Application::GetInstance()->GetAppResource()->GetString(IDS_WIFI, getWifi);
	__pWifiCheckButton = new (std::nothrow) CheckButton();
	__pWifiCheckButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT),
			CHECK_BUTTON_STYLE_ONOFF_SLIDING, BACKGROUND_STYLE_DEFAULT, false, getWifi);
	__pWifiCheckButton->SetActionId(ID_BUTTON_CHECKED, ID_BUTTON_UNCHECKED, ID_BUTTON_SELECTED);
	__pWifiCheckButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pWifiCheckButton);

	// Description
	String getDescription, getDescriptionGuide;
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION, getDescription);
	Application::GetInstance()->GetAppResource()->GetString(IDS_DESCRIPTION_GUIDE, getDescriptionGuide);
	__pDescriptionEditField = new (std::nothrow) EditField();
	__pDescriptionEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pDescriptionEditField->SetGuideText(getDescriptionGuide);
	__pDescriptionEditField->SetName(L"Description");
	__pDescriptionEditField->SetTitleText(getDescription);
	__pDescriptionEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pDescriptionEditField);

	AddControl(__pScrollPanel);

	return r;
}

result
CreateProfileForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void
CreateProfileForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_BUTTON_SAVE:
		if (__pSubjectEditField->GetText().IsEmpty())
		{
			int doModal;
			MessageBox messageBox;
			String getError, getProfileNameError;
			Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME_ERROR, getProfileNameError);
			Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
			messageBox.Construct(getError, getProfileNameError, MSGBOX_STYLE_OK, 0);
			messageBox.ShowAndWait(doModal);
		}
		else
		{
			AppLog("mobilehunter.net test!!!");
			pSceneManager->GoBackward(BackwardSceneTransition());

			ProfileListForm *pProfileListForm = static_cast< ProfileListForm* >(Application::GetInstance()->GetAppFrame()->GetFrame()->GetControl(FORM_LIST));
			if (pProfileListForm != NULL) {
				pProfileListForm->SaveUsingmodeProfile(__pSubjectEditField->GetText(),
						__pStartEditDate->GetYear(),
						__pStartEditDate->GetMonth(),
						__pStartEditDate->GetDay(),
						__pStartEditTime->GetHour(),
						__pStartEditTime->GetMinute(),
						__pDueEditDate->GetYear(),
						__pDueEditDate->GetMonth(),
						__pDueEditDate->GetDay(),
						__pDueEditTime->GetHour(),
						__pDueEditTime->GetMinute(),
						0,
						0,
						__pVolumeSlider->GetValue(),
						__pWifiCheckButton->IsSelected()?1:0,
						__pDescriptionEditField->GetText());
				AppLog("mobilehunter.net test!!!111");
			}
		}
		break;
	case ID_LOCATION_BUTTON:
		pSceneManager->GoForward(ForwardSceneTransition(SCENE_LOCATION));
		break;
	default:
		break;
	}
}

void
CreateProfileForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition());
}

void
CreateProfileForm::OnDateChanged(const Tizen::Ui::Control& source, int year, int month, int day)
{
	if ((__pStartEditDate->GetDate() > __pDueEditDate->GetDate()) || (__pStartEditDate->GetDate() == __pDueEditDate->GetDate() && __pStartEditTime->GetTime() > __pDueEditTime->GetTime()))
	{
		__pDueEditDate->SetDate(__pStartEditDate->GetDate());
		__pDueEditDate->Invalidate(false);
		__pDueEditTime->SetTime(__pStartEditTime->GetTime());
		__pDueEditTime->Invalidate(false);
	}
}

void
CreateProfileForm::OnDateChangeCanceled(const Tizen::Ui::Control& source)
{
}

void
CreateProfileForm::OnTimeChanged(const Control& source, int hour, int minute)
{
	if ((__pStartEditDate->GetDate() > __pDueEditDate->GetDate()) || (__pStartEditDate->GetDate() == __pDueEditDate->GetDate() && __pStartEditTime->GetTime() > __pDueEditTime->GetTime()))
	{
		__pDueEditDate->SetDate(__pStartEditDate->GetDate());
		__pDueEditDate->Invalidate(false);
		__pDueEditTime->SetTime(__pStartEditTime->GetTime());
		__pDueEditTime->Invalidate(false);
	}
}

void
CreateProfileForm::OnTimeChangeCanceled(const Control& source)
{
}

void
CreateProfileForm::CalculateAnchorPosition(Button* pButton, ContextMenu* pContextMenu)
{
	int scrollPosition = __pScrollPanel->GetScrollPosition();
	Rectangle buttonRectangle = pButton->GetBounds();

	Point contextMenuPoint = pContextMenu->GetAnchorPosition();
	contextMenuPoint.y = buttonRectangle.y + CONTEXT_POSITION - scrollPosition;

	pContextMenu->SetAnchorPosition(contextMenuPoint);
}

void
CreateProfileForm::OnAdjustmentValueChanged(const Control& source, int adjustment)
{
}

void
CreateProfileForm::SetMap(float x, float y)
{
	AppLog("수정 (%f, %f)", x, y);

	String mapButtonString;
	mapButtonString.Format(20, L"수정 (%f, %f)", x, y);
	__pLocationButton->SetText(mapButtonString);
}
