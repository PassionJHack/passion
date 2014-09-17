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

#ifndef _CREATE_PROFILE_FORM_H_
#define _CREATE_PROFILE_FORM_H_

#include <FBase.h>
#include <FSocial.h>
#include <FUi.h>

class CreateProfileForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Ui::IDateChangeEventListener
	, public Tizen::Ui::ITimeChangeEventListener
	, public Tizen::Ui::IAdjustmentEventListener
{
public:
	CreateProfileForm();
	virtual ~CreateProfileForm();

	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	virtual void OnDateChanged(const Tizen::Ui::Control& source, int year, int month, int day);
	virtual void OnDateChangeCanceled(const Tizen::Ui::Control& source);

	virtual void OnTimeChanged(const Tizen::Ui::Control& source, int hour, int minute);
	virtual void OnTimeChangeCanceled(const Tizen::Ui::Control& source);
	virtual void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);

private:
//	result CreateProfile(void);
	void CalculateAnchorPosition(Tizen::Ui::Controls::Button* pButton, Tizen::Ui::Controls::ContextMenu* pContextMenu);

private:
	static const int ID_BUTTON_SAVE = 100;

	static const int ID_LOCATION_BUTTON = 200;
	static const int ID_CONTEXT_STATUS_NONE = 500;
	static const int ID_CONTEXT_STATUS_NEEDSACTION = 501;
	static const int ID_CONTEXT_STATUS_COMPLETED = 502;
	static const int ID_CONTEXT_STATUS_INPROCESS = 503;
	static const int ID_CONTEXT_STATUS_CANCELLED = 504;

    static const int ID_BUTTON_CHECKED   = 101;
    static const int ID_BUTTON_UNCHECKED = 102;
    static const int ID_BUTTON_SELECTED  = 103;

	Tizen::Ui::Controls::ScrollPanel* __pScrollPanel;

	Tizen::Ui::Controls::EditDate* __pStartEditDate;
	Tizen::Ui::Controls::EditTime* __pStartEditTime;

	Tizen::Ui::Controls::EditDate* __pDueEditDate;
	Tizen::Ui::Controls::EditTime* __pDueEditTime;

	Tizen::Ui::Controls::EditField* __pSubjectEditField;
	Tizen::Ui::Controls::Button*    __pLocationButton;
	Tizen::Ui::Controls::EditField* __pDescriptionEditField;

	Tizen::Ui::Controls::Slider* __pVolumeSlider;
	Tizen::Ui::Controls::CheckButton* __pWifiCheckButton;
public:
	void SetMap(int x, int y);

};

#endif // _CREATE_PROFILE_FORM_H_
