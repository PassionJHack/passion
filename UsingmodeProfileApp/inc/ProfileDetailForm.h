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

#ifndef _PROFILE_DETAIL_FORM_H_
#define _PROFILE_DETAIL_FORM_H_

#include <FBase.h>
#include <FSocial.h>
#include <FUi.h>

class ProfileDetailForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Ui::Scenes::ISceneEventListener
{

public:
	ProfileDetailForm();
	virtual ~ProfileDetailForm();

	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId);

private:
//	result GetProfile(Tizen::Social::RecordId todoId);
	void DeleteProfile(void);
//	void UpdateProfileView(void);

private:
	static const int ID_FOOTER_EDIT = 100;
	static const int ID_FOOTER_DELETE = 101;
	static const int ID_FOOTER_BACK = 102;
	static const int ID_BUTTON_YES_POPUP = 200;
	static const int ID_BUTTON_CANCEL_POPUP = 201;

	Tizen::Ui::Controls::Label* __pSubjectLabelData;
	Tizen::Ui::Controls::Label* __pStartDateLabelData;
	Tizen::Ui::Controls::Label* __pDueDateLabelData;
	Tizen::Ui::Controls::Label* __pLocationLabelData;

	Tizen::Ui::Controls::Label* __pVolumeLabelData;
	Tizen::Ui::Controls::Label* __pWifiLabelData;
	Tizen::Ui::Controls::Label* __pDescriptionLabelData;

	int __currentID;
};

#endif // _PROFILE_DETAIL_FORM_H_
