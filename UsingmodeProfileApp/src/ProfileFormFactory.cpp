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

#include "ProfileFormFactory.h"
#include "ProfileListForm.h"
#include "CreateProfileForm.h"
#include "ProfileDetailForm.h"
#include "EditProfileForm.h"
#include "LocationMapForm.h"

using namespace Tizen::Ui::Scenes;

// Definitions of extern.
const wchar_t* FORM_LIST = L"ProfileListForm";
const wchar_t* FORM_DETAIL = L"ProfileDetailForm";
const wchar_t* FORM_CREATION = L"CreateProfileForm";
const wchar_t* FORM_EDITION = L"EditProfileForm";
const wchar_t* FORM_LOCATION = L"LocationMapForm";

ProfileFormFactory::ProfileFormFactory(void)
{
}

ProfileFormFactory::~ProfileFormFactory(void)
{
}

Tizen::Ui::Controls::Form*
ProfileFormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == FORM_LIST)
	{
		ProfileListForm* pForm = new (std::nothrow) ProfileListForm();
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == FORM_CREATION)
	{
		CreateProfileForm* pForm = new (std::nothrow) CreateProfileForm();
		pForm->Initialize();
		pNewForm = pForm;
	}
	else if (formId == FORM_DETAIL)
	{
		ProfileDetailForm* pForm = new (std::nothrow) ProfileDetailForm();
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == FORM_EDITION)
	{
		EditProfileForm* pForm = new (std::nothrow) EditProfileForm();
		pForm->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pForm);
		pNewForm = pForm;
	}
	else if (formId == FORM_LOCATION)
	{
		LocationMapForm* pForm = new (std::nothrow) LocationMapForm();
		pForm->Initialize();
		pNewForm = pForm;
	}

	return pNewForm;
}
