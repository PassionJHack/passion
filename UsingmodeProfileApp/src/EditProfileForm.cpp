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
#include "EditProfileForm.h"
#include "SceneRegister.h"

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
	: __pProfile(null)
	, __selectedPriority(TODO_PRIORITY_LOW)
	, __selectedSensitivity(SENSITIVITY_PUBLIC)
	, __selectedStatus(TODO_STATUS_NONE)
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

	return true;
}

result
EditProfileForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	AppAssert(pHeader);
	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pHeader->SetTitleText(L"Edition");

	Footer* pFooter = GetFooter();
	AppAssert(pFooter);
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);

	FooterItem footerSave;
	footerSave.Construct(ID_BUTTON_SAVE);
	footerSave.SetText(L"Save");
	pFooter->AddItem(footerSave);
	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

	static const unsigned int COLOR_BACKGROUND_LABEL = 0xFFEFEDE5;
	static const unsigned int COLOR_TITLE_LABEL = 0xFF808080;

	static const int UI_X_POSITION_GAP = 20;
	static const int UI_WIDTH = GetClientAreaBounds().width - 40;
	static const int UI_X_POSITION_MIDDLE = UI_WIDTH / 4;
	static const int UI_HEIGHT = 112;
	static const int BUTTON_HEIGHT = 74;
	static const int UI_SPACE = 26;
	int yPosition = 0;

	__pScrollPanel = new (std::nothrow) ScrollPanel();
	__pScrollPanel->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height));

	// Subject
	__pSubjectEditField = new (std::nothrow) EditField();
	__pSubjectEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pSubjectEditField->SetGuideText(L"Enter the subject");
	__pSubjectEditField->SetName(L"Subject");
	__pSubjectEditField->SetTitleText(L"Subject");
	__pSubjectEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pSubjectEditField);

	// Start Date
	int minYear = Calendarbook::GetMinDateTime().GetYear() + 1;
	int maxYear = Calendarbook::GetMaxDateTime().GetYear() - 1;

	Label* pStartDateLabel = new (std::nothrow) Label();
	pStartDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), L"Start");
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
	pDueDateLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Due");
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
	__pLocationEditField = new (std::nothrow) EditField();
	__pLocationEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pLocationEditField->SetGuideText(L"Enter the location");
	__pLocationEditField->SetName(L"Location");
	__pLocationEditField->SetTitleText(L"Location");
	__pLocationEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pLocationEditField);

	// Priority
	Label* pPriorityLabel = new (std::nothrow) Label();
	pPriorityLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), L"Priority");
	pPriorityLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pPriorityLabel->SetTextColor(COLOR_TITLE_LABEL);
	pPriorityLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pPriorityLabel);

	__pPriorityContextButton = new (std::nothrow) Button();
	__pPriorityContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"Low");
	__pPriorityContextButton->SetActionId(ID_BUTTON_PRIORITY);
	__pPriorityContextButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pPriorityContextButton);

	__pPriorityTextContextMenu = new (std::nothrow) ContextMenu();
	__pPriorityTextContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + CONTEXT_POSITION), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pPriorityTextContextMenu->AddItem(L"High", ID_CONTEXT_PRIORITY_HIGH);
	__pPriorityTextContextMenu->AddItem(L"Normal", ID_CONTEXT_PRIORITY_NORMAL);
	__pPriorityTextContextMenu->AddItem(L"Low", ID_CONTEXT_PRIORITY_LOW);
	__pPriorityTextContextMenu->AddActionEventListener(*this);

	// Sensitivity
	Label* pSensitivityLabel = new (std::nothrow) Label();
	pSensitivityLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Sensitivity");
	pSensitivityLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pSensitivityLabel->SetTextColor(COLOR_TITLE_LABEL);
	pSensitivityLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pSensitivityLabel);

	__pSensitivityContextButton = new (std::nothrow) Button();
	__pSensitivityContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"Public");
	__pSensitivityContextButton->SetActionId(ID_BUTTON_SENSITIVITY);
	__pSensitivityContextButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pSensitivityContextButton);

	__pSensitivityTextContextMenu = new (std::nothrow) ContextMenu();
	__pSensitivityTextContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + CONTEXT_POSITION), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pSensitivityTextContextMenu->AddItem(L"Public", ID_CONTEXT_SENSITIVITY_PUBLIC);
	__pSensitivityTextContextMenu->AddItem(L"Private", ID_CONTEXT_SENSITIVITY_PRIVATE);
	__pSensitivityTextContextMenu->AddItem(L"Confidential", ID_CONTEXT_SENSITIVITY_CONFIDENTIAL);
	__pSensitivityTextContextMenu->AddActionEventListener(*this);

	// Status
	Label* pStatusLabel = new (std::nothrow) Label();
	pStatusLabel->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT, UI_WIDTH, UI_HEIGHT), L"Status");
	pStatusLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pStatusLabel->SetTextColor(COLOR_TITLE_LABEL);
	pStatusLabel->SetBackgroundColor(COLOR_BACKGROUND_LABEL);
	__pScrollPanel->AddControl(pStatusLabel);

	__pStatusContextButton = new (std::nothrow) Button();
	__pStatusContextButton->Construct(Rectangle(UI_X_POSITION_MIDDLE + UI_X_POSITION_GAP, yPosition + 19, UI_WIDTH * 3 / 4, BUTTON_HEIGHT), L"None");
	__pStatusContextButton->SetActionId(ID_BUTTON_STATUS);
	__pStatusContextButton->AddActionEventListener(*this);
	__pScrollPanel->AddControl(__pStatusContextButton);

	__pStatusTextContextMenu = new (std::nothrow) ContextMenu();
	__pStatusTextContextMenu->Construct(Point(UI_X_POSITION_GAP + UI_WIDTH * 5 / 8, yPosition + CONTEXT_POSITION), CONTEXT_MENU_STYLE_LIST, CONTEXT_MENU_ANCHOR_DIRECTION_UPWARD);
	__pStatusTextContextMenu->AddItem(L"None", ID_CONTEXT_STATUS_NONE);
	__pStatusTextContextMenu->AddItem(L"Needs action", ID_CONTEXT_STATUS_NEEDSACTION);
	__pStatusTextContextMenu->AddItem(L"Completed", ID_CONTEXT_STATUS_COMPLETED);
	__pStatusTextContextMenu->AddItem(L"In process", ID_CONTEXT_STATUS_INPROCESS);
	__pStatusTextContextMenu->AddItem(L"Cancelled", ID_CONTEXT_STATUS_CANCELLED);
	__pStatusTextContextMenu->SetMaxVisibleItemsCount(3);
	__pStatusTextContextMenu->AddActionEventListener(*this);

	// Description
	__pDescriptionEditField = new (std::nothrow) EditField();
	__pDescriptionEditField->Construct(Rectangle(UI_X_POSITION_GAP, yPosition += UI_HEIGHT + UI_SPACE, UI_WIDTH, UI_HEIGHT), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, EDIT_FIELD_TITLE_STYLE_TOP);
	__pDescriptionEditField->SetGuideText(L"Enter the description");
	__pDescriptionEditField->SetName(L"Description");
	__pDescriptionEditField->SetTitleText(L"Description");
	__pDescriptionEditField->SetOverlayKeypadCommandButtonVisible(false);
	__pScrollPanel->AddControl(__pDescriptionEditField);

	AddControl(__pScrollPanel);

	return r;
}

