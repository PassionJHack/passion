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
#include "ProfileFormFactory.h"
#include "EditProfileForm.h"
#include "SceneRegister.h"
#include "ProfileListForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Graphics;
using namespace Tizen::Locales;
using namespace Tizen::Social;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

static const int CONTEXT_POSITION = 200;

EditProfileForm::EditProfileForm()
{
}

EditProfileForm::~EditProfileForm()
{
}

bool
EditProfileForm::Initialize(void)
{
	result r = E_SUCCESS;

	r = Construct(FORM_STYLE_NORMAL | FORM_STYLE_FOOTER | FORM_STYLE_HEADER | FORM_STYLE_PORTRAIT_INDICATOR);
	TryReturn(!IsFailed(r), false, "[%s] Failed to construct the form.", GetErrorMessage(r));
    SetName(FORM_EDITION);
	__latitude = 0;
	__longitude = 0;
    __currentID = -1;
	return true;
}

result
EditProfileForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppResource * pAppResource = Application::GetInstance()->GetAppResource();
	String resourceString;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
    String getProfileCreationTitle;
    pAppResource->GetString(IDS_EDIT, getProfileCreationTitle);
	pHeader->SetTitleText(getProfileCreationTitle);

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_BUTTON_SAVE);
    String getSave;
    pAppResource->GetString(IDS_SAVE, getSave);
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

	// 1. Profile Name
	__pNameEditField = new (std::nothrow) EditField();
	__pNameEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
    String getProfileName, getProfileNameGuid;
    pAppResource->GetString(IDS_PROFILE_NAME, getProfileName);
    pAppResource->GetString(IDS_PROFILE_GUIDE, getProfileNameGuid);
    __pNameEditField->SetGuideText(getProfileNameGuid);
    __pNameEditField->SetName(L"Name");
    __pNameEditField->SetTitleText(getProfileName);

	__pNameEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pNameEditField);

	// 2. Profile Start Date
	int minYear = Calendarbook::GetMinDateTime().GetYear() + 1;
	int maxYear = Calendarbook::GetMaxDateTime().GetYear() - 1;

	Label* pStartDateLabel = new (std::nothrow) Label();
    String getStartDateTime, getDudueDateTime;
    pAppResource->GetString(IDS_START_DATETIME, getStartDateTime);
    pAppResource->GetString(IDS_END_DATETIME, getDudueDateTime);
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

	// 3. Profile Due Date
	Label* pDueDateLabel = new (std::nothrow) Label();
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), getDudueDateTime);
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

	 // 4~5. Profile Location(Latitude, Longitude)
    String  getLocationGuide;
    pAppResource->GetString(IDS_LOCATION_GUIDE, getLocationGuide);
    __pLocationButton = new (std::nothrow) Button();
    __pLocationButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), getLocationGuide);
    __pLocationButton->SetActionId(ID_LOCATION_BUTTON);
    __pLocationButton->AddActionEventListener(*this);
    __pScrollPanel->AddControl(__pLocationButton);

    // 6. Profile Volume
    String getVolume;
    pAppResource->GetString(IDS_VOLUME, getVolume);
    __pVolumeSlider = new (std::nothrow) Slider();
    __pVolumeSlider->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT + 30), BACKGROUND_STYLE_DEFAULT, true, 0, 15);
    __pVolumeSlider->SetValue(5);
    __pVolumeSlider->SetTitleText(getVolume);
    __pVolumeSlider->AddAdjustmentEventListener(*this);
    __pScrollPanel->AddControl(__pVolumeSlider);
    
    // 7. Profile Wifi
    String getWifi;
    pAppResource->GetString(IDS_WIFI, getWifi);
    __pWifiCheckButton = new (std::nothrow) CheckButton();
    __pWifiCheckButton->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT),
                                  CHECK_BUTTON_STYLE_ONOFF_SLIDING, BACKGROUND_STYLE_DEFAULT, false, getWifi);
    __pWifiCheckButton->SetActionId(ID_BUTTON_CHECKED, ID_BUTTON_UNCHECKED, ID_BUTTON_SELECTED);
    __pWifiCheckButton->AddActionEventListener(*this);
    __pScrollPanel->AddControl(__pWifiCheckButton);

    // 8. Profile Memo
    String getDescription, getDescriptionGuide;
    pAppResource->GetString(IDS_DESCRIPTION, getDescription);
    pAppResource->GetString(IDS_DESCRIPTION_GUIDE, getDescriptionGuide);
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
EditProfileForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void
EditProfileForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_BUTTON_SAVE:
	{
		if (__pNameEditField->GetText().IsEmpty())
		{
			int doModal;
			MessageBox messageBox;
			AppResource * pAppResource = Application::GetInstance()->GetAppResource();
			String getError, getProfileNameError;
			pAppResource->GetString(IDS_ERROR, getError);
			pAppResource->GetString(IDS_PROFILE_NAME_ERROR, getProfileNameError);
			messageBox.Construct(getError, getProfileNameError, MSGBOX_STYLE_OK, 0);
			messageBox.ShowAndWait(doModal);
		}
		else
		{
            ProfileListForm *pProfileListForm = static_cast< ProfileListForm* >(Application::GetInstance()->GetAppFrame()->GetFrame()->GetControl(FORM_LIST));
            if (pProfileListForm != NULL) {
				DateTime startDateTime, dueDateTime;
				startDateTime.SetValue(__pStartEditDate->GetYear(),
						__pStartEditDate->GetMonth(),
						__pStartEditDate->GetDay(),
						__pStartEditTime->GetHour(),
						__pStartEditTime->GetMinute(),
						0);
				dueDateTime.SetValue(__pDueEditDate->GetYear(),
						__pDueEditDate->GetMonth(),
						__pDueEditDate->GetDay(),
						__pDueEditTime->GetHour(),
						__pDueEditTime->GetMinute(),
						0);
				_profile_t_ profileSave = { __currentID, __pNameEditField->GetText(), startDateTime, dueDateTime, __latitude, __longitude, __pVolumeSlider->GetValue(),
						__pWifiCheckButton->IsSelected()?1:0,
						__pDescriptionEditField->GetText() };

				ArrayList* pList = new (std::nothrow) ArrayList();
				pList->Construct();
		        pList->Add(*new (std::nothrow) Integer(profileSave.index));
		        pList->Add(*new (std::nothrow) String(profileSave.name));
		        pList->Add(*new (std::nothrow) String(profileSave.startDateTime.ToString()));
		        pList->Add(*new (std::nothrow) String(profileSave.dueDateTime.ToString()));
		        pList->Add(*new (std::nothrow) Double(profileSave.latitude));
		        pList->Add(*new (std::nothrow) Double(profileSave.longitude));
		        pList->Add(*new (std::nothrow) Integer(profileSave.volume));
		        pList->Add(*new (std::nothrow) Integer(profileSave.wifi));
		        pList->Add(*new (std::nothrow) String(profileSave.memo));

				pSceneManager->GoBackward(BackwardSceneTransition(SCENE_DETAIL), pList);
				pProfileListForm->UpdateUsingmodeProfile(profileSave);	// Update
			}
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
EditProfileForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	pSceneManager->GoBackward(BackwardSceneTransition());
}

void
EditProfileForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	if (pArgs != null)
	{
        Integer* pId = static_cast< Integer* >(pArgs->GetAt(0));				// 0. Profile Index : Not List Index
        if (pId == null)
        {
            MessageBox messageBox;
            String getError, getFailGet;
			AppResource * pAppResource = Application::GetInstance()->GetAppResource();
			pAppResource->GetString(IDS_ERROR, getError);
			pAppResource->GetString(IDS_FAIL_GET, getFailGet);
            messageBox.Construct(getError, getFailGet, MSGBOX_STYLE_OK, 0);
            int doModal;
            messageBox.ShowAndWait(doModal);
        }
        else
        {
            __currentID = pId->ToInt();

            String* pNameValue = static_cast< String* >(pArgs->GetAt(1));		// 1. Profile Name
            if (pNameValue == null) {
            	__pNameEditField->SetText(L"(No Name)");
            } else {
            	__pNameEditField->SetText(*pNameValue);
            }
            String* pStartDateString = static_cast< String* >(pArgs->GetAt(2));	// 2. Profile Start Date
            DateTime StartDateTime;
            Tizen::Base::DateTime::Parse(*pStartDateString, StartDateTime);
            __pStartEditDate->SetDate(StartDateTime);
            __pStartEditTime->SetTime(StartDateTime);
            String* pDueDateString = static_cast< String* >(pArgs->GetAt(3));	// 3. Profile Due Date
            DateTime DueDateTime;
            Tizen::Base::DateTime::Parse(*pDueDateString, DueDateTime);
            __pDueEditDate->SetDate(DueDateTime);
            __pDueEditTime->SetTime(DueDateTime);
            Double* pLatitude = static_cast< Double* >(pArgs->GetAt(4));		// 4. Profile Location(Latitude)
            Double* pLongitude = static_cast< Double* >(pArgs->GetAt(5));		// 5. Profile Location(Longitude)
        	String LocationString;
        	LocationString.Format(50, L"latitude: %.2f, longitude: %.2f", pLatitude->value, pLongitude->value);
            __pLocationButton->SetText(LocationString);
            Integer* pVolume = static_cast< Integer* >(pArgs->GetAt(6));		// 6. Profile Volume
            __pVolumeSlider->SetValue(pVolume->ToInt());
            Integer* pWifi = static_cast< Integer* >(pArgs->GetAt(7));			// 7. Profile Wifi
            __pWifiCheckButton->SetSelected(pWifi->ToInt()==1?true:false);
            String* pMemo = static_cast< String* >(pArgs->GetAt(8));			// 8. Profile Memo
            String PropertyValue = L"(No description)";
            if (pMemo != null) {
                PropertyValue = *pMemo;
            }
            __pDescriptionEditField->SetText(PropertyValue);
            
            Invalidate(true);
        }
        pArgs->RemoveAll(true);
        delete pArgs;
    }
}

