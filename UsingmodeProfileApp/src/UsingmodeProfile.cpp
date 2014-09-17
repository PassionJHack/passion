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

#include "UsingmodeProfile.h"
#include "ProfileFrame.h"
#include "ProfileFormFactory.h"
#include "SceneRegister.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


UsingmodeProfileApp::UsingmodeProfileApp(void)
{
}

UsingmodeProfileApp::~UsingmodeProfileApp(void)
{
}

UiApp*
UsingmodeProfileApp::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new UsingmodeProfileApp();
}

bool
UsingmodeProfileApp::OnAppInitializing(AppRegistry& appRegistry)
{
	return true;
}

bool
UsingmodeProfileApp::OnAppInitialized(void)
{
	result r = E_SUCCESS;

	// Create a Frame
	ProfileFrame* pProfileFrame = new ProfileFrame();
	pProfileFrame->Construct();
	pProfileFrame->SetName(L"UsingmodeProfile");
	AddFrame(*pProfileFrame);

	// SceneManagement initializing
	SceneRegister::RegisterAllScenes();

	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	r = pSceneManager->GoForward(ForwardSceneTransition(SCENE_LIST));
	TryReturn(!IsFailed(r), false, "%s", GetErrorMessage(r));

	return true;
}

bool
UsingmodeProfileApp::OnAppWillTerminate(void)
{
	return true;
}

bool
UsingmodeProfileApp::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}

void
UsingmodeProfileApp::OnForeground(void)
{
}

void
UsingmodeProfileApp::OnBackground(void)
{
}

void
UsingmodeProfileApp::OnLowMemory(void)
{
}

void
UsingmodeProfileApp::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
}

void
UsingmodeProfileApp::OnScreenOn(void)
{
}

void
UsingmodeProfileApp::OnScreenOff(void)
{
}