result
EditProfileForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	if (__pProfile != null)
	{
		delete __pProfile;
	}

	__pPriorityTextContextMenu->Destroy();
	__pSensitivityTextContextMenu->Destroy();
	__pStatusTextContextMenu->Destroy();

	return r;
}

void
EditProfileForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	result r = E_SUCCESS;

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch (actionId)
	{
	case ID_BUTTON_SAVE:
	{
		if (__pSubjectEditField->GetText().IsEmpty())
		{
			int doModal;
			MessageBox messageBox;
			String getError, getProfileNameError;
			Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
			Application::GetInstance()->GetAppResource()->GetString(IDS_PROFILE_NAME_ERROR, getProfileNameError);
			messageBox.Construct(getError, getProfileNameError, MSGBOX_STYLE_OK, 0);
			messageBox.ShowAndWait(doModal);
		}
		else
		{
			r = UpdateProfile();
			TryReturnVoid(!IsFailed(r), "[%s] Failed to update Profile.", GetErrorMessage(r));

			ArrayList* pList = new (std::nothrow) ArrayList();
			pList->Construct();
			pList->Add(*new (std::nothrow) Integer(__pProfile->GetRecordId()));

			pSceneManager->GoBackward(BackwardSceneTransition(SCENE_DETAIL), pList);
		}
	}
	break;

	case ID_BUTTON_PRIORITY:
	{
		CalculateAnchorPosition(__pPriorityContextButton, __pPriorityTextContextMenu);

		__pPriorityTextContextMenu->SetFocusable(true);
		__pPriorityTextContextMenu->SetShowState(true);
		__pPriorityTextContextMenu->SetFocus();
		__pPriorityTextContextMenu->Show();
	}
	break;

	case ID_CONTEXT_PRIORITY_LOW:
	{
		__selectedPriority = TODO_PRIORITY_LOW;
		__pPriorityContextButton->SetText(L"Low");
		__pPriorityContextButton->SetFocus();
		__pPriorityContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_PRIORITY_NORMAL:
	{
		__selectedPriority = TODO_PRIORITY_NORMAL;
		__pPriorityContextButton->SetText(L"Normal");
		__pPriorityContextButton->SetFocus();
		__pPriorityContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_PRIORITY_HIGH:
	{
		__selectedPriority = TODO_PRIORITY_HIGH;
		__pPriorityContextButton->SetText(L"High");
		__pPriorityContextButton->SetFocus();
		__pPriorityContextButton->Invalidate(false);
	}
	break;

	case ID_BUTTON_SENSITIVITY:
	{
		CalculateAnchorPosition(__pSensitivityContextButton, __pSensitivityTextContextMenu);

		__pSensitivityTextContextMenu->SetFocusable(true);
		__pSensitivityTextContextMenu->SetShowState(true);
		__pSensitivityTextContextMenu->SetFocus();
		__pSensitivityTextContextMenu->Show();
	}
	break;

	case ID_CONTEXT_SENSITIVITY_PUBLIC:
	{
		__selectedSensitivity = SENSITIVITY_PUBLIC;
		__pSensitivityContextButton->SetText(L"Public");
		__pSensitivityContextButton->SetFocus();
		__pSensitivityContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_SENSITIVITY_PRIVATE:
	{
		__selectedSensitivity = SENSITIVITY_PRIVATE;
		__pSensitivityContextButton->SetText(L"Private");
		__pSensitivityContextButton->SetFocus();
		__pSensitivityContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_SENSITIVITY_CONFIDENTIAL:
	{
		__selectedSensitivity = SENSITIVITY_CONFIDENTIAL;
		__pSensitivityContextButton->SetText(L"Confidential");
		__pSensitivityContextButton->SetFocus();
		__pSensitivityContextButton->Invalidate(false);
	}
	break;

	case ID_BUTTON_STATUS:
	{
		CalculateAnchorPosition(__pStatusContextButton, __pStatusTextContextMenu);

		__pStatusTextContextMenu->SetFocusable(true);
		__pStatusTextContextMenu->SetShowState(true);
		__pStatusTextContextMenu->SetFocus();
		__pStatusTextContextMenu->Show();
	}
	break;

	case ID_CONTEXT_STATUS_NONE:
	{
		__selectedStatus = TODO_STATUS_NONE;
		__pStatusContextButton->SetText(L"None");
		__pStatusContextButton->SetFocus();
		__pStatusContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_STATUS_NEEDSACTION:
	{
		__selectedStatus = TODO_STATUS_NEEDS_ACTION;
		__pStatusContextButton->SetText(L"Needs action");
		__pStatusContextButton->SetFocus();
		__pStatusContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_STATUS_COMPLETED:
	{
		__selectedStatus = TODO_STATUS_COMPLETED;
		__pStatusContextButton->SetText(L"Completed");
		__pStatusContextButton->SetFocus();
		__pStatusContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_STATUS_INPROCESS:
	{
		__selectedStatus = TODO_STATUS_IN_PROCESS;
		__pStatusContextButton->SetText(L"In process");
		__pStatusContextButton->SetFocus();
		__pStatusContextButton->Invalidate(false);
	}
	break;

	case ID_CONTEXT_STATUS_CANCELLED:
	{
		__selectedStatus = TODO_STATUS_CANCELLED;
		__pStatusContextButton->SetText(L"Cancelled");
		__pStatusContextButton->SetFocus();
		__pStatusContextButton->Invalidate(false);
	}
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
		__pProfile = static_cast< CalTodo* >(pArgs->GetAt(0));
		LoadProfile();
		pArgs->RemoveAll(false);
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
EditProfileForm::LoadProfile(void)
{
	// Loads the Subject
	__pSubjectEditField->SetText(__pProfile->GetSubject());

	// Convert UTC time to local time
	DateTime startDate = __pProfile->GetStartDate();
	DateTime dueDate = __pProfile->GetDueDate();

	LocaleManager localeManager;
	localeManager.Construct();

	TimeZone timeZone = localeManager.GetSystemTimeZone();
	startDate = timeZone.UtcTimeToWallTime(startDate);
	dueDate = timeZone.UtcTimeToWallTime(dueDate);

	// Loads the start date
	__pStartEditDate->SetDate(startDate);
	__pStartEditTime->SetTime(startDate);

	// Loads the due date
	__pDueEditDate->SetDate(dueDate);
	__pDueEditTime->SetTime(dueDate);

	// Loads the Location
	__pLocationEditField->SetText(__pProfile->GetLocation());

	// Loads the Priority
	__selectedPriority = __pProfile->GetPriority();
	switch (__selectedPriority)
	{
	case TODO_PRIORITY_LOW:
		__pPriorityContextButton->SetText(L"Low");
		break;

	case TODO_PRIORITY_NORMAL:
		__pPriorityContextButton->SetText(L"Normal");
		break;

	case TODO_PRIORITY_HIGH:
		__pPriorityContextButton->SetText(L"High");
		break;

	default:
		break;
	}

	// Loads the Sensitivity
	__selectedSensitivity = __pProfile->GetSensitivity();
	switch (__selectedSensitivity)
	{
	case SENSITIVITY_PUBLIC:
		__pSensitivityContextButton->SetText(L"Public");
		break;

	case SENSITIVITY_PRIVATE:
		__pSensitivityContextButton->SetText(L"Private");
		break;

	case SENSITIVITY_CONFIDENTIAL:
		__pSensitivityContextButton->SetText(L"Confidential");
		break;

	default:
		break;
	}

	// Loads the Status
	__selectedStatus = __pProfile->GetStatus();
	switch (__selectedStatus)
	{
	case TODO_STATUS_NONE:
		__pStatusContextButton->SetText(L"None");
		break;

	case TODO_STATUS_NEEDS_ACTION:
		__pStatusContextButton->SetText(L"Needs action");
		break;

	case TODO_STATUS_COMPLETED:
		__pStatusContextButton->SetText(L"Completed");
		break;

	case TODO_STATUS_IN_PROCESS:
		__pStatusContextButton->SetText(L"In process");
		break;

	case TODO_STATUS_CANCELLED:
		__pStatusContextButton->SetText(L"Cancelled");
		break;

	default:
		break;
	}

	// Loads the Description
	__pDescriptionEditField->SetText(__pProfile->GetDescription());

}

result
EditProfileForm::UpdateProfile(void)
{
	result r = E_SUCCESS;

	Calendarbook calendarbook;
	r = calendarbook.Construct();
	TryReturn(!IsFailed(r), r, "[%s] Failed to construct the calendarbook.", GetErrorMessage(r));

	// Sets the subject
	__pProfile->SetSubject(__pSubjectEditField->GetText());

	// Sets the Time zone
	LocaleManager localeManager;
	localeManager.Construct();

	TimeZone timeZone = localeManager.GetSystemTimeZone();

	DateTime startDate;
	DateTime dueDate;

	// Sets the start date
	startDate.SetValue(__pStartEditDate->GetYear(), __pStartEditDate->GetMonth(), __pStartEditDate->GetDay(), __pStartEditTime->GetHour(), __pStartEditTime->GetMinute(), 0);
	r = __pProfile->SetStartDate(timeZone.WallTimeToUtcTime(startDate));
	TryReturn(!IsFailed(r), r, "[%s] Failed to sets the start date.", GetErrorMessage(r));

	// Sets the due date
	dueDate.SetValue(__pDueEditDate->GetYear(), __pDueEditDate->GetMonth(), __pDueEditDate->GetDay(), __pDueEditTime->GetHour(), __pDueEditTime->GetMinute(), 0);
	r = __pProfile->SetDueDate(timeZone.WallTimeToUtcTime(dueDate));
	TryReturn(!IsFailed(r), r, "[%s] Failed to sets the due date.", GetErrorMessage(r));

	// Sets the location
	__pProfile->SetLocation(__pLocationEditField->GetText());

	// Sets the status
	__pProfile->SetStatus(__selectedStatus);

	// Sets the Sensitivity
	__pProfile->SetSensitivity(__selectedSensitivity);

	// Sets the priority
	__pProfile->SetPriority(__selectedPriority);

	// Sets the description
	__pProfile->SetDescription(__pDescriptionEditField->GetText());

	r = calendarbook.UpdateTodo(*__pProfile);
	if (IsFailed(r))
	{
		MessageBox messageBox;
		String getError, getFailUpdate;
		Application::GetInstance()->GetAppResource()->GetString(IDS_ERROR, getError);
		Application::GetInstance()->GetAppResource()->GetString(IDS_FAIL_UPDATE, getFailUpdate);

		messageBox.Construct(getError, getFailUpdate, MSGBOX_STYLE_OK, 0);
		int doModal;
		messageBox.ShowAndWait(doModal);
	}
	TryReturn(!IsFailed(r), r, "[%s] Failed to update Profile.", GetErrorMessage(r));

	return r;
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
