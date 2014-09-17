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

#ifndef _EDIT_PROFILE_FORM_H_
#define _EDIT_PROFILE_FORM_H_

#include <FBase.h>
#include <FSocial.h>
#include <FUi.h>

class EditProfileForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Ui::Scenes::ISceneEventListener
	, public Tizen::Ui::IDateChangeEventListener
	, public Tizen::Ui::ITimeChangeEventListener
{

public:
	EditProfileForm();
	virtual ~EditProfileForm();

	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId);

	virtual void OnDateChanged(const Tizen::Ui::Control& source, int year, int month, int day);
	virtual void OnDateChangeCanceled(const Tizen::Ui::Control& source);

	virtual void OnTimeChanged(const Tizen::Ui::Control& source, int hour, int minute);
	virtual void OnTimeChangeCanceled(const Tizen::Ui::Control& source);

private:
	void LoadProfile(void);
	result UpdateProfile(void);
void CalculateAnchorPosition(Tizen::Ui::Controls::Button* pButton, Tizen::Ui::Controls::ContextMenu* pContextMenu);

private:
	static const int ID_BUTTON_SAVE = 100;
	static const int ID_BUTTON_PRIORITY = 200;
	static const int ID_BUTTON_SENSITIVITY = 201;
	static const int ID_BUTTON_STATUS = 202;
	static const int ID_CONTEXT_PRIORITY_HIGH = 300;
	static const int ID_CONTEXT_PRIORITY_NORMAL = 301;
	static const int ID_CONTEXT_PRIORITY_LOW = 302;
	static const int ID_CONTEXT_SENSITIVITY_PUBLIC = 400;
	static const int ID_CONTEXT_SENSITIVITY_PRIVATE = 401;
	static const int ID_CONTEXT_SENSITIVITY_CONFIDENTIAL = 402;
	static const int ID_CONTEXT_STATUS_NONE = 500;
	static const int ID_CONTEXT_STATUS_NEEDSACTION = 501;
	static const int ID_CONTEXT_STATUS_COMPLETED = 502;
	static const int ID_CONTEXT_STATUS_INPROCESS = 503;
	static const int ID_CONTEXT_STATUS_CANCELLED = 504;

	Tizen::Ui::Controls::ScrollPanel* __pScrollPanel;
	Tizen::Ui::Controls::Button* __pPriorityContextButton;
	Tizen::Ui::Controls::Button* __pSensitivityContextButton;
	Tizen::Ui::Controls::Button* __pStatusContextButton;
	Tizen::Ui::Controls::ContextMenu* __pPriorityTextContextMenu;
	Tizen::Ui::Controls::ContextMenu* __pSensitivityTextContextMenu;
	Tizen::Ui::Controls::ContextMenu* __pStatusTextContextMenu;
	Tizen::Ui::Controls::EditDate* __pStartEditDate;
	Tizen::Ui::Controls::EditDate* __pDueEditDate;
	Tizen::Ui::Controls::EditTime* __pStartEditTime;
	Tizen::Ui::Controls::EditTime* __pDueEditTime;
	Tizen::Ui::Controls::EditField* __pSubjectEditField;
	Tizen::Ui::Controls::EditField* __pLocationEditField;
	Tizen::Ui::Controls::EditField* __pDescriptionEditField;
	Tizen::Social::CalTodo* __pProfile;
	Tizen::Social::TodoPriority __selectedPriority;
	Tizen::Social::RecordSensitivity __selectedSensitivity;
	Tizen::Social::TodoStatus __selectedStatus;

};

#endif // _EDIT_PROFILE_FORM_H_