void
EditProfileForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
}

void
EditProfileForm::OnDateChanged(const Tizen::Ui::Control& source, int year, int month, int day)
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
EditProfileForm::OnDateChangeCanceled(const Tizen::Ui::Control& source)
{
}

void
EditProfileForm::OnTimeChanged(const Control& source, int hour, int minute)
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
EditProfileForm::OnTimeChangeCanceled(const Control& source)
{
}

void
EditProfileForm::CalculateAnchorPosition(Button* pButton, ContextMenu* pContextMenu)
{
	int scrollPosition = __pScrollPanel->GetScrollPosition();
	Rectangle buttonRectangle = pButton->GetBounds();

	Point contextMenuPoint = pContextMenu->GetAnchorPosition();
	contextMenuPoint.y = buttonRectangle.y + CONTEXT_POSITION - scrollPosition;

	pContextMenu->SetAnchorPosition(contextMenuPoint);
}
void
EditProfileForm::OnAdjustmentValueChanged(const Control& source, int adjustment)
{
}

void
EditProfileForm::SetMap(double latitude, double longitude)
{
	String mapButtonString;
	mapButtonString.Format(50, L"latitude: %.2f, longitude: %.2f", latitude, longitude);
	__latitude = latitude;
	__longitude = longitude;
	__pLocationButton->SetText(mapButtonString);
}
